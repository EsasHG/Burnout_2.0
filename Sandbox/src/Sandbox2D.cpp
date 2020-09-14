#include "Sandbox2D.h"

#include "imgui/imgui.h"	
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include "Burnout/Cameras/OrthographicCameraController.h"

static const uint32_t s_MapWidth = 25;
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWGGGGWWWWWWWWWWWWWWW"
"WWWWGGGGGGGGGGGGGGGGWWWWW"
"WWWWGGGGGGGGGGGWWWGGGWWWW"
"WWWGGGGGGGGGGGGGWWGGGGWWW"
"WWWGGGGGGGGGGGGGGGGGGGWWW"
"WWWWWGGGGGGGGGGWGGGGGWWWW"
"WWWWWWWWGGGGGGGGGGGGWWWWW"
"WWWWWWGGGGGGGGGGGGWWWWWWW"
"WWWWWGGGGGGGGGGGGGGGWWWWW"
"WWWWWWWWWWGGGGGGGGGGGWWWW"
"WWWWWWWWWGGGGGGGGGGWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWWW";


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_OrthoCamera(1280.f/720.f, true)
{
}
void Sandbox2D::OnAttach()
{
	BO_PROFILE_FUNCTION();

	m_Texture = Burnout::Texture2D::Create("assets/textures/me.png");
	m_SpriteSheet = Burnout::Texture2D::Create("assets/game/textures/colored_tilemap_packed.png");

	m_TextureBow = Burnout::SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(8, 5), glm::vec2(8, 8));
	m_TextureBubble = Burnout::SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(1, 8), glm::vec2(8, 8));
	m_TextureHeart  = Burnout::SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2( 4, 3 ), glm::vec2( 8, 8 ), glm::vec2(3,1));

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

	s_TextureMap['W'] = Burnout::SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(13, 1), glm::vec2(8,8));
	s_TextureMap['G'] = Burnout::SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(1, 8), glm::vec2(8, 8));

	m_Particle.ColorBegin = { 254 / 255.f, 212 / 255.f, 123 / 255.f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.f, 109 / 255.f, 41/ 255.f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 2.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f,0.0f };
}

void Sandbox2D::OnDetach()
{
	BO_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Burnout::Timestep ts)
{
	BO_PROFILE_FUNCTION();

	m_OrthoCamera.OnUpdate(ts);

	Burnout::Renderer2D::ResetStats();

	{
		BO_PROFILE_SCOPE("Renderer Prep");

		Burnout::RenderCommand::SetClearColor({ 0.11f, 0.11f, 0.11f, 1 });
		Burnout::RenderCommand::Clear();
	}

#if 0
	{
		static float rotation = 0.0f;
		rotation += ts * 20.f;
		BO_PROFILE_SCOPE("Renderer Draw");

		Burnout::Renderer2D::BeginScene(m_OrthoCamera.GetCamera());
	
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		Burnout::Renderer2D::DrawQuad(glm::vec3(0.5f, -0.5f, 0.f), glm::vec2(0.5f, 0.75f), glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
		Burnout::Renderer2D::DrawQuad(glm::vec3(-1.f, 0.f, 0.f), glm::vec2(0.8f, 0.8f), glm::vec4(0.2f, 0.2f, 0.8f, 1.0f));
		Burnout::Renderer2D::DrawRotatedQuad(glm::vec3(1.f, 0.f, 1.f), glm::vec2(0.8f, 0.8f),glm::radians(-45.f), glm::vec4(0.2f, 0.8f, 0.2f, 1.0f));
		Burnout::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.2f), glm::vec2(20.0f, 20.0f), m_Texture, 1.f);
		Burnout::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.1f), glm::vec2(1.0f, 1.0f), m_Texture, 1.f);
		Burnout::Renderer2D::DrawRotatedQuad(glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::radians(rotation), m_Texture, 1.f);
		
		//Burnout::Renderer2D::EndScene();
		//Burnout::Renderer2D::BeginScene(m_OrthoCamera.GetCamera());
		
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x <5.0f; x += 0.5f)
			{

				glm::vec4 color = { (x + 5.f) / 10.0f, 0.4f,(y + 5.0f) / 10.f, 0.5f };
				Burnout::Renderer2D::DrawQuad(glm::vec3(x,y, 0.f), glm::vec2(0.45f, 0.45f), color);
			}
		
		}

		//Burnout::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		//Burnout::Renderer2D::DrawQuad(glm::vec2(-1.0f, 0.0f), glm::vec2(0.8f, 0.8f  ), glm::vec4( 0.8f, 0.2f, 0.3f, 1.0f ));
		//Burnout::Renderer2D::DrawQuad(glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.75f ), glm::vec4( 0.2f, 0.3f, 0.8f, 1.0f ));
		//Burnout::Renderer2D::DrawQuad(glm::vec2(0.5f, -0.5f), glm::vec2(0.5f, 0.75f ), glm::vec4( 0.2f, 0.3f, 0.8f, 1.0f ));
		//Burnout::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture, 10.0f);

		Burnout::Renderer2D::EndScene();
	}
#endif

	Burnout::Renderer2D::BeginScene(m_OrthoCamera.GetCamera());

	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * m_MapWidth];
			Burnout::Ref<Burnout::SubTexture2D> texture;

			if (s_TextureMap.find(tileType) != s_TextureMap.end())
			{
				texture = s_TextureMap[tileType];
			}
			else
			{
				texture = m_TextureBow;
			}

			Burnout::Renderer2D::DrawQuad(glm::vec3(x - m_MapWidth/2.f, m_MapHeight -  y - m_MapHeight / 2.f, -0.9f), glm::vec2(1.0f, 1.0f), texture);

		}
	}

	//Burnout::Renderer2D::DrawQuad(glm::vec3(0.0f, 0.0f, -0.9f), glm::vec2(1.0f, 1.0f), m_TextureBow);
//	Burnout::Renderer2D::DrawQuad(glm::vec3(1.0f, 0.0f, -0.9f), glm::vec2(1.0f, 1.0f), m_TextureBubble);
	//Burnout::Renderer2D::DrawQuad(glm::vec3(0.0f, 1.0f, -0.9f), glm::vec2(3.0f, 1.0f), m_TextureHeart);

	Burnout::Renderer2D::EndScene();
	

	if (Burnout::Input::IsMouseButtonPressed(BO_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Burnout::Input::GetMousePosition();

		auto width = Burnout::Application::Get().GetWindow().GetWidth();
		auto height = Burnout::Application::Get().GetWindow().GetHeight();

		auto bounds = m_OrthoCamera.GetBounds();

		auto pos = m_OrthoCamera.GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5 - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 15; i++)
			m_ParticleSystem.Emit(m_Particle);
	}
	
	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_OrthoCamera.GetCamera());
}

void Sandbox2D::OnImGuiRender()
{

	BO_PROFILE_FUNCTION();

	ImGui::Begin("Settings");


	auto stats = Burnout::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Burnout::Event& e)
{
	m_OrthoCamera.OnEvent(e);
}