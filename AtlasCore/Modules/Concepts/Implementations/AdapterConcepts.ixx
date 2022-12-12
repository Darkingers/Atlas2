module;

#include "../../../../Macros/Macros.h"

export module AtlasConcepts:AdapterConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename T>
	concept IsNoexceptSize = noexcept( SizeAdapter<T>::Size( std::declval<T>( ) ) );

	template<typename T>
	concept IsNoexceptHash = noexcept( HashAdapter<T>::Hash( std::declval<T>( ) ) );

	template<typename TIterator>
	concept IsNoexceptMove = noexcept( IteratorAdapter<TIterator>::Move( std::declval<TIterator>( ) , std::declval<int>( ) ) );

	template<typename TIterator>
	concept IsNoexceptIterators = IsNoexceptMove<TIterator> && IsNoexceptCurrent<TIterator>;;

	template<typename TCollection>
	concept IsNoexceptClear = noexcept( ClearAdapter<TCollection>::Clear( std::declval<TCollection>( ) ) );

	template<typename TCollection , typename TElement>
	concept IsNoexceptContain = noexcept( ContainAdapter<TCollection , TElement>::Contain( std::declval<TCollection>( ) , std::declval<TElement>( ) ) );

	template<typename TExpected , typename TActual>
	concept IsNoexceptCount = noexcept( CountAdapter<TExpected, TActual>::Count( std::declval<TActual>( ) ) );

	template<typename TCollection>
	concept IsNoexceptBegin = noexcept( IterableAdapter<TCollection>::Begin( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptEnd = noexcept( IterableAdapter<TCollection>::End( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptConstBegin = noexcept( IterableAdapter<TCollection>::ConstBegin( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptConstEnd = noexcept( IterableAdapter<TCollection>::ConstEnd( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptCurrent = noexcept( IteratorAdapter<TCollection>::Current( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept HasNoexceptIterator = IsNoexceptBegin<TCollection> && IsNoexceptEnd<TCollection> && IsNoexceptIterators<typename CollectionTraits<TCollection>::IteratorType>;

	template<typename TCollection>
	concept HasNoexceptConstIterator = IsNoexceptConstBegin<TCollection> && IsNoexceptConstEnd<TCollection> && IsNoexceptIterators<typename CollectionTraits<TCollection>::IteratorType>;

	template<typename TIterator, typename TSource>
	concept IsNoexceptReplaceFrom = noexcept( ReplaceFromAdapter<TIterator, TSource>::ReplaceFrom( std::declval<TIterator>( ) , std::declval<TSource>( ) ) );

	template<typename TIteratorSource , typename TIteratorTarget>
	concept IsNoexceptCopy = noexcept( CopyAdapter<TIteratorSource , TIteratorTarget>::Move( std::declval<TIteratorSource>( ) , std::declval<TIteratorTarget>( ) ), std::declval<unsigned int>() );

	template<template<typename...> typename Adapter, typename... TArgs>
	concept HasAdapter = Adapter<TArgs...>::value;
}
