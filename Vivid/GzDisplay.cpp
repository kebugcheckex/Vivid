#include "stdafx.h"
#include "GzDisplay.h"


GzDisplay::GzDisplay(GzDisplayClass dispClass, int xRes, int yRes)
{
	m_xRes = xRes;
	m_yRes = yRes;
	m_dispClass = dispClass;
	m_pFrameBuffer = new GzPixel[sizeof(GzPixel) * xRes * yRes];
}


GzDisplay::~GzDisplay()
{
}

int GzDisplay::GetDisplayParams(int *xRes, int *yRes, GzDisplayClass *dispClass)
{
	*dispClass = m_dispClass;
	*xRes =m_xRes;
	*yRes = m_yRes;
	return GZ_SUCCESS;
}
