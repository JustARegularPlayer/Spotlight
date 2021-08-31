#pragma once
#include <Spotlight.h>

class Layer_Render : public Spotlight::Layer
{
public:
	Layer_Render();

	void OnUpdate() override;
	void OnUIRender() override;
	void OnEvent(Spotlight::Event &e) override;

private:
	Spotlight::OrthoCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;

	std::shared_ptr<Spotlight::VertexArray> m_VAO;
	std::shared_ptr<Spotlight::Shader> m_Shader;

	std::shared_ptr<Spotlight::VertexArray> m_SquareVAO;
	std::shared_ptr<Spotlight::Shader> m_SquareShader;
};
