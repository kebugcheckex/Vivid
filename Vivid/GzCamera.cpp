/*
	File name:		GzCamera.h
	Description:	Implemetation of the GzCamera class.
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-05

	Contributors:	Xinyu Chen
					Shuo Li
*/

#include "stdafx.h"
#include "GzCamera.h"


GzCamera::GzCamera()
{
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
	m_Xpi = xpi;
	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_Xpi.Set(i, j, xpi.Get(i, j));
		}
	}*/
}

void GzCamera::SetXiwMatrix(const GzMatrix& xiw) {
	m_Xiw = xiw;
	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_Xiw.Set(i, j, xiw.Get(i, j));
		}
	}*/
}