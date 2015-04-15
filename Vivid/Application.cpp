#include "stdafx.h"
#include "GzDef.h"
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

GzDisplay* Application::GetDisplay()
{
	return display_;
}

GzRender* Application::GetRender()
{
	return render_;
}

char* Application::GetFrameBuffer()
{
	return frame_buffer_;
}

void Application::Initialize()
{
	
	GzToken		nameListShader[9]; 	    /* shader attribute names */
	GzPointer   valueListShader[9];		/* shader attribute pointers */
	GzToken     nameListLights[10];		/* light info */
	GzPointer   valueListLights[10];	
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

	/* Put a default camera in the render */
	GzCamera camera;
	camera.MoveTo(GzPoint(-3, -25, -4));
	camera.LookAt(GzPoint(7.8, -0.7, 6.5));
	camera.SetWorldUpDirection(GzVector(-0.2, 1.0, 0.0));
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

	nameListLights[0] = GZ_DIRECTIONAL_LIGHT;
	valueListLights[0] = (GzPointer)&light1;
	nameListLights[1] = GZ_DIRECTIONAL_LIGHT;
	valueListLights[1] = (GzPointer)&light2;
	nameListLights[2] = GZ_DIRECTIONAL_LIGHT;
	valueListLights[2] = (GzPointer)&light3;
	render_->PutAttribute(3, nameListLights, valueListLights);
	nameListLights[0] = GZ_AMBIENT_LIGHT;
	valueListLights[0] = (GzPointer)&ambient_light;
	render_->PutAttribute(1, nameListLights, valueListLights);

	nameListShader[0] = GZ_DIFFUSE_COEFFICIENT;
	nameListShader[1] = GZ_INTERPOLATE;
	interpStyle = GZ_NORMALS;         /* Phong shading */
	valueListShader[1] = (GzPointer)&interpStyle;
	valueListShader[0] = (GzPointer)&diffuseCoefficient;
	nameListShader[2] = GZ_AMBIENT_COEFFICIENT;
	valueListShader[2] = (GzPointer)&ambientCoefficient;
	nameListShader[3] = GZ_SPECULAR_COEFFICIENT;
	valueListShader[3] = (GzPointer)&specularCoefficient;
	nameListShader[4] = GZ_DISTRIBUTION_COEFFICIENT;
	specpower = 32;
	valueListShader[4] = (GzPointer)&specpower;
	/*nameListShader[5] = GZ_TEXTURE_MAP;
	valueListShader[5] = (GzPointer)(tex_fun);	 or use ptex_fun */
	render_->PutAttribute(5, nameListShader, valueListShader);

	render_->PushMatrix(scale);
	render_->PushMatrix(rotateY);
	render_->PushMatrix(rotateX);
}

void Application::Render()
{
	GzToken		nameListTriangle[3]; 	/* vertex attribute names */
	GzPointer	valueListTriangle[3]; 	/* vertex attribute pointers */
	GzVector		vertexList[3];	/* vertex position coordinates */ 
	GzVector		normalList[3];	/* vertex normals */
	GzTextureIndex  	uvList[3];		/* vertex texture map indices */ 
	char		dummy[256]; 
	int			status; 


	/* Initialize Display */
	//status |= GzInitDisplay(m_pDisplay); 
	
	/* 
	* Tokens associated with triangle vertex values 
	*/ 
	nameListTriangle[0] = GZ_POSITION; 
	nameListTriangle[1] = GZ_NORMAL; 
	nameListTriangle[2] = GZ_TEXTURE_INDEX;  

	// I/O File open
	FILE *infile;
	if( (infile  = fopen("pot4.asc" , "r" )) == NULL )
	{
         AfxMessageBox(L"The input file was not opened\n" );
		 return;
	}

	FILE *outfile;
	if( (outfile  = fopen("output.ppm" , "wb" )) == NULL )
	{
         AfxMessageBox(L"The output file was not opened\n" );
	}

	/* 
	* Walk through the list of triangles, set color 
	* and render each triangle 
	*/ 
	while( fscanf(infile, "%s", dummy) == 1) { 	/* read in tri word */
	    fscanf(infile, "%f %f %f %f %f %f %f %f", 
		&(vertexList[0][0]), &(vertexList[0][1]),  
		&(vertexList[0][2]), 
		&(normalList[0][0]), &(normalList[0][1]), 	
		&(normalList[0][2]), 
		&(uvList[0].x), &(uvList[0].y) ); 
	    fscanf(infile, "%f %f %f %f %f %f %f %f", 
		&(vertexList[1][0]), &(vertexList[1][1]), 	
		&(vertexList[1][2]), 
		&(normalList[1][0]), &(normalList[1][1]), 	
		&(normalList[1][2]), 
		&(uvList[1].x), &(uvList[1].y) ); 
	    fscanf(infile, "%f %f %f %f %f %f %f %f", 
		&(vertexList[2][0]), &(vertexList[2][1]), 	
		&(vertexList[2][2]), 
		&(normalList[2][0]), &(normalList[2][1]), 	
		&(normalList[2][2]), 
		&(uvList[2].x), &(uvList[2].y) ); 

	    /* 
	     * Set the value pointers to the first vertex of the 	
	     * triangle, then feed it to the renderer 
	     * NOTE: this sequence matches the nameList token sequence
	     */ 
	     valueListTriangle[0] = (GzPointer)vertexList; 
		 valueListTriangle[1] = (GzPointer)normalList; 
		 valueListTriangle[2] = (GzPointer)uvList; 
		 render_->PutTriangle(3, nameListTriangle, valueListTriangle); 
	} 

	display_->FlushDisplay2File("output.ppm"); 	/* write out or update display to file*/
	display_->FlushDisplay2FrameBuffer(m_pFrameBuffer);	// write out or update display to frame buffer

	/* 
	 * Close file
	 */ 

	if( fclose( infile ) )
      AfxMessageBox(L"The input file was not closed\n" );

	if( fclose( outfile ) )
      AfxMessageBox(L"The output file was not closed\n" );
}
