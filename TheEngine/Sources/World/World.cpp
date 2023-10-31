#include "World/World.h"
#include "Object/Actor.h"
#include "Engine.h"

using namespace NPEngine;

bool World::Initialize(const Param& Params)
{
	return true;
}

void World::Shutdown(const Param& Params)
{
	UnloadWorld();
}

//Flow function ---------------------------------------------

void World::StartFrame()
{
	//Check for load new scene
	if (_DataLoadScene.bLoadScene)
	{
		OnLoadScene();
	}

	//Check for add new actor
	if (!_ActorsToAdd.empty())
	{
		OnCreateActor();
		_ActorsToAdd.clear();
	}

	//Begin play
	if (!_ActorsToCallBeginPlay.empty())
	{
		for (const char* Name : _ActorsToCallBeginPlay)
		{
			Actor* CurrActor = GetActorByName(Name);
			if (!CurrActor) continue;

			IActorWorld* ActorWorld = static_cast<IActorWorld*>(CurrActor);
			if (ActorWorld)
			{
				ActorWorld->BeginPlay();
			}
		}
	}
}

void World::Update(float DeltaTime)
{
	for (auto& Value : _Actors)
	{
		Actor* CurrActor = Value.second;
		if (!CurrActor) continue;

		IActorWorld* ActorWorld = static_cast<IActorWorld*>(CurrActor);
		if (ActorWorld)
		{
			ActorWorld->Update(DeltaTime);
		}
	}
}

void World::PostUpdate()
{
}

void World::Render()
{
	for (auto& Value : _Actors)
	{
		Actor* CurrActor = Value.second;
		if (!CurrActor) continue;

		IActorWorld* ActorWorld = static_cast<IActorWorld*>(CurrActor);
		if (ActorWorld)
		{
			ActorWorld->Draw();
		}
	}
}

void World::PostRender()
{
}

void World::EndFrame()
{
	//Check for delete actor
	if (!_ActorsToDelete.empty())
	{
		OnDeleteActor();
		_ActorsToDelete.clear();
	}
}

//-----------------------------------------------------------

//Actor function --------------------------------------------

void World::AddActor(Actor* Actor, const Param& Params)
{
	if (!Actor) return;

	std::type_index TypeIndex(typeid(*Actor));

	DataActorToAdd CurrDataActorToAdd = DataActorToAdd();
	CurrDataActorToAdd.CurrentActor = Actor;
	CurrDataActorToAdd.TypeIndex = TypeIndex;
	CurrDataActorToAdd.Params = Params;
	_ActorsToAdd.push_back(CurrDataActorToAdd);
}

void World::OnDeleteActor()
{
	for (DataActorToDelete& DataActor : _ActorsToDelete)
	{
		auto ActorIT = _Actors.find(DataActor.Name);
		if (ActorIT == _Actors.end()) continue;

		Actor* ActorToRemove = ActorIT->second;

		std::type_index TypeIndex(typeid(*(ActorToRemove)));
		auto ClassActorsIT = _ClassActors.find(TypeIndex);
		if (ClassActorsIT != _ClassActors.end())
		{
			std::vector<Actor*>& ActorVector = ClassActorsIT->second;
			auto NewEnd = std::remove(ActorVector.begin(), ActorVector.end(), ActorToRemove);
			ActorVector.erase(NewEnd, ActorVector.end());
		}

		_Actors.erase(ActorIT);

		IActorWorld* ActorWorld = static_cast<IActorWorld*>(ActorToRemove);
		if (ActorWorld)
		{
			ActorWorld->Destroy(DataActor.Params);
		}

		delete ActorToRemove;
	}
}

void World::OnCreateActor()
{
	for (DataActorToAdd& DataActor : _ActorsToAdd)
	{
		Actor* NewActor = DataActor.CurrentActor;

		//Check if actor is valid
		if (!NewActor) continue;

		const char* NewActorName = NewActor->GetName();
		IActorWorld* ActorWorld = static_cast<IActorWorld*>(NewActor);

		//Check if an actor already has this name
		Actor* CheckActor = GetActorByName(NewActorName);
		if (CheckActor)
		{
			Engine::GetLogger()->LogMessage("An actor already has this name");
			if (ActorWorld)
			{
				ActorWorld->Destroy();
			}
			delete NewActor;
			continue;
		}

		if (ActorWorld)
		{
			if (!ActorWorld->Initialise(DataActor.Params))
			{
				Engine::GetLogger()->LogMessage("Initialise failed");
				ActorWorld->Destroy();
				delete NewActor;
				continue;
			}
		}

		_Actors[NewActorName] = NewActor;
		_ClassActors[DataActor.TypeIndex].push_back(NewActor);
		_ActorsToCallBeginPlay.push_back(NewActorName);
	}
}

