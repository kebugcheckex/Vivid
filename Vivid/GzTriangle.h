#pragma once
#include "GzEdge.h"
#include "GzPoint.h"
#include "GzRectangle.h"
class GzTriangle
{
public:
	GzTriangle(GzVector *screenVerts, GzVector *modelVerts, GzVector *modelNormals,
		GzTextureIndex& texture);
	GzRectangle GetScreenBoundingBox(const GzRectangle& screenboundary);
	void GetLines(std::vector<GzLine>& lines);
	GzVector GetNormal();		/* Get triangle plane normal */
	bool CheckPointInside(const GzPoint& point);
	bool CheckPointOnEdge(const GzPoint& point);
	float InterpolateZ(const GzPoint& point);
private:
	GzPoint p_, q_;				/* Screen space vertices, 2D */
	GzPoint a_, b_, c_;			/* Model space vertices, 3D */
	GzVector na_, nb_, nc_;		/* Model space normals, 3D */
	GzTextureIndex texture_;	/* Texture Index */
	GzEdge ea_, eb_, ec;		/* Edges */
	GzEdge sea_, seb_, sec_;	/* Sorted edges */
};

