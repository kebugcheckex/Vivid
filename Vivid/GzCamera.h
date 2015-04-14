/*
	File name:		GzCamera.h
	Description:	Definition of the GzCamera class. This class implements
					the camera data structure.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-05

	Contributors:	Xinyu Chen
*/
#pragma once
#include "GzMatrix.h"
#include "GzPoint.h"
#include "GzVector.h"

class GzCamera
{
public:
	GzCamera();

	/* Get and set FOV */
	float GetFov();
	void SetFov(float fov);

	/* Get the world up direction */
	GzVector GetWorldUp();
	/* Set the world up direction */
	void SetWorldUpDirection(GzVector worldup);

	/* Returns the vector from camera position to look-at position */
	GzVector GetLookDirection();

	/* Set the look at posision */
	void LookAt(GzPoint position);

	/* Return the camera position vector */
	GzVector GetPosition();

	/* Change the camera position */
	void MoveTo(GzPoint position);

	/* Set the transform matrices */
	void SetXpiMatrix(const GzMatrix& xpi);
	void SetXiwMatrix(const GzMatrix& xiw);
private:
	/* Horizontal field of view */
	float m_fov;
	/* Position of the camera space origin */
	GzPoint m_position;
	/* Position that the camera is looking at */
	GzPoint m_lookAt;
	/* Vector specifying the up direction */
	GzVector m_worldUp;
	/* Transform matrix from world space to camera space */
	GzMatrix m_Xiw;
	/* Transform matrix for perspective projection */
	GzMatrix m_Xpi;
};

