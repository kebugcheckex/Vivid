#pragma once
#include "GzDef.h"
#include "GzPixel.h"
#include "GzSize.h"

class GzDisplay
{
public:
	GzDisplay(GzDisplayClass dispClass, int xRes, int yRes);
	~GzDisplay();
private:
	unsigned short m_xRes;
	unsigned short m_yRes;
	GzDisplayClass m_dispClass;
	bool	m_isOpen;
	GzPixel	*m_pFrameBuffer;
public:
	bool GetParam(__out int *xRes, __out int *yRes, __out GzDisplayClass *dispClass);
	bool Init();
	bool PutPixel(int i, int j, GzPixel pixel);
	GzPixel GetPixel(int i, int j);
	int FlushDisplay2File(std::string fileName);
	int GzFlushDisplay2FrameBuffer(char *frameBuffer);
	GzSize GetResolution();
};

#define	ARRAY(x,y)	(x+(y*m_xRes))	/* simplify fbuf indexing */