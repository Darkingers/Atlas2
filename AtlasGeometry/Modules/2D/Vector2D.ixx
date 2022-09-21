module;

#include "../../../Macros/Macros.h"

export module AtlasGeometry2D:Vector2D;
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
		constexpr Vector2D( ) noexcept
		{}
		
		public:
		constexpr Vector2D( const NumberType& x, const NumberType& y ) noexcept:
			X(x ),
			Y(y )
		{}

		public:
		constexpr NumberType Length( )const noexcept
		{
			return Math::SquareRoot( X * X + Y * Y );
		}

		public:
		constexpr VectorType& Normalise( )
		{
			const auto div = 1 / Length( );
			X *= div;
			Y *= div;

			return *this;
		}

		public:
		constexpr VectorType& Rotate( double angle ) noexcept
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
		constexpr VectorType& Rotate(const VectorType& pivot, double angle ) noexcept
		{
			X -= pivot.X;
			Y -= pivot.Y;

			VectorType::Rotate( angle );

			X += pivot.X;
			Y += pivot.Y;

			return *this;
		}

		public:
		constexpr bool operator==( const VectorType& vector ) const noexcept
		{
			return X == vector.X && Y == vector.Y;
		}

		public:
		constexpr bool operator!=( const VectorType& vector ) const noexcept
		{
			return !( *this ) == vector;
		}

		public:
		constexpr VectorType& operator=( const VectorType& vector ) const noexcept
		{
			X = vector.X;
			Y = vector.Y;

			return *this;
		}

		public:
		constexpr VectorType& operator+=( const VectorType& vector ) const noexcept
		{
			X += vector.X;
			Y += vector.Y;

			return *this;
		}

		public:
		constexpr VectorType& operator-=( const VectorType& vector ) const noexcept
		{
			X -= vector.X;
			Y -= vector.Y;

			return *this;
		}

		public:
		constexpr VectorType operator+( const VectorType& vector ) const noexcept
		{
			return VectorType( X + vector.X , Y + vector.Y );
		}

		public:
		constexpr VectorType operator-( const VectorType& vector ) const noexcept
		{
			return VectorType( X - vector.X , Y - vector.Y );
		}
	};
}