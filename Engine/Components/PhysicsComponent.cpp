#include "pch.h"
#include "PhysicsComponent.h"

namespace gk
{
    bool PhysicsComponent::Create(void* data)
    {
        return true;
    }

    void PhysicsComponent::Destroy()
    {

    }

    void PhysicsComponent::Update()
    {
        m_velocity += m_force * m_owner->m_engine->GetTimer().DeltaTime();
        m_velocity *= m_drag;
        m_owner->m_transform.position += m_velocity * m_owner->m_engine->GetTimer().DeltaTime();
    }
}

