#pragma once
#include "GzRender.h"
class Application
{
public:
	Application();
	~Application();
	void Initialize();
private:
	GzDisplay *display_;
	GzRender *render_;
};

