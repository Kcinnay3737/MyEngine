#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	struct Delegate
	{
	public:
		using FunctionType = Param(*)(const Param&);

	private:
		std::map<FunctionType, std::function<Param(const Param&)>> Functions;

	public:
		~Delegate()
		{
			Functions.clear();
		}

		void AddFunction(FunctionType FunctionPtr)
		{
			auto IT = Functions.find(FunctionPtr);
			if (IT != Functions.end()) return;

			std::function<Param(const Param&)> Function = FunctionPtr;
			Functions[FunctionPtr] = Function;
		}

		void RemoveFunction(FunctionType FunctionPtr)
		{
			auto IT = Functions.find(FunctionPtr);
			if (IT == Functions.end()) return;

			Functions.erase(IT);
		}

		void Broadcast(const Param& Params = Param{})
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
	};
}