#include "stdafx.h"
#include "GzDisplay.h"


GzDisplay::GzDisplay(GzDisplayClass dispClass, int xRes, int yRes)
{
	// Create a new display object, initialize its members
	if (xRes < 0 || yRes < 0 || xRes > MAXXRES || yRes > MAXYRES)
	{
		AfxThrowInvalidArgException();
	}
	m_xRes = xRes;
	m_yRes = yRes;
	m_isOpen = true;
	m_dispClass = dispClass;
	m_pFrameBuffer = new GzPixel[xRes * yRes];
}


GzDisplay::~GzDisplay()
{
	if (m_pFrameBuffer != NULL)
	{
		delete[] m_pFrameBuffer;
		m_pFrameBuffer = NULL;
	}
}


bool GzDisplay::GetParam(int *xRes, int *yRes, GzDisplayClass *dispClass)
{
	if (!xRes || !yRes || !dispClass)
	{
		AfxThrowInvalidArgException();
		return GZ_FAILURE;
	}
	*xRes = m_xRes;
	*yRes = m_yRes;
	*dispClass = m_dispClass;
	return GZ_SUCCESS;
}


bool GzDisplay::Init()
{
	for (int row = 0; row < m_xRes; row++)
	{
		// display columns (X coords)
		for (int col = 0; col < m_yRes; col++)
		{
			int idx = ARRAY(col, row);
			// use brown color for background
			m_pFrameBuffer[idx].red = 153 << 4;
			m_pFrameBuffer[idx].green = 102 << 4;
			m_pFrameBuffer[idx].blue = 54 << 4;
			// make the pixel completely opaque
			m_pFrameBuffer[idx].alpha = 100;
			// use maximum Z value so it will be sure to be overwritten later
			m_pFrameBuffer[idx].z = INT_MAX;
		}
	}
	return GZ_SUCCESS;
}


bool GzDisplay::PutPixel(int i, int j, GzPixel pixel)
{
	if (i < 0 || j < 0 || i >= m_xRes || j >= m_yRes)
	{
		AfxThrowInvalidArgException();
		return GZ_FAILURE;
	}

	if (pixel.red < 0)
		pixel.red = 0;
	else if (pixel.red > RGB_MAX_INTENSITY)
		pixel.red = RGB_MAX_INTENSITY;

	if (pixel.green < 0)
		pixel.green = 0;
	else if (pixel.green > RGB_MAX_INTENSITY)
		pixel.green = RGB_MAX_INTENSITY;

	if (pixel.blue < 0)
		pixel.blue = 0;
	else if (pixel.blue > RGB_MAX_INTENSITY)
		pixel.blue = RGB_MAX_INTENSITY;

	int idx = ARRAY(i, j);

	m_pFrameBuffer[idx].red = pixel.red;
	m_pFrameBuffer[idx].green = pixel.green;
	m_pFrameBuffer[idx].blue = pixel.blue;

	m_pFrameBuffer[idx].alpha = pixel.alpha;
	m_pFrameBuffer[idx].z = pixel.z;
	return GZ_SUCCESS;
}


bool GzDisplay::GetPixel(int i, int j, GzPixel& pixel)
{
	if (i < 0 || j < 0 || i >= m_xRes || j >= m_yRes)
	{
		AfxThrowInvalidArgException();
		return GZ_FAILURE;
	}
	int idx = ARRAY(i, j);

	pixel.red = m_pFrameBuffer[idx].red;
	pixel.green = m_pFrameBuffer[idx].green;
	pixel.blue = m_pFrameBuffer[idx].blue;
	pixel.alpha = m_pFrameBuffer[idx].alpha;
	pixel.z = m_pFrameBuffer[idx].z;
	return GZ_SUCCESS;
}


int GzDisplay::FlushDisplay2File(FILE* outfile)
{
	/* write pixels to ppm file based on display class -- "P6 %d %d 255\r" */

	if (!outfile)
	{
		AfxThrowInvalidArgException();
		return GZ_FAILURE;
	}
		

	char buffer[1024];

	// create and write out header
	sprintf_s(buffer, 1024, "P6 %d %d 255\r", m_xRes, m_yRes);
	fwrite(buffer, sizeof(char), strlen(buffer), outfile);

	for (int row = 0; row < m_yRes; row++)
	{
		for (int col = 0; col < m_xRes; col++)
		{
			// clear the buffer just in case
			memset(buffer, 0, sizeof(1024));

			int idx = ARRAY(col, row);

			// we want binary representation in the file, so shift 4 bits over and write RGB chars to file
			sprintf_s(buffer, 1024, "%c%c%c",
				m_pFrameBuffer[idx].red >> 4,
				m_pFrameBuffer[idx].green >> 4,
				m_pFrameBuffer[idx].blue >> 4);
			fwrite(buffer, sizeof(char), strlen(buffer), outfile);
		}
	}

	return GZ_SUCCESS;
}


int GzDisplay::GzFlushDisplay2FrameBuffer(char *frameBuffer)
{
	/* write pixels to framebuffer:
	- Put the pixels into the frame buffer
	- Caution: store the pixel to the frame buffer as the order of blue, green, and red
	- Not red, green, and blue !!!
	*/

	// check for bad pointers
	if (!frameBuffer)
	{
		AfxThrowInvalidArgException();
	}

	// display rows (Y coords)
	for (int row = 0; row < m_xRes; row++)
	{
		// display columns (X coords)
		for (int col = 0; col < m_yRes; col++)
		{
			int fbufIdx = ARRAY(col, row);

			char * blueLoc = &(frameBuffer[fbufIdx * 3]); // each idx has 3 chars: B, G, & R
			char * greenLoc = blueLoc + sizeof(char);
			char * redLoc = greenLoc + sizeof(char);

			// we need to reduce the 12-bit RGB intensity values to fit into 8 bits
			char red = m_pFrameBuffer[fbufIdx].red >> 4;
			char green = m_pFrameBuffer[fbufIdx].green >> 4;
			char blue = m_pFrameBuffer[fbufIdx].blue >> 4;

			*blueLoc = blue;
			*greenLoc = green;
			*redLoc = red;
		}
	}

	return GZ_SUCCESS;
}


GzSize GzDisplay::GetResolution()
{
	return GzSize();
}
