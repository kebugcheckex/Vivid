#include "stdafx.h"
#include "GzLine.h"


GzLine::GzLine()
{
	A = B = C = 0;
}

/*	Construct a line with two points
	Line equation: Ax + By + C = 0
	Two points (x_1, y_1) and (x_2, y_2)
	The equation is 
	\frac{y_2-y_1}{x_2-x_1}(x-x_1)=y-y_1
	This solves to
	A = y_2-y_1
	B = -(x_2-x_1)
	C = -(Ax_1+By_1)
*/
GzLine::GzLine(const GzPoint& pa, const GzPoint& pb)
{
	A = pb.Y - pa.Y;
	B = -(pb.X - pa.X);
	C = -(A * pa.X + B * pa.Y);
}

/*	Construct a line with a vector and a point
	Line equation: Ax + By + C = 0
	Given a vector \mathbf{v}=(a, b) and a point (x_0, y_0)
	The equation is
	\frac{b}{a}(x-x_0)=y-y_0
	This solves to
	A = b;
	B = -a;
	C = -(Ax_0+By_0);
*/
GzLine::GzLine(const GzVector& v, const GzPoint& p)
{
	A = v.Y;
	B = -v.X;
	C = -(A * p.X + B * p.Y);
}

/*	Check whether a point is on this line
	Substitute the point coordinate into the the line equation
*/
bool GzLine::IsOnTheLine(const GzPoint& p)
{
	return WhichSide(p);
}

/*	Check which size a point is to the line
	Substitute the point into the line equation
	Ax + By + C  > 0 -- to the left
	Ax + By + C == 0 -- on the line
	Ax + By + C  < 0 -- to the right
*/
int GzLine::WhichSide(const GzPoint& p)
{
	float val = A * p.X + B * p.Y + C;
	if (val == 0.0) return 0;	// TODO - Possible float point accuracy problem
	return val > 0.0 ? 1 : -1;
}