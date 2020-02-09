#pragma once

#include "Burnout/Layer.h"
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

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		float m_Time = 0.f;

	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);

		bool OnWindowResized(WindowResizeEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);
	};
}