void World::DeleteActorByName(const char* Name, const Param& Params)
{
	DataActorToDelete DataActor = DataActorToDelete();
	DataActor.Name = Name;
	DataActor.Params = Params;
	_ActorsToDelete.push_back(DataActor);
}

//-----------------------------------------------------------

//World function --------------------------------------------

void World::UnloadWorld()
{
	UnloadScene();

	for (auto IT : _Scenes)
	{
		IScene* Scene = IT.second;
		if (!Scene) continue;

		ISceneProvider* SceneProvider = static_cast<ISceneProvider*>(Scene);
		if (SceneProvider)
		{
			SceneProvider->Destroy();
		}

		delete Scene;
	}
	_Scenes.clear();
}

//-----------------------------------------------------------

//Scene function --------------------------------------------

void World::LoadScene(const char* Name, const Param& Params)
{
	_DataLoadScene.bLoadScene = true;
	_DataLoadScene.SceneName = Name;
	_DataLoadScene.Params = Params;
}

void World::UnloadScene()
{
	//Clear actor to call begin play
	_ActorsToCallBeginPlay.clear();

	//Clear class actor list
	_ClassActors.clear();

	//Clear actor to delete list
	_ActorsToDelete.clear();

	//Reset load scene data
	_DataLoadScene.bLoadScene = false;
	_DataLoadScene.SceneName = "";
	_DataLoadScene.Params.clear();

	//Delete all new actor to add and clear list
	for (DataActorToAdd& DataActor : _ActorsToAdd)
	{
		Actor* CurrActor = DataActor.CurrentActor;
		if (!CurrActor) continue;
		
		IActorWorld* ActorWorld = static_cast<IActorWorld*>(CurrActor);
		if (ActorWorld)
		{
			ActorWorld->Destroy();
		}

		delete CurrActor;
	}
	_ActorsToAdd.clear();

	//Delete all actors
	for (auto IT : _Actors)
	{
		Actor* CurrActor = IT.second;
		if (!CurrActor) continue;

		IActorWorld* ActorWorld = static_cast<IActorWorld*>(CurrActor);
		if (ActorWorld)
		{
			ActorWorld->Destroy();
		}
		
		delete CurrActor;
	}
	_Actors.clear();
}

void World::OnLoadScene()
{
	IScene* Scene = GetSceneByName(_DataLoadScene.SceneName);
	if (!Scene)
	{
		Engine::GetLogger()->LogMessage("No scene matches the name for load");
		return;
	}
	ISceneProvider* SceneProvider = static_cast<ISceneProvider*>(Scene);
	if (!SceneProvider)
	{
		Engine::GetLogger()->LogMessage("The scene provider is not valid for load");
		return;
	}
	
	Param Params = _DataLoadScene.Params;
	UnloadScene();
	SceneProvider->Load(Params);
}

Scene* World::CreateScene(const char* Name, const Param& Params)
{
	Scene* CheckScene = GetSceneByName(Name);
	if (CheckScene)
	{
		Engine::GetLogger()->LogMessage("A scene already has this name");
		return nullptr;
	}

	Scene* NewScene = new Scene();
	
	ISceneProvider* SceneProvider = static_cast<ISceneProvider*>(NewScene);
	if (SceneProvider)
	{
		if (!SceneProvider->Initialize(Params))
		{
			Engine::GetLogger()->LogMessage("Failed to initialize scene");
			SceneProvider->Destroy();
			delete NewScene;
			return nullptr;
		}
	}

	_Scenes[Name] = NewScene;

	return NewScene;
}

void World::DeleteScene(const char* Name, const Param& Params)
{
	auto IT = _Scenes.find(Name);
	if (IT == _Scenes.end())
	{
		Engine::GetLogger()->LogMessage("No scene matches the name for delete");
		return;
	}
	ISceneProvider* SceneProvider = static_cast<ISceneProvider*>(IT->second);
	if (SceneProvider)
	{
		SceneProvider->Destroy(Params);
	}
	
	delete IT->second;
	_Scenes.erase(IT);
}

//----------------------------------------------------------

//Getter, Setter -------------------------------------------

Actor* World::GetActorByName(const char* Name)
{
	auto IT = _Actors.find(Name);
	if (IT == _Actors.end()) return nullptr;
	return IT->second;
}

Scene* World::GetSceneByName(const char* Name)
{
	auto IT = _Scenes.find(Name);
	if (IT == _Scenes.end()) return nullptr;
	return IT->second;
}