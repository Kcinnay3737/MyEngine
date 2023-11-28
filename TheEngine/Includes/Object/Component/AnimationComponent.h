#pragma once

#include "Object/Component/AtlasComponent.h"

namespace NPEngine
{
	struct AnimationData
	{
		float FrameInterval = 0.0f;
		int StartIndex = 0;
		int EndIndex = 0;
		bool bLoop = true;

		Flip AnimationFlip = Flip();
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

		void AddAnimation(const std::string& AnimationName, const AnimationData& NewAnimationData);
		void RemoveAnimation(const std::string& AnimationName);

		AnimationData& GetAnimationData(const std::string& AnimationName);

		void SetCurrentAnimation(const std::string AnimationName);

	private:
		void Update(float DeltaTime) override;

	};
}