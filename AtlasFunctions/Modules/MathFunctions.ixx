module;

#include <iterator>
#include <algorithm>
#include "../../Macros/Macros.h"

export module AtlasMathFunctions;
import AtlasDefinitions;
import AtlasConfiguration;
import AtlasValidation;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename NumberType>
		class Math
		{
			private: template<typename... Args>
			constexpr static inline auto Minimum( const NumberType& previousMin , const NumberType& current , const Args&... arguments )
			{
				auto min = previousMin < current ? previousMin : current;

				if constexpr ( sizeof...( arguments ) > 0 )
				{
					return MathFunctions<NumberType>::Minimum( min , std::forward<const Args&>( arguments )... );
				}
				else
				{
					return min;
				}
			}

			private: template<typename... Args>
			constexpr static inline auto Maximum( const NumberType& previousMax , const NumberType& current , const Args&... arguments )
			{
				auto max = previousMax > current ? previousMax : current;

				if constexpr ( sizeof...( arguments ) > 0 )
				{
					return MathFunctions<NumberType>::Maximum( max , std::forward<const Args&>( arguments )... );
				}
				else
				{
					return max;
				}
			}

			public:
			constexpr static inline auto SquareRoot( const NumberType& data )
			{
				return sqrt( data );
			}
		
			public:
			constexpr static inline auto Pow( const NumberType& data , const NumberType& exponental )
			{
				return pow( data , exponental );
			}
		
			public: 
			constexpr static inline auto Cos( const NumberType& data )
			{
				return cos( data );
			}

			public:
			constexpr static inline auto ACos( const NumberType& data )
			{
				return acos( data );
			}

			public:
			constexpr static inline auto Sin( const NumberType& data )
			{
				return sin( data );
			}

			public:
			constexpr static inline auto ASin( const NumberType& data )
			{
				return asin( data );
			}
		};
	}

	class DLLApi Math
	{
		public: constexpr static double PI = 3.14;

		public: template<typename... Args>
		constexpr static inline auto Maximum(const Args&... arguments )
		{
			static_assert( sizeof...( arguments ) > 0 , "At least one element is required!" );

			return Implementation::Math<Deduce::IndexedArgumentType<0 , Args...>>::Maximum( std::forward<const Args&>( arguments )... );
		}
			   
		public: template<typename... Args>
		constexpr static inline auto Minimum( const Args&... arguments )
		{
			static_assert( sizeof...( arguments ) > 0 , "At least one element is required!" );

			return Implementation::Math<Deduce::IndexedArgumentType<0 , Args...>>::Minimum( std::forward<const Args&>( arguments )... );
		}

		public: template<typename NumberType>
		constexpr static inline auto SquareRoot( const NumberType& data )
		{
			Validate::IsPositive( data );

			return Implementation::Math<NumberType>::SquareRoot( data );
		}

		public: template<typename NumberType>
		constexpr static inline auto Pow( const NumberType& data, const NumberType& exponental )
		{
			return Implementation::Math<NumberType>::Pow( data, exponental );
		}

		public: template<typename NumberType>
		constexpr static inline auto Cos( const NumberType& data )
		{
			return Implementation::Math<NumberType>::Cos( data );
		}
		
		public: template<typename NumberType>
		constexpr static inline auto ACos( const NumberType& data )
		{
			return Implementation::Math<NumberType>::ACos( data );
		}
		
		public: template<typename NumberType>
		constexpr static inline auto Sin( const NumberType& data )
		{
			return Implementation::Math<NumberType>::Sin( data );
		}
		
		public: template<typename NumberType>
		constexpr static inline auto ASin( const NumberType& data )
		{
			return Implementation::Math<NumberType>::ASin( data );
		}

		public: template<typename NumberType>
		constexpr static inline auto AngleToRadian( const NumberType& angle )
		{
			return 2 * PI * ( angle / 360 );
		}
		public: template<typename NumberType>
		constexpr static inline auto RadianToAngle( const NumberType& radian )
		{
			return radian * 360 / ( 2 * PI );
		}
	};
}