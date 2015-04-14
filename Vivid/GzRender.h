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

enum RenderClass { Z_BUFFER_RENDER };

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
	GzRender(RenderClass renderClass, GzDisplay *display);
	~GzRender();
	static const int MAX_LIGHTS = 10;
	static const int MAX_MAT_LEVEL = 100;
private:
	RenderClass render_class_;
	GzDisplay	*display_;
	bool		open_;
	GzCamera	camera_;
	//short		   matlevel;	        /* top of stack - current xform */
	std::stack<GzMatrix> Ximage_;		/* stack of xforms (Xsm) */
	std::stack<GzMatrix> Xnorm_;	/* xforms for norms (Xim) */
	GzMatrix		Xsp_;		        /* NDC to screen (pers-to-screen) */
	GzColor		flatcolor_;				/* color state for flat shaded triangles */
	int			interpmode_;
	std::vector<GzLight> lights_;
	GzLight		ambientlight_;
	GzColor		Ka, Kd, Ks;
	float		    spec_;		/* specular power */
	GzTexture		tex_fun;    /* tex_fun(float u, float v, GzColor color) */
	float aa_shiftx_;
	float aa_shifty_;
public:
	int BeginRender();
	int PutAttribute(int numAtrributes, GzToken * nameList, GzPointer * valueList);
	int PutTriangle(int numParts, GzToken * nameList, GzPointer * valueList);
	void PushMatrix(GzMatrix matrix);
	int PutCamera(GzCamera camera);
	void PopMatrix();
private:
	bool rasterize(GzTriangle& triangle);
	void buildMatrices();
};

