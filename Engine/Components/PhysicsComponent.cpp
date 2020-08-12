#include "pch.h"
#include "PhysicsComponent.h"

namespace gk
{
    bool PhysicsComponent::Create(void* data)
    {
        return false;
    }

    void PhysicsComponent::Destroy()
    {

    }

    void PhysicsComponent::Update()
    {
        m_velocity += m_force;// *timer.DeltaTime();
        m_velocity *= m_drag;
        m_owner->m_transform.position += m_velocity;// *timer.DeltaTime();
    }
}

