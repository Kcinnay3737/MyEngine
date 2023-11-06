#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class Actor;

	class IPhysicsProvider : public IServiceProvider
	{
		friend class PhysicsComponent;
		friend class Engine;
	public:
		virtual ~IPhysicsProvider() = default;

	private:
		virtual bool Initialize(const Param& Params = Param{}) override = 0;
		virtual void Shutdown(const Param& Params = Param{}) override = 0;

		virtual void UpdatePhysics(float DeltaTime) = 0;

		virtual void AddPhysicsActor(const Actor* ActorToAdd) = 0;
		virtual void RemovePhysicsActor(const std::string& Name) = 0;

		virtual void OnPhysicsComponentStateChanged(const std::string& Name) = 0;
	};
}