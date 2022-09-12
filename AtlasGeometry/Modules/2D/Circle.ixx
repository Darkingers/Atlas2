module;

#include "../../../Macros/Macros.h"

export module AtlasGeometry2D:Circle;
import :Vector2D;

export namespace Atlas::Geometry
{
	template<typename NumberType>
	class DLLApi Circle
	{
		public: Vector2D<NumberType> Center;
		public: NumberType Radius;

	};
}