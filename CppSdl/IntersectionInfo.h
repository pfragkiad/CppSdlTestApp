#pragma once

#include "../Algebra/Algebra.h"

namespace GL
{
	class IntersectionInfo
	{
	public:
		IntersectionInfo() : Valid(false) {}
		IntersectionInfo(VD intersectionPoint,VD localNormal, VD localColor) :
			Valid(true), Point(intersectionPoint), Normal(localNormal), Color(localColor)
		{ }


		bool Valid;
		VD Point;
		VD Normal; //LocalNormal
		VD Color; //LocalColor
	};
}