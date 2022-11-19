module;

#include <math.h>
#include "../../../../Macros/Macros.h"

export module AtlasMath:Cos;

import AtlasConfiguration;

import :Factorial;

export namespace Atlas
{
	//A Cos calulator, using minimax polynominal approximation
	template<typename NumberType>
	class DLLApi Cos
	{
		public:
		constexpr static inline auto Calculate( NumberType number )
			noexcept( noexcept( std::cos( number ) ) )
		{
			return std::cos( number );
		}
	};

	template<typename NumberType>
	class DLLApi Cos
	{
		private: template<unsigned int Level>
		constexpr static inline auto CosImpl( NumberType sum , const NumberType power , const NumberType x2 )
			noexcept
		{
			constexpr NumberType factorial = Factorial<NumberType>::Calculate( Level * 2 );

			if constexpr ( Level > 0 )
			{
				if constexpr ( Level % 2 == 0 )
				{
					sum += power / factorial;
				}
				else
				{
					sum -= power / factorial;
				}
			}

			if constexpr ( Level < Configuration::CosPrecision )
			{
				return CosImpl<NumberType , Level + 1>( sum , power * x2 , x2 );
			}
			else
			{
				return sum;
			}
		}

		public:
		constexpr static inline auto Calculate( NumberType number )
			noexcept
		{
			return CosImpl<0>( 1 , 1 , number * number );
		}
	};

	template<>
	class DLLApi Cos<double>
	{
		public:
		constexpr static inline auto Calculate( double number )
			noexcept( noexcept( std::cosf( number ) ) )
		{
			return std::cos( number );
		}
	};

	template<>
	class DLLApi Cos<float>
	{
		public:
		constexpr static inline auto Calculate( float number )
			noexcept( noexcept( std::cosf( number ) ) )
		{
			return std::cosf( number );
		}
	};

	template<>
	class DLLApi Cos<long double>
	{
		public:
		constexpr static inline auto Calculate( long double number )
			noexcept( noexcept( std::cosl( number ) ) )
		{
			return std::cosl( number );
		}
	};

	template<>
	class DLLApi Cos<int>
	{
		public:
		constexpr static inline auto Calculate( int number )
			noexcept( noexcept( std::cos( number ) ) )
		{
			return std::cos( static_cast<double>( number ) );
		}
	};

	template<>
	class DLLApi Cos<long>
	{
		public:
		constexpr static inline auto Calculate( long number )
			noexcept( noexcept( std::cosl( number ) ) )
		{
			return std::cos( static_cast<double>( number ) );
		}
	};

	template<>
	class DLLApi Cos<long long>
	{
		public:
		constexpr static inline auto Calculate( long long number )
			noexcept( noexcept( std::cos( static_cast<double>( number ) ) ) )
		{
			return std::cos( static_cast<double>( number ) );
		}
	};

	template<>
	class DLLApi Cos<unsigned int>
	{
		public:
		constexpr static inline auto Calculate( unsigned int number )
			noexcept( noexcept( std::cos( static_cast<double>( number ) ) ) )
		{
			return std::cos( static_cast<double>( number ) );
		}
	};
	
	template<>
	class DLLApi Cos<unsigned long>
	{
		public:
		constexpr static inline auto Calculate( unsigned long number )
			noexcept( noexcept( std::cos( static_cast<double>( number ) ) ) )
		{
			return std::cos( static_cast<double>( number ) );
		}
	};

	template<>
	class DLLApi Cos<unsigned long long>
	{
		public:
		constexpr static inline auto Calculate( unsigned long long number )
			noexcept( noexcept( std::cos( static_cast<double>( number ) ) ) )
		{
			return std::cos( static_cast<double>( number ) );
		}
	};

	template<>
	class DLLApi Cos<short>
	{
		public:
		constexpr static inline auto Calculate( short number )
			noexcept( noexcept( std::cos( static_cast<double>( number ) ) ) )
		{
			return std::cos( static_cast<double>( number ) );
		}
	};
	
	template<>
	class DLLApi Cos<unsigned short>
	{
		public:
		constexpr static inline auto Calculate( unsigned short number )
			noexcept( noexcept( std::cos( static_cast<double>( number ) ) ) )
		{
			return std::cos( static_cast<double>( number ) );
		}
	};
}