#pragma once

#include "World/IScene.h"
#include "Utility/Delegate.h"

namespace NPEngine
{
	class Scene final : public IScene
	{
	public:
		Delegate OnLoadScene;

	private:
		std::map<const char*, unsigned int> _PrototypeToSpawn;

	public:
		virtual ~Scene() = default;

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;

		virtual void Load(const Param& Params) override;
	
	public:
		virtual int GetNumberSpawnPrototype(const char* Name) override;
		virtual void SetNumberSpawnPrototype(const char* Name, unsigned int Number) override;

	};
}