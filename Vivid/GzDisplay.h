#pragma once
#include "Gz.h"

typedef	struct {
	GzIntensity    red;
	GzIntensity    green;
	GzIntensity    blue;
	GzIntensity    alpha;
	GzDepth	 z;
} GzPixel;

class GzDisplay
{
public:
	GzDisplay(GzDisplayClass dispClass, int xRes, int yRes);
	~GzDisplay();
	int GetDisplayParams(int *xRes, int *yRes, GzDisplayClass *dispClass);
private:
	unsigned short	m_xRes;
	unsigned short	m_yRes;
	bool			m_bOpen;
	GzPixel*		m_pFrameBuffer;		/* frame buffer array */
	GzDisplayClass	m_dispClass;
};

