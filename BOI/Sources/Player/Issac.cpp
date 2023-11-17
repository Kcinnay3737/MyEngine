#include "Player/Issac.h"
#include "Engine.h"
#include "Object/Component/ControllerComponent.h"
#include "Object/Component/TransformComponent.h"
#include "Object/Actor/Projectil.h"
#include <typeindex>
#include <typeinfo>

Isaac::Isaac(const std::string& Name) : Actor(Name)
{

}

bool Isaac::Initialise(const Param& Params)
{
	Actor::Initialise(Params);

	CreateComponentOfClass<PhysicsComponent>(std::string("PhysicsComponent"), Params);
	CreateComponentOfClass<ControllerComponent>(std::string("ControllerComponent"), Params);
	CreateComponentOfClass<AtlasComponent>(std::string("AtlasComponent"), Params);
	CreateComponentOfClass<AnimationComponent>(std::string("AnimationComponent"), Params);

	return true;
}

void Isaac::BeginPlay()
{
	Actor::BeginPlay();

	_PhysicsComponent = GetComponentOfClass<PhysicsComponent>();
	if (_PhysicsComponent)
	{
		_PhysicsComponent->SetCollision(ECollisionType::Box);
		//_PhysicsComponent->SetDrawCollision(true);
		_PhysicsComponent->SetMaxVelocityMagnetude(200.0f);
		_PhysicsComponent->AddIgnoreActorClass<Projectil>();
	}

	ControllerComponent* CurrControllerComponent = GetComponentOfClass<ControllerComponent>();
	if (CurrControllerComponent)
	{
		CurrControllerComponent->SetMoveSpeed(200.0f);
	}

	_AtlasComponent = GetComponentOfClass<AtlasComponent>();
	if (_AtlasComponent)
	{
		_AtlasComponent->LoadTexture(std::string("HeadIsaac.png"));
		_AtlasComponent->SetTileSize(Vector2D<int>(32, 32));
		_AtlasComponent->SetTileIndex(0);
		_AtlasComponent->SetOffsetPosition(Vector2D<float>(0.0f, -15.0f));
	}

	_AnimationComponent = GetComponentOfClass<AnimationComponent>();
	if (_AnimationComponent)
	{
		_AnimationComponent->LoadTexture(std::string("BodyIsaac.png"));
		_AnimationComponent->SetTileSize(Vector2D<int>(32, 32));
		_AnimationComponent->SetOffsetPosition(Vector2D<float>(2.0f, 25.0f));

		AnimationData IdleDownAnimation = AnimationData();
		IdleDownAnimation.FrameInterval = 100.0f;
		IdleDownAnimation.StartIndex = 0;
		IdleDownAnimation.EndIndex = 0;
		_AnimationComponent->AddAnimation(std::string("IdleDownAnimation"), IdleDownAnimation);

		AnimationData WalkDownAnimation = AnimationData();
		WalkDownAnimation.FrameInterval = 0.1f;
		WalkDownAnimation.StartIndex = 0;
		WalkDownAnimation.EndIndex = 9;
		_AnimationComponent->AddAnimation(std::string("WalkDownAnimation"), WalkDownAnimation);

		AnimationData IdleUpAnimation = AnimationData();
		IdleUpAnimation.FrameInterval = 100.0f;
		IdleUpAnimation.StartIndex = 0;
		IdleUpAnimation.EndIndex = 0;
		_AnimationComponent->AddAnimation(std::string("IdleUpAnimation"), IdleUpAnimation);

		AnimationData WalkUpAnimation = AnimationData();
		WalkUpAnimation.FrameInterval = 0.1f;
		WalkUpAnimation.StartIndex = 0;
		WalkUpAnimation.EndIndex = 9;
		_AnimationComponent->AddAnimation(std::string("WalkUpAnimation"), WalkUpAnimation);

		AnimationData IdleRightAnimation = AnimationData();
		IdleRightAnimation.FrameInterval = 100.0f;
		IdleRightAnimation.StartIndex = 10;
		IdleRightAnimation.EndIndex = 10;
		_AnimationComponent->AddAnimation(std::string("IdleRightAnimation"), IdleRightAnimation);

		AnimationData WalkRightAnimation = AnimationData();
		WalkRightAnimation.FrameInterval = 0.1f;
		WalkRightAnimation.StartIndex = 10;
		WalkRightAnimation.EndIndex = 19;
		_AnimationComponent->AddAnimation(std::string("WalkRightAnimation"), WalkRightAnimation);

		AnimationData IdleLeftAnimation = AnimationData();
		IdleLeftAnimation.FrameInterval = 100.0f;
		IdleLeftAnimation.StartIndex = 10;
		IdleLeftAnimation.EndIndex = 10;
		IdleLeftAnimation.AnimationFlip = Flip(true, false);
		_AnimationComponent->AddAnimation(std::string("IdleLeftAnimation"), IdleLeftAnimation);

		AnimationData WalkLeftAnimation = AnimationData();
		WalkLeftAnimation.FrameInterval = 0.1f;
		WalkLeftAnimation.StartIndex = 10;
		WalkLeftAnimation.EndIndex = 19;
		WalkLeftAnimation.AnimationFlip = Flip(true, false);
		_AnimationComponent->AddAnimation(std::string("WalkLeftAnimation"), WalkLeftAnimation);

		_AnimationComponent->SetCurrentAnimation(std::string("IdleDownAnimation"));
	}

	_CurrShootDelay = _ShootDelay;
}

void Isaac::Update(float DeltaTime)
{
	Actor::Update(DeltaTime);

	UpdateShoot(DeltaTime);
	UpdateBodyAnimation();
	UpdateHeadAtlas();
}

void Isaac::UpdateShoot(float DeltaTime)
{
	_ShootDirection = Vector2D<float>(0.0f, 0.0f);

	if (Engine::GetInput()->IsKeyDown(Key_UpArrow))
	{
		_ShootDirection.Y -= 1.0f;
	}
	if (Engine::GetInput()->IsKeyDown(Key_DownArrow))
	{
		_ShootDirection.Y += 1.0f;
	}
	if (Engine::GetInput()->IsKeyDown(Key_LeftArrow))
	{
		_ShootDirection.X -= 1.0f;
	}
	if (Engine::GetInput()->IsKeyDown(Key_RightArrow))
	{
		_ShootDirection.X += 1.0f;
	}

	if (_ShootDirection.X != 0.0f && _ShootDirection.Y != 0.0f)
	{
		_ShootDirection.X = 0;
	}

	_ShootDirection.Normalize();

	_CurrShootDelay += DeltaTime;

	if (_ShootDirection.Magnitude() > 0 && _CurrShootDelay >= _ShootDelay)
	{
		_CurrShootDelay = 0;
		Vector2D<float> ProjectilSize = Vector2D<float>(20.0f, 20.0f);
		Vector2D<float> ProjectilPosition = GetPosition() + ((GetSize() / 2) - (ProjectilSize / 2));

		Projectil* NewProjectil = Engine::GetWorld()->CreateActorOfClass<Projectil>(Projectil::GetNextProjectileName(), {
			{"DrawDepth", GetDrawDepth() + 1},
			{"Position", ProjectilPosition},
			{"Size", ProjectilSize},
			{"IgnoreActor", std::vector<std::type_index>{typeid(*this)}}
		});
		NewProjectil->SetMoveSpeed(1000.0f);
		NewProjectil->SetDirection(_ShootDirection);
	}
}

void Isaac::UpdateBodyAnimation()
{
	Vector2D<float> CurrVeloDir = Vector2D<float>(0.0f, 0.0f);

	if (_PhysicsComponent)
	{
		CurrVeloDir = _PhysicsComponent->GetVelocity();
		CurrVeloDir.Normalize();
	}

	float ShootMagnetude = _ShootDirection.Magnitude();

	if (CurrVeloDir.Magnitude() > 0.0f && CurrVeloDir != _LastVeloDir)
	{
		if (CurrVeloDir.Y > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("WalkDownAnimation"));
		}
		else if (CurrVeloDir.Y < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("WalkUpAnimation"));
		}
		else if (CurrVeloDir.X > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("WalkRightAnimation"));
		}
		else if (CurrVeloDir.X < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("WalkLeftAnimation"));
		}
	}
	else if (_LastVeloDir.Magnitude() > 0.0f && CurrVeloDir.Magnitude() == 0.0f)
	{
		if (_LastVeloDir.Y > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("IdleDownAnimation"));
		}
		else if (_LastVeloDir.Y < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("IdleUpAnimation"));
		}
		else if (_LastVeloDir.X > 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("IdleRightAnimation"));
		}
		else if (_LastVeloDir.X < 0.0f)
		{
			_AnimationComponent->SetCurrentAnimation(std::string("IdleLeftAnimation"));
		}
	}

	_LastVeloDir = CurrVeloDir;
}

void Isaac::UpdateHeadAtlas()
{
	if (_ShootDirection.Magnitude() > 0)
	{
		if (_ShootDirection.Y > 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(0);
		}
		else if (_ShootDirection.Y < 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(4);
		}
		else if (_ShootDirection.X > 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(2);
		}
		else if (_ShootDirection.X < 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(true, false));
			_AtlasComponent->SetTileIndex(2);
		}
	}
	else if (_LastVeloDir.Magnitude() > 0)
	{
		if (_LastVeloDir.Y > 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(0);
		}
		else if (_LastVeloDir.Y < 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(4);
		}
		else if (_LastVeloDir.X > 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(false, false));
			_AtlasComponent->SetTileIndex(2);
		}
		else if (_LastVeloDir.X < 0.0f)
		{
			_AtlasComponent->SetFlip(Flip(true, false));
			_AtlasComponent->SetTileIndex(2);
		}
	}
}

Actor* Isaac::Clone(const std::string& Name, const Param& Params)
{
	Isaac* CopyIsaac = new Isaac(Name);
	return CopyIsaac;
}