#pragma once

#include "World/InstanceManager/IInstanceManager.h"

namespace NPEngine
{
	class Actor;

	class InstanceManager : public IInstanceManager
	{
	private:
		std::map<std::string, Actor*> _Instances;

	public:
		virtual ~InstanceManager() = default;

		virtual void AddInstance(Actor* ActorInstance) override;
		virtual void DeleteInstanceAt(std::string Name, const Param& Params = Param{}) override;
		virtual Actor* GetInstanceAt(std::string Name) override;
		virtual Actor* GetCopyAt(std::string Name, std::string CopyName) override;
		virtual Actor* SpawnCopyInWorldAt(std::string Name, std::string CopyName, const Param& Params = Param{}) override;

	private:
		virtual bool Initialize(const Param& Params = Param{}) override;
		virtual void Shutdown(const Param& Params = Param{}) override;
	};
}