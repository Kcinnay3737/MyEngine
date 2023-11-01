#pragma once

#include "World/IWorld.h"
#include "World/Scene/Scene.h"
#include "Object/IObjectManager.h"
#include <typeindex>
#include <typeinfo>

namespace NPEngine
{
	class Object;
	class Actor;

	struct DataActorToAdd
	{
	public:
		Actor* CurrentActor = nullptr;
		std::type_index TypeIndex = std::type_index(typeid(void));
		Param Params = Param{};
	};

	struct DataActorToDelete
	{
	public:
		std::string Name = "";
		Param Params = Param{};
	};

	struct DataLoadScene
	{
	public:
		bool bLoadScene = false;
		std::string SceneName = "";
		Param Params = Param{};
	};

	class World final : public IWorld, public IObjectManager
	{
	private:
		std::unordered_map<size_t, Object*> _IDObject;

		std::vector<std::string> _ActorsToCallBeginPlay;

		std::map<std::string, Actor*> _Actors;
		std::map<std::type_index, std::vector<Actor*>> _ClassActors;

		std::vector<DataActorToAdd> _ActorsToAdd;
		std::vector<DataActorToDelete> _ActorsToDelete;

		std::map<std::string, Scene*> _Scenes;

		DataLoadScene _DataLoadScene = DataLoadScene();

		unsigned char _MaxDrawDepth = 0;
		std::vector<std::vector<Actor*>> _DrawActorOrder;

	public:
		virtual ~World() = default;

		//Scene function
		virtual void LoadScene(std::string& Name, const Param& Params = Param{}) override;
		virtual Scene* CreateScene(std::string& Name, const Param& Params = Param{}) override;
		virtual void DeleteScene(std::string& Name, const Param& Params = Param{}) override;
		//-------------

		//Actor function
		virtual void AddActor(Actor* Actor, const Param& Params = Param{}) override;
		virtual void DeleteActorByName(std::string& Name, const Param& Params = Param{}) override;
		template <typename T>
		T* CreateActorOfClass(std::string& Name, const Param& Params = Param{});
		//-------------
		
		void ResetDrawOrder();

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Shutdown(const Param& Params) override;

		//World function
		virtual void UnloadWorld() override;
		//-------------

		//Scene function
		virtual void UnloadScene() override;
		virtual void OnLoadScene() override;
		//-------------

		//Flow function 
		virtual void StartFrame() override;

		virtual void Update(float DeltaTime) override;
		virtual void PostUpdate() override;

		virtual void Render() override;
		virtual void PostRender() override;

		virtual void EndFrame() override;
		//------------

		//Actor function
		virtual void OnDeleteActor() override;
		virtual void OnCreateActor() override;
		//-------------

		virtual void AddObject(size_t ID, Object* NewObject) override;
		virtual void RemoveId(size_t ID) override;

	public:
		//Getter, Setter
		virtual Object* GetObject(size_t ID) override;

		virtual Scene* GetSceneByName(std::string& Name) override;

		virtual Actor* GetActorByName(std::string& Name) override;
		template <typename T>
		T* GetActorOfClass();
		template <typename T>
		std::vector<T*> GetAllActorOfClass();
	};

	template<typename T>
	inline T* World::CreateActorOfClass(std::string& Name, const Param& Params)
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must be a derived class of Actor");

		T* NewActor = new T(Name);
		if (!NewActor) return nullptr;

		std::type_index TypeIndex(typeid(T));

		DataActorToAdd CurrDataActorToAdd = DataActorToAdd();
		CurrDataActorToAdd.CurrentActor = NewActor;
		CurrDataActorToAdd.TypeIndex = TypeIndex;
		CurrDataActorToAdd.Params = Params;
		_ActorsToAdd.push_back(CurrDataActorToAdd);

		return NewActor;
	}

	template<typename T>
	inline T* World::GetActorOfClass()
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must be a derived class of Actor");

		std::type_index TypeIndex(typeid(T));
		auto& IT = _ClassActors.find(TypeIndex);

		if (IT != _ClassActors.end() && !IT->second.empty())
		{
			T* ActorOfClass = dynamic_cast<T*>(IT->second[0]);
			if (ActorOfClass) return ActorOfClass;
		}

		for (auto& IT : _ClassActors)
		{
			for (Actor* BaseActor : IT->second)
			{
				T* DerivedActor = dynamic_cast<T*>(BaseActor);
				if (DerivedActor) return DerivedActor;
			}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> World::GetAllActorOfClass()
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must be a derived class of Actor");

		std::vector<T*> ActorsOfClass;

		for (auto& IT : _ClassActors)
		{
			for (Actor* BaseActor : IT->second)
			{
				T* DerivedActor = dynamic_cast<T*>(BaseActor);
				if (!DerivedActor) break;
				ActorsOfClass.push_back(DerivedActor);
			}
		}

		return ActorsOfClass;
	}
}