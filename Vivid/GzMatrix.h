#pragma once
#include "GzVector.h"
class GzMatrix
{
public:
	/* Default constructor */
	GzMatrix();
	/* Initialize with four column vectors */
	GzMatrix(GzVector *vectors);
	GzVector& operator [] (const int index);
	friend GzVector operator * (const GzMatrix& lhs, const GzVector& rhs);
private:
	float elements_[4][4];
};

