#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "camera.h"
#include "CamearEditor.h"

#include "scene.h"

void CamearEditor::Init()
{
	bool show_demo_window = true;
	_camera = CManager::GetScene()->GetGameObject<CCamera>(TYPE_CAMERA);
	ImGui::ShowDemoWindow(&show_demo_window);
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplDX11_InvalidateDeviceObjects();
	ImGui_ImplDX11_CreateDeviceObjects();
	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());
	ImGui::NewFrame();
}

void CamearEditor::Update()
{
	bool open = true;
	float color = 0.5f;

	ImGui::Begin("Stats");
	//ImGui::LabelText("", "FPS:%4.2f (%4.2f ms)", 810);
	//ImGui::LabelText("", "Camera Pos:(%.2f, %.2f, %.2f )", _camera->GetPosition().x, _camera->GetPosition().y, _camera->GetPosition().z);
	//ImGui::Spacing();
	////ImGui::SetNextTreeNodeOpen(true, ImGuiSetCond_Once);
	//if (ImGui::CollapsingHeader("PostEffect"))
	//{
	//	if (ImGui::TreeNode("Tonemap"))
	//	{
	//		ImGui::SliderFloat("Gamma", nullptr, 0.0f, 4.0f);
	//		// ...
	//		ImGui::TreePop();
	//	}
	//	// ...
	//	ImGui::TreePop();
	//}
	//...
	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	ImGui::Checkbox("Demo Window", &open);      // Edit bools storing our window open/close state
	ImGui::Checkbox("Another Window", &open);

	ImGui::SliderFloat("float", &color, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("clear color", (float*)&color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		
	ImGui::SameLine();


	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::End();
	
	ImGui::Render();
}
