#include <Burnout.h>
#include <Burnout/Core/EntryPoint.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "EditorLayer.h"

namespace Burnout
{
	class BurnoutEditor : public Application
	{
	public: 
		BurnoutEditor()
			: Application("Burnout Editor")
		{
			//ExampleLayer* l = new ExampleLayer();
			//PushLayer(l);
			PushLayer(new EditorLayer());

		}
		~BurnoutEditor()
		{

		}

	};
	Application* CreateApplication()
	{
		return new BurnoutEditor();
	}
	}