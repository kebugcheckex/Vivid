/*
	File name:		GzCamera.h
	Description:	Implemetation of the GzCamera class.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-05

	Contributors:	Xinyu Chen
*/

#include "stdafx.h"
#include "GzCamera.h"


GzCamera::GzCamera()
{
	m_position.X = -10.0;
	m_position.Y = 5.0;
	m_position.Z = -10.0;

	m_lookAt.X = 0;
	m_lookAt.Y = 0;
	m_lookAt.Z = 0;

	m_fov = 35.0;

	m_worldUp.X = 0;
	m_worldUp.Y = 1;
	m_worldUp.Z = 0;
}

float GzCamera::GetFov() {
	return m_fov;
}

void GzCamera::SetFov(float fov) {
	m_fov = fov;
}

GzVector GzCamera::GetWorldUp() {
	return m_worldUp;
}

void GzCamera::SetWorldUpDirection(GzVector worldup) {
	m_worldUp = worldup;
}

void GzCamera::LookAt(GzPoint lookat) {
	m_lookAt = lookat;
}

GzVector GzCamera::GetPosition() {
	GzVector vector;
	vector.X = m_position.X;
	vector.Y = m_position.Y;
	vector.Z = m_position.Z;
	return vector;
}

void GzCamera::MoveTo(GzPoint position) {
	m_position.X = position.X;
	m_position.Y = position.Y;
	m_position.Z = position.Z;
}

void GzCamera::SetXpiMatrix(const GzMatrix& xpi) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_Xpi.Set(i, j, xpi.Get(i, j));
		}
	}
}

void GzCamera::SetXiwMatrix(const GzMatrix& xiw) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_Xiw.Set(i, j, xiw.Get(i, j));
		}
	}
}