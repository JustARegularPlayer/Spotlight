#include <Spotlight.h>

class Sandbox2D : public Spotlight::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Spotlight::Timestep ts) override;
	void OnUIRender() override;
	void OnEvent(Spotlight::Event &e) override;
private:
	Spotlight::OrthoCameraController m_Controller;
	glm::vec4 m_Color = {0.2f, 0.3f, 0.8f, 1.0f};

	Spotlight::Ref<Spotlight::Texture2D> m_Texture;
};