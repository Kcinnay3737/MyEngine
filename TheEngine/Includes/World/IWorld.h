#pragma once

#include "World/IWorldProvider.h"

namespace NPEngine
{
	class IScene;
	class Actor;

	class IWorld : public IWorldProvider
	{
	public:
		virtual ~IWorld() = default;

		virtual void LoadScene(const char* Name, const Param& Params = Param{}) = 0;
		virtual IScene* CreateScene(const char* Name, const Param& Params = Param{}) = 0;
		virtual void DeleteScene(const char* Name, const Param& Params = Param{}) = 0;

		virtual void AddActor(Actor* Actor, const Param& Params = Param{}) = 0;
		virtual void DeleteActorByName(const char* Name, const Param& Params = Param{}) = 0;
		virtual Actor* GetActorByName(const char* Name) = 0;

	private:
		virtual bool Initialize(const Param& Params) override = 0;
		virtual void Shutdown(const Param& Params) override = 0;

		virtual void UnloadWorld() = 0;

		virtual void UnloadScene() = 0;
		virtual void OnLoadScene() = 0;

		virtual void StartFrame() override = 0;

		virtual void Update(float DeltaTime) override = 0;
		virtual void PostUpdate() override = 0;

		virtual void Render() override = 0;
		virtual void PostRender() override = 0;

		virtual void EndFrame() override = 0;

		virtual void OnDeleteActor() = 0;
		virtual void OnCreateActor() = 0;

	public:
		virtual IScene* GetSceneByName(const char* Name) = 0;
	};
}