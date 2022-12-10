module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <string>

export module AtlasConcepts:FunctionalConcepts;

export namespace Atlas::Concept
{
	export namespace Standard
	{
		template<typename T>
		concept IsHashable = requires( const T instance )
		{
			{
				std::hash<T>( instance )
			}->std::convertible_to<size_t>;
		};

		template<typename TCollection>
		concept IsClearable = requires ( TCollection instance )
		{
			instance.clear( );
		};

		template<typename TCollection>
		concept IsCountable = requires ( const TCollection instance )
		{
			{
				instance.size( )
			}->std::convertible_to<size_t>;
		};
	}

	template<typename TReturn , typename TInvokable , typename... TArgs>
	concept IsInvokable = requires( TInvokable invokable , TArgs... args )
	{
		{
			invokable( args... )
		} -> std::convertible_to<TReturn>;
	};

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

	template<typename TCollection , typename TElement>
	concept HasContainFunction = requires ( const TCollection collection , const TElement element )
	{
		{
			collection.Contains( element )
		}->std::convertible_to<bool>;
	};
	template<typename TIterable>
	concept IsIterable = requires ( TIterable instance )
	{
		{
			instance.begin( )
		};
		{
			instance.end( )
		};
	};

	template<typename TIterable , typename TIterated>
	concept IsIterableWith = requires ( TIterable instance )
	{
		{
			*( instance.begin( ) )
		} -> std::convertible_to<TIterated>;
		{
			*( instance.end( ) )
		} -> std::convertible_to<TIterated>;
	};

	template<typename TCollection>
	concept IsClearable = requires ( TCollection instance )
	{
		instance.Clear( );
	};

	template<typename TCollection>
	concept IsCountable = requires ( const TCollection instance )
	{
		{
			instance.Count( )
		}->std::convertible_to<unsigned int>;
	};

	template<typename T>
	concept IsHashable = requires( const T instance )
	{
		{
			instance.GetHash( )
		}->std::convertible_to<unsigned int>;
	};
}
