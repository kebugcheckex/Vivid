/*	TODO
	This is the core render class. I suggest implement this at last
*/



#include "stdafx.h"
#include "GzLine.h"
#include "GzRender.h"

using namespace std;

GzRender::GzRender(RenderClass render_class, GzDisplay *display)
	: Xsp_(MATRIX_EYE), open_(false)
{
	// Currently the only supported render is Z buffer render, so the following
	// line is kind of useless
	if (render_class = Z_BUFFER_RENDER) render_class = render_class_;
	display_ = display;
	camera_.MoveTo(GzPoint(-10.0, 5.0, -10.0));	// Default camera location
	camera_.LookAt(GzPoint(0.0, 0.0, 0.0));		// Default look at position
	camera_.SetWorldUpDirection(GzVector(0.0, 1.0, 0.0));	// Default world up
	camera_.SetFov(35.0);
	ambientlight_.SetColor(GzColor(1.0, 0.5, 1.0));
	spec_ = 32;	// Default specular power
	aa_shiftx_ = aa_shifty_ = 0.0;
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
		{
			GzColor *color = static_cast<GzColor*>(values[i]);
			Ka = *color;
			break;
		}
		case GZ_DIFFUSE_COEFFICIENT:
		{
			GzColor *color = static_cast<GzColor*>(values[i]);
			Kd = *color;
			break;
		}
		case GZ_SPECULAR_COEFFICIENT:
		{
			GzColor *color = static_cast<GzColor*>(values[i]);
			Ks = *color;
			break;
		}
		default:
			// Throw some exceptions
			break;
		}
	}
	return 0;
}


int GzRender::PutTriangle(int num, GzToken *names, GzPointer *values)
{
	GzVector *modelVerts = nullptr;
	GzVector *modelNormals = nullptr;
	GzVector screenVerts[3];
	GzVector cameraVerts[3];
	GzVector cameraNormals[3];
	GzTextureIndex textureIndex;
	for (int i = 0; i < num; i++)
	{
		switch (names[i])
		{
		case GZ_NULL_TOKEN:
			break;
		case GZ_POSITION:
		{	/*	When we get three vertices of a triangle, they are in model space.
				First thing we need to do is to transform it to the screen space using
				the top matrix in the matrices stack. And then check whether it is
				behind the screen, or whether it is inside the screen.
			*/
			modelVerts = static_cast<GzVector*>(values[i]);
			bool behind_camera = false;
			for (int j = 0; j < 3; j++)
			{
				GzMatrix T = Ximage_.top();
				screenVerts[j] = T * modelVerts[j];
				if (screenVerts[j][2] < 0)
				{
					behind_camera = true;
					break;
				}
			}
			if (behind_camera) continue;
			if (!isTriangleInScreen(screenVerts)) continue;
			break;
		}
		case GZ_NORMAL:
			modelNormals = static_cast<GzVector*>(values[i]);
			break;
		case GZ_TEXTURE_INDEX:
		{
			float *ind = static_cast<float*>(values[i]);
			textureIndex.x = ind[0]; textureIndex.y = ind[1];
			break;
		}
		default:
			break;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		cameraVerts[i] = Ximage_.top() * modelVerts[i];
		cameraNormals[i] = Xnorm_.top() * modelNormals[i];
	}
	GzTriangle triangle(screenVerts, modelVerts, modelNormals, textureIndex);
	rasterize(triangle);
	return 0;
}


void GzRender::PushMatrix(GzMatrix matrix)
{
	if (Ximage_.size() == 0)
		Ximage_.push(matrix);
	else
		Ximage_.push(Ximage_.top() * matrix);

}


int GzRender::PutCamera(GzCamera camera)
{
	camera_ = camera;
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
	GzSize scr_res = display_->GetResolution();
	float x = scr_res.X / 2.0;
	float y = scr_res.Y / 2.0;
	float z = INT_MAX / d;
	Xsp_.Set(0, 0, x);
	Xsp_.Set(0, 3, x);
	Xsp_.Set(1, 1, y);
	Xsp_.Set(1, 3, y);
	Xsp_.Set(2, 2, 2);
}
