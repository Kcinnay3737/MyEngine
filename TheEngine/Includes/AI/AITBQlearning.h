#pragma once

#include "AI/IAIQLearning.h"
#include "Utility/Utility.h"

#include <AIToolbox/MDP/Algorithms/QLearning.hpp>
#include <AIToolbox/MDP/Model.hpp>

namespace NPEngine
{
	class AITBQLearning : public IAIQLearning
	{
	private:
		AIToolbox::MDP::Model _Model = AIToolbox::MDP::Model(0, 0);
		AIToolbox::MDP::QLearning _QLearning = AIToolbox::MDP::QLearning(0, 0);

	public:
		AITBQLearning();
		virtual ~AITBQLearning() = default;

	};
}