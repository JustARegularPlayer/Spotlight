#pragma once

#include "Spotlight/Core/Application.h"

#if defined SPL_PLATFORM_WINDOWS

extern Spotlight::SpotlightApp *Spotlight::CreateApp();

int main(int argc, char *argv[])
{
	auto app = Spotlight::CreateApp();
	app->Run();

	return 0;
}

#endif