#pragma once

#include "Component.h"

namespace gk
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw() = 0;
	};
}