#pragma once
#include "GzPoint.h"
class GzEdge
{
public:
	GzEdge();
	GzEdge(GzPoint& begin, GzPoint& end);
	bool Colored;
private:
	GzPoint begin_, end_;
};

