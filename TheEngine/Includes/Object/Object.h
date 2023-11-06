#pragma once

#include <queue>
#include "Utility/Utility.h"

namespace NPEngine
{
	class Object
	{
	private:
		static size_t _CurrentID;
		static std::queue<size_t> _IDFree;

		size_t _ID;

	public:
		Object();
		virtual ~Object();

	private:
		size_t GetNextID();
	};
}