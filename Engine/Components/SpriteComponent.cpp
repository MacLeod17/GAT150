#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace gk
{
    bool SpriteComponent::Create(void* data)
    {
        m_texture = m_owner->m_engine->GetSystem<gk::ResourceManager>()->Get<gk::Texture>("cars.png", m_owner->m_engine->GetSystem<gk::Renderer>());
        
        return true;
    }

    void SpriteComponent::Destroy()
    {

    }

    void SpriteComponent::Update()
    {

    }

    void SpriteComponent::Draw()
    {
        m_texture->Draw({ 0, 16, 64, 144 }, m_owner->m_transform.position, { 1, 1 }, m_owner->m_transform.angle);
    }
}

