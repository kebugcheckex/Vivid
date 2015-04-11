/*	TODO
	This is the core render class. I suggest implement this at last
*/



#include "stdafx.h"
#include "GzLine.h"
#include "GzRender.h"

using namespace std;

GzRender::GzRender(GzRenderClass renderClass, GzDisplay *display)
	: Xsp_(MATRIX_EYE)
{

}


GzRender::~GzRender()
{
}


int GzRender::BeginRender()
{
	// Build Xpi, Xiw, Xsp matrices
	buildMatrices();
	// Push those matrices into the stack

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


void GzRender::PushMatrix(GzMatrix matrix)
{
	
}


int GzRender::PutCamera(GzCamera camera)
{
	return 0;
}


void GzRender::PopMatrix()
{
	if (Ximage_.size() > 0)
	{
		Ximage_.pop();
		Xnorm_.pop();
	}
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
			GzPoint point(x, y);
			if (!triangle.CheckPointOnEdge(point) &&
				!triangle.CheckPointInside(point))
				continue;
			float screenz = triangle.InterpolateZ(point);
			GzPixel pixel = this->display_->GetPixel(x, y);
			if (screenz < 0 || screenz > pixel.z) continue;
			this->display_->PutPixel(x, y, pixel);
		}
		
	}
	return false;
}


void GzRender::buildMatrices()
{
	// First build the Xpi matrix
	float fov = camera_.GetFov();
	float d = 1 / tan(fov / 2);
	GzMatrix Xpi(MATRIX_EYE);
	Xpi.Set(3, 2, 1 / d);
	camera_.SetXpiMatrix(Xpi);

	// Then build the Xiw matrix
	GzVector camZ = camera_.GetLookDirection();
	camZ.Normalize();

	GzVector world_up = camera_.GetWorldUp();
	GzVector cam_up = world_up - (world_up * camZ) * camZ;
	GzVector camY = cam_up;
	GzVector camX = camY ^ camZ;
	GzVector cam_pos = camera_.GetPosition();
	
	GzMatrix Xiw(MATRIX_EYE);
	camX[3] = -(camX * cam_pos);
	Xiw.SetRow(0, camX);
	camY[3] = -(camY * cam_pos);
	Xiw.SetRow(1, camY);
	camZ[3] = -(camZ * cam_pos);
	Xiw.SetRow(2, camZ);
	camera_.SetXiwMatrix(Xiw);

	// Finally build the Xsp matrix
	//float fov = render->camera.FOV / 180 * PI;
	//float d = 1 / tan(fov / 2);

	//float x = render->display->xres / 2.0;
	//float y = render->display->yres / 2.0;
	//float z = INT_MAX / d;
	//GzMatrix Xsp;
	//Xsp[0][0] = x;	Xsp[0][1] = 0;	Xsp[0][2] = 0;	Xsp[0][3] = x;
	//Xsp[1][0] = 0;	Xsp[1][1] = -y;	Xsp[1][2] = 0;	Xsp[1][3] = y;
	//Xsp[2][0] = 0;	Xsp[2][1] = 0;	Xsp[2][2] = z;	Xsp[2][3] = 0;
	//Xsp[3][0] = 0;	Xsp[3][1] = 0;	Xsp[3][2] = 0;	Xsp[3][3] = 1;

	GzSize scr_res = display_.GetResolution();
	float x = scr_res.X / 2.0;
	float y = scr_res.Y / 2.0;
	float z = INT_MAX / d;
	Xsp_.Set(0, 0, x);
	Xsp_.Set(0, 3, x);
	Xsp_.Set(1, 1, y);
	Xsp_.Set(1, 3, y);
	Xsp_.Set(2, 2, 2);
}
