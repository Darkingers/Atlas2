module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:TypeDeducers;

export namespace Atlas
{
	template<typename IteratorType>
	using DeduceIteratedType = decltype( std::declval<IteratorType>( )->operator*( ) );

	template<typename CollectionType>
	using DeduceBeginIteratorType = typename std::remove_pointer_t<decltype( std::begin( std::declval<CollectionType>( ) ) )>;

	template<typename CollectionType>
	using DeduceEndIteratorType = typename std::remove_pointer_t<decltype( std::end( std::declval<CollectionType>( ) ) )>;

	template<typename CollectionType>
	using DeduceIteratorType = DeduceBeginIteratorType<CollectionType>;

	template<typename CollectionType>
	using DeduceConstBeginIteratorType = typename std::remove_pointer_t<decltype( std::cbegin( std::declval<CollectionType>( ) ) )>;

	template<typename CollectionType>
	using DeduceConstEndIteratorType = typename std::remove_pointer_t<decltype( std::cend( std::declval<CollectionType>( ) ) )>;

	template<typename CollectionType>
	using DeduceConstIteratorType = DeduceConstBeginIteratorType<CollectionType>;

	template<typename CollectionType , typename IndexType>
	using DeduceCollectionIndexedType = decltype( std::declval<CollectionType>( )->operator[]( std::declval<IndexType>( ) ) );

	template<unsigned int Index , typename Tuple>
	using DeduceTupleIndexedType = decltype( std::get<Index>( std::declval<Tuple>( ) ) );

	template<typename CollectionType>
	using DeduceCollectionContainedType = DeduceIteratedType<DeduceBeginIteratorType<CollectionType>>;

	template<unsigned int Index , typename... Args>
	using DeduceIndexedArgumentType = typename std::tuple_element<Index , std::tuple<Args...>>;

	template<typename Invokable , typename... Args>
	using DeduceReturnType = typename std::invoke_result_t<Invokable( Args... )>;
}