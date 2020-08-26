#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"

namespace gk
{
	void ObjectFactoryImpl::Initialize()
	{
		gk::ObjectFactory::Instance().Register("GameObject", new Creator<GameObject, Object>);
		gk::ObjectFactory::Instance().Register("PhysicsComponent", new Creator<PhysicsComponent, Object>);
		gk::ObjectFactory::Instance().Register("SpriteComponent", new Creator<SpriteComponent, Object>);
		gk::ObjectFactory::Instance().Register("SpriteAnimationComponent", new Creator<SpriteAnimationComponent, Object>);
	}
}

