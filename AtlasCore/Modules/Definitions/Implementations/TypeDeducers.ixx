module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:TypeDeducers;

namespace Atlas::Implementation
{
	template<typename DataType>
	struct SimpleType
	{
		using type = DataType;
	};

	template<typename DataType>
	struct SimpleType<DataType*>
	{
		using type = DataType*;
	};

	template<typename DataType>
	struct SimpleType<DataType&>
	{
		using type = DataType;
	};

	template<typename DataType>
	struct SimpleType<const DataType>
	{
		using type = DataType;
	};

	template<typename DataType>
	struct SimpleType<const DataType*>
	{
		using type = DataType*;
	};

	template<typename DataType>
	struct SimpleType<const DataType&>
	{
		using type = DataType;
	};
}

export namespace Atlas::Deduce
{
	template<typename IteratorType>
	using IteratedType = decltype( std::declval<IteratorType>( ).operator*( ) );

	template<typename CollectionType>
	using BeginIteratorType = typename std::remove_pointer_t<decltype( std::begin( CollectionType( ) ) )>;

	template<typename CollectionType>
	using EndIteratorType = typename std::remove_pointer_t<decltype( std::end( CollectionType( ) ) )>;

	template<typename CollectionType>
	using IteratorType = BeginIteratorType<CollectionType>;

	template<typename CollectionType>
	using ConstBeginIteratorType = typename std::remove_pointer_t<decltype( std::cbegin( CollectionType( ) ) )>;

	template<typename CollectionType>
	using ConstEndIteratorType = typename std::remove_pointer_t<decltype( std::cend( CollectionType( ) ) )>;

	template<typename CollectionType>
	using ConstIteratorType = ConstBeginIteratorType<CollectionType>;

	template<typename CollectionType , typename IndexType>
	using CollectionIndexedType = decltype( std::declval<CollectionType>( )->operator[]( IndexType( ) ) );

	template<unsigned int Index , typename Tuple>
	using TupleIndexedType = decltype( std::get<Index>( Tuple( ) ) );

	template<typename CollectionType>
	using CollectionContainedType = IteratedType<BeginIteratorType<CollectionType>>;

	template<unsigned int Index , typename... Args>
	using IndexedArgumentType = typename std::tuple_element<Index , std::tuple<Args...>>;

	template<typename Invokable , typename... Args>
	using ReturnType = typename std::invoke_result_t<Invokable( Args... )>;

	template<typename DataType>
	using SimpleType = typename Atlas::Implementation::SimpleType<DataType>::type;
}