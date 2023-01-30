module;

#include "../../../../../Macros/Macros.h"

export module AtlasConcepts:ManipulationConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{

	template<typename TCollection>
	concept HasClearFunction = requires ( TCollection instance )
	{
		instance.Clear( );
	};

	template<typename TCollection>
	concept IsNoexceptClear = 
		noexcept( 
			ClearAdapter<TCollection>::Clear( 
				std::declval<TCollection>( )
			) 
		);
	
	template<typename... TArgs>
	concept IsNoexceptReplaceFrom =
		noexcept(
			ReplaceFromAdapter<TArgs...>::ReplaceFrom( 
				std::declval<TArgs>( )... 
			) 
		);

	template<typename TCollectionA, typename TCollectionB>
	concept IsNoexceptCopyCollectionToCollection = 
		noexcept(
			CopyCollectionToCollectionAdapter<TCollectionA, TCollectionB>::Copy(
				std::declval<TCollectionA>( ), 
				std::declval<unsigned int>( ),
				std::declval<unsigned int>( ),
				std::declval<TCollectionB>( ),
				std::declval<unsigned int>( )
			) 
		);

	template<typename TIterator , typename TCollection>
	concept IsNoexceptCopyIteratorToCollection =
		noexcept(
			CopyIteratorToCollectionAdapter<TIterator , TCollection>::Copy(
				std::declval<TIterator>( ) ,
				std::declval<TIterator>( ) ,
				std::declval<TCollection>( ) ,
				std::declval<unsigned int>( )
			)
		);

	template<typename TCollection , typename TIterator>
	concept IsNoexceptCopyCollectionToIterator =
		noexcept(
			CopyCollectionToIteratorAdapter<TCollection , TIterator>::Copy(
				std::declval<TCollection>( ) ,
				std::declval<unsigned int>( ) ,
				std::declval<unsigned int>( ) ,
				std::declval<TIterator>( )
			)
		);

	template<typename TIteratorA , typename TIteratorB>
	concept IsNoexceptCopyIteratorToIterator =
		noexcept(
			CopyIteratorToCollectionAdapter<TIteratorA , TIteratorB>::Copy(
				std::declval<TIteratorA>( ) ,
				std::declval<TIteratorA>( ) ,
				std::declval<TIteratorB>( ) 
			)
		);

	template<typename TCollection>
	concept IsNoexceptShift = 
		noexcept ( 
			ShiftCollectionAdapter<TCollection>::Shift(
				std::declval<TCollection>( ) ,
				std::declval<unsigned int>( ) ,
				std::declval<unsigned int>( ) ,
				std::declval<unsigned int>( )
			) 
		);

	template<typename TCollection>
	concept IsNoexceptResize = 
		noexcept ( 
			ResizeAdapter<TCollection>::Resize( 
				std::declval<TCollection>( ) , 
				std::declval<unsigned int>( )
			) 
		);
}
