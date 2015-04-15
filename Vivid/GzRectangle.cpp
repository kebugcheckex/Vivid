#include "stdafx.h"
#include "GzRectangle.h"


GzRectangle::GzRectangle()
	: Left(0.0), Top(0.0), Right(0.0), Bottom(0.0)
{}


GzRectangle::GzRectangle(float l, float t, float r, float b)
	: Left(l), Top(t), Right(r), Bottom(b)
{}

GzRectangle::GzRectangle(GzPoint& topleft, GzPoint& bottomright)
{
	Left = topleft.X;
	Top = topleft.Y;
	Right = bottomright.X;
	Bottom = bottomright.Y;
}