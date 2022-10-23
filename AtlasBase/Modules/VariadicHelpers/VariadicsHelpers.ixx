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
		public: template<typename... Args>
		constexpr static inline auto Size( const Args&... arguments )
			noexcept( ( (noexcept( Adapter::Size( arguments ) ) ) && ...) )
		{
			return ( (Adapter::Size( arguments ) ) + ...);
		}

		public: template<typename DataType , typename... Args>
		constexpr static inline bool AnyFulfills( const DataType& data , const Args&... conditions )
			noexcept( ( (noexcept( conditions(data ) ) ) && ...) )
		{
			return ( (conditions( data ) ) || ...);
		}

		public: template<typename DataType , typename... Args>
		constexpr static inline bool AllFulfills( const DataType& data ,  const Args&... conditions )
			noexcept( ( (noexcept( conditions( data ) ) ) && ...) )
		{
			return ( (conditions( data ) ) && ...);
		}

		public: template<typename CollectionType , typename... Args>
		constexpr static inline auto CountAnyFulfills( const CollectionType& collection , const Args&... conditions )
			noexcept( Concept::IsNoexceptIterable && ( (noexcept( conditions( std::declval<Deduce::CollectionContainedType<CollectionType>>() ) ) ) && ...) )
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

		public: template<typename CollectionType , typename... Args>
		constexpr static inline auto CountAllFullfills( const CollectionType& collection , const Args&... conditions )
			noexcept( Concept::IsNoexceptIterable && ((noexcept( conditions( std::declval<Deduce::CollectionContainedType<CollectionType>>( ) ) ) ) && ... ) )
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
	
		public: template<typename DataType , typename... Args>
		constexpr static inline bool AnyContains( const DataType& data , const Args&... arguments )
			noexcept( ( (noexcept( Adapter::Contains(arguments, data ) ) ) && ...) )
		{
			return ((Adapter::Contains( data , arguments )) || ... );
		}

		public: template<typename DataType , typename... Args>
		constexpr static inline bool AllContains( const DataType& data , const Args&... arguments )
			noexcept( ( (noexcept( Adapter::Contains(arguments, data ) ) ) && ...) )
		{
			return ((Adapter::Contains( data , arguments ) ) && ...);
		}
	};
}