#include "Object/Component/AnimationComponent.h"

using namespace NPEngine;

AnimationComponent::AnimationComponent(std::string& Name) : AtlasComponent(Name)
{
}

void AnimationComponent::AddAnimation(const std::string& AnimationName, const AnimationData& NewAnimationData)
{
	_Animations[AnimationName] = NewAnimationData;
}

void AnimationComponent::RemoveAnimation(const std::string& AnimationName)
{
	_Animations.erase(AnimationName);
}

AnimationData& AnimationComponent::GetAnimationData(const std::string& AnimationName)
{
	auto& IT = _Animations.find(AnimationName);
	if (IT == _Animations.end()) return _BaseAnimationData;
	return IT->second;
}

void AnimationComponent::SetCurrentAnimation(const std::string AnimationName)
{
	auto& IT = _Animations.find(AnimationName);
	if (IT == _Animations.end()) return;

	_CurrentAnimation = IT->second;
	_CurrentFrameTime = 0.0f;
	SetTileIndex(_CurrentAnimation.StartIndex);
	SetFlip(_CurrentAnimation.AnimationFlip);
}

void AnimationComponent::Update(float DeltaTime)
{
	_CurrentFrameTime += DeltaTime;

	if (_CurrentFrameTime >= _CurrentAnimation.FrameInterval)
	{
		_CurrentFrameTime = 0.0f;
		
		if (GetTileIndex() >= _CurrentAnimation.EndIndex)
		{
			SetTileIndex(_CurrentAnimation.StartIndex);
		}
		else
		{
			SetTileIndex(GetTileIndex() + 1);
		}
	}
}