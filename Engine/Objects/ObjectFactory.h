#pragma once

#include "Core/Factory.h"
#include "Core/Singleton.h"
#include "Object.h"

namespace gk
{
	class ObjectFactoryImpl : public Factory<Object, std::string> 
	{
	public:
		void Initialize();
	};
	class ObjectFactory : public Singleton<ObjectFactoryImpl> 
	{
	public:

	private:
		ObjectFactory() {}
	};
}