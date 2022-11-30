module;

#include "../../../../Macros/Macros.h"

export module AtlasConcepts:AdapterConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename T>
	concept IsNoexceptSize = noexcept( SizeAdapter<Deduce::SimpleType<T>>::Size( std::declval<T>( ) ) );

	template<typename T>
	concept IsNoexceptHash = noexcept( HashAdapter<Deduce::SimpleType<T>>::Hash( std::declval<T>( ) ) );

	template<typename TIterator>
	concept IsNoexceptMove = noexcept( IteratorAdapter<Deduce::SimpleType<TIterator>>::Move( std::declval<TIterator>( ) , std::declval<int>( ) ) );

	template<typename TIterator>
	concept IsNoexceptIterators = IsNoexceptMove<TIterator> && IsNoexceptCurrent<TIterator>;;

	template<typename TCollection>
	concept IsNoexceptClear = noexcept( ClearAdapter<Deduce::SimpleType<TCollection>>::Clear( std::declval<TCollection>( ) ) );

	template<typename TCollection , typename TElement>
	concept IsNoexceptContain = noexcept( ContainAdapter<Deduce::SimpleType<TCollection> , Deduce::SimpleType<TElement>>::Contain( std::declval<TCollection>( ) , std::declval<TElement>( ) ) );

	template<typename TCollectionA , typename TCollectionB>
	concept IsNoexceptContainAll = noexcept( ContainAllAdapter<Deduce::SimpleType<TCollectionA> , Deduce::SimpleType<TCollectionB>>::ContainAll( std::declval<TCollectionA>( ) , std::declval<TCollectionB>( ) ) );

	template<typename TExpected , typename TActual>
	concept IsNoexceptCount = noexcept( CountAdapter<Deduce::SimpleType<TActual>, Deduce::SimpleType<TExpected>>::Count( std::declval<TActual>( ) ) );

	template<typename TCollection>
	concept IsNoexceptBegin = noexcept( IterableAdapter<Deduce::SimpleType<TCollection>>::Begin( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptEnd = noexcept( IterableAdapter<Deduce::SimpleType<TCollection>>::End( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptConstBegin = noexcept( IterableAdapter<Deduce::SimpleType<TCollection>>::ConstBegin( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptConstEnd = noexcept( IterableAdapter<Deduce::SimpleType<TCollection>>::ConstEnd( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept IsNoexceptCurrent = noexcept( IteratorAdapter<Deduce::SimpleType<TCollection>>::Current( std::declval<TCollection>( ) ) );

	template<typename TCollection>
	concept HasNoexceptIterator = IsNoexceptBegin<TCollection> && IsNoexceptEnd<TCollection> && IsNoexceptIterators<CollectionTraits<TCollection>::IteratorType>;

	template<typename TCollection>
	concept HasNoexceptConstIterator = IsNoexceptConstBegin<TCollection> && IsNoexceptConstEnd<TCollection> && IsNoexceptIterators<CollectionTraits<TCollection>::IteratorType>;

	template<template<typename...> typename Adapter, typename... TArgs>
	concept HasAdapter = Adapter<TArgs...>::value;
}
