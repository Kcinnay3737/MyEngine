#pragma once

#include "Object/Component/SpriteComponent.h"

namespace NPEngine
{
	class AtlasComponent : public SpriteComponent
	{
	public:
		AtlasComponent(std::string& Name);
		virtual ~AtlasComponent() = default;
	};
}