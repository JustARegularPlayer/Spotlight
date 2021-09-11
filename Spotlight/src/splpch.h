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
#include <imgui.h>

#if defined SPL_PLATFORM_WINDOWS
	#include <Windows.h>
#endif