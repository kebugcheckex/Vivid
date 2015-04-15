/*
	File name:		GzLight.cpp
	Description:	Implementation of the GzLight class.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-04-03

	Contributors:	Xinyu Chen
*/

#include "stdafx.h"
#include "GzLight.h"

GzLight::GzLight()
{
	is_on_ = true;
}

GzLight::GzLight(GzColor& color, GzVector& direction)
{
	color_ = color;
	direction_ = direction;
}

GzColor GzLight::GetColor()
{
	if (is_on_)
		return color_;
	else
		return GzColor(0, 0, 0);
}

GzVector GzLight::GetDirection()
{
	return direction_;
}

void GzLight::SetColor(GzColor& color)
{
	color_ = color;
}

void GzLight::SetColor(float r, float g, float b, float a = 1.0)
{
	color_.Red = r;
	color_.Green = g;
	color_.Blue = b;
	color_.Alpha = a;
}

void GzLight::SetDirection(GzVector& direction)
{
	direction_ = direction;
}

void GzLight::SetDirection(float x, float y, float z)
{
	direction_.X = x;
	direction_.Y = y;
	direction_.Z = z;
}

void GzLight::TurnOff()
{
	is_on_ = false;
}

void GzLight::TurnOn()
{
	is_on_ = true;
}