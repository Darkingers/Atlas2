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
import AtlasVariadic;

export namespace Atlas
{
	namespace Implementation
	{
		template<typename CollectionType>
		class DataFunctions
		{
			private: using DataType = DeduceCollectionContainedType<CollectionType>;
			private: using IteratorType = DeduceIteratorType<CollectionType>;
			private: using ConstIteratorType = DeduceConstIteratorType<CollectionType>;

			public: template<typename TargetCollectionType> requires IsSame<DataType, DeduceCollectionContainedType<TargetCollectionType>>
			inline static ConstIteratorType Copy( const CollectionType&& collection , const unsigned int copyStart , const unsigned int copySize , TargetCollectionType& destination )
			{
				using TargetIteratorType = DeduceIteratorType<TargetCollectionType>;

				ConstIteratorType source = std::cbegin( collection );
				TargetIteratorType target = std::begin( destination );
				std::advance( source , copyStart );

				for ( unsigned int i = 0 ; i< copySize; ++i, std::advance( source , 1 ) )
				{
					( *target ) = ( *source );
				}

				return source;
			}

			public: 
			inline static void Shift( CollectionType& collection , const unsigned int shiftStart , const unsigned int shiftSize , const unsigned int shiftOffset )
			{
				const unsigned int destinationIndex = shiftStart + shiftOffset;

				ConstIteratorType copyFrom = std::cbegin( collection );
				std::advance( copyFrom , destinationIndex );

				IteratorType copyTo = std::begin( collection );
				std::advance( copyTo , shiftStart );

				for ( unsigned int i = 0; i < shiftSize; ++i, std::advance( copyTo , 1 ), std::advance( copyFrom , 1 ) )
				{
					(*copyTo) = (*copyFrom);
				}
			}

