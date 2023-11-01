#pragma once

namespace NPEngine
{
	class Object;

	class IObjectManager
	{
		friend class Object;
	public:
		virtual Object* GetObject(size_t ID) = 0;

	private:
		virtual void AddObject(size_t ID, Object* NewObject) = 0;
		virtual void RemoveId(size_t ID) = 0;
	};
}