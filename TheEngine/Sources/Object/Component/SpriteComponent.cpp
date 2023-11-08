#include "Object/Component/SpriteComponent.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Actor/Actor.h"
#include "Engine.h"

using namespace NPEngine;

SpriteComponent::SpriteComponent(std::string& Name) : Component(Name)
{
}

void SpriteComponent::Draw()
{
	TransformComponent* CurrTransformComponent = GetOwner()->GetComponentOfClass<TransformComponent>();
	
	Rectangle2D<float> DrawRect = Rectangle2D<float>(Vector2D<float>(0.0f, 0.0f), Vector2D<float>(0.0f, 0.0f));

	if (CurrTransformComponent)
	{
		DrawRect.Position = CurrTransformComponent->GetPosition();
		DrawRect.Size = CurrTransformComponent->GetSize();
	}

	DrawRect.Position += _OffsetPosition;
	DrawRect.Size += _OffsetSize;

	Engine::GetGraphics()->DrawRect(DrawRect, Color::Blue, true);
}
