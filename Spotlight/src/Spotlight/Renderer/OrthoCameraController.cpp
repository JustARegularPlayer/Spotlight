#include "splpch.h"
#include "OrthoCameraController.h"

#include "Spotlight/Core/Input.h"
#include "Spotlight/Core/KeyCodes.h"

namespace Spotlight
{

	OrthoCameraController::OrthoCameraController(float aspectRatio, bool enableRotation)
		: m_AspectRatio(aspectRatio),
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		m_IsRotationEnabled(enableRotation)
	{
	}

	void OrthoCameraController::OnUpdate(Timestep ts)
	{
		SPL_PROFILE_FUNC();

		if (Input::IsKeyPressed(SPL_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(SPL_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(SPL_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(SPL_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		m_Camera.SetPosition(m_CameraPosition);

		if (m_IsRotationEnabled)
		{
			if (Input::IsKeyPressed(SPL_KEY_Q))
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(SPL_KEY_E))
				m_CameraRotation += m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void OrthoCameraController::OnEvent(Event &e)
	{
		SPL_PROFILE_FUNC();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Event_MouseScrolled>(SPL_BIND_FUNC(OrthoCameraController::OnMouseScrolled));
		dispatcher.Dispatch<Event_WindowResized>(SPL_BIND_FUNC(OrthoCameraController::OnWindowResized));
	}

	bool OrthoCameraController::OnMouseScrolled(Event_MouseScrolled &e)
	{
		SPL_PROFILE_FUNC();

		m_ZoomLevel -= e.GetYOffset() * 0.5f;
		m_ZoomLevel = (m_ZoomLevel < 0.3f ? 0.3f : m_ZoomLevel);
		m_Camera.SetProj(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthoCameraController::OnWindowResized(Event_WindowResized &e)
	{
		SPL_PROFILE_FUNC();

		m_AspectRatio = (float) e.GetWidth() / (float) e.GetHeight();
		m_Camera.SetProj(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}