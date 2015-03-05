/*
	File name:		GzCamera.h
	Description:	Definition of the GzCamera class. This class implements
					the camera data structure.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-05
*/
#pragma once
#include "GzMatrix.h"
#include "GzPoint.h"
#include "GzVector.h"

class GzCamera
{
public:
	GzCamera();
	~GzCamera();
private:
	/* Horizontal field of view. */
	float m_fov;
	/* Position of the camera space origin. */
	GzPoint m_position;
	/* Position that the camera is looking at. */
	GzPoint m_lookAt;
	/* Vector specifying the UP direction. */
	GzVector m_worldUp;
	/* Transform matrix from world space to camera space. */
	GzMatrix m_Xiw;
	/* Transform matrix for perspective projection. */
	GzMatrix m_Xpi;
};

