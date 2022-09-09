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
		template<typename DataType>
		class Math
		{
			private: template<typename... Args>
			inline static DataType Minimum( const DataType& previousMin , const DataType& current , const Args&... arguments )
			{
				DataType min = static_cast<DataType>( previousMin < current ? previousMin : current );

				if constexpr ( sizeof...( arguments ) > 0 )
				{
					return MathFunctions<DataType>::Minimum( min , std::forward<const Args&>( arguments )... );
				}
				else
				{
					return min;
				}
			}

			private: template<typename... Args>
			inline static DataType Maximum( const DataType& previousMax , const DataType& current , const Args&... arguments )
			{
				DataType max = static_cast<DataType>( previousMax > current ? previousMax : current );

				if constexpr ( sizeof...( arguments ) > 0 )
				{
					return MathFunctions<DataType>::Maximum( max , std::forward<const Args&>( arguments )... );
				}
				else
				{
					return max;
				}
			}

			public:
			inline static DataType SquareRoot( const DataType& data )
			{
				return static_cast<DataType>( sqrt( data ));
			}
		
			public:
			inline static DataType Pow( const DataType& data , const DataType& exponental )
			{
				return static_cast<DataType>( std::pow(data, exponental) );
			}
		
			public: 
			inline static DataType Cos( const DataType& data )
			{
				return cos( data );
			}

			public:
			inline static DataType ACos( const DataType& data )
			{
				return acos( data );
			}

			public:
			inline static DataType Sin( const DataType& data )
			{
				return sin( data );
			}

			public:
			inline static DataType ASin( const DataType& data )
			{
				return asin( data );
			}
		};
	}

	class DLLApi Math
	{
		public: constexpr static double PI = 3.14;

		public: template<typename... Args>
		inline static auto Maximum(const Args&... arguments )
		{
			static_assert( sizeof...( arguments ) > 0 , "At least one element is required!" );

			return Implementation::Math<Deduce::IndexedArgumentType<0 , Args...>>::Maximum( std::forward<const Args&>( arguments )... );
		}
			   
		public: template<typename... Args>
		inline static auto Minimum( const Args&... arguments )
		{
			static_assert( sizeof...( arguments ) > 0 , "At least one element is required!" );

			return Implementation::Math<Deduce::IndexedArgumentType<0 , Args...>>::Minimum( std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType>
		inline static DataType SquareRoot( const DataType& data )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( data );
			}

			return Implementation::Math<DataType>::SquareRoot( data );
		}

		public: template<typename DataType>
		inline static DataType Pow( const DataType& data, const DataType& exponental ) 
		{
			return Implementation::Math<DataType>::Pow( data, exponental );
		}

		public: template<typename DataType>
		inline static DataType Cos( const DataType& data )
		{
			return Implementation::Math<DataType>::Cos( data );
		}
		public: template<typename DataType>
		inline static DataType ACos( const DataType& data )
		{
			return Implementation::Math<DataType>::ACos( data );
		}
		public: template<typename DataType>
		inline static DataType Sin( const DataType& data )
		{
			return Implementation::Math<DataType>::Sin( data );
		}
		public: template<typename DataType>
		inline static DataType ASin( const DataType& data )
		{
			return Implementation::Math<DataType>::ASin( data );
		}

		public:
		inline static double AngleToRadian( double angle )
		{
			return 2 * PI * ( angle / 360 );
		}

		public:
		inline static double RadianToAngle( double radian )
		{
			return radian * 360 / ( 2 * PI );
		}
	};
}