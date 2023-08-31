module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:ManipulationAPI;

import AtlasDefinitions;
import AtlasValidation;
import AtlasConfiguration;
import AtlasConcepts;

import :QueryAPI;

export namespace Atlas
{
	class DLLApi ManipulationAPI
	{

	public:

		template<typename TCollection>
		constexpr static inline void Clear( TCollection& collection)
		{
			ClearAdapter<TCollection&>::Clear( collection );
		}

		template<typename TCollectionA , typename TCollectionB> requires 
			Concept::AreCompatibleCollections<TCollectionA , TCollectionB>
		constexpr static inline void Copy(
			const TCollectionA& source ,
			unsigned int sourceStart ,
			unsigned int sourceEnd ,
			TCollectionB& target ,
			unsigned int targetStart
		)
		{
			
			Validate<Configuration::EnableManipulationAPICopyCheck>::IsPositiveRange( sourceStart , sourceEnd );
			Validate<Configuration::EnableManipulationAPICopyCheck>::IsPositive( targetStart );
			Validate<Configuration::EnableManipulationAPICopyCheck>::IsMoreOrEqual(
				QueryAPI::Length( target ) - targetStart,
				sourceEnd - sourceStart
			);

			CopyCollectionToCollectionAdapter<const TCollectionA& , TCollectionB&>::Copy(
				source ,
				sourceStart ,
				sourceEnd ,
				target ,
				targetStart
			);
		}

		template<typename TCollectionA , typename TCollectionB> requires 
			Concept::AreCompatibleCollections<TCollectionA , TCollectionB>
		constexpr static inline void Copy( const TCollectionA& source ,TCollectionB& target ) 
		{
			const auto sourceLength = QueryAPI::Length( source );
			
			Validate<Configuration::EnableManipulationAPICopyCheck>::IsMoreOrEqual(
				QueryAPI::Length( target ) ,
				sourceLength
			);

			CopyCollectionToCollectionAdapter<const TCollectionA& , TCollectionB&>::Copy(
				source ,
				0,
				sourceLength,
				target ,
				0
			);
		}

		template<typename TCollection , typename TIterator> requires
			Concept::IsCompatibleIteratorFor<TIterator , TCollection>
		constexpr static inline void Copy(
			const TCollection& source ,
			unsigned int sourceStart ,
			unsigned int sourceEnd ,
			TIterator& target
		)
		{
			Validate<Configuration::EnableManipulationAPICopyCheck>::IsPositiveRange( sourceStart , sourceEnd );

			CopyCollectionToIteratorAdapter<const TCollection& , TIterator&> ::Copy(
				source ,
				sourceStart ,
				sourceEnd ,
				target
			);
		}	

		template<typename TIterator , typename TCollection> requires
			Concept::IsCompatibleIteratorFor<TIterator , TCollection>
		constexpr static inline void Copy(
			TIterator& sourceStart,
			const TIterator& sourceEnd,
			TCollection& destination,
			unsigned int destinationStart
		)
		{
			CopyIteratorToCollectionAdapter<const TCollection& , TIterator&>  ::Copy(
				sourceStart ,
				sourceEnd ,
				destination,
				destinationStart
			);
		}

		template<typename TIteratorSource , typename TIteratorTarget> requires
			Concept::AreCompatibleIterators<TIteratorSource , TIteratorTarget>
		constexpr static inline void Copy(
			TIteratorSource& sourceStart ,
			const TIteratorSource& sourceEnd ,
			TIteratorTarget& target
		)
		{
			CopyIteratorToIteratorAdapter<TIteratorSource& , TIteratorTarget&> ::Copy(
				sourceStart ,
				sourceEnd ,
				target
			);
		}

		template<typename... TArgs> 
		constexpr static inline void ReplaceFrom( 
			TArgs&&... args
		)
		{
			ReplaceFromAdapter<TArgs&&...>::ReplaceFrom( std::forward<TArgs&&...>( args )... );
		}

		template<typename TIterator, typename... TArgs> requires 
			Concept::IsIterator<TIterator>
		constexpr static inline void ReplaceFrom( 
			TIterator iterator ,
			const TArgs&&... args
		)
		{
			ReplaceFromAdapter<TIterator , TArgs&&...>::ReplaceFrom
			( 
				iterator , 
				std::forward<const TArgs&&>( args )...
			);
		}

		template<typename TCollection , typename... TArgs> requires
			Concept::IsCollection<TCollection>
		constexpr static inline void ReplaceFrom(
			TCollection& collection, 
			unsigned int start ,
			const TArgs&&... args
		)
		{		
			ReplaceFromAdapter<TCollection&, unsigned int, const TArgs&&...>::ReplaceFrom
			(
				collection, 
				start ,
				std::forward<const TArgs&&>( args )...
			);
		}

		template<typename... TArgs>
		constexpr static inline void Shift( 
			TArgs&&... args
		)
		{
			ShiftCollectionAdapter<TArgs&&...>::Shift( std::forward<TArgs&&>( args )... );
		}

		template<typename TCollection> requires
			Concept::IsCollection<TCollection>
		constexpr static inline void Shift(
			TCollection& collection , 
			unsigned int shiftStart ,
			int shiftOffset,
			unsigned int shiftLength 
		)
		{
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftStart );
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftLength );
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftLength );
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftStart + shiftOffset );

			ShiftCollectionAdapter<TCollection& , unsigned int , int , unsigned int>::Shift
			( 
				collection , 
				shiftStart , 
				shiftOffset , 
				shiftLength
			);
		}	
	};
}
