#include "stdafx.h"
#include "Application.h"


Application::Application()
{
	display_ = new GzDisplay(RGB_DISPLAY, 256, 256);
	render_ = new GzRender(Z_BUFFER_RENDER, display_);
}


Application::~Application()
{
	delete render_;
	render_ = nullptr;
	delete display_;
	display_ = nullptr;
}


void Application::Initialize()
{
	
	GzToken		nameListShader[9]; 	    /* shader attribute names */
	GzPointer   valueListShader[9];		/* shader attribute pointers */
	GzToken     nameListLights[10];		/* light info */
	GzPointer   valueListLights[10];	
	GzToken		nameListAntiAliasing[2];	/* anti aliasing attribute names */
	GzPointer	valueListAntiAliasing[2];	/* anti aliasing attribute pointers */
	int			shaderType, interpStyle;
	float		specpower;
	int			status;

	/* Translation matrix */
	GzMatrix scale(MATRIX_EYE);
	scale *= 3.25;
	scale.Set(3, 2, -3.25);
	scale.Set(3, 3, 3.5);
	scale.Set(3, 4, 1.0);

	GzMatrix rotateX(ROTATE_X, 45);
	GzMatrix rotateY(ROTATE_Y, 30);

	GzCamera camera;
	camera.MoveTo(-3, -25, -4);	// TODO Implement this method
	camera.LookAt(7.8, -0.7, 6.5);
	GzVector worldup(-0.2, 1.0, 0.0);
	camera.SetWorldUpDirection(worldup);
	camera.SetFov(63.7);

	GzColor light_color(0.3, 0.3, 0.3);
	GzVector light_direction(0.0, 0.0, 0.0);
	GzLight ambient_light(light_color, light_direction);

	light_color = GzColor(0.5, 0.5, 0.9);
	light_direction = GzVector(-0.7071, 0.7071, 0);
	GzLight light1(light_color, light_direction);

	light_color = GzColor(0.9, 0.2, 0.3);
	light_direction = GzVector(0, -0.7071, -0.7071);
	GzLight light2(light_color, light_direction);

	light_color = GzColor(0.2, 0.7, 0.3);
	light_direction = GzVector(0.7071, 0.0, -0.7071);
	GzLight light3(light_color, light_direction);

	GzColor specularCoefficient{ 0.3, 0.3, 0.3 };
	GzColor ambientCoefficient{ 0.1, 0.1, 0.1 };
	GzColor diffuseCoefficient{ 0.7, 0.7, 0.7 };

	/*
	renderer is ready for frame --- define lights and shader at start of frame
	*/
	for (int i = 0; i < AAKERNEL_SIZE; i++)
	{
		/*
		* Tokens associated with light parameters
		*/
		nameListLights[0] = GZ_DIRECTIONAL_LIGHT;
		valueListLights[0] = (GzPointer)&light1;
		nameListLights[1] = GZ_DIRECTIONAL_LIGHT;
		valueListLights[1] = (GzPointer)&light2;
		nameListLights[2] = GZ_DIRECTIONAL_LIGHT;
		valueListLights[2] = (GzPointer)&light3;
		status |= GzPutAttribute(m_pRender[i], 3, nameListLights, valueListLights);
		nameListLights[0] = GZ_AMBIENT_LIGHT;
		valueListLights[0] = (GzPointer)&ambientlight;
		status |= GzPutAttribute(m_pRender[i], 1, nameListLights, valueListLights);

		/*
		* Tokens associated with shading
		*/
		nameListShader[0] = GZ_DIFFUSE_COEFFICIENT;
		valueListShader[0] = (GzPointer)diffuseCoefficient;

		/*
		* Select either GZ_COLOR or GZ_NORMALS as interpolation mode
		*/
		nameListShader[1] = GZ_INTERPOLATE;
		interpStyle = GZ_NORMALS;         /* Phong shading */
		valueListShader[1] = (GzPointer)&interpStyle;

		nameListShader[2] = GZ_AMBIENT_COEFFICIENT;
		valueListShader[2] = (GzPointer)ambientCoefficient;
		nameListShader[3] = GZ_SPECULAR_COEFFICIENT;
		valueListShader[3] = (GzPointer)specularCoefficient;
		nameListShader[4] = GZ_DISTRIBUTION_COEFFICIENT;
		specpower = 32;
		valueListShader[4] = (GzPointer)&specpower;

		nameListShader[5] = GZ_TEXTURE_MAP;
#if 0   /* set up null texture function or valid pointer */
		valueListShader[5] = (GzPointer)0;
#else
		valueListShader[5] = (GzPointer)(tex_fun);	/* or use ptex_fun */
#endif
		status |= GzPutAttribute(m_pRender[i], 6, nameListShader, valueListShader);

		status |= GzPushMatrix(m_pRender[i], scale);
		status |= GzPushMatrix(m_pRender[i], rotateY);
		status |= GzPushMatrix(m_pRender[i], rotateX);

		nameListAntiAliasing[0] = GZ_AASHIFTX;
		valueListAntiAliasing[0] = (GzPointer)&(AAFilter[i][X]);
		nameListAntiAliasing[1] = GZ_AASHIFTX;
		valueListAntiAliasing[1] = (GzPointer)&(AAFilter[i][Y]);
		status |= GzPutAttribute(m_pRender[i], 2, nameListAntiAliasing, valueListAntiAliasing);
	}

	if (status) exit(GZ_FAILURE);

	if (status)
		return(GZ_FAILURE);
	else
		return(GZ_SUCCESS);
}
