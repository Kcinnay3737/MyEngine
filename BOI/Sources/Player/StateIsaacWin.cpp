#include "Player/StateIsaacWin.h"
#include "Engine.h"

StateIsaacWin::StateIsaacWin()
{
}

void StateIsaacWin::OnEnter(Object* Owner)
{
}

void StateIsaacWin::Execute(float DeltaTime, Object* Owner)
{
	_CurrentDelayRestart += DeltaTime;
	if (_CurrentDelayRestart >= _DelayRestart)
	{
		Engine::GetWorld()->LoadScene("SceneMenu");
	}
}

void StateIsaacWin::OnExit(Object* Owner)
{
}

void StateIsaacWin::OnCollision(const std::vector<CollisionData>& CollisionsData)
{
}
