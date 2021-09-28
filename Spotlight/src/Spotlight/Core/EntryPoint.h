#pragma once

#include "Spotlight/Core/Application.h"
#include "Spotlight/Debug/Instrumentor.h"

#if defined SPL_PLATFORM_WINDOWS

extern Spotlight::SpotlightApp *Spotlight::CreateApp();

int main(int argc, char *argv[])
{
	SPL_PROFILE_BEGIN_SESSION("Startup", "SplProfile_Startup.json");
	auto app = Spotlight::CreateApp();
	SPL_PROFILE_END_SESSION();

	SPL_PROFILE_BEGIN_SESSION("Runtime", "SplProfile_Runtime.json");
	app->Run();
	SPL_PROFILE_END_SESSION();

	SPL_PROFILE_BEGIN_SESSION("Shutdown", "SplProfile_Shutdown.json");
	delete app;
	SPL_PROFILE_END_SESSION();

	return 0;
}

#endif