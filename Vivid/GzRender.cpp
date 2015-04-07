#include "stdafx.h"
#include "GzLine.h"
#include "GzRender.h"

using namespace std;

GzRender::GzRender(GzRenderClass renderClass, GzDisplay *display)
{
	display_ = display;
}


GzRender::~GzRender()
{
}


int GzRender::BeginRender()
{
	return 0;
}


int GzRender::PutAttribute(int num, GzToken *tokens, GzPointer *values)
{
	for (int i = 0; i < num; i++)
	{
		switch (tokens[i])
		{
		case GZ_RGB_COLOR:
		{
			GzColor *color = (GzColor*)values[i];
			flatcolor_ = *color;
			break;
		}
		case GZ_INTERPOLATE:
		{
			int *interpmode = (int*)values[i];
			interpmode_ = *interpmode;
			break;
		}
		case GZ_AMBIENT_LIGHT:
		{
			GzLight *light = (GzLight*)values[i];
			ambientlight_ = *light;
			break;
		}
		case GZ_DIRECTIONAL_LIGHT:
		{
			if (lights_.size() >= MAX_LIGHTS)
			{
				AfxMessageBox(_T("Reached maximum number of lights"));
				return GZ_FAILURE;
			}
			GzLight *light = (GzLight*)values[i];
			lights_.push_back(*light);
			break;
		}
		case GZ_AMBIENT_COEFFICIENT:
			// TODO - I went to shower at this point.
		default:
			break;
		}
	}
	return 0;
}


int GzRender::PutTriangle(int numParts, GzToken * nameList, GzPointer * valueList)
{
	return 0;
}


int GzRender::PushMatrix(GzMatrix matrix)
{
	return 0;
}


int GzRender::PutCamera(GzCamera camera)
{
	return 0;
}


int GzRender::PopMatrix()
{
	return 0;
}


bool GzRender::rasterize(GzTriangle& triangle)
{
	GzSize screenres = this->display_->GetResolution();
	GzRectangle screenrect(0, 0, screenres.X, screenres.Y);
	GzRectangle boundingbox = triangle.GetScreenBoundingBox(screenrect);
	vector<GzLine> lines;
	triangle.GetLines(lines);
	for (int y = boundingbox.Top; y <= boundingbox.Bottom; y++)
	{
		for (int x = boundingbox.Left; x <= boundingbox.Right; x++)
		{
			// TODO - I am too sleepy to continue coding. See you tomorrow.
		}
	}
	return false;
}
