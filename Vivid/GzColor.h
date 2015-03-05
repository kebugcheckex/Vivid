#pragma once
class GzColor
{
public:
	// Constructors
	GzColor();
	GzColor(float r, float g, float b, float a);
	// Destructor
	~GzColor();
public:
	// Public member variables
	float Red;
	float Green;
	float Blue;
	float Alpha;
};

