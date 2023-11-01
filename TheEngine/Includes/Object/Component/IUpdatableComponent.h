#pragma once

namespace NPEngine
{
	class IUpdatableComponent
	{
		friend class Actor;
	private:
		virtual void Update(float DeltaTime) = 0;
	};
}