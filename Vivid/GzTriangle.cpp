#include "stdafx.h"
#include "GzTriangle.h"

#undef max	// There is a macro in windows headers
#undef min

GzTriangle::GzTriangle(GzVector *screenVerts, GzVector *modelVerts, GzVector *modelNormals,
	GzTextureIndex& texture)
{
	p_ = screenVerts[0];
	q_ = screenVerts[1];
	a_ = modelVerts[0];
	b_ = modelVerts[1];
	c_ = modelVerts[2];
	na_ = modelNormals[0];
	nb_ = modelNormals[1];
	nc_ = modelNormals[2];
	texture_ = texture;
	ea_ = GzEdge(a_, b_);
	eb_ = GzEdge(b_, c_);
	ec_ = GzEdge(c_, a_);
}

float GzTriangle::GetXmax()
{
	float m = std::max(a_.X, std::max(b_.X, c_.X));
	return m;
}

float GzTriangle::GetXmin()
{
	float m = std::min(a_.X, std::min(b_.X, c_.X));
	return m;
}

float GzTriangle::GetYmax()
{
	float m = std::max(a_.Y, std::max(b_.Y, c_.Y));
	return m;
}

float GzTriangle::GetYmin()
{
	float m = std::min(a_.Y, std::min(b_.Y, c_.Y));
	return m;
}

void GzTriangle::GetSortedEdges(GzEdge *edges)
{

}