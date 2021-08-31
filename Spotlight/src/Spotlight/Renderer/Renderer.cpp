#include "splpch.h"
#include "Renderer.h"

namespace Spotlight
{

	Renderer::SceneData *Renderer::sm_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthoCamera& camera)
	{
		sm_SceneData->ViewProjMatrix = camera.GetViewProjMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader,
						  const std::shared_ptr<VertexArray> & vao)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProj", sm_SceneData->ViewProjMatrix);

		vao->Bind();
		RenderCmd::DrawIndexed(vao);
	}

}