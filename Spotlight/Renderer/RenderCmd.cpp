#include "splpch.h"
#include "RenderCmd.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Spotlight
{

	RendererAPI *RenderCmd::sm_API = new OpenGLRendererAPI;

}