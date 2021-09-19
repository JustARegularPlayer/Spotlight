#include "splpch.h"
#include "Renderer.h"

// Temporary includes
#include "Platform/OpenGL/OpenGLShader.h"

namespace Spotlight
{

	Renderer::SceneData *Renderer::sm_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCmd::Init();
	}

	void Renderer::OnWindowResized(uint32_t width, uint32_t height)
	{
		RenderCmd::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthoCamera& camera)
	{
		sm_SceneData->ViewProjMatrix = camera.GetViewProjMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader,
						  const Ref<VertexArray>& vao,
						  const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProj", sm_SceneData->ViewProjMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vao->Bind();
		RenderCmd::DrawIndexed(vao);
	}

}