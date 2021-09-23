#include "splpch.h"
#include "LayerStack.h"

namespace Spotlight
{

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_LayerArray)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerArray.emplace(m_LayerArray.begin() + m_LayerIterator, layer);
		m_LayerIterator++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_LayerArray.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_LayerArray.begin(), m_LayerArray.end(), layer);
		if (it != m_LayerArray.end())
		{
			layer->OnDetach();
			m_LayerArray.erase(it);
			m_LayerIterator--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_LayerArray.begin(), m_LayerArray.end(), overlay);
		if (it != m_LayerArray.end())
		{
			m_LayerArray.erase(it);
			overlay->OnDetach();
		}
	}

}