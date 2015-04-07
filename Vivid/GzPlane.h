#pragma once
#include "GzVector.h"
class GzPlane
{
public:
	GzPlane();
	/* Construct a plane by specifying the four coefficients
		in the standard plane equation. */
	GzPlane(float a, float b, float c, float d);
	/* Construct a plane by specifying three non-collinear
		points in the space. */
	GzPlane(const GzPoint& pa, const GzPoint& pb, const GzPoint& pc);
	/* Construct a plane by specifying its normal vector
		and a point on the plane. */
	GzPlane(const GzVector& normal, const GzPoint& pt);
	
};

