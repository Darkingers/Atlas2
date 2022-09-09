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
		class MathFunctions
		{
			private: template<typename... Args>
			inline static DataType Minimum( const DataType& previousMin , const DataType& current , const Args&... arguments )
			{
				DataType min = static_cast<DataType>( previousMin < current ? previousMin : current );

				if constexpr ( sizeof...( arguments ) > 0 )
				{
					return MathFunctions<DataType>::Minimum<DataType>( min , std::forward<const Args&>( arguments )... );
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
					return MathFunctions<DataType>::Maximum<DataType>( max , std::forward<const Args&>( arguments )... );
				}
				else
				{
					return max;
				}
			}

			public: template<typename DataType>
			inline static DataType SquareRoot( const DataType& data )
			{
				return static_cast<DataType>( sqrt( data ));
			}
		
			public: template<typename DataType>
			inline static DataType Pow( const DataType& data , const DataType& exponental )
			{
				return static_cast<DataType>( std::pow(data, exponental) );
			}
		};
	}

	class DLLApi MathFunctions
	{
		public: template<typename... Args>
		inline static auto Maximum(const Args&... arguments )
		{
			static_assert( sizeof...( arguments ) > 0 , "At least one element is required!" );

			return Implementation::MathFunctions<Deduce::IndexedArgumentType<0 , Args...>>::Maximum( std::forward<const Args&>( arguments )... );
		}
			   
		public: template<typename... Args>
		inline static auto Minimum( const Args&... arguments )
		{
			static_assert( sizeof...( arguments ) > 0 , "At least one element is required!" );

			return Implementation::MathFunctions<Deduce::IndexedArgumentType<0 , Args...>>::Minimum( std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType>
		inline static DataType SquareRoot( const DataType& data )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( data );
			}

			return Implementation::MathFunctions<DataType>::SquareRoot( data );
		}

		public: template<typename DataType>
		inline static DataType Pow( const DataType& data, const DataType& exponental ) 
		{
			return Implementation::MathFunctions<DataType>::Pow( data, exponental );
		}
	};
}