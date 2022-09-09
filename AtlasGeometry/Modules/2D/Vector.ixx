module;

#include "../../../Macros/Macros.h"

export module AtlasGeometry2D:Vector;
import AtlasValidation;
import AtlasMathFunctions;
import AtlasConfiguration;

export namespace Atlas::Geometry
{
	template<typename NumberType>
	class DLLApi Vector2D
	{
		private: using VectorType = Vector2D<NumberType>;


		public: NumberType X;
		public: NumberType Y;


		public:
		Vector2D( ) noexcept
		{}
		
		public:
		Vector2D( const NumberType& x, const NumberType& y ) noexcept:
			X(x ),
			Y(y )
		{}

		public:
		NumberType Length( )const noexcept
		{
			return Math::SquareRoot( X * X + Y * Y );
		}

		public:
		VectorType& Normalise( )
		{
			const auto div = 1 / Length( );
			X *= div;
			Y *= div;

			return *this;
		}

		public:
		VectorType& Rotate( double angle ) noexcept
		{
			const double radian = Math::AngleToRadian( angle );
			const auto cos = Math::Cos( radian );
			const auto sin = Math::Sin( radian );

			NumberType px = X * cos - Y * sin;
			NumberType py = X * sin + Y * cos;

			X = px;
			Y = py;

			return *this;
		}

		public:
		VectorType& Rotate(const VectorType& pivot, double angle ) noexcept
		{
			X -= pivot.X;
			Y -= pivot.Y;

			VectorType::Rotate( angle );

			X += pivot.X;
			Y += pivot.Y;

			return *this;
		}

		public:
		bool operator==( const VectorType& vector ) const noexcept
		{
			return X == vector.X && Y == vector.Y;
		}

		public:
		bool operator!=( const VectorType& vector ) const noexcept
		{
			return !( *this ) == vector;
		}

		public:
		VectorType& operator=( const VectorType& vector ) const noexcept
		{
			X = vector.X;
			Y = vector.Y;

			return *this;
		}

		public:
		VectorType& operator+=( const VectorType& vector ) const noexcept
		{
			X += vector.X;
			Y += vector.Y;

			return *this;
		}

		public:
		VectorType& operator-=( const VectorType& vector ) const noexcept
		{
			X -= vector.X;
			Y -= vector.Y;

			return *this;
		}

		public:
		VectorType operator+( const VectorType& vector ) const noexcept
		{
			return VectorType( X + vector.X , Y + vector.Y );
		}

		public:
		VectorType operator-( const VectorType& vector ) const noexcept
		{
			return VectorType( X - vector.X , Y - vector.Y );
		}
	};
}