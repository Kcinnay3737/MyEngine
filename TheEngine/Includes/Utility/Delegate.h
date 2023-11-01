#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	struct DelegateReturnParams
	{
	public:
		using FunctionType = Param(*)(const Param&);

	private:
		std::map<FunctionType, std::function<Param(const Param&)>> Functions;

	public:
		~DelegateReturnParams();

		void AddFunction(FunctionType FunctionPtr);

		void RemoveFunction(FunctionType FunctionPtr);

		std::vector<Param> Broadcast(const Param& Params = Param{});
	};

	struct DelegateReturn
	{
	public:
		using FunctionType = Param(*)(void);

	private:
		std::map<FunctionType, std::function<Param(void)>> Functions;

	public:
		~DelegateReturn();

		void AddFunction(FunctionType FunctionPtr);

		void RemoveFunction(FunctionType FunctionPtr);

		std::vector<Param> Broadcast(void);
	};

	struct DelegateParams
	{
	public:
		using FunctionType = void(*)(const Param&);

	private:
		std::map<FunctionType, std::function<void(const Param&)>> Functions;

	public:
		~DelegateParams();

		void AddFunction(FunctionType FunctionPtr);

		void RemoveFunction(FunctionType FunctionPtr);

		void Broadcast(const Param& Params = Param{});
	};

	struct Delegate
	{
	public:
		using FunctionType = void(*)(void);

	private:
		std::map<FunctionType, std::function<void(void)>> Functions;

	public:
		~Delegate();

		void AddFunction(FunctionType FunctionPtr);

		void RemoveFunction(FunctionType FunctionPtr);

		void Broadcast(void);
	};
}