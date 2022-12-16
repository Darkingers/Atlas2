module;

#include "../../../../../Macros/Macros.h"

export module AtlasConcepts:ManipulationAdapterConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	// Code generation helper:
	// Clear<TCollection>-auto Clear(TCollection)
	// ReplaceFrom<TITerator,TSource>-auto ReplaceFrom(TIterator, TSource, unsigned int)
	// Copy<TIteratorSource,TITeratorTarget>-auto Move(TIteratorSource, TIteratorTarget, unsigned int)
	// Shift<TCollection>-auto Shift(T, int, unsigned int)
	// Resize<TCollection>-void Resize( T, unsigned int)

	template<typename TCollection>
	concept IsNoexceptClear = noexcept( ClearAdapter<TCollection>::Clear( std::declval<TCollection>( ) ) );
	
	template<typename TIterator , typename TSource>
	concept IsNoexceptReplaceFrom = noexcept( ReplaceFromAdapter<TIterator , TSource>::ReplaceFrom( std::declval<TIterator>( ) , std::declval<TSource>( ) ) );

	template<typename TIteratorSource , typename TIteratorTarget>
	concept IsNoexceptCopy = noexcept( CopyAdapter<TIteratorSource , TIteratorTarget>::Move( std::declval<TIteratorSource>( ) , std::declval<TIteratorTarget>( ) , std::declval<unsigned int>( ) ) );
	
	template<typename TCollection>
	concept IsNoexceptShift = noexcept ( ShiftAdapter<TCollection>::Shift( std::declval<TCollection>( ) , std::declval<unsigned int>( ), std::declval<int>( ) , std::declval<unsigned int>( ) ) );

	template<typename TCollection>
	concept IsNoexceptResize = noexcept ( ResizeAdapter<TCollection>::Resize( std::declval<TCollection>( ) , std::declval<unsigned int>( ) ) );
}
