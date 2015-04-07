#include "stdafx.h"
#include "GzRectangle.h"


GzRectangle::GzRectangle()
	: left(0.0), top(0.0), right(0.0), bottom(0.0)
{
}


GzRectangle::GzRectangle(float l, float t, float r, float b)
	: left(l), top(t), right(r), bottom(b)
{
}
