/*
	File name:		GzRender.h
	Description:	Definition of the GzRender class. This is the core class of the whole
					project. 
	Created by:		Xinyu Chen (collectchen@gmail.com)
	Created on:		2015-03-01

	Contributor:	Xinyu Chen
*/
#pragma once
#include "stdafx.h"
#include "GzCamera.h"
#include "GzColor.h"
#include "GzDisplay.h"
#include "GzLight.h"
#include "GzMatrix.h"
#include "GzRectangle.h"
#include "GzTriangle.h"
#include "GzVector.h"

/*	TODO -
	This class was converted from the C structure in the homework framework.
	It needs to be rewrite in C++ style completely.
*/
/* Camera defaults */
#define	DEFAULT_FOV		35.0
#define	DEFAULT_IM_Z	(-10.0)  /* world coords for image plane origin */
#define	DEFAULT_IM_Y	(5.0)    /* default look-at point = 0,0,0 */
#define	DEFAULT_IM_X	(-10.0)

#define	DEFAULT_AMBIENT	{0.1, 0.1, 0.1}
#define	DEFAULT_DIFFUSE	{0.7, 0.6, 0.5}
#define	DEFAULT_SPECULAR	{0.2, 0.3, 0.4}
#define	DEFAULT_SPEC		32


class GzRender
{
public:
	GzRender(GzRenderClass renderClass, GzDisplay *display);
	~GzRender();
	static const int MAX_LIGHTS = 10;
	static const int MAX_MAT_LEVEL = 100;
private:
	GzRenderClass m_renderClass;
	GzDisplay	display_;
	bool		   m_isOpen;
	GzCamera		camera_;
	short		    matlevel;	        /* top of stack - current xform */
	GzMatrix		Ximage[MAX_MAT_LEVEL];	/* stack of xforms (Xsm) */
	GzMatrix		Xnorm[MAX_MAT_LEVEL];	/* xforms for norms (Xim) */
	GzMatrix		Xsp_;		        /* NDC to screen (pers-to-screen) */
	GzColor		flatcolor_;				/* color state for flat shaded triangles */
	int			interpmode_;
	std::vector<GzLight> lights_;
	GzLight		ambientlight_;
	GzColor		Ka, Kd, Ks;
	float		    spec;		/* specular power */
	GzTexture		tex_fun;    /* tex_fun(float u, float v, GzColor color) */
public:
	int BeginRender();
	int PutAttribute(int numAtrributes, GzToken * nameList, GzPointer * valueList);
	int PutTriangle(int numParts, GzToken * nameList, GzPointer * valueList);
	int PushMatrix(GzMatrix matrix);
	int PutCamera(GzCamera camera);
	int PopMatrix();
private:
	bool rasterize(GzTriangle& triangle);
	void buildMatrices();
};

