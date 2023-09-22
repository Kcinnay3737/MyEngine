#pragma once

namespace NPEngine
{
	class Object
	{
	private:
		static size_t _CurrentID;

		size_t _ID;

	public:
		Object();
		virtual ~Object();

	private:
		size_t GetNextID();
	};
}