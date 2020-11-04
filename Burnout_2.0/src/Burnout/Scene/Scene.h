#pragma once

#include "entt.hpp"


#include "Burnout/Core/Timestep.h"

namespace Burnout
{
	class Scene
	{
	public :
		Scene();
		~Scene();

		void OnUpdate(Timestep ts);

		entt::entity CreateEntity();

		//TEMP 
		entt::registry& Reg() { return m_Registry; }

	private:
		entt::registry m_Registry;


	};
}