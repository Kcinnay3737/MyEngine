#include "World/InstanceManager/InstanceManager.h"
#include "Object/Actor/Actor.h"
#include "Engine.h"

using namespace NPEngine;

bool InstanceManager::Initialize(const Param& Params)
{
    return true;
}

void InstanceManager::Shutdown(const Param& Params)
{
	for (auto& IT : _Instances)
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
	_Instances.clear();
}

void InstanceManager::AddInstance(Actor* ActorInstance)
{
	if (!ActorInstance) return;

	const std::string& InstanceName = ActorInstance->GetName();

	auto IT = _Instances.find(InstanceName);
	if (IT != _Instances.end())
	{
		Engine::GetLogger()->LogMessage("An instance already has this name");
		return;
	}

	_Instances[InstanceName] = ActorInstance;
}

void InstanceManager::DeleteInstanceAt(std::string Name, const Param& Params)
{
	auto IT = _Instances.find(Name);
	if (IT == _Instances.end()) return;

	Actor* CurrActor = IT->second;

	_Instances.erase(IT);

	if (!CurrActor) return;

	IActorWorld* ActorWorld = static_cast<IActorWorld*>(CurrActor);
	if (ActorWorld)
	{
		ActorWorld->Destroy(Params);
	}

	delete CurrActor;
}

Actor* InstanceManager::GetInstanceAt(std::string Name)
{
	auto IT = _Instances.find(Name);
	if (IT == _Instances.end()) return nullptr;
	return IT->second;
}

Actor* InstanceManager::GetCopyAt(std::string Name, std::string CopyName)
{
	auto IT = _Instances.find(Name);
	if (IT == _Instances.end()) return nullptr;

	Actor* Instance = IT->second;
	Actor* CopyInstance = Instance->Clone(CopyName);
	return CopyInstance;
}

Actor* InstanceManager::SpawnCopyInWorldAt(std::string Name, std::string CopyName, const Param& Params)
{
	auto IT = _Instances.find(Name);
	if (IT == _Instances.end()) return nullptr;

	Actor* Instance = IT->second;
	Actor* CopyInstance = Instance->Clone(CopyName);

	Engine::GetWorld()->AddActor(CopyInstance, Params);

	return CopyInstance;
}
