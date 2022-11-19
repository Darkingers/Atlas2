module;

#include "../../../../Macros/Macros.h"

export module AtlasMath:Sin;

import :Factorial;

export namespace Atlas
{
	template<typename NumberType>
	class DLLApi Sin
	{
		private: template<unsigned int Level>
		constexpr static inline auto SinImpl( NumberType sum , const NumberType power , const NumberType x2 )
			noexcept
		{
			constexpr NumberType factorial = Factorial<NumberType>::Calculate( Level * 2 + 1 );

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

			if constexpr ( Level < Configuration::SinPrecision )
			{
				return SinImpl<NumberType , Level + 1>( sum , power * x2 , x2 );
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
			return SinImpl<0>( number , number , number * number );
		}
	};

	template<>
	class DLLApi Sin<double>
	{
		public:
		constexpr static inline auto Calculate( double number )
			noexcept( noexcept( std::sinf( number ) ) )
		{
			return std::sin( number );
		}
	};
	
	template<>
	class DLLApi Sin<float>
	{
		public:
		constexpr static inline auto Calculate( float number )
			noexcept( noexcept( std::sinf( number ) ) )
		{
			return std::sinf( number );
		}
	};

	template<>
	class DLLApi Sin<long double>
	{
		public:
		constexpr static inline auto Calculate( long double number )
			noexcept( noexcept( std::sinl( number ) ) )
		{
			return std::sinl( number );
		}
	};

	template<>
	class DLLApi Sin<int>
	{
		public:
		constexpr static inline auto Calculate( int number )
			noexcept( noexcept( std::sin( number ) ) )
		{
			return std::sin( number );
		}
	};

	template<>
	class DLLApi Sin<long>
	{
		public:
		constexpr static inline auto Calculate( long number )
			noexcept( noexcept( std::sin( number ) ) )
		{
			return std::sin( number );
		}
	};

	template<>
	class DLLApi Sin<long long>
	{
		public:
		constexpr static inline auto Calculate( long long number )
			noexcept( noexcept( std::sin( number ) ) )
		{
			return std::sin( number );
		}
	};

	template<>
	class DLLApi Sin<unsigned int>
	{
		public:
		constexpr static inline auto Calculate( unsigned int number )
			noexcept( noexcept( std::sin( number ) ) )
		{
			return std::sin( number );
		}
	};
	
	template<>
	class DLLApi Sin<unsigned long>
	{
		public:
		constexpr static inline auto Calculate( unsigned long number )
			noexcept( noexcept( std::sin( number ) ) )
		{
			return std::sin( number );
		}
	};
	
	template<>
	class DLLApi Sin<unsigned long long>
	{
		public:
		constexpr static inline auto Calculate( unsigned long long number )
			noexcept( noexcept( std::sin( number ) ) )
		{
			return std::sin( number );
		}
	};

	template<>
	class DLLApi Sin<short>
	{
		public:
		constexpr static inline auto Calculate( short number )
			noexcept( noexcept( std::sin( number ) ) )
		{
			return std::sin( number );
		}
	};
	
	template<>
	class DLLApi Sin<unsigned short>
	{
		public:
		constexpr static inline auto Calculate( unsigned short number )
			noexcept( noexcept( std::sin( number ) ) )
		{
			return std::sin( number );
		}
	};
}