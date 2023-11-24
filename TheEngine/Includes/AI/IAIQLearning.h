#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	class IAIQLearning
	{
	public:
		virtual ~IAIQLearning() = default;

		// Initialise QLearning parameters
		virtual void Initialize(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon) = 0;

		// Get the best action for a state
		virtual int GetAction(int State) const = 0;

		// Update the QTable with the current state, action, reward, new state
		virtual void UpdateQTable(int CurrentState, int Action, double Reward, int NewState) = 0;

		// Set and get parameters
		virtual void SetLearningRate(double LearningRate) = 0;
		virtual double GetLearningRate() const = 0;
		virtual void SetDiscountFactor(double DiscountFactor) = 0;
		virtual double GetDiscountFactor() const = 0;
	};
}