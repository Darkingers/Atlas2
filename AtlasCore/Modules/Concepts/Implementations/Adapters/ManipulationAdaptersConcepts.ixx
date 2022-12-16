module;

#include "../../../../../Macros/Macros.h"

export module AtlasConcepts:ManipulationAdapterConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename TCollection>
	concept IsNoexceptClear = noexcept( ClearAdapter<TCollection>::Clear( std::declval<TCollection>( ) ) );
	
	template<typename TIterator , typename TSource>
	concept IsNoexceptReplaceFrom = noexcept( ReplaceFromAdapter<TIterator , TSource>::ReplaceFrom( std::declval<TIterator>( ) , std::declval<TSource>( ));

	template<typename TIteratorSource , typename TIteratorTarget>
	concept IsNoexceptCopy = noexcept( CopyAdapter<TIteratorSource , TIteratorTarget>::Move( std::declval<TIteratorSource>( ) , std::declval<TIteratorTarget>( ) ) , std::declval<unsigned int>( ) );
	
	template<typename T>
	concept IsNoexceptShift = noexcept ( ShiftAdapter<T>::Shift( std::declval<T>( ) , std::declval<unsigned int>( ) ) , std::declval<int>( ) , std::declval<unsigned int>( ) );
}
