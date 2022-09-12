module;

#include "../../../Macros/Macros.h"

export module AtlasGeometry2D:Ellipse;
import :Vector2D;

export namespace Atlas::Geometry
{
	template<typename NumberType>
	class DLLApi Ellipse
	{
		public: Vector2D<NumberType> Center1;
		public: Vector2D<NumberType> Center2;
		public: NumberType Radius;

	};
}