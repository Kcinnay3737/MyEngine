#include "World/Scene.h"
#include "Engine.h"

using namespace NPEngine;

bool Scene::Initialize(const Param& Params)
{
	return true;
}

void Scene::Destroy(const Param& Params)
{
	_PrototypeToSpawn.clear();
}

void Scene::Load(const Param& Params)
{
	OnLoadScene.Broadcast(Params);
}

void Scene::SetNumberSpawnPrototype(const char* Name, unsigned int Number)
{
	_PrototypeToSpawn[Name] = Number;
}

int Scene::GetNumberSpawnPrototype(const char* Name)
{
	auto IT = _PrototypeToSpawn.find(Name);
	if (IT == _PrototypeToSpawn.end()) return 0;
	return IT->second;
}