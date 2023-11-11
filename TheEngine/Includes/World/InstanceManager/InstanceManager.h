#pragma once

#include "World/InstanceManager/IInstanceManager.h"

namespace NPEngine
{
	class Actor;

	class InstanceManager : public IInstanceManager
	{
	private:
		std::map<std::string, InstanceActor> _Instances;

		InstanceActor _BaseInstanceActor = InstanceActor();

	public:
		virtual ~InstanceManager() = default;

		virtual void AddInstance(Actor* ActorInstance, const Param& InitialiseParams = Param{}, const Param& DestroyParams = Param{}, const Param& CloneParams = Param{}) override;
		virtual void DeleteInstanceAt(std::string Name) override;
		virtual InstanceActor& GetInstanceAt(std::string Name) override;
		virtual Actor* GetCopyAt(std::string Name, std::string CopyName) override;
		virtual Actor* SpawnCopyInWorldAt(std::string Name, std::string CopyName) override;

	private:
		virtual bool Initialize(const Param& Params = Param{}) override;
		virtual void Shutdown(const Param& Params = Param{}) override;
	};
}