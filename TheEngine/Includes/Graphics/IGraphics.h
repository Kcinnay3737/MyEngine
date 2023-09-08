#pragma once

namespace NPEngine
{
	class IGraphics
	{
	public:
		virtual ~IGraphics() = default;

	protected:
		friend class Engine;
		virtual bool InitGraphics(void* Window) = 0;
	};
}