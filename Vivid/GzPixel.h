#pragma once
#include "GzDef.h"

class GzPixel
{
public:
	GzPixel();
public:
	GzIntensity red;
	GzIntensity green;
	GzIntensity blue;
	GzIntensity alpha;
	GzDepth z;
};

