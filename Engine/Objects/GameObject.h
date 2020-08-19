#pragma once

#include "Engine.h"
#include "Math/Transform.h"
#include "Object.h"
#include <vector>

namespace gk
{
	class Component; //Forward Declaration
	
	class GameObject : public Object
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual void Read(const rapidjson::Value& value);
		void ReadComponents(const rapidjson::Value& value);

		void Update();
		void Draw();

		template <typename T>
		T* GetComponent()
		{
			T* result{ nullptr };
			for (auto component : m_components)
			{
				result = dynamic_cast<T*>(component);
				if (result) break;
			}

			return result;
		}

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveAllComponents();

		friend class Component;
		friend class PhysicsComponent;

	public:
		std::string m_name;
		Transform m_transform;
		Engine* m_engine;

	protected:
		std::vector<Component*> m_components;
	};
}