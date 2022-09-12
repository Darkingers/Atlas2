module;

#include "../../../Macros/Macros.h"

export module AtlasGeometry2D:Triangle;
import :Vector2D;

export namespace Atlas::Geometry
{
	template<typename NumberType>
	class DLLApi Triangle
	{
		public: Vector2D<NumberType> A;
		public: Vector2D<NumberType> B;
		public: Vector2D<NumberType> C;
	};
}