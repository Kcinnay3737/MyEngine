#pragma once

#include "IServiceProvider.h"

namespace NPEngine
{
	class Actor;

	class IInstanceManager : public IServiceProvider
	{
	public:
		virtual ~IInstanceManager() = default;

		virtual void AddInstance(Actor* ActorInstance) = 0;
		virtual void DeleteInstanceAt(std::string Name, const Param& Params = Param{}) = 0;
		virtual Actor* GetInstanceAt(std::string Name) = 0;
		virtual Actor* GetCopyAt(std::string Name, std::string CopyName) = 0;
		virtual Actor* SpawnCopyInWorldAt(std::string Name, std::string CopyName, const Param& Params = Param{}) = 0;

	private:
		virtual bool Initialize(const Param& Params = Param{}) override = 0;
		virtual void Shutdown(const Param& Params = Param{}) override = 0;
	};
}