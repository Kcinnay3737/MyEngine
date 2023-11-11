#pragma once

#include "Object/Actor/Button.h"

using namespace NPEngine;

class ButtonLoadScene : public Button
{
private:
	std::string _LoadSceneName = "";

public:
	ButtonLoadScene(const std::string& Name);
	virtual ~ButtonLoadScene() = default;

	virtual Actor* Clone(std::string& Name, const Param& Params = Param{}) override;

private:
	virtual bool Initialise(const Param& Params) override;
	virtual void Destroy(const Param& Params) override;
	virtual void BeginPlay() override;

	void LoadScene();

public:
	void SetLoadSceneName(const std::string& Name) { _LoadSceneName = Name; }

};