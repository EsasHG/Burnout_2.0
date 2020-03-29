#pragma once

#include "Burnout/Core/Layer.h"
#include "Burnout/Events/MouseEvent.h"
#include "Burnout/Events/KeyEvent.h"
#include "Burnout/Events/ApplicationEvent.h"


namespace Burnout
{
	class BURNOUT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;


		void Begin();
		void End();

	private:
		float m_Time = 0.f;
	};
}