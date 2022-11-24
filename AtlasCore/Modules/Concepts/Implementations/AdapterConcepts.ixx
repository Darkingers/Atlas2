module;

#include "../../../../Macros/Macros.h"

export module AtlasConcepts:AdapterConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename CollectionType>
	concept IsNoexceptClear = noexcept( ClearAdapter<Deduce::SimpleType<CollectionType>>::Clear( std::declval<CollectionType>( ) ) );

	template<typename CollectionType , typename ElementType>
	concept IsNoexceptContain = noexcept( ContainAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<ElementType>>::Contain( std::declval<CollectionType>( ) , std::declval<ElementType>( ) ) );

	template<typename CollectionType , typename ContainedCollectionType>
	concept IsNoexceptContainAll = noexcept( ContainAllAdapter<Deduce::SimpleType<CollectionType> , Deduce::SimpleType<ContainedCollectionType>>::ContainAll( std::declval<CollectionType>( ) , std::declval<ContainedCollectionType>( ) ) );

	template<typename ExpectedType , typename ActualType>
	concept IsNoexceptCount = noexcept( CountAdapter<Deduce::SimpleType<ActualType>, Deduce::SimpleType<ExpectedType>>::Count( std::declval<ActualType>( ) ) );

	template<typename T>
	concept IsNoexceptSize = noexcept( SizeAdapter<Deduce::SimpleType<T>>::Size( std::declval<T>( ) ) );

	template<typename T>
	concept IsNoexceptHash = noexcept( HashAdapter<Deduce::SimpleType<T>>::Hash( std::declval<T>( ) ) );

	template<typename CollectionType>
	concept IsNoexceptBegin = noexcept( IterableAdapter<Deduce::SimpleType<CollectionType>>::Begin( std::declval<CollectionType>( ) ) );

	template<typename CollectionType>
	concept IsNoexceptEnd = noexcept( IterableAdapter<Deduce::SimpleType<CollectionType>>::End( std::declval<CollectionType>( ) ) );

	template<typename CollectionType>
	concept IsNoexceptConstBegin = noexcept( IterableAdapter<Deduce::SimpleType<CollectionType>>::ConstBegin( std::declval<CollectionType>( ) ) );

	template<typename CollectionType>
	concept IsNoexceptConstEnd = noexcept( IterableAdapter<Deduce::SimpleType<CollectionType>>::ConstEnd( std::declval<CollectionType>( ) ) );

	template<typename IteratorType>
	concept IsNoexceptCurrent = noexcept( IteratorAdapter<Deduce::SimpleType<IteratorType>>::Current( std::declval<IteratorType>( ) ) );

	template<typename IteratorType>
	concept IsNoexceptMove = noexcept( IteratorAdapter<Deduce::SimpleType<IteratorType>>::Move( std::declval<IteratorType>( ) , std::declval<int>( ) ) );

	template<typename IteratorType>
	concept IsNoexceptIterators = IsNoexceptMove<IteratorType> && IsNoexceptCurrent<IteratorType>;;
	
	template<typename CollectionType>
	concept HasNoexceptIterator = IsNoexceptBegin<CollectionType> && IsNoexceptEnd<CollectionType> && IsNoexceptIterators<Deduce::IteratorType<CollectionType>>;

	template<typename CollectionType>
	concept HasNoexceptConstIterator = IsNoexceptConstBegin<CollectionType> && IsNoexceptConstEnd<CollectionType> && IsNoexceptIterators<Deduce::IteratorType<CollectionType>>;

	template<template<typename...> typename AdapterTemplate, typename... Arguments>
	concept HasAdapter = AdapterTemplate<Arguments...>::value;
}
