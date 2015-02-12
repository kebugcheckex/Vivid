#pragma once
#include "GzDisplay.h"

/* Camera defaults */
#define	DEFAULT_FOV		35.0
#define	DEFAULT_IM_Z	(-10.0)  /* world coords for image plane origin */
#define	DEFAULT_IM_Y	(5.0)    /* default look-at point = 0,0,0 */
#define	DEFAULT_IM_X	(-10.0)

#define	DEFAULT_AMBIENT	{0.1, 0.1, 0.1}
#define	DEFAULT_DIFFUSE	{0.7, 0.6, 0.5}
#define	DEFAULT_SPECULAR	{0.2, 0.3, 0.4}
#define	DEFAULT_SPEC		32

#define	MATLEVELS	100		/* how many matrix pushes allowed */
#define	MAX_LIGHTS	10		/* how many lights allowed */

/* Dummy definition : change it later */
#ifndef GzLight
#define GzLight		GzPointer
#endif

#ifndef GzTexture
#define GzTexture	GzPointer
#endif

class GzRender
{
public:
	GzRender(GzRenderClass renderClass, GzDisplay *display);
	~GzRender();
private:
	GzRenderClass m_renderClass;
	GzDisplay	m_pDisplay;
	bool		   m_isOpen;
	GzCamera		m_Camera;
	short		    matlevel;	        /* top of stack - current xform */
	GzMatrix		Ximage[MATLEVELS];	/* stack of xforms (Xsm) */
	GzMatrix		Xnorm[MATLEVELS];	/* xforms for norms (Xim) */
	GzMatrix		Xsp;		        /* NDC to screen (pers-to-screen) */
	GzColor		flatcolor;          /* color state for flat shaded triangles */
	int			interp_mode;
	int			numlights;
	GzLight		lights[MAX_LIGHTS];
	GzLight		ambientlight;
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
};

