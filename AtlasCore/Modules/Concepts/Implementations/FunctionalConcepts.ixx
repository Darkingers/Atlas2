module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <string>

export module AtlasConcepts:FunctionalConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename TReturn , typename TInvokable , typename... TArgs>
	concept IsInvokable = requires( TInvokable invokable , TArgs... args )
	{
		{
			invokable( args... )
		} -> std::convertible_to<TReturn>;
	};

	template<typename TReturn , typename TInvokable , typename... TArgs>
	concept IsNoexceptInvokable =
		IsInvokable< TReturn , TInvokable , TArgs...> &&
		noexcept( std::declval<TInvokable>( )( std::declval<TArgs>( )... ) );

	template<typename TReturn , typename TExecutable>
	concept IsExecutable = requires( TExecutable executable )
	{
		{ executable( ) } ->  std::convertible_to<TReturn>;
	};

	template<typename TReturn , typename TExecutable>
	concept IsNoexceptExecutable =
		IsExecutable< TReturn , TExecutable> &&
		noexcept( std::declval<TExecutable>( )( ) );

	template<typename T>
	concept HasToString = requires ( T instance )
	{
		{ instance.ToString( ) } -> std::convertible_to<char*>;	
	};

	template<typename T>
	concept IsNoexceptToString = 
		HasToString<T> &&
		noexcept( std::declval<T>( ).ToString( ) );
	
	template<typename TCollection>
	concept IsIndexable = requires( TCollection collection , unsigned int index )
	{
		{ collection[index] } -> std::convertible_to<typename CollectionTraits<TCollection>::ElementType>;
	};

	template<typename TCollection>
	concept IsNoexceptIndexable = 
		IsIndexable<TCollection> &&
		noexcept( std::declval<TCollection>( )[std::declval<int>()] );

	template<typename TReturn , typename TIndexed , typename TIndex>
	concept HasIndexOperator = requires( TIndexed instance , const TIndex index )
	{
		{ instance[index] } -> std::convertible_to<TReturn>;
	};

	template<typename T>
	concept IsHashable = requires( const T instance )
	{
		{ instance.GetHash( ) }->std::convertible_to<unsigned int>;
	};

	template<typename T>
	concept IsNoexceptHashable =
		IsHashable<T> &&
		noexcept( std::declval<T>( ).GetHash( ) );

	template<typename TA , typename TB>
	concept HasEqualOperator = requires( const TA x , const TB y )
	{
		{ x == y } -> std::convertible_to<bool>;
	};

	template<typename TA , typename TB>
	concept HasNoexceptEqualOperator =
		HasEqualOperator<TA , TB> &&
		noexcept( std::declval<TA>( ) == std::declval<TB> );

	template<typename TA , typename TB>
	concept HasNotEqualOperator = requires( const TA x , const TB y )
	{
		{ x != y } -> std::convertible_to<const bool>;
	};

	template<typename TA , typename TB>
	concept HasNoexceptNotEqualOperator =
		HasNotEqualOperator<TA , TB> &&
		noexcept( std::declval<TA>( ) != std::declval<TB> );

	template<typename TA , typename TB>
	concept HasLessOperator = requires( const TA x , const TB y )
	{
		{ x < y } -> std::convertible_to<bool>;
	};

	template<typename TA , typename TB>
	concept HasNoexceptLessOperator =
		HasLessOperator<TA , TB> &&
		noexcept( std::declval<TA>( ) < std::declval<TB> );

	template<typename TA , typename TB>
	concept HasLessOperatorOrEqual = requires( const TA x , const TB y )
	{
		{ x <= y } -> std::convertible_to<bool>;
	};

	template<typename TA , typename TB>
	concept HasNoexceptLessOperatorOrEqual =
		HasLessOperatorOrEqual<TA , TB> &&
		noexcept( std::declval<TA>( ) <= std::declval<TB> );

	template<typename TA , typename TB>
	concept HasMoreOperator = requires( const TA x , const TB y )
	{
		{ x > y } -> std::convertible_to<bool>;
	};

	template<typename TA , typename TB>
	concept HasNoexceptMoreOperator =
		HasMoreOperator<TA , TB> &&
		noexcept( std::declval<TA>( ) > std::declval<TB> );

	template<typename TA , typename TB>
	concept HasMoreOperatorOrEqual = requires( const TA x , const TB y )
	{
		{ x >= y } -> std::convertible_to<bool>;
	};

	template<typename TA , typename TB>
	concept HasNoexceptMoreOperatorOrEqual =
		HasMoreOperatorOrEqual<TA , TB> &&
		noexcept( std::declval<TA>( ) >= std::declval<TB> );

	template<typename T>
	concept HasSize = requires( const T instance )
	{
		{ instance.GetSize( ) }->std::convertible_to<unsigned int>;
	};

	template<typename T>
	concept HasNoexceptSize =
		HasSize<T> &&
		noexcept( std::declval<T>( ).GetSize( ) );
	
	template<typename TSource , typename TTarget>
	concept IsConvertibleTo = requires( const TSource source )
	{
		{ static_cast<TTarget>( source ) } -> std::convertible_to<TTarget>;
	};

	template<typename TSource , typename TTarget>
	concept IsNoexceptConvertibleTo = 
		IsConvertibleTo<TSource , TTarget> &&
		noexcept( static_cast<TTarget>( std::declval<TSource>( ) ) );

	template<typename TActual , typename... TArgs>
	concept IsConstructible = std::is_constructible<TActual , TArgs...>::value;

	template<typename TActual , typename... TArgs>
	concept IsNoexceptConstructible =
		IsConstructible<TActual , TArgs...> &&
		noexcept ( TActual( std::declval<TArgs>( )... ) );

	template<typename TLeft, typename TRight>
	concept IsAssignable = std::is_assignable<TLeft , TRight>::value;
	
	template<typename TLeft , typename TRight>
	concept IsNoexceptAssignable =
		IsAssignable<TLeft, TRight> &&
		noexcept ( std::declval<TLeft>( ) = std::declval<TRight>( ) );
}
