#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class Actor;

	struct InstanceActor
	{
		Actor* ActorInstance = nullptr;
		Param InitialiseParams = Param{};
		Param DestroyParams = Param{};
		Param CloneParam = Param{};
	};

	class IInstanceManager : public IServiceProvider
	{
	public:
		virtual ~IInstanceManager() = default;

		virtual void AddInstance(Actor* ActorInstance, const Param& InitialiseParams = Param{}, const Param& DestroyParams = Param{}, const Param& CloneParams = Param{}) = 0;
		virtual void DeleteInstanceAt(std::string Name) = 0;
		virtual InstanceActor& GetInstanceAt(std::string Name) = 0;
		virtual Actor* GetCopyAt(std::string Name, std::string CopyName) = 0;
		virtual Actor* SpawnCopyInWorldAt(std::string Name, std::string CopyName) = 0;

	private:
		virtual bool Initialize(const Param& Params = Param{}) override = 0;
		virtual void Shutdown(const Param& Params = Param{}) override = 0;
	};
}