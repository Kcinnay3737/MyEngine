#include "Utility/Delegate.h"

using namespace NPEngine;

//Delegate Return params --------------------------------------------------------

DelegateReturnParams::~DelegateReturnParams()
{
	Functions.clear();
}

void DelegateReturnParams::AddFunction(FunctionType FunctionPtr)
{
	auto IT = Functions.find(FunctionPtr);
	if (IT != Functions.end()) return;

	std::function<Param(const Param&)> Function = FunctionPtr;
	Functions[FunctionPtr] = Function;
}

void DelegateReturnParams::RemoveFunction(FunctionType FunctionPtr)
{
	auto IT = Functions.find(FunctionPtr);
	if (IT == Functions.end()) return;

	Functions.erase(IT);
}

std::vector<Param> DelegateReturnParams::Broadcast(const Param& Params)
{
	std::vector<Param> ReturnParams;

	for (auto& IT : Functions)
	{
		if (!IT.first) continue;

		try
		{
			ReturnParams.push_back(IT.second(Params));
		}
		catch (...)
		{

		}
	}

	return ReturnParams;
}

//-------------------------------------------------------------------------------

//Delegate Return ---------------------------------------------------------------

DelegateReturn::~DelegateReturn()
{
	Functions.clear();
}

void DelegateReturn::AddFunction(FunctionType FunctionPtr)
{
	auto IT = Functions.find(FunctionPtr);
	if (IT != Functions.end()) return;

	std::function<Param(void)> Function = FunctionPtr;
	Functions[FunctionPtr] = Function;
}

void DelegateReturn::RemoveFunction(FunctionType FunctionPtr)
{
	auto IT = Functions.find(FunctionPtr);
	if (IT == Functions.end()) return;

	Functions.erase(IT);
}

std::vector<Param> NPEngine::DelegateReturn::Broadcast(void)
{
	std::vector<Param> ReturnParams;

	for (auto& IT : Functions)
	{
		if (!IT.first) continue;

		try
		{
			ReturnParams.push_back(IT.second());
		}
		catch (...)
		{

		}
	}

	return ReturnParams;
}

//------------------------------------------------------------------------------

//Delegate Params --------------------------------------------------------------

DelegateParams::~DelegateParams()
{
	Functions.clear();
}

void DelegateParams::AddFunction(FunctionType FunctionPtr)
{
	auto IT = Functions.find(FunctionPtr);
	if (IT != Functions.end()) return;

	std::function<void(const Param&)> Function = FunctionPtr;
	Functions[FunctionPtr] = Function;
}

void DelegateParams::RemoveFunction(FunctionType FunctionPtr)
{
	auto IT = Functions.find(FunctionPtr);
	if (IT == Functions.end()) return;

	Functions.erase(IT);
}

void DelegateParams::Broadcast(const Param& Params)
{
	for (auto& IT : Functions)
	{
		if (!IT.first) continue;

		try
		{
			IT.second(Params);
		}
		catch (...)
		{

		}
	}
}

//------------------------------------------------------------------------------

//Delegate ---------------------------------------------------------------------

Delegate::~Delegate()
{
	Functions.clear();
}

void Delegate::AddFunction(FunctionType FunctionPtr)
{
	auto IT = Functions.find(FunctionPtr);
	if (IT != Functions.end()) return;

	std::function<void(void)> Function = FunctionPtr;
	Functions[FunctionPtr] = Function;
}

void Delegate::RemoveFunction(FunctionType FunctionPtr)
{
	auto IT = Functions.find(FunctionPtr);
	if (IT == Functions.end()) return;

	Functions.erase(IT);
}

void Delegate::Broadcast(void)
{
	for (auto& IT : Functions)
	{
		if (!IT.first) continue;

		try
		{
			IT.second();
		}
		catch (...)
		{

		}
	}
}

//------------------------------------------------------------------------------