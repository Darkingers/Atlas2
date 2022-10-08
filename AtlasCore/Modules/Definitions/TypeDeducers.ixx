module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:TypeDeducers;

import :Implementations;

export namespace Atlas::Deduce
{
	template<typename IteratorType>
	using IteratedType = decltype( std::declval<IteratorType>( )->operator*( ) );

	template<typename CollectionType>
	using BeginIteratorType = typename std::remove_pointer_t<decltype( std::begin( std::declval<CollectionType>( ) ) )>;

	template<typename CollectionType>
	using EndIteratorType = typename std::remove_pointer_t<decltype( std::end( std::declval<CollectionType>( ) ) )>;

	template<typename CollectionType>
	using IteratorType = BeginIteratorType<CollectionType>;

	template<typename CollectionType>
	using ConstBeginIteratorType = typename std::remove_pointer_t<decltype( std::cbegin( std::declval<CollectionType>( ) ) )>;

	template<typename CollectionType>
	using ConstEndIteratorType = typename std::remove_pointer_t<decltype( std::cend( std::declval<CollectionType>( ) ) )>;

	template<typename CollectionType>
	using ConstIteratorType = ConstBeginIteratorType<CollectionType>;

	template<typename CollectionType , typename IndexType>
	using CollectionIndexedType = decltype( std::declval<CollectionType>( )->operator[]( std::declval<IndexType>( ) ) );

	template<unsigned int Index , typename Tuple>
	using TupleIndexedType = decltype( std::get<Index>( std::declval<Tuple>( ) ) );

	template<typename CollectionType>
	using CollectionContainedType = IteratedType<BeginIteratorType<CollectionType>>;

	template<unsigned int Index , typename... Args>
	using IndexedArgumentType = typename std::tuple_element<Index , std::tuple<Args...>>;

	template<typename Invokable , typename... Args>
	using ReturnType = typename std::invoke_result_t<Invokable( Args... )>;

	template<typename DataType>
	using SimpleType = typename Atlas::Implementation::SimpleType<DataType>::type;
}