#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include <Windows.h>
#include "Engine.h"
#include "Player/Issac.h"

void Test()
{
	Engine::GetLogger()->LogMessage("Test");
}

void InitGameplay(void)
{
	Engine::GetInput()->OnButtonReleased[EButtonKeys::Mouse_Left].AddFunction(Test);

	Isaac* InstanceIsaac = new Isaac(std::string("Isaac"));
	Engine::GetInstanceManager()->AddInstance(InstanceIsaac);

	Scene* Level1 = Engine::GetWorld()->CreateScene(std::string("Level1"));
	if (Level1)
	{
		Level1->SetNumberSpawnPrototype("Isaac", 1);
	}
	Engine::GetWorld()->LoadScene(std::string("Level1"));
}

INT WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ PSTR, _In_ INT)
{
	NPEngine::Engine TheEngine;
	if (TheEngine.InitEngine("TestGame", 800, 600))
	{
		InitGameplay();
		TheEngine.Start();
	}

	return 0;
}