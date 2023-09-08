#pragma once

namespace NPEngine
{
	class IWindow
	{
	public:
		virtual ~IWindow() = default;

	protected:
		friend class Engine;
		virtual bool InitWindow(const char* WindowName, int WindowWidht, int WindowHeight) = 0;
	};
}