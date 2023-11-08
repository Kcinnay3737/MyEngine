#pragma once

#include "Object/Component/AtlasComponent.h"

namespace NPEngine
{
	class AnimationComponent : public AtlasComponent
	{
	public:
		AnimationComponent(std::string& Name);
		virtual ~AnimationComponent() = default;
	};
}