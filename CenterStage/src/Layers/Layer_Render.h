#pragma once
#include <Spotlight.h>

class Layer_Render : public Spotlight::Layer
{
public:
	Layer_Render();

	void OnUpdate(Spotlight::Timestep ts) override;
	void OnUIRender() override;
	void OnEvent(Spotlight::Event &e) override;

private:
	Spotlight::OrthoCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraMoveSpeed = 2.5f;
	float m_CameraRotateSpeed = 45.0f;

	Spotlight::Ref<Spotlight::VertexArray> m_VAO;
	Spotlight::Ref<Spotlight::Shader> m_Shader;

	Spotlight::Ref<Spotlight::VertexArray> m_SolidColorVAO;
	Spotlight::Ref<Spotlight::Shader> m_SolidColorShader;
	Spotlight::Ref<Spotlight::Shader> m_TextureShader;

	Spotlight::Ref<Spotlight::Texture2D> m_Texture;

	glm::vec4 m_SolidColor;
};
