#pragma once

#include "World/IWorld.h"
#include "World/Scene.h"
#include <vector>
#include <typeindex>
#include <typeinfo>

namespace NPEngine
{
	class Actor;
	class IScene;

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
		const char* Name = "";
		Param Params = Param{};
	};

	struct DataLoadScene
	{
	public:
		bool bLoadScene = false;
		const char* SceneName = "";
		Param Params = Param{};
	};

	class World final : public IWorld
	{
	private:
		std::vector<const char*> _ActorsToCallBeginPlay;

		std::map<const char*, Actor*> _Actors;
		std::map<std::type_index, std::vector<Actor*>> _ClassActors;

		std::vector<DataActorToAdd> _ActorsToAdd;
		std::vector<DataActorToDelete> _ActorsToDelete;

		std::map<const char*, Scene*> _Scenes;

		DataLoadScene _DataLoadScene = DataLoadScene();

	public:
		virtual ~World() = default;

		//Scene function
		virtual void LoadScene(const char* Name, const Param& Params = Param{}) override;
		virtual Scene* CreateScene(const char* Name, const Param& Params = Param{}) override;
		virtual void DeleteScene(const char* Name, const Param& Params = Param{}) override;
		//-------------

		//Actor function
		virtual void AddActor(Actor* Actor, const Param& Params = Param{}) override;
		virtual void DeleteActorByName(const char* Name, const Param& Params = Param{}) override;
		template <typename T>
		T* CreateActorOfClass(const char* Name, const Param& Params = Param{});
		//-------------

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

	public:
		//Getter, Setter
		virtual Scene* GetSceneByName(const char* Name) override;

		virtual Actor* GetActorByName(const char* Name) override;
		template <typename T>
		T* GetActorOfClass();
		template <typename T>
		std::vector<T*> GetAllActorOfClass();
	};

	template<typename T>
	inline T* World::CreateActorOfClass(const char* Name, const Param& Params)
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
		auto IT = _ClassActors.find(TypeIndex);
		if (IT == _ClassActors.end()) return nullptr;
		if (IT->second.empty()) return nullptr;
		T* ActorOfClass = dynamic_cast<T*>(IT->second[0]);
		if (!ActorOfClass) return nullptr;
		return ActorOfClass;
	}

	template<typename T>
	inline std::vector<T*> World::GetAllActorOfClass()
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must be a derived class of Actor");

		std::type_index TypeIndex(typeid(T));
		auto IT = _ClassActors.find(TypeIndex);
		if (IT == _ClassActors.end()) return std::vector<T*>();
		
		std::vector<T*> ActorsOfClass;
		for (Actor* BaseActor : IT->second) 
		{
			T* DerivedActor = dynamic_cast<T*>(BaseActor);
			if (DerivedActor) 
			{
				ActorsOfClass.push_back(DerivedActor);
			}
		}
		return ActorsOfClass;
	}
}