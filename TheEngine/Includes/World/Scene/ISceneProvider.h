#pragma once

#include "Utility/Utility.h"

namespace NPEngine
{
	class ISceneProvider
	{
		friend class World;
	public:
		virtual ~ISceneProvider() = default;

	private:
		virtual bool Initialize(const Param& Params = Param{}) = 0;
		virtual void Destroy(const Param& Params = Param{}) = 0;

		virtual void Load(const Param& Params = Param{}) = 0;
		
	};
}