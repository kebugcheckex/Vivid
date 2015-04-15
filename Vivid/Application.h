#pragma once
#include "GzRender.h"
class Application
{
public:
	Application();
	~Application();

	GzDisplay* GetDisplay();
	GzRender* GetRender();
	char* GetFrameBuffer();
	void Initialize();
	void Render();
	int Width;
	int Height;
	
private:
	GzDisplay *display_;
	GzRender *render_;
	char *frame_buffer_;
};

