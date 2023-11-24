#pragma once

#include "Object/Actor/Actor.h"
#include "AI/IAIQLearning.h"

namespace NPEngine
{
	class Model;

	class AI : public Actor
	{
	public:

	protected:
		IAIQLearning* _IAQLearning = nullptr;

	public:
		AI(const std::string& Name);
		virtual ~AI() = default;

		virtual Actor* Clone(const std::string& Name, const Param& Params = Param{});

	protected:
		virtual bool Initialise(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;

		virtual void BeginPlay() override;
		virtual void Update(float DeltaTime) override;

		//AI function
		virtual int GetCurrentState();
		virtual void PerformAction(int Action);
		virtual int GetNewState();
		virtual double GetReward();
		//----------

	public:
	};
}