			public: template<typename... Args>
			inline static IteratorType ReplaceFrom( IteratorType& iterator , const DataType& data , Args&&... arguments )
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
			inline static IteratorType ReplaceFrom( IteratorType& iterator , DataType&& data , Args&&... arguments )
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
			inline static IteratorType ReplaceFrom( IteratorType& iterator , SourceCollectionType& collection , Args&&... arguments )
			{
				using CollectionIteratorType = DeduceConstIteratorType<SourceCollectionType>;

				CollectionIteratorType current = std::cbegin( collection );
				const CollectionIteratorType end = std::cend( collection );

				for ( ; current != end; std::advance( current , 1 ), std::advance( iterator , 1 ) )
				{
					( *iterator ) = *current;
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
			inline static IteratorType ReplaceFrom( IteratorType& iterator , SourceCollectionType&& collection , Args&... arguments )
			{
				using CollectionIteratorType = DeduceConstIteratorType<SourceCollectionType>;

				CollectionIteratorType current = std::cbegin( collection );
				const CollectionIteratorType end = std::cend( collection );

				for ( ; current != end; std::advance( current , 1 ), std::advance( iterator , 1 ) )
				{
					( *iterator ) = std::move( *current );
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

			public: template<typename CurrentCollectionType , typename... Args> requires IsIterableWith<CollectionType , DataType>
			inline static bool Contains(const CollectionType& collection, const CurrentCollectionType& current , const Args&... arguments ) 
			{
				bool contains = ContainAllAdapter<CollectionType , CurrentCollectionType>::ContainsAll( collection , current );

				if constexpr ( sizeof...( arguments ) == 0 )
				{
					return contains;
				}
				else
				{
					return contains && DataFunctions<CollectionType>::Contains( collection, std::forward<const Args&>( arguments )... );
				}
			}

			public: template<typename CurrentType , typename... Args> requires IsA<CollectionType , DataType>
			inline static bool Contains( const CollectionType& collection , const CurrentType& current , const Args&... arguments ) 
			{
				bool contains = ContainAdapter<CollectionType , CurrentType>::Contains( collection , current );

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
			inline static unsigned int Count( const CollectionType& collection , const Args&... arguments )
			{
				ConstIteratorType iterator = std::cbegin( collection );
				const ConstIteratorType end = std::cend( collection );

				unsigned int count = 0;

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if ( VariadicConditionChecker<const DataType&>::All( ( *iterator ) , std::forward<const Args&>( arguments )... ))
					{
						++count;
					}
				}

				return count;
			}

			public: template<typename... Args>
			inline static bool All( const CollectionType& collection , const Args&... arguments ) 
			{
				ConstIteratorType iterator = std::cbegin( collection );
				const ConstIteratorType end = std::cend( collection );

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if (!VariadicConditionChecker<const DataType&>::All( ( *iterator ) , std::forward<const Args&>( arguments )... ))
					{
						return false;
					}
				}

				return true;
			}

			public: template<typename... Args>
			inline static bool Any( const CollectionType& collection , const Args&... arguments ) 
			{
				ConstIteratorType iterator = std::cbegin( collection );
				const ConstIteratorType end = std::cend( collection );

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if ( VariadicConditionChecker<DataType>::All( ( *iterator ) , std::forward<const Args&>( arguments )... ))
					{
						return true;
					}
				}

				return false;
			}

			public: template<typename... Args>
			inline static DataType& First( const CollectionType& collection , const Args&... arguments )
			{
				ConstIteratorType iterator = std::cbegin( collection );
				const ConstIteratorType end = std::cend( collection );

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if ( VariadicConditionChecker<DataType>::All( ( *iterator ) , std::forward<const Args&>( arguments )... ))
					{
						return &(*iterator );
					}
				}

				throw NotFoundException( "No element found matching the given condition!" );
			}

			public: template<typename... Args>
			inline static DataType* FirstOrNullptr( const CollectionType& collection , const Args&... arguments ) 
			{
				ConstIteratorType iterator = std::cbegin( collection );
				const ConstIteratorType end = std::cend( collection );

				for ( ; iterator != end; std::advance( iterator , 1 ) )
				{
					if ( VariadicConditionChecker<DataType>::All( ( *iterator ) , std::forward<const Args&>( arguments )... ))
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
		inline static auto Copy( const CollectionType& collection , const unsigned int copyStart , const unsigned int copySize , TargetCollectionType& destination )
		{
			if constexpr ( Configuration::EnableArgumentCheck  )
			{
				Ensure::IsPositive( copyStart );
				Ensure::IsPositive( copySize );
			
				if constexpr ( !Type<CollectionType>::IsPointer )
				{
					const unsigned int sourceCount = CountAdapter<CollectionType>::Count( collection );

					Ensure::IsLess( copyStart , sourceCount );
					Ensure::IsLess( copyStart + copySize , sourceCount );
				}

				if constexpr ( !Type<TargetCollectionType>::IsPointer )
				{
					const unsigned int destinationCount = CountAdapter<TargetCollectionType>::Count( collection );

					Ensure::IsLess( copySize , destinationCount );
				}
			}

			return Implementation::DataFunctions<CollectionType>::Copy( collection , copyStart , copySize , destination );
		}

		public: template<typename CollectionType , typename TargetCollectionType>
		inline static auto Copy( const CollectionType& collection , const unsigned int copySize , TargetCollectionType& destination )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( copySize );

				if constexpr ( !Type<CollectionType>::IsPointer )
				{
					const unsigned int sourceCount = CountAdapter<CollectionType>::Count( collection );

					Ensure::IsLess( copySize , sourceCount );
				}

				if constexpr ( !Type<TargetCollectionType>::IsPointer )
				{
					const unsigned int destinationCount = CountAdapter<TargetCollectionType>::Count( collection );

					Ensure::IsLess( copySize , destinationCount );
				}
			}

			return Implementation::DataFunctions<CollectionType>::Copy( collection , 0 , copySize , destination );
		}

		public: template<typename CollectionType>
		inline static void Shift( CollectionType& collection , const unsigned int shiftStart, const unsigned int shiftSize, const unsigned int shiftOffset )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsPositive( shiftStart );
				Ensure::IsPositive( shiftSize );
				Ensure::IsPositive( shiftStart + shiftOffset );
				Ensure::IsPositive( shiftStart + shiftOffset + shiftSize );

				if constexpr ( !Type<CollectionType>::IsPointer )
				{
					const unsigned int sourceCount = CountAdapter<CollectionType>::Count( collection );

					Ensure::IsLess( shiftStart , sourceCount );
					Ensure::IsLess( shiftStart + shiftOffset , sourceCount );
					Ensure::IsLess( shiftStart + shiftSize , sourceCount );
					Ensure::IsLess( shiftStart + shiftOffset + shiftSize , sourceCount );
				}
			}

			Implementation::DataFunctions<CollectionType>::Shift( collection , shiftStart, shiftSize , shiftOffset );
		}

		public: template<typename CollectionType, typename... Args>
		inline static auto ReplaceFrom( CollectionType&& collection , unsigned int index, Args&&... arguments )
		{
			DataFunctions::Validate( collection , index );

			using Iterator = DeduceIteratorType<CollectionType>;

			Iterator iterator = std::begin( collection );
			std::advance( index );

			return Implementation::DataFunctions<CollectionType>::ReplaceFrom( iterator , std::forward<Args&&>( arguments )... );
		}

		public: template<typename CollectionType, typename... Args>
		inline static bool Contains( const CollectionType& collection , const Args&... arguments ) 
		{
			return Implementation::DataFunctions<CollectionType>::Contains( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		inline static unsigned int Count( const CollectionType& collection , const Args&... arguments ) 
		{
			return Implementation::DataFunctions<CollectionType>::Count( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		inline static bool All( const CollectionType& collection , const Args&... arguments ) 
		{
			return Implementation::DataFunctions<CollectionType>::All( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		inline static bool Any( const CollectionType& collection , const Args&... arguments ) 
		{
			return Implementation::DataFunctions<CollectionType>::Any( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		inline static DeduceCollectionContainedType<CollectionType>& First( const CollectionType& collection , const Args&... arguments )
		{
			return Implementation::DataFunctions<CollectionType>::First( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		inline static  DeduceCollectionContainedType<CollectionType>* FirstOrNullptr( const CollectionType& collection , const Args&... arguments )
		{
			return Implementation::DataFunctions<CollectionType>::FirstOrNullptr( collection , std::forward<const Args&>( arguments )... );
		}
	};
}