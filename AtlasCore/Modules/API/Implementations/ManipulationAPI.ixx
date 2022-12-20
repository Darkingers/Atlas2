module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:ManipulationAPI;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasConfiguration;

import :QueryAPI;

export namespace Atlas
{
	class DLLApi ManipulationAPI
	{

	public:

		template<typename TCollection>
		constexpr static inline void Clear( TCollection& collection )
			noexcept( Concept::IsNoexceptClear<TCollection&> )
		{
			ClearAdapter<TCollection&>::Clear( collection );
		}

		template<typename... TArgs>
		constexpr static inline void Copy( TArgs&&... args )
			noexcept ( Concept::IsNoexceptCopy<TArgs&&...> )
		{
			CopyAdapter<TArgs&&...>::Copy( std::forward<TArgs&&>( args )... );
		}

		template<typename... TArgs> 
		constexpr static inline void ReplaceFrom( TArgs&&... args )
			noexcept ( Concept::IsNoexceptReplaceFrom<TArgs&&...> )
		{
			ReplaceFromAdapter<TArgs&&...>::ReplaceFrom( std::forward<TArgs&&...>( args )... );
		}

		template<typename TIterator, typename... TArgs> requires 
			Concept::IsIterator<TIterator>
		constexpr static inline void ReplaceFrom( TIterator iterator , const TArgs&&... args )
			noexcept ( Concept::IsNoexceptReplaceFrom<TIterator, const TArgs&&...> )
		{
			ReplaceFromAdapter<TIterator , TArgs&&...>::ReplaceFrom
			( 
				iterator , 
				std::forward<TArgs&&>( args )... 
			);
		}

		template<typename TCollection , typename... TArgs> requires
			Concept::IsCollection<TCollection>
		constexpr static inline void ReplaceFrom( TCollection& collection, const unsigned int start , const TArgs&&... args )
			noexcept 
			(
				!Configuration::EnableManipulationAPIReplaceFromCheck &&
				Concept::IsNoexceptReplaceFrom<TCollection& , const unsigned int, const TArgs&&...>
			)
		{
			Validate<Configuration::EnableManipulationAPIReplaceFromCheck>::IsMoreOrEqual
			(
				QueryAPI::Length( collection ) - start ,
				QueryAPI::CountType<typename CollectionTraits<TCollection>::ElementType>( args... )
			);
				
			ReplaceFromAdapter<TCollection&, const unsigned int, const TArgs&&...>::ReplaceFrom
			(
				collection, 
				start ,
				std::forward<TArgs&&>( args )...
			);
		}

		template<typename... TArgs>
		constexpr static inline void Shift( TArgs&&... args )
			noexcept ( Concept::IsNoexceptShift<TArgs&&...> )
		{
			ShiftAdapter<TArgs&&...>::Shift( std::forward<TArgs&&>( args )... );
		}

		template<typename TCollection> requires
			Concept::IsCollection<TCollection>
		constexpr static inline void Shift( TCollection& collection , const unsigned int shiftStart , const int shiftOffset,const unsigned int shiftLength )
			noexcept
			(	
				!Configuration::EnableManipulationAPIShiftCheck &&
				Concept::IsNoexceptShift<TCollection&, const unsigned int, const int, const unsigned int> 
			)
		{
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsMoreOrEqual
			( 
				QueryAPI::Length( collection ) ,
				shiftStart + shiftOffset + shiftLength 
			);
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftStart );
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftLength );
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftLength );
			Validate<Configuration::EnableManipulationAPIShiftCheck>::IsPositive( shiftStart + shiftOffset );

			ShiftAdapter<TCollection& , const unsigned int , const int , const unsigned int>::Shift
			( 
				collection , 
				shiftStart , 
				shiftOffset , 
				shiftLength
			);
		}	
	};
}
