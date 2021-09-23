#pragma once

#include "Spotlight/Core/Core.h"
#include "Spotlight/Core/Layer.h"

namespace Spotlight
{

	class SPOTLIGHT_API LayerStack
	{
		typedef std::vector<Layer*> LayerPtrVector;
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		inline LayerPtrVector::iterator begin() { return m_LayerArray.begin(); }
		inline LayerPtrVector::iterator end() { return m_LayerArray.end(); }
	private:
		LayerPtrVector m_LayerArray;
		unsigned int m_LayerIterator = 0;
	};

}

