module;

#include "../../../Macros/Macros.h"

export module AtlasGeometry2D:Rectangle;
import :Vector2D;

export namespace Atlas::Geometry
{
	template<typename NumberType>
	class DLLApi Rectangle
	{
		public: Vector2D<NumberType> BottomLeft;
		public: NumberType Width;
		public: NumberType Height;
	};
}