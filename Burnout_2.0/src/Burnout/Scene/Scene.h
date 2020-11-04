#pragma once

#include "entt.hpp"


#include "Burnout/Core/Timestep.h"

namespace Burnout
{
	class Entity;

	class Scene
	{
	public :
		Scene();
		~Scene();

		void OnUpdate(Timestep ts);

		Entity CreateEntity(const std::string& name = std::string());

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}