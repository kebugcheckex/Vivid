#pragma once
#include "GzDef.h"

class GzPixel
{
public:
	GzPixel();
	~GzPixel();
public:
	GzIntensity red;
	GzIntensity greed;
	GzIntensity blue;
	GzIntensity alpha;
	GzDepth z;
};

