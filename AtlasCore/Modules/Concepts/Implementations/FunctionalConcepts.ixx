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
	concept IsNoexceptInvokable = noexcept( std::declval<TInvokable>( )( std::declval<TArgs>( )... ) ) &&
		IsInvokable< TReturn , TInvokable , TArgs...>;

	template<typename TReturn , typename TExecutable>
	concept IsExecutable = requires( TExecutable executable )
	{
		{
			executable( )
		} ->  std::convertible_to<TReturn>;
	};

	template<typename T>
	concept HasToString = requires ( T instance )
	{
		{
			instance.ToString( )
		} -> std::convertible_to<char*>;	
	};

	template<typename TCollection>
	concept IsIndexable = requires( TCollection collection , unsigned int index )
	{
		{
			collection[index]
		} -> std::convertible_to<typename CollectionTraits<TCollection>::ElementType>;
	};

	template<typename TReturn , typename TIndexed , typename TIndex>
	concept HasIndexOperator = requires( TIndexed instance , const TIndex index )
	{
		{
			instance[index]
		} -> std::convertible_to<TReturn>;
	};

	template<typename TA , typename TB>
	concept HasEqualOperator = requires( const TA x , const TB y )
	{
		{
			x == y
		} -> std::convertible_to<bool>;
	};

	template<typename TA , typename TB>
	concept HasNotEqualOperator = requires( const TA x , const TB y )
	{
		{
			x != y
		} -> std::convertible_to<const bool>;
	};

	template<typename TA , typename TB>
	concept HasLessOperator = requires( const TA x , const TB y )
	{
		{
			x < y
		} -> std::convertible_to<bool>;
	};

	template<typename TA , typename TB>
	concept HasLessOperatorOrEqual = requires( const TA x , const TB y )
	{
		{
			x <= y
		} -> std::convertible_to<bool>;
	};

	template<typename TA , typename TB>
	concept HasMoreOperator = requires( const TA x , const TB y )
	{
		{
			x > y
		} -> std::convertible_to<bool>;
	};

	template<typename TA , typename TB>
	concept HasMoreOperatorOrEqual = requires( const TA x , const TB y )
	{
		{
			x >= y
		} -> std::convertible_to<bool>;
	};

	template<typename T>
	concept IsHashable = requires( const T instance )
	{
		{
			instance.GetHash( )
		}->std::convertible_to<unsigned int>;
	};

	template<typename T>
	concept HasSize = requires( const T instance )
	{
		{
			instance.GetSize( )
		}->std::convertible_to<unsigned int>;
	};
}
