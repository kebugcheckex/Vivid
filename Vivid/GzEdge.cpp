#include "stdafx.h"
#include "GzEdge.h"

GzEdge::GzEdge()
{}

GzEdge::GzEdge(GzPoint& begin, GzPoint& end)
{
	begin_ = begin;
	end_ = end;
}

