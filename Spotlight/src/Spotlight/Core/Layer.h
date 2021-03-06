#pragma once

#include "Spotlight/Core/Core.h"
#include "Spotlight/Events/Event.h"
#include "Spotlight/Core/Timestep.h"

namespace Spotlight
{

	class SPOTLIGHT_API Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnUIRender() {}
		virtual void OnEvent(Event& e) {}
	};

}