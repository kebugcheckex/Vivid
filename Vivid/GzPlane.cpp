#include "stdafx.h"
#include "GzPlane.h"


GzPlane::GzPlane()
	: A(0.0), B(0.0), C(0.0), D(0.0)
{}

GzPlane::GzPlane(float a, float b, float c, float d)
	: A(a), B(b), C(c), D(d)
{}

GzPlane::GzPlane(const GzPoint& pa, const GzPoint& pb, const GzPoint& pc)
{
	GzVector va(pc, pb);
	GzVector vb(pb, pa);
	GzVector normal = vb^vb;
	A = normal.X;
	B = normal.Y;
	C = normal.Z;
	D = -A*pc.X - B*pc.Y - C*pc.Z;
}

GzPlane::GzPlane(const GzVector& normal, const GzPoint& pt)
{
	A = normal.X;
	B = normal.Y;
	C = normal.Z;
	D = -A*pt.X - B*pt.Y - C*pt.Z;
}

float GzPlane::GetInterpolatedZ(float x, float y)
{
	return -(A*x + B*y + D) / C;
}