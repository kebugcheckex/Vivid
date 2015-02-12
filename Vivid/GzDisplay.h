#pragma once
#include "GzDef.h"

#define	MAXXRES	1024	/* put some bounds on size in case of error */
#define	MAXYRES	1024

#ifndef GZ_PIXEL
typedef	struct {
	GzIntensity		red;
	GzIntensity		green;
	GzIntensity		blue;
	GzIntensity		alpha;
	GzDepth			z;
} GzPixel;
#define GZ_PIXEL
#endif;


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
	bool GetPixel(int i, int j, __out GzPixel& pixel);
	int FlushDisplay2File(FILE* outfile);
	int GzFlushDisplay2FrameBuffer(char *frameBuffer);
};

#define	ARRAY(x,y)	(x+(y*m_xRes))	/* simplify fbuf indexing */