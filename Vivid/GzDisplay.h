#pragma once
#include "GzDef.h"
#include "GzPixel.h"
#include "GzSize.h"

typedef enum tagDisplayClass
{
	RGB_DISPLAY
} DisplayClass;

class GzDisplay
{
public:
	GzDisplay(DisplayClass dispClass, int xRes, int yRes);
	~GzDisplay();
	static const int MAX_XRES = 1024;
	static const int MAX_YRES = 1024;
private:
	unsigned short m_xRes;
	unsigned short m_yRes;
	DisplayClass m_dispClass;
	bool	open_;
	GzPixel	*m_pFrameBuffer;
public:
	bool GetParam(int *xRes, int *yRes, DisplayClass *dispClass);
	bool Init();
	bool PutPixel(int i, int j, GzPixel pixel);
	GzPixel GetPixel(int i, int j);
	
	int FlushDisplay2File(std::string fileName);
	int GzFlushDisplay2FrameBuffer(char *frameBuffer);
	GzSize GetResolution();
};

#define	ARRAY(x,y)	(x+(y*m_xRes))	/* simplify fbuf indexing */