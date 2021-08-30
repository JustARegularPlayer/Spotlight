#include "splpch.h"
#include "Renderer.h"

namespace Spotlight
{

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray> &vao)
	{
		vao->Bind();
		RenderCmd::DrawIndexed(vao);
	}

}