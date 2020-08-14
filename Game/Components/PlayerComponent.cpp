#include "pch.h"
#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"

namespace gk
{
    bool PlayerComponent::Create(void* data)
    {
        return false;
    }

    void PlayerComponent::Destroy()
    {

    }

    void PlayerComponent::Update()
    {
		//Player Controls
		if (m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == gk::InputSystem::eButtonState::HELD ||
			m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == gk::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle -= 120.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == gk::InputSystem::eButtonState::HELD ||
			m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == gk::InputSystem::eButtonState::HELD)
		{
			m_owner->m_transform.angle += 120.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}

		//Physics
		gk::Vector2 force{ 0,0 };
		if (m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == gk::InputSystem::eButtonState::HELD ||
			m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == gk::InputSystem::eButtonState::HELD)
		{
			force = gk::Vector2::forward * 1000;
		}
		if (m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_DOWN) == gk::InputSystem::eButtonState::HELD ||
			m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_S) == gk::InputSystem::eButtonState::HELD)
		{
			force = -(gk::Vector2::forward * 1000);
		}
		force = gk::Vector2::Rotate(force, gk::DegreesToRadians(m_owner->m_transform.angle));

		PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
		if (component)
		{
			component->ApplyForce(force);
		}
    }
}

