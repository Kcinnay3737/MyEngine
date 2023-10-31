#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include <Windows.h>
#include "Engine.h"
#include "Player/Issac.h"

using namespace NPEngine;

Param Test(const Param& yo)
{
	Engine::GetLogger()->LogMessage("Test");
	Engine::GetWorld()->CreateActorOfClass<Isaac>("Issac");
	return Param{};
}

void InitGameplay(void)
{
	Scene* Level1 = Engine::GetWorld()->CreateScene("Level1");
	if (Level1)
	{
		Level1->OnLoadScene.AddFunction(Test);
	}
	Engine::GetWorld()->LoadScene("Level1", Param{ {"Bob", 6}});
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