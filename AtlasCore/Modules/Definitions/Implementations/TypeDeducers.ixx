module;

#include <algorithm>
#include <functional>
#include <tuple>

export module AtlasDefinitions:TypeDeducers;

namespace Atlas::Implementation
{
	template<typename T>
	struct SimpleType
	{
		using type = T;
	};

	template<typename T>
	struct SimpleType<T*>
	{
		using type = T*;
	};

	template<typename T>
	struct SimpleType<T&>
	{
		using type = T;
	};

	template<typename T>
	struct SimpleType<const T>
	{
		using type = T;
	};

	template<typename T>
	struct SimpleType<const T*>
	{
		using type = T*;
	};

	template<typename T>
	struct SimpleType<const T&>
	{
		using type = T;
	};
}

export namespace Atlas::Deduce
{
	template<typename Type>
	using DereferencedType = decltype( std::declval<Type>( ).operator*( ) );

	template<typename InvokableType , typename... Arguments>
	using ReturnType = typename std::invoke_result_t<InvokableType( Arguments... )>;

	template<typename DataType>
	using SimpleType = typename Atlas::Implementation::SimpleType<DataType>::type;
	
	
	template<typename IteratorType>
	using IteratedType = DereferencedType<IteratorType>;

	template<typename CollectionType>
	using BeginIteratorType = typename std::remove_pointer_t<decltype( std::begin( CollectionType( ) ) )>;

	template<typename CollectionType>
	using EndIteratorType = typename std::remove_pointer_t<decltype( std::end( CollectionType( ) ) )>;
	
	template<typename CollectionType>
	using ConstBeginIteratorType = typename std::remove_pointer_t<decltype( std::cbegin( CollectionType( ) ) )>;

	template<typename CollectionType>
	using ConstEndIteratorType = typename std::remove_pointer_t<decltype( std::cend( CollectionType( ) ) )>;
	
	template<typename CollectionType>
	using IteratorType = BeginIteratorType<CollectionType>;

	template<typename CollectionType>
	using ConstIteratorType = ConstBeginIteratorType<CollectionType>;

	
	template<typename CollectionType , typename IndexType>
	using CollectionIndexedType = decltype( std::declval<CollectionType>( )->operator[]( IndexType( ) ) );

	template<typename CollectionType>
	using CollectionElementType = IteratedType<BeginIteratorType<CollectionType>>;

	
	template<unsigned int Index , typename TupleType>
	using TupleIndexedType = decltype( std::get<Index>( std::declval<TupleType>( ) ) );

	
	template<unsigned int Index , typename... Arguments>
	using IndexedArgumentType = typename std::tuple_element<Index , std::tuple<Arguments...>>;

}