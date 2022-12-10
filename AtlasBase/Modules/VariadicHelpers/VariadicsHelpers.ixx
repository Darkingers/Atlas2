module;

#include "../../../Macros/Macros.h"

export module AtlasVariadicHelpers;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasIntegration;

export namespace Atlas
{
	class DLLApi VariadicHelper
	{
		public: template<typename... TArgs>
		constexpr static inline auto Size( const TArgs&... args )
			noexcept( ( (noexcept( Adapter::Size( TArgs ) ) ) && ...) )
		{
			return ( (Adapter::Size( TArgs ) ) + ...);
		}

		public: template<typename DataType , typename... TArgs>
		constexpr static inline bool AnyFulfills( const DataType& data , const TArgs&... conditions )
			noexcept( ( (noexcept( conditions(data ) ) ) && ...) )
		{
			return ( (conditions( data ) ) || ...);
		}

		public: template<typename DataType , typename... TArgs>
		constexpr static inline bool AllFulfills( const DataType& data ,  const TArgs&... conditions )
			noexcept( ( (noexcept( conditions( data ) ) ) && ...) )
		{
			return ( (conditions( data ) ) && ...);
		}

		public: template<typename TCollection , typename... TArgs>
		constexpr static inline auto CountAnyFulfills( const TCollection& collection , const TArgs&... conditions )
			noexcept( Concept::IsNoexceptIterable && ( (noexcept( conditions( std::declval<Deduce::CollectionContainedType<TCollection>>() ) ) ) && ...) )
		{
			const auto endIterator = std::cend(collection);
			auto currentIterator = std::begin(collection);

			auto counter = ((conditions( *currentIterator )) || ...);

			for ( std::advance( currentIterator , 1 ); currentIterator != endIterator; std::advance( currentIterator , 1 ) )
			{
				counter += ((conditions( *currentIterator )) || ...);
			}

			return counter;
		}

		public: template<typename TCollection , typename... TArgs>
		constexpr static inline auto CountAllFullfills( const TCollection& collection , const TArgs&... conditions )
			noexcept( Concept::IsNoexceptIterable && ((noexcept( conditions( std::declval<Deduce::CollectionContainedType<TCollection>>( ) ) ) ) && ... ) )
		{
			const auto endIterator = std::cend( collection );
			auto currentIterator = std::begin( collection );

			auto counter = ((conditions( *currentIterator ) ) && ...);

			for ( std::advance( currentIterator , 1 ); currentIterator != endIterator; std::advance( currentIterator , 1 ) )
			{
				counter += ((conditions( *currentIterator )) && ...);
			}

			return counter;
		}
	
		public: template<typename DataType , typename... TArgs>
		constexpr static inline bool AnyContains( const DataType& data , const TArgs&... args )
			noexcept( ( (noexcept( Adapter::Contains(TArgs, data ) ) ) && ...) )
		{
			return ((Adapter::Contains( data , TArgs )) || ... );
		}

		public: template<typename DataType , typename... TArgs>
		constexpr static inline bool AllContains( const DataType& data , const TArgs&... args )
			noexcept( ( (noexcept( Adapter::Contains(TArgs, data ) ) ) && ...) )
		{
			return ((Adapter::Contains( data , TArgs ) ) && ...);
		}
	};
}