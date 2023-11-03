#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <cstddef>

namespace NPEngine
{
	template<typename ReturnType, typename... Args>
	class Delegate
	{
	private:
		template<typename T>
		size_t GetHash(T* Instance, ReturnType(T::* Method)(Args...))
		{
			std::uintptr_t InstanceIntPtr = reinterpret_cast<std::uintptr_t>(Instance);
			size_t InstanceHash = std::hash<std::uintptr_t>()(InstanceIntPtr);
			
			const auto* MethodPtr = reinterpret_cast<const unsigned char*>(&Method);
			size_t MethodHash = 0;
			for (size_t i = 0; i < sizeof(Method); i++) 
			{
				MethodHash = (MethodHash * 131) + MethodPtr[i];
			}

			return InstanceHash ^ (MethodHash << 1);
		}

		size_t GetHash(ReturnType(*Method)(Args...))
		{
			std::hash<ReturnType(*)(Args...)> Hasher;
			return Hasher(Method);
		}

		std::unordered_map<size_t, std::function<ReturnType(Args...)>> Functions;

	public:
		template<typename T>
		void AddFunction(T* Instance, ReturnType(T::* Method)(Args...)) 
		{
			size_t Key = GetHash<T>(Instance, Method);
			Functions[Key] = [Instance, Method](Args... args) -> ReturnType 
			{
				return (Instance->*Method)(args...);
			};
		}

		void AddFunction(ReturnType(*Function)(Args...)) 
		{
			size_t Key = GetHash(Function);
			Functions[Key] = Function;
		}

		template<typename T>
		void RemoveFunction(T* Instance, ReturnType(T::* Method)(Args...)) 
		{
			size_t Key = GetHash<T>(Instance, Method);
			Functions.erase(Key);
		}

		void RemoveFunction(ReturnType(*Function)(Args...)) 
		{
			size_t Key = GetHash(Function);
			Functions.erase(Key);
		}

		std::vector<ReturnType> BroadcastResult(Args... args)
		{
			std::vector<ReturnType> Results;
			Results.reserve(Functions.size());
			for (auto& [Key, Function] : Functions)
			{
				if (Function != nullptr)
				{
					try
					{
						Results.push_back(Function(args...));
					}
					catch (...)
					{
						
					}
				}
			}
			return Results;
		}

		void Broadcast(Args... args)
		{
			for (auto& [Key, Function] : Functions)
			{
				if (Function != nullptr)
				{
					try
					{
						Function(args...);
					}
					catch (...)
					{

					}
				}
			}
		}
	};
}