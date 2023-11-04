#include "Object/Actor/Actor.h"
#include "Engine.h"
#include "Object/Component/Component.h"

using namespace NPEngine;

Actor::Actor(std::string& Name) : Object()
{
	_Name = Name;
}

Actor::~Actor()
{
	
}

//Flow ----------------------------------------------------

bool Actor::Initialise(const Param& Params)
{
	return true;
}

void Actor::Destroy(const Param& Params)
{
}

void Actor::BeginPlay()
{
}

void Actor::Update(float DeltaTime)
{
	for (auto& Value : _UpdatableComponent)
	{
		IUpdatableComponent* CurrComponent = Value.second;
		if (!CurrComponent) continue;
		CurrComponent->Update(DeltaTime);
	}
}

void Actor::Draw()
{
	for (auto& Value : _DrawableComponent)
	{
		IDrawableComponent* CurrComponent = Value.second;
		if (!CurrComponent) continue;
		CurrComponent->Draw();
	}
}

//---------------------------------------------------------

//Component -----------------------------------------------

void Actor::AddComponent(Component* Component, const Param& Params)
{
	if (!Component) return;

	std::type_index TypeIndex(typeid(*Component));

	DataComponentToAdd CurrDataComponentToAdd = DataComponentToAdd();
	CurrDataComponentToAdd.CurrentComponent = Component;
	CurrDataComponentToAdd.TypeIndex = TypeIndex;
	CurrDataComponentToAdd.Params = Params;
	_ComponentToAdd.push_back(CurrDataComponentToAdd);

	Engine::GetWorld()->AddActorToCallCreateComponent(GetName());
}

void Actor::DeleteComponentByName(std::string& Name, const Param& Params)
{
	DataComponentToDelete DataActor = DataComponentToDelete();
	DataActor.ComponentName = Name;
	DataActor.Params = Params;
	_ComponentToDelete.push_back(DataActor);

	Engine::GetWorld()->AddActorToCallDeleteComponent(Name);
}

void Actor::OnCreateComponent()
{
	for (DataComponentToAdd& DataComponent : _ComponentToAdd)
	{
		Component* NewComponent = DataComponent.CurrentComponent;

		if (!NewComponent) continue;

		std::string& NewComponentName = NewComponent->GetName();
		IActorComponent* ActorComponent = static_cast<IActorComponent*>(NewComponent);

		//Check if an compoennt already has this name
		Component* CheckComponent = GetComponentByName(NewComponentName);
		if (CheckComponent)
		{
			Engine::GetLogger()->LogMessage("A component already has this name");
			if (ActorComponent)
			{
				ActorComponent->Destroy();
			}
			delete NewComponent;
			continue;
		}

		if (ActorComponent)
		{
			if (!ActorComponent->Initialise(DataComponent.Params))
			{
				Engine::GetLogger()->LogMessage("Initialise failed");
				ActorComponent->Destroy();
				delete NewComponent;
				continue;
			}
		}

		IUpdatableComponent* UpdatableComponent = dynamic_cast<IUpdatableComponent*>(NewComponent);
		if (UpdatableComponent)
		{
			_UpdatableComponent[NewComponentName] = UpdatableComponent;
		}

		IDrawableComponent* DrawableComponent = dynamic_cast<IDrawableComponent*>(NewComponent);
		if (DrawableComponent)
		{
			_DrawableComponent[NewComponentName] = DrawableComponent;
		}
		
		_Components[NewComponentName] = NewComponent;
		_ClassComponents[DataComponent.TypeIndex].push_back(NewComponent);
	}
	_ComponentToAdd.clear();
}

void Actor::OnDeleteComponent()
{
	for (DataComponentToDelete& DataComponent : _ComponentToDelete)
	{
		auto ComponentIT = _Components.find(DataComponent.ComponentName);
		if (ComponentIT == _Components.end()) continue;

		Component* ComponentToRemove = ComponentIT->second;

		std::type_index TypeIndex(typeid(*ComponentToRemove));

		auto ClassComponentIT = _ClassComponents.find(TypeIndex);
		if (ClassComponentIT != _ClassComponents.end())
		{
			std::vector<Component*>& ComponentVector = ClassComponentIT->second;
			auto NewEnd = std::remove(ComponentVector.begin(), ComponentVector.end(), ComponentToRemove);
			ComponentVector.erase(NewEnd, ComponentVector.end());
		}

		_Components.erase(ComponentIT);
		_UpdatableComponent.erase(DataComponent.ComponentName);
		_DrawableComponent.erase(DataComponent.ComponentName);

		IActorComponent* ActorComponent = static_cast<IActorComponent*>(ComponentToRemove);
		if (ActorComponent)
		{
			ActorComponent->Destroy(DataComponent.Params);
		}

		delete ComponentToRemove;
	}
	_ComponentToDelete.clear();
}

//---------------------------------------------------------

Actor* Actor::Clone(std::string& Name)
{
	Actor* CloneActor = new Actor(Name);
	return CloneActor;
}

void Actor::SetDrawDepth(unsigned char DrawDepth)
{
	_DrawDepth = DrawDepth;

	Engine::GetWorld()->ResetDrawOrder();
}

//Getter, setter -----------------------------------------

Component* Actor::GetComponentByName(std::string& Name)
{
	auto& IT = _Components.find(Name);
	if (IT == _Components.end()) return nullptr;
	return IT->second;
}
