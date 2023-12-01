#pragma once

#include "Object/Component/AtlasComponent.h"

namespace NPEngine
{
	//Structure for switch animation
	struct AnimationSwitch
	{
	public:
		bool bSwitchAnimation = false;
		std::string SwitchAnimationName = "";
		int SwitchIndex = 0;
	};

	struct AnimationData
	{
		friend class AnimationComponent;
	public:
		float FrameInterval = 0.0f;
		int StartIndex = 0;
		int EndIndex = 0;
		bool bLoop = true;

		AnimationSwitch SwitchAnimationData = AnimationSwitch();

		Flip AnimationFlip = Flip();

		Delegate<void, int, const std::string&> AnimationObserver = Delegate<void, int, const std::string&>();

		void AddFrameToCallObserver(int Frame);
		void RemoveFrameToCallObserver(int Frame);
		void ClearAllFrameToCallObserver();

	private:
		std::unordered_map<int, bool> FrameToCallObserver;
		std::string AnimationName = "";
	};

	class AnimationComponent : public AtlasComponent, public IUpdatableComponent
	{
	private:
		AnimationData _BaseAnimationData = AnimationData();

		AnimationData& _CurrentAnimation = _BaseAnimationData;

		std::map<std::string, AnimationData> _Animations;

		float _CurrentFrameTime = 0.0f;

	public:
		AnimationComponent(const std::string& Name);
		virtual ~AnimationComponent() = default;

		void AddAnimation(const std::string& AnimationName, AnimationData& NewAnimationData);
		void RemoveAnimation(const std::string& AnimationName);

		AnimationData& GetAnimationData(const std::string& AnimationName);

		void SetCurrentAnimation(const std::string AnimationName);

	private:
		void Update(float DeltaTime) override;

	};
}