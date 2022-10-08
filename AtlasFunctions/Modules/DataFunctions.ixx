module;

#include "../../Macros/Macros.h"

export module AtlasDataFunctions;
import AtlasDefinitions;
import AtlasConcepts;
import AtlasAdapters;
import AtlasValidation;
import AtlasExceptions;
import AtlasConfiguration;
import AtlasTypeInfo;
import AtlasVariadics;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename CollectionType>
		class DataFunctions
		{
			private: using DataType = Deduce::CollectionContainedType<CollectionType>;
			private: using IteratorType = Deduce::IteratorType<CollectionType>;
			private: using ConstIteratorType = Deduce::ConstIteratorType<CollectionType>;

			public: template<typename TargetCollectionType> 
				requires Concept::IsSame<DataType, Deduce::CollectionContainedType<TargetCollectionType>>
				  constexpr inline static ConstIteratorType Copy( const CollectionType& collection , const unsigned int copyStart , const unsigned int copySize , TargetCollectionType& destination )
			{
				auto sourceIterator = std::cbegin( collection );
				auto targetIterator = std::begin( destination );
				std::advance( sourceIterator , copyStart );

				for ( unsigned int i = 0 ; i< copySize; ++i, std::advance( sourceIterator , 1 ), std::advance( targetIterator , 1 ) )
				{
					( *targetIterator ) = ( *sourceIterator );
				}

				return sourceIterator;
			}

			public: 
			constexpr inline static void Shift( CollectionType& collection , const unsigned int shiftStart , const unsigned int shiftSize , const unsigned int shiftOffset )
			{
				const unsigned int destinationIndex = shiftStart + shiftOffset;

				auto copyFrom = std::cbegin( collection );
				std::advance( copyFrom , destinationIndex );

				auto copyTo = std::begin( collection );
				std::advance( copyTo , shiftStart );

				for ( unsigned int i = 0; i < shiftSize; ++i, std::advance( copyTo , 1 ), std::advance( copyFrom , 1 ) )
				{
					(*copyTo) = (*copyFrom);
				}
			}

			public: template<typename... Args>
			constexpr inline static IteratorType ReplaceFrom( IteratorType& iterator , const DataType& data , Args&&... arguments )
			{
				( *iterator ) = data;

				std::advance( iterator , 1 );

				if constexpr ( sizeof...( arguments ) > 0 )
				{
					return DataFunctions<CollectionType>::ReplaceFrom( iterator , std::forward<Args&&>( arguments )... );
				}
				else
				{
					return iterator;
				}
			}

			public: template<typename... Args>
			constexpr inline static IteratorType ReplaceFrom( IteratorType& iterator , DataType&& data , Args&&... arguments )
			{
				( *iterator ) = std::move( data );

				std::advance( iterator , 1 );

				if constexpr ( sizeof...( arguments ) > 0 )
				{
					return DataFunctions<CollectionType>::ReplaceFrom( iterator , std::forward<Args&&>( arguments )... );
				}
				else
				{
					return iterator;
				}
			}

			public: template<typename SourceCollectionType , typename... Args>
			constexpr inline static IteratorType ReplaceFrom( IteratorType& iterator , SourceCollectionType& collection , Args&&... arguments )
			{
				auto collectionIterator = std::cbegin( collection );
				const auto end = std::cend( collection );

				for ( ; collectionIterator != end; std::advance( collectionIterator , 1 ), std::advance( iterator , 1 ) )
				{
					( *iterator ) = *collectionIterator;
				}

				if constexpr ( sizeof...( arguments ) > 0 )
				{
					return DataFunctions<CollectionType>::ReplaceFrom( iterator , std::forward<Args&&>( arguments )... );
				}
				else
				{
					return iterator;
				}
			}

			public: template<typename SourceCollectionType , typename... Args>
			constexpr inline static IteratorType ReplaceFrom( IteratorType& iterator , SourceCollectionType&& collection , Args&&... arguments )
			{
				auto collectionIterator = std::cbegin( collection );
				const auto end = std::cend( collection );

				for ( ; collectionIterator != end; std::advance( collectionIterator , 1 ), std::advance( iterator , 1 ) )
				{
					( *iterator ) = std::move( *collectionIterator );
				}

				if constexpr ( sizeof...( arguments ) > 0 )
				{
					return DataFunctions<CollectionType>::ReplaceFrom( iterator , std::forward<Args&&>( arguments )... );
				}
				else
				{
					return iterator;
				}
			}

			public: template<typename CurrentCollectionType , typename... Args> 
				requires Concept::IsIterableWith<CollectionType , DataType>
			constexpr inline static bool Contains(const CollectionType& collection, const CurrentCollectionType& current , const Args&... arguments )
			{
				const bool contains = Adapter::ContainsAll( collection , current );

				if constexpr ( sizeof...( arguments ) == 0 )
				{
					return contains;
				}
				else
				{
					return contains && DataFunctions<CollectionType>::Contains( collection, std::forward<const Args&>( arguments )... );
				}
			}

			public: template<typename CurrentType , typename... Args>
				requires Concept::IsSame<DataType, CurrentType>
			constexpr inline static bool Contains( const CollectionType& collection , const CurrentType& current , const Args&... arguments )
			{
				const bool contains = Adapter::Contains( collection , current );

				if constexpr ( sizeof...( arguments ) == 0 )
				{
					return contains;
				}
				else
				{
					return contains && DataFunctions<CollectionType>::Contains( collection, std::forward<const Args&>( arguments )... );
				}
			}
		
			public: template<typename... Args>
			constexpr inline static unsigned int Count( const CollectionType& collection , const Args&... arguments )
			{
				auto iterator = std::cbegin( collection );
				const auto end = std::cend( collection );

				unsigned int count = 0;

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if ( Variadic::AllFulFills( ( *iterator ) , std::forward<const Args&>( arguments )... ))
					{
						++count;
					}
				}

				return count;
			}

			public: template<typename... Args>
			constexpr inline static bool All( const CollectionType& collection , const Args&... arguments )
			{
				auto iterator = std::cbegin( collection );
				const auto end = std::cend( collection );

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if (!Variadic::AllFulFills( ( *iterator ) , std::forward<const Args&>( arguments )... ))
					{
						return false;
					}
				}

				return true;
			}

			public: template<typename... Args>
			constexpr inline static bool Any( const CollectionType& collection , const Args&... arguments )
			{
				auto iterator = std::cbegin( collection );
				const auto end = std::cend( collection );

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if ( Variadic::AllFulFills( ( *iterator ) , std::forward<const Args&>( arguments )... ))
					{
						return true;
					}
				}

				return false;
			}

			public: template<typename... Args>
			constexpr inline static DataType& First( const CollectionType& collection , const Args&... arguments )
			{
				auto iterator = std::cbegin( collection );
				const auto end = std::cend( collection );

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if ( Variadic::AllFulFills( ( *iterator ) , std::forward<const Args&>( arguments )... ))
					{
						return &(*iterator );
					}
				}

				//Throw<NotFoundException>( "No element found matching the given condition!" );
			}

			public: template<typename... Args>
			constexpr inline static DataType* FirstOrNullptr( const CollectionType& collection , const Args&... arguments )
			{
				auto iterator = std::cbegin( collection );
				const auto end = std::cend( collection );

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if ( Variadic::AllFulFills( ( *iterator ) , std::forward<const Args&>( arguments )... ))
					{
						return &( *iterator );
					}
				}

				return nullptr;
			}
		};
	}

	class DLLApi DataFunctions
	{
		public: template<typename CollectionType, typename TargetCollectionType>
		constexpr inline static auto Copy( const CollectionType& collection , const unsigned int copyStart , const unsigned int copySize , TargetCollectionType& destination )
		{
			Validate::IsPositive( copyStart );
			Validate::IsPositive( copySize );

			if constexpr ( !Type<CollectionType>::IsPointer )
			{
				const unsigned int sourceCount = Adapter::Count( collection );

				Validate::IsLess( copyStart , sourceCount );
				Validate::IsLess( copyStart + copySize , sourceCount );
			}

			if constexpr ( !Type<TargetCollectionType>::IsPointer )
			{
				const unsigned int destinationCount = Adapter::Count( collection );

				Validate::IsLess( copySize , destinationCount );
			}

			return Implementation::DataFunctions<CollectionType>::Copy( collection , copyStart , copySize , destination );
		}

		public: template<typename CollectionType , typename TargetCollectionType>
		constexpr inline static auto Copy( const CollectionType& collection , const unsigned int copySize , TargetCollectionType& destination )
		{
			Validate::IsPositive( copySize );

			if constexpr ( !Type<CollectionType>::IsPointer )
			{
				const unsigned int sourceCount = Adapter::Count( collection );

				Validate::IsLess( copySize , sourceCount );
			}

			if constexpr ( !Type<TargetCollectionType>::IsPointer )
			{
				const unsigned int destinationCount = Adapter::Count( collection );

				Validate::IsLess( copySize , destinationCount );
			}

			return Implementation::DataFunctions<CollectionType>::Copy( collection , 0 , copySize , destination );
		}

		public: template<typename CollectionType>
		constexpr inline static void Shift( CollectionType& collection , const unsigned int shiftStart, const unsigned int shiftSize, const unsigned int shiftOffset )
		{
			Validate::IsPositive( shiftStart );
			Validate::IsPositive( shiftSize );
			Validate::IsPositive( shiftStart + shiftOffset );
			Validate::IsPositive( shiftStart + shiftOffset + shiftSize );

			if constexpr ( !Type<CollectionType>::IsPointer )
			{
				const unsigned int sourceCount = Adapter::Count( collection );

				Validate::IsLess( shiftStart , sourceCount );
				Validate::IsLess( shiftStart + shiftOffset , sourceCount );
				Validate::IsLess( shiftStart + shiftSize , sourceCount );
				Validate::IsLess( shiftStart + shiftOffset + shiftSize , sourceCount );
			}

			Implementation::DataFunctions<CollectionType>::Shift( collection , shiftStart, shiftSize , shiftOffset );
		}

		public: template<typename CollectionType, typename... Args>
		constexpr inline static auto ReplaceFrom( CollectionType&& collection , unsigned int index, Args&&... arguments )
		{
			if constexpr ( !Type<CollectionType>::IsPointer )
			{
				const auto count = Adapter::Count( collection );
				Validate::IsInRange( index, 0 , count );
				Validate::IsLess( index + Variadic::Count( std::forward<const Args&>( arguments )... ) , count );
			}
			else
			{
				Validate::IsPositive( index );
			}

			auto iterator = std::begin( collection );
			std::advance( index );

			return Implementation::DataFunctions<CollectionType>::ReplaceFrom( iterator , std::forward<Args&&>( arguments )... );
		}

		public: template<typename CollectionType, typename... Args>
		constexpr inline static bool Contains( const CollectionType& collection , const Args&... arguments )
		{
			return Implementation::DataFunctions<CollectionType>::Contains( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		constexpr inline static unsigned int Count( const CollectionType& collection , const Args&... arguments )
		{
			return Implementation::DataFunctions<CollectionType>::Count( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		constexpr inline static bool All( const CollectionType& collection , const Args&... arguments )
		{
			return Implementation::DataFunctions<CollectionType>::All( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		constexpr inline static bool Any( const CollectionType& collection , const Args&... arguments )
		{
			return Implementation::DataFunctions<CollectionType>::Any( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		constexpr inline static auto First( const CollectionType& collection , const Args&... arguments )
		{
			return Implementation::DataFunctions<CollectionType>::First( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		constexpr inline static auto FirstOrNullptr( const CollectionType& collection , const Args&... arguments )
		{
			return Implementation::DataFunctions<CollectionType>::FirstOrNullptr( collection , std::forward<const Args&>( arguments )... );
		}
	};
}