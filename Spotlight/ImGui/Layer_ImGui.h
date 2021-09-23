#pragma once

#include "Spotlight/Core/Layer.h"
#include "Spotlight/Events/AppEvent.h"
#include "Spotlight/Events/KeyEvent.h"
#include "Spotlight/Events/MouseEvent.h"

namespace Spotlight
{

	class SPOTLIGHT_API Layer_ImGui : public Layer
	{
	public:
		Layer_ImGui();
		~Layer_ImGui();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUIRender() override;

		void Begin();
		void End();
	};

}