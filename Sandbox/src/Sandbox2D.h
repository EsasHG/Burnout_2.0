#pragma once

#include "Burnout.h"

#include "ParticleSystem.h"

class Sandbox2D	: public Burnout::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Burnout::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Burnout::Event& e) override;
private:

	Burnout::OrthographicCameraController m_OrthoCamera;
	
	//temp
	Burnout::Ref<Burnout::VertexArray> m_VertexArray;
	Burnout::Ref<Burnout::Shader> m_FlatColorShader;

	Burnout::Ref<Burnout::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = { 0.2f ,0.3f ,0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};