#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include <Windows.h>
#include "Engine.h"
#include "Player/Issac.h"

using namespace NPEngine;

void InitGameplay(void)
{
	Isaac* NewIsaac = new Isaac(std::string("Isaac"));

	Engine::GetInstanceManager()->AddInstance(NewIsaac);

	Scene* SceneMenu = Engine::GetWorld()->CreateScene(std::string("SceneMenu"));
	if (SceneMenu)
	{
		SceneMenu->SetNumberSpawnPrototype("Isaac", 1);
	}

	Scene* SceneGame1 = Engine::GetWorld()->CreateScene(std::string("SceneGame1"));
	if (SceneGame1)
	{
		//Level1->SetNumberSpawnPrototype("Isaac", 1);
	}

	Engine::GetWorld()->LoadScene(std::string("SceneMenu"));
}

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT)
{
	Engine TheEngine;
	if (TheEngine.InitEngine("TestGame", 1200, 800))
	{
		InitGameplay();
		TheEngine.Start();
	}

	return 0;
}