#include "stdafx.h"

/*
* universal constants
*/
#define GZ_SUCCESS      0
#define GZ_FAILURE      1

/*
* display classes
*/
#define GZ_RGBAZ_DISPLAY        1



/* renderer-state color values for default (flat) shading */
//#define GZ_RGB_COLOR            99	/* we use RGB color space */


#define GZ_SHADER			96	/* define the shade mode */



/* select interpolation mode of the shader (either one - not both) */
#define	GZ_COLOR			1	/* interpolate vertex color */
#define	GZ_NORMALS			2	/* interpolate normals */

/*
* As far as the application is concerned, the renderer
* and the display are of type void *.
* Naturally the rendering and display routines will define
* them however they wish.
*/

#ifndef GZDATA
#define GZDATA
typedef void    *GzPointer;
//typedef float   GzColor[3];
typedef unsigned short   GzIntensity;	/* 0 - 4095 in lower 12-bits */
//typedef float	GzMatrix[4][4];
typedef int		GzDepth;	/* z is signed for clipping */
typedef	int(*GzTexture)();	/* pointer to texture sampling method */
#endif

#define RED     0               /* array indicies for color vector */
#define GREEN   1
#define BLUE    2

#define U       0               /* array indicies for texture coords */
#define V       1

#define RGB_MAX_INTENSITY 4095

typedef enum
{
	GZ_RGB_COLOR,
	GZ_INTERPOLATE,
	GZ_AMBIENT_LIGHT,
	GZ_DIRECTIONAL_LIGHT,
	GZ_AMBIENT_COEFFICIENT,
	GZ_DIFFUSE_COEFFICIENT,
	GZ_SPECULAR_COEFFICIENT,
	GZ_DISTRIBUTION_COEFFICIENT,
	GZ_TEXTURE_MAP,
	GZ_NULL_TOKEN,
	GZ_POSITION,
	GZ_NORMAL,
	GZ_TEXTURE_INDEX
} GzToken;

typedef struct
{
	float x;
	float y;
} GzTextureIndex;