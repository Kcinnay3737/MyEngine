#include "AI/AITBQlearning.h"

using namespace NPEngine;

AITBQLearning::AITBQLearning()
{
	
}

void NPEngine::AITBQLearning::Initialize(int StateSize, int ActionSize, double LearningRate, double DiscountFactor)
{
}

int NPEngine::AITBQLearning::GetAction(int State) const
{
	return 0;
}

void NPEngine::AITBQLearning::UpdateQTable(int CurrentState, int Action, double Reward, int NewState)
{
}

void NPEngine::AITBQLearning::SaveQTable(const std::string& filePath)
{
}

void NPEngine::AITBQLearning::LoadQTable(const std::string& filePath)
{
}
