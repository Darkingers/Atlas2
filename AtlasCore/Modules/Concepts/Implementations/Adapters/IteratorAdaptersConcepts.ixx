module;

#include "../../../../../Macros/Macros.h"

export module AtlasConcepts:IteratorAdapterConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename TIterator>
	concept IsNoexceptMove = noexcept( IteratorAdapter<TIterator>::Move( std::declval<TIterator>( ) , std::declval<int>( ) ) );

	template<typename TCollection>
	concept IsNoexceptCurrent = noexcept( IteratorAdapter<TCollection>::Current( std::declval<TCollection>( ) ) );
	
	template<typename TCollection>
	concept IsNoexceptAt = noexcept( IterableAdapter<TCollection>::At( std::declval<TCollection>( ) ) , std::declval<unsigned int>( ) );

	template<typename TCollection>
	concept IsNoexceptConstAt = noexcept( IterableAdapter<TCollection>::ConstAt( std::declval<TCollection>( ) ) , std::declval<unsigned int>( ) );

	template<typename TCollection>
	concept IsNoexceptBegin = noexcept( IterableAdapter<TCollection>::Begin( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptEnd = noexcept( IterableAdapter<TCollection>::End( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptConstBegin = noexcept( IterableAdapter<TCollection>::ConstBegin( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptConstEnd = noexcept( IterableAdapter<TCollection>::ConstEnd( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept HasNoexceptIterator = IsNoexceptBegin<TCollection> && IsNoexceptEnd<TCollection> && IsNoexceptIterators<typename CollectionTraits<TCollection>::IteratorType>;

	template<typename TCollection>
	concept HasNoexceptConstIterator = IsNoexceptConstBegin<TCollection> && IsNoexceptConstEnd<TCollection> && IsNoexceptIterators<typename CollectionTraits<TCollection>::IteratorType>;
}
