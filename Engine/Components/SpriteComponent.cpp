#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace gk
{
    bool SpriteComponent::Create(void* data)
    {
        m_owner = static_cast<GameObject*>(data);
        
        return true;
    }

    void SpriteComponent::Destroy()
    {

    }

    void SpriteComponent::Read(const rapidjson::Value& value)
    {
        gk::json::Get(value, "texture", m_textureName);
        gk::json::Get(value, "origin", m_origin);
        gk::json::Get(value, "rect", m_rect);
    }

    void SpriteComponent::Update()
    {

    }

    void SpriteComponent::Draw()
    {
        Texture* texture = m_owner->m_engine->GetSystem<gk::ResourceManager>()->Get<gk::Texture>(m_textureName, m_owner->m_engine->GetSystem<gk::Renderer>());
        texture->Draw(m_rect, m_owner->m_transform.position, m_owner->m_transform.angle, gk::Vector2::one * m_owner->m_transform.scale, m_origin);
    }
}

