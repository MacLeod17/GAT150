#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace gk
{
    bool SpriteComponent::Create(void* data)
    {
        m_texture = m_owner->m_engine->GetSystem<gk::ResourceManager>()->Get<gk::Texture>(m_textureName, m_owner->m_engine->GetSystem<gk::Renderer>());
        ASSERT(m_texture);

        return true;
    }

    void SpriteComponent::Destroy()
    {

    }

    void SpriteComponent::Read(const rapidjson::Value& value)
    {
        gk::json::Get(value, "texture", m_textureName);
        gk::json::Get(value, "rect", m_rect);
    }

    void SpriteComponent::Update()
    {

    }

    void SpriteComponent::Draw()
    {
        m_texture->Draw(m_rect, m_owner->m_transform.position, gk::Vector2{ 1, 1 } * m_owner->m_transform.scale, m_owner->m_transform.angle);
    }
}

