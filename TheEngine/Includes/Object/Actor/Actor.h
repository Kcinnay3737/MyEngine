#pragma once

#include "Object/Object.h"
#include "Object/Actor/IActorWorld.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

namespace NPEngine
{
	class Component;
	class IUpdatableComponent;
	class IDrawableComponent;

	struct DataComponentToAdd
	{
	public:
		Component* CurrentComponent = nullptr;
		std::type_index TypeIndex = std::type_index(typeid(void));
		Param Params = Param{};
	};

	struct DataComponentToDelete
	{
	public:
		std::string ComponentName = "";
		Param Params = Param{};
	};

	class Actor : public Object, public IActorWorld
	{
	private:
		unsigned char _DrawDepth = 0;

		std::string _Name;

	public:
		Actor(std::string& Name);
		virtual ~Actor() = default;

		virtual Actor* Clone(std::string& Name);

		//Component
		void AddComponent(Component* Component, const Param& Params = Param{});
		void DeleteComponentByName(std::string& Name, const Param& Params = Param{});
		template <typename T>
		T* CreateComponentOfClass(std::string& Name, const Param& Params = Param{});
		//---------

	private:
		std::map<std::string, Component*> _Components;
		std::unordered_map<std::type_index, std::vector<Component*>> _ClassComponents;

		std::map<std::string, IUpdatableComponent*> _UpdatableComponent;
		std::map<std::string, IDrawableComponent*> _DrawableComponent;

		std::vector<DataComponentToAdd> _ComponentToAdd;
		std::vector<DataComponentToDelete> _ComponentToDelete;

		virtual bool Initialise(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;

		virtual void BeginPlay() override;
		virtual void Update(float DeltaTime) override;
		virtual void Draw() override;

		virtual void OnCreateComponent() override final;
		virtual void OnDeleteComponent() override final;
		
	public:
		std::string GetName() const { return _Name; }

		virtual void SetDrawDepth(unsigned char DrawDepth) override;
		virtual unsigned char GetDrawDepth() override { return _DrawDepth; }

		//Component
		Component* GetComponentByName(std::string& Name);
		template <typename T>
		T* GetComponentOfClass();
		template <typename T>
		std::vector<T*> GetAllComponentOfClass();
		//---------

	};

	template<typename T>
	inline T* Actor::CreateComponentOfClass(std::string& Name, const Param& Params)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		T* NewComponent = new T(Name);
		if (!NewComponent) return nullptr;

		AddComponent(NewComponent, Params);
		return NewComponent;
	}

	template<typename T>
	inline T* Actor::GetComponentOfClass()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		std::type_index TypeIndex(typeid(T));
		auto& IT = _ClassComponents.find(TypeIndex);

		if (IT != _ClassComponents.end() && !IT->second.empty())
		{
			T* ComponentOfClass = dynamic_cast<T*>(IT->second[0]);
			if (ComponentOfClass) return ComponentOfClass;
		}

		for (auto& IT : _ClassComponents)
		{
			for (Component* BaseComponent : IT.second)
			{
				T* DerivedComponent = dynamic_cast<T*>(BaseComponent);
				if (DerivedComponent) return DerivedComponent;
			}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetAllComponentOfClass()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be a derived class of Component");

		std::vector<T*> ComponentsOfClass;

		for (auto& IT : _ClassComponents)
		{
			for (Component* BaseComponent : IT->second)
			{
				T* DerivedComponent = dynamic_cast<T*>(BaseComponent);
				if (!DerivedComponent) break;
				ComponentsOfClass.push_back(DerivedComponent);
			}
		}

		return ComponentsOfClass;
	}
}