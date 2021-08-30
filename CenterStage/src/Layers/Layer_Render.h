#pragma once

#include <Spotlight/Core/Layer.h>

#include <Spotlight/Renderer/Renderer.h>
#include <Spotlight/Renderer/VertexArray.h>
#include <Spotlight/Renderer/Buffer.h>
#include <Spotlight/Renderer/Shader.h>

class Layer_Render : public Spotlight::Layer
{
public:
	Layer_Render();

	void OnUpdate() override;
	void OnUIRender() override;
	void OnEvent(Spotlight::Event &e) override;

private:
	std::shared_ptr<Spotlight::VertexArray> m_VAO;
	std::shared_ptr<Spotlight::Shader> m_Shader;

	std::shared_ptr<Spotlight::VertexArray> m_SquareVAO;
	std::shared_ptr<Spotlight::Shader> m_SquareShader;
};
