/*
	File name:		GzLight.h
	Description:	Definition of the GzLight class. This class implements the
					light object in the render.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-04-03

	Contributors:	Xinyu Chen
*/
#pragma once

#include "GzColor.h"
#include "GzDef.h"
#include "GzVector.h"

class GzLight
{
public:
	GzLight();
	/* Initialize specifying color and direction */
	GzLight(GzColor& color, GzVector& direction);
	GzColor GetColor();
	GzVector GetDirection();
	void SetColor(GzColor& color);
	void SetColor(float r, float g, float b, float a = 1.0);
	void SetDirection(GzVector& direction);
	void SetDirection(float x, float y, float z);
	void TurnOff();
	void TurnOn();
private:
	GzColor color_;
	GzVector direction_;
	bool is_on_;
};

