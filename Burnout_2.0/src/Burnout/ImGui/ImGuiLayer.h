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
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.f;
	};
}