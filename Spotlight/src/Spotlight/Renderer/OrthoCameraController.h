#pragma once

#include "Spotlight/Renderer/OrthoCamera.h"
#include "spotlight/Core/Timestep.h"

#include "Spotlight/Events/AppEvent.h"
#include "Spotlight/Events/MouseEvent.h"

namespace Spotlight
{

	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, bool enableRotation = false);

		inline OrthoCamera &GetCamera() { return m_Camera; }
		inline const OrthoCamera &GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level) { m_ZoomLevel = level; }
		inline float GetZoomLevel() { return m_ZoomLevel; }

		void OnUpdate(Timestep ts);
		void OnEvent(Event &e);
	private:
		bool OnMouseScrolled(Event_MouseScrolled &e);
		bool OnWindowResized(Event_WindowResized &e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthoCamera m_Camera;
		bool m_IsRotationEnabled;

		glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};

}