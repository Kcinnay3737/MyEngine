#include "AI/AITBQlearning.h"

using namespace NPEngine;

AITBQLearning::AITBQLearning(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon)
{
	_Model = new AIToolbox::MDP::Model(StateSize, ActionSize, DiscountFactor);
	_QLearning = new AIToolbox::MDP::QLearning(StateSize, ActionSize, DiscountFactor, LearningRate);
	_QGreedyPolicy = new AIToolbox::MDP::QGreedyPolicy(_QLearning->getQFunction());
	_EpsilonPolicy = new AIToolbox::MDP::EpsilonPolicy(*_QGreedyPolicy, Epsilon);
	_Epsilon = Epsilon;
}

AITBQLearning::~AITBQLearning()
{
	delete _Model;
	delete _QLearning;
	delete _QGreedyPolicy;
	delete _EpsilonPolicy;
}

void AITBQLearning::Initialize(int StateSize, int ActionSize, double LearningRate, double DiscountFactor, double Epsilon)
{
	delete _Model;
	delete _QLearning;
	delete _QGreedyPolicy;
	delete _EpsilonPolicy;

	_Model = new AIToolbox::MDP::Model(StateSize, ActionSize, DiscountFactor);
	_QLearning = new AIToolbox::MDP::QLearning(StateSize, ActionSize, DiscountFactor, LearningRate);
	_QGreedyPolicy = new AIToolbox::MDP::QGreedyPolicy(_QLearning->getQFunction());
	_EpsilonPolicy = new AIToolbox::MDP::EpsilonPolicy(*_QGreedyPolicy, Epsilon);
	_Epsilon = Epsilon;
}

int AITBQLearning::GetAction(int State) const
{
	return _EpsilonPolicy->sampleAction(State);
}

void AITBQLearning::UpdateQTable(int CurrentState, int Action, double Reward, int NewState)
{
	_QLearning->stepUpdateQ(CurrentState, Action, NewState, Reward);
	_EpsilonPolicy = new AIToolbox::MDP::EpsilonPolicy(*_QGreedyPolicy, _Epsilon);
}

void AITBQLearning::SetLearningRate(double LearningRate)
{
	_QLearning->setLearningRate(LearningRate);
}

double AITBQLearning::GetLearningRate() const
{
	return _QLearning->getLearningRate();
}

void AITBQLearning::SetDiscountFactor(double DiscountFactor)
{
	_Model->setDiscount(DiscountFactor);
	_QLearning->setDiscount(DiscountFactor);
}

double AITBQLearning::GetDiscountFactor() const
{
	return _QLearning->getDiscount();
}