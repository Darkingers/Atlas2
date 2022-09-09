module;

#include "../../../Macros/Macros.h"

export module AtlasGeometry2D:Ellipse;

export namespace Atlas::Geometry
{
	template<typename NumberType>
	class DLLApi Circle
	{
		public: Vecotr2D<NumberType> Centre;

	};
}