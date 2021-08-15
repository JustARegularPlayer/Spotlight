#pragma once

#include "Spotlight/Core/Core.h"
#include "Spotlight/Core/Events/Event.h"

namespace Spotlight
{

	class SPOTLIGHT_API Layer
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Attach() {}
		virtual void Detach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}
	};

}