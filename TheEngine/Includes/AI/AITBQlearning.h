#pragma once

#include "AI/IAIQLearning.h"
#include "Utility/Utility.h"

#include <AIToolbox/MDP/Algorithms/QLearning.hpp>
#include <AIToolbox/MDP/Model.hpp>
#include <AIToolbox/MDP/Policies/EpsilonPolicy.hpp>
#include <AIToolbox/MDP/Policies/QGreedyPolicy.hpp>
#include <AIToolbox/Seeder.hpp>
#include <fstream>
#include <random>

namespace NPEngine
{
	class AITBQLearning : public IAIQLearning
	{
	private:
		AIToolbox::MDP::Model* _Model = nullptr;
		AIToolbox::MDP::QLearning* _QLearning = nullptr;
		AIToolbox::MDP::QGreedyPolicy* _QGreedyPolicy = nullptr;
		mutable AIToolbox::MDP::EpsilonPolicy* _EpsilonPolicy = nullptr;
		double _Epsilon = 0.0;

	public:
		AITBQLearning(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon);
		virtual ~AITBQLearning();

		//IAIQLearning interface
		virtual void Initialize(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon) override;

		virtual int GetAction(int State) const override;

		virtual void UpdateQTable(int CurrentState, int Action, double Reward, int NewState) override;

		virtual void SetLearningRate(double LearningRate) override;
		virtual double GetLearningRate() const override;
		virtual void SetDiscountFactor(double DiscountFactor) override;
		virtual double GetDiscountFactor() const override;
		//---------------------
	};
}