#include "stdafx.h"
#include "GzTriangle.h"

#undef max	// There is a macro in windows headers
#undef min

GzTriangle::GzTriangle(GzPoint& a, GzPoint& b, GzPoint& c)
{
	a_ = a;
	b_ = b;
	c_ = c;
}

float GzTriangle::GetXmax()
{
	float m = std::max(a_.x, std::max(b_.x, c_.x));
	return m;
}

float GzTriangle::GetXmin()
{
	float m = std::min(a_.x, std::min(b_.x, c_.x));
	return m;
}

float GzTriangle::GetYmax()
{
	float m = std::max(a_.y, std::max(b_.y, c_.y));
	return m;
}

float GzTriangle::GetYmin()
{
	float m = std::min(a_.y, std::min(b_.y, c_.y));
	return m;
}