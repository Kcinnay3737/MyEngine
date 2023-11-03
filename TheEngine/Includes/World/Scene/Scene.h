#pragma once

#include "World/Scene/IScene.h"
#include "Utility/Delegate.h"

namespace NPEngine
{
	class Scene final : public IScene
	{
	public:
		Delegate<void, const Param&> OnLoadScene;

	private:
		std::map<std::string, unsigned int> _PrototypeToSpawn;

	public:
		virtual ~Scene() = default;

	private:
		virtual bool Initialize(const Param& Params) override;
		virtual void Destroy(const Param& Params) override;

		virtual void Load(const Param& Params) override;
	
	public:
		virtual unsigned int GetNumberSpawnPrototype(const char* Name) override;
		virtual void SetNumberSpawnPrototype(const char* Name, unsigned int Number) override;

	};
}