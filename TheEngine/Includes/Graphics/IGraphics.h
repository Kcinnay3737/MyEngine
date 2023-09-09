#pragma once

namespace NPEngine
{
	class IGraphics
	{
	public:
		virtual ~IGraphics() = default;

	protected:
		friend class Engine;
		virtual bool Init() = 0;
		friend class Enigne;
		virtual bool InitWindow(const char* WindowName, int WindowWidht, int WindowHeight) = 0;
		friend class Engine;
		virtual bool InitRenderer() = 0;

		friend class Engine;
		virtual void Render() = 0;
	};
}