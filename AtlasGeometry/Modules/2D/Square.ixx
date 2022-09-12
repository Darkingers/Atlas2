module;

#include "../../../Macros/Macros.h"

export module AtlasGeometry2D:Square;
import :Vector2D;

export namespace Atlas::Geometry
{
	template<typename NumberType>
	class DLLApi Square
	{
		public: Vector2D<NumberType> BottomLeft;
		public: NumberType Width;
	};
}