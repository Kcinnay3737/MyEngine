#pragma once

#include "World/ISceneProvider.h"


namespace NPEngine
{
	class IScene : public ISceneProvider
	{
	public:


	public:
		virtual ~IScene() = default;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Destroy(const Param& Params) override = 0;

		virtual void Load(const Param& Params) override = 0;

	public:
		virtual void SetNumberSpawnPrototype(const char* Name, unsigned int Number) = 0;
		virtual int GetNumberSpawnPrototype(const char* Name) = 0;
		
	};
}