module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:ManipulationAPI;

import AtlasDefinitions;
import AtlasValidation;
import AtlasConfiguration;
import AtlasConcepts;

export namespace Atlas
{
	class DLLApi ManipulationAPI
	{

	public:

		template<typename TCollection>
		constexpr static inline void Clear
			(
				TCollection& collection
			)
			noexcept( Concept::IsNoexceptClear<TCollection&> )
		{
			ClearAdapter<TCollection&>::Clear( collection );
		}

		template<typename TCollectionSource , typename TCollectionTarget> requires
			Concept::AreCompatibleCollections<TCollectionSource , TCollectionTarget>
		constexpr static inline void Copy
			(
					const TCollectionSource& source ,
					unsigned int sourceStart ,
					unsigned int sourceEnd ,
					TCollectionTarget& target ,
					unsigned int targetStart
			) 
			noexcept( Concept::IsNoexceptCopy<const TCollectionSource& , unsigned int , unsigned int , TCollectionTarget& , unsigned int> )
		{
			Validate<Configuration::EnableManipulationAPICopyCheck>::IsPositiveRange( sourceStart , sourceEnd );
			Validate<Configuration::EnableManipulationAPICopyCheck>::IsPositive( targetStart );

			CopyAdapter<const TCollectionSource& ,unsigned int ,unsigned int ,TCollectionTarget& ,unsigned int>::Copy(
				source ,
				sourceStart ,
				sourceEnd ,
				target ,
				targetStart
			);
		}

		template<typename TCollectionSource , typename TIteratorTarget> requires
			Concept::IsCompatibleIteratorFor<TIteratorTarget , TCollectionSource>
		constexpr static inline void Copy
			(
					const TCollectionSource& source ,
					unsigned int sourceStart ,
					unsigned int sourceEnd ,
					TIteratorTarget& target
			)
			noexcept( Concept::IsNoexceptCopy<const TCollectionSource& , unsigned int , unsigned int , TIteratorTarget&> )
		{
			Validate<Configuration::EnableManipulationAPICopyCheck>::IsPositiveRange( sourceStart , sourceEnd );

			CopyAdapter<const TCollectionSource& , unsigned int , unsigned int , TIteratorTarget&>::Copy(
				source ,
				sourceStart ,
				sourceEnd ,
				target
			);
		}	

		template<typename TCollectionSource , typename TCollectionTarget> requires
			Concept::AreCompatibleCollections<TCollectionSource , TCollectionTarget>
		constexpr static inline void Copy
			(
					const TCollectionSource& source ,
					TCollectionTarget& target 
			) 
			noexcept( Concept::IsNoexceptCopy<const TCollectionSource& , unsigned int , unsigned int , TCollectionTarget& , unsigned int> )
		{
			CopyAdapter<const TCollectionSource& , unsigned int , unsigned int , TCollectionTarget& , unsigned int>::Copy(
				source ,
				0 ,
				0 ,
				target ,
				0
			);
		}

		template<typename TIteratorSource , typename TIteratorTarget> requires
			Concept::AreCompatibleIterators<TIteratorSource , TIteratorTarget>
		constexpr static inline void Copy
			(
					TIteratorSource& sourceStart ,
					const TIteratorSource& sourceEnd ,
					TIteratorTarget& target
			)
			noexcept( Concept::IsNoexceptCopy<TIteratorSource&, const TIteratorSource&, TIteratorTarget&> )
		{
			CopyAdapter<TIteratorSource& , const TIteratorSource& , TIteratorTarget&>::Copy(
				sourceStart ,
				sourceEnd ,
				target
			);
		}

		template<typename... TArgs> 
		constexpr static inline void ReplaceFrom
			( 
				TArgs&&... args
			)
			noexcept ( Concept::IsNoexceptReplaceFrom<TArgs&&...> )
		{
			ReplaceFromAdapter<TArgs&&...>::ReplaceFrom( std::forward<TArgs&&...>( args )... );
		}

		template<typename TIterator, typename... TArgs> requires 
			Concept::IsIterator<TIterator>
		constexpr static inline void ReplaceFrom
			( 
				TIterator iterator ,
				const TArgs&&... args
			)
			noexcept ( Concept::IsNoexceptReplaceFrom<TIterator, const TArgs&&...> )
		{
			ReplaceFromAdapter<TIterator , TArgs&&...>::ReplaceFrom
			( 
				iterator , 
				std::forward<const TArgs&&>( args )...
			);
		}

		template<typename TCollection , typename... TArgs> requires
			Concept::IsCollection<TCollection>
		constexpr static inline void ReplaceFrom
			(
				TCollection& collection, 
				unsigned int start ,
				const TArgs&&... args
			)
			noexcept 
			(
				!Configuration::EnableManipulationAPIReplaceFromCheck &&
				Concept::IsNoexceptReplaceFrom<TCollection& , unsigned int, const TArgs&&...>
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
		constexpr static inline void Shift
			( 
				TArgs&&... args
			)
			noexcept ( Concept::IsNoexceptShift<TArgs&&...> )
		{
			ShiftAdapter<TArgs&&...>::Shift( std::forward<TArgs&&>( args )... );
		}

		template<typename TCollection> requires
			Concept::IsCollection<TCollection>
		constexpr static inline void Shift
			(
				TCollection& collection , 
				unsigned int shiftStart ,
				int shiftOffset,
				unsigned int shiftLength 
			)
			noexcept
			(	
				!Configuration::EnableManipulationAPIShiftCheck &&
				Concept::IsNoexceptShift<TCollection&, unsigned int, int, unsigned int> 
			)
		{
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftStart );
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftLength );
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftLength );
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftStart + shiftOffset );

			ShiftAdapter<TCollection& , unsigned int , int , unsigned int>::Shift
			( 
				collection , 
				shiftStart , 
				shiftOffset , 
				shiftLength
			);
		}	
	};
}
