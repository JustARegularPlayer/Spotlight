#pragma once

#include <memory>
#include <functional>

#include <filesystem>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>

#include "Spotlight/Core/Log.h"
#include "Spotlight/Debug/Instrumentor.h"
#include <imgui.h>

#if defined _WIN32
	#include <Windows.h>
#elif defined defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
#else
	#error "Unknown platform!"
#endif