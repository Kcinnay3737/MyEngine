#pragma once

#include "Object/Object.h"

namespace NPEngine
{
	class Actor : public Object
	{
	private:
		const char* _Name;

	public:
		Actor(const char* Name);
		virtual ~Actor();

		virtual void Start() {};
		virtual void Update(float dt) {};
		virtual void Draw() {};
		virtual void Destroy() {};
		
	public:
		const char* GetName() { return _Name; }

	};
}