#pragma once

namespace NPEngine
{
	class IDrawableComponent
	{
		friend class Actor;
	private:
		virtual void Draw() = 0;
	};
}