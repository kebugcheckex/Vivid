/*
	File name:		GzColor.h
	Description:	Definition of the GzColor class. This class implements the
					color data structure. In this class, color are in RGB space.
					And they are represented using float numbers. Integer color
					representation is implemented in the GzPixel class.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-01
*/

#pragma once
class GzColor
{
public:
	GzColor();
	/* Construct a color specifying the red, green, blue, alpha channel. */
	GzColor(float r, float g, float b, float a);
	~GzColor();
public:
	// Public member variables
	float Red;
	float Green;
	float Blue;
	float Alpha;
};

