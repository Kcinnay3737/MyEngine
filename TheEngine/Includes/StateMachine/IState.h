#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	class Object;

	class IState
	{
	public:
		virtual ~IState() = default;

		virtual void OnEnter(Object* Owner) = 0;
		virtual void Execute(Object* Owner) = 0;
		virtual void OnExit(Object* Owner) = 0;
	};
}