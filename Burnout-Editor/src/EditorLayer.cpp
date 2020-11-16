#include "EditorLayer.h"

#include "imgui/imgui.h"	
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
//TEMP
//#include <entt/include/entt.hpp>

#include "Burnout/Cameras/OrthographicCameraController.h"

namespace Burnout
{

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


	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), m_OrthoCamera(1280.f/720.f, true), m_MapWidth(s_MapWidth), m_MapHeight(strlen(s_MapTiles) / s_MapWidth)
	{
		m_MapWidth = s_MapWidth;
		m_MapHeight = strlen(s_MapTiles) / s_MapWidth;
	}

	void EditorLayer::OnAttach()
	{
		BO_PROFILE_FUNCTION();

		m_Texture = Texture2D::Create("assets/textures/me.png");
		m_SpriteSheet = Texture2D::Create("assets/game/textures/colored_tilemap_packed.png");

		m_TextureBow = SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(8, 5), glm::vec2(8, 8));
		m_TextureBubble = SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(1, 8), glm::vec2(8, 8));
		m_TextureHeart  = SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2( 4, 3 ), glm::vec2( 8, 8 ), glm::vec2(3,1));

		m_MapWidth = s_MapWidth;
		m_MapHeight = strlen(s_MapTiles) / s_MapWidth;

		s_TextureMap['W'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(13, 1), glm::vec2(8,8));
		s_TextureMap['G'] = SubTexture2D::CreateFromCoords(m_SpriteSheet, glm::vec2(1, 8), glm::vec2(8, 8));

		/*m_Particle.ColorBegin = { 254 / 255.f, 212 / 255.f, 123 / 255.f, 1.0f };
		m_Particle.ColorEnd = { 254 / 255.f, 109 / 255.f, 41/ 255.f, 1.0f };
		m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
		m_Particle.LifeTime = 2.0f;
		m_Particle.Velocity = { 0.0f, 0.0f };
		m_Particle.VelocityVariation = { 3.0f, 1.0f };
		m_Particle.Position = { 0.0f,0.0f };*/

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();

		//Entity
		auto square = m_ActiveScene->CreateEntity("GreenSquare");

		square.AddComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});
		m_SquareEntity = square;

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
		m_CameraEntity.AddComponent<CameraComponent>();

		m_SecondCamera = m_ActiveScene->CreateEntity("Clip Space Camera");
		auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
		cc.Primary = false;



		class CameraController : public  ScriptableEntity
		{
		public:
			void OnCreate()
			{
				std::cout << "OnCreate: " << std::endl;

			}
			
			void OnDestroy()
			{
			}

			void OnUpdate(Timestep ts)
			{
				std::cout << "Timestep: " << ts << std::endl;
				auto& transform = GetComponent<TransformComponent>().Transform;
				float speed = 5.0f;
				
				if (Input::IsKeyPressed(BO_KEY_A))
					transform[3][0] -= speed * ts;
				if (Input::IsKeyPressed(BO_KEY_D))
					transform[3][0] += speed * ts;
				if (Input::IsKeyPressed(BO_KEY_W))
					transform[3][1] += speed * ts;
				if (Input::IsKeyPressed(BO_KEY_S))
					transform[3][1] -= speed * ts;
			}
		};
		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
	}

	void EditorLayer::OnDetach()
	{
		BO_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		BO_PROFILE_FUNCTION();

		if(m_ViewportFocused)
			m_OrthoCamera.OnUpdate(ts);

		Renderer2D::ResetStats();

		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.61f, 0.11f, 0.11f, 1 });
		RenderCommand::Clear();
		
		//UpdateScene
		m_ActiveScene->OnUpdate(ts);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		BO_PROFILE_FUNCTION();
		
		static bool dockspaceOpen = true;

		//-----------------------------------------------------------------------------
		// [SECTION] Example App: Docking, DockSpace / ShowExampleAppDockSpace()
		//-----------------------------------------------------------------------------

		// Demonstrate using DockSpace() to create an explicit docking node within an existing window.
		// Note that you already dock windows into each others _without_ a DockSpace() by just moving windows
		// from their title bar (or by holding SHIFT if io.ConfigDockingWithShift is set).
		// DockSpace() is only useful to construct to a central location for your application.

		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Docking"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit"))
					Application::Get().Close();

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
	
	
		ImGui::Begin("Settings");
	
		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats: ");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		if (m_SquareEntity)
		{

			ImGui::Separator();
			ImGui::Text("%s", m_SquareEntity.GetComponent<TagComponent>().Tag.c_str());
			glm::vec4& squareColor =  m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;
			ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
			
		}
		ImGui::DragFloat3("Camera Transform", glm::value_ptr(
			m_CameraEntity.GetComponent<TransformComponent>().Transform[3]));

		if(ImGui::Checkbox("Camera A", &m_PrimaryCamera))
		{
			m_CameraEntity.GetComponent<CameraComponent>().Primary = m_PrimaryCamera;
			m_SecondCamera.GetComponent<CameraComponent>().Primary = !m_PrimaryCamera;
		}

		{
			auto& camera = m_SecondCamera.GetComponent<CameraComponent>().Camera;
			float orthoSize = camera.GetOrthographicSize();
			if (ImGui::DragFloat("Second Camera Ortho Size", &orthoSize))
			{
				camera.SetOrthographicSize(orthoSize);
			}

		}



		ImGui::End();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0, });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*) & viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_Framebuffer->Resize(m_ViewportSize.x, m_ViewportSize.y);

			m_OrthoCamera.OnResize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
	
		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_OrthoCamera.OnEvent(e);
	}
}