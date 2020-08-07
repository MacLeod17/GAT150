#pragma once

namespace gk
{
	class System
	{
		virtual bool Startup() = 0;
		virtual void Update() = 0;
		virtual void Shutdown() = 0;
	};
}