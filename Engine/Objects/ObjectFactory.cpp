#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"

namespace gk
{
	void ObjectFactoryImpl::Initialize()
	{
		gk::ObjectFactory::Instance().Register("GameObject", gk::Object::Instantiate<gk::GameObject>);
		gk::ObjectFactory::Instance().Register("PhysicsComponent", gk::Object::Instantiate<gk::PhysicsComponent>);
		gk::ObjectFactory::Instance().Register("SpriteComponent", gk::Object::Instantiate<gk::SpriteComponent>);
		gk::ObjectFactory::Instance().Register("SpriteAnimationComponent", gk::Object::Instantiate<gk::SpriteAnimationComponent>);
	}
}

