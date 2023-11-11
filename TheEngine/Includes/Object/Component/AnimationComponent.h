#pragma once

#include "Object/Component/AtlasComponent.h"

namespace NPEngine
{
	struct AnimationData
	{
		float FrameInterval = 0.0f;
		int StartIndex = 0;
		int EndIndex = 0;

		Flip AnimationFlip = Flip();
	};

	class AnimationComponent : public AtlasComponent, public IUpdatableComponent
	{
	private:
		AnimationData& _CurrentAnimation = AnimationData();

		AnimationData _BaseAnimationData = AnimationData();

		std::map<std::string, AnimationData> _Animations;

		float _CurrentFrameTime = 0.0f;

	public:
		AnimationComponent(std::string& Name);
		virtual ~AnimationComponent() = default;

		void AddAnimation(const std::string& AnimationName, const AnimationData& NewAnimationData);
		void RemoveAnimation(const std::string& AnimationName);

		AnimationData& GetAnimationData(const std::string& AnimationName);

		void SetCurrentAnimation(const std::string AnimationName);

	private:
		void Update(float DeltaTime) override;

	};
}