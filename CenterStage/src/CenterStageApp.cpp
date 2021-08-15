#include "Spotlight.h"

class CenterStage : public Spotlight::SpotlightApp
{
public:
	CenterStage()
	{
	}

	~CenterStage()
	{
	}
};

Spotlight::SpotlightApp* Spotlight::CreateApp()
{
	return new CenterStage();
}