#include "pch.h"
#include "PlayerComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/SpriteComponent.h"

namespace gk
{
    bool PlayerComponent::Create(void* data)
    {
		m_owner = static_cast<GameObject*>(data);
		
		return true;
    }

    void PlayerComponent::Destroy()
    {

    }

    void PlayerComponent::Update()
    {
		auto contacts = m_owner->GetContactsWithTag("Floor");
		bool onGround = !contacts.empty();
		
		gk::Vector2 force{ 0,0 };

		//Player Controls
		if (m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_LEFT) == gk::InputSystem::eButtonState::HELD ||
			m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == gk::InputSystem::eButtonState::HELD)
		{
			force.x = -150;
		}
		if (m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_RIGHT) == gk::InputSystem::eButtonState::HELD ||
			m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == gk::InputSystem::eButtonState::HELD)
		{
			force.x = 150;
		}

		if ((m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_UP) == gk::InputSystem::eButtonState::PRESSED ||
			m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == gk::InputSystem::eButtonState::PRESSED ||
			m_owner->m_engine->GetSystem<gk::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == gk::InputSystem::eButtonState::PRESSED) &&
			onGround)
		{
			force.y = -2500;
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				audioComponent->SetSoundName("jump.wav");
				audioComponent->Play();
			}
		}

		PhysicsComponent* component = m_owner->GetComponent<RigidBodyComponent>();
		if (component)
		{
			component->ApplyForce(force);

			float velocity = component->GetVelocity().x;
			SpriteComponent* sprite = m_owner->GetComponent<SpriteComponent>();

			if (velocity <= -0.15f) sprite->Flip();
			if (velocity >=  0.15f) sprite->Flip(false);
		}

		auto coinContacts = m_owner->GetContactsWithTag("Coin");
		for (GameObject* contact : coinContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
			//Play Sound
		}

		auto enemyContacts = m_owner->GetContactsWithTag("Enemy");
		for (GameObject* contact : enemyContacts)
		{
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				//audioComponent->SetSoundName("enter sound here");
				//audioComponent->Play();
			}
		}
    }

	void PlayerComponent::CollisionEvent(GameObject* gameObject)
	{

	}
}

