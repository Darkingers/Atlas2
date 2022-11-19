module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <string>

export module AtlasConcepts:FunctionalConcepts;

export namespace Atlas::Concept
{
	template<typename ReturnType , typename InvokableType , typename... Arguments>
	concept IsInvokable = requires( InvokableType invokable , Arguments... arguments )
	{
		{
			invokable( arguments... )
		} -> std::convertible_to<ReturnType>;
	};

	template<typename ReturnType , typename ExecutableType>
	concept IsExecutable = requires( ExecutableType executable )
	{
		{
			executable( )
		} ->  std::convertible_to<ReturnType>;
	};

	template<typename T>
	concept HasToString = requires ( T instance )
	{
		{
			instance.ToString( )
		} -> std::convertible_to<char*>;	
	};

	template<typename ReturnType, typename IndexableType , typename IndexType>
	concept HasIndexOperator = requires( IndexableType instance , const IndexType index )
	{
		{
			instance[index]
		} -> std::convertible_to<ReturnType>;
	};

	template<typename TypeA , typename TypeB>
	concept HasEqualOperator = requires( const TypeA x , const TypeB y )
	{
		{
			x == y
		} -> std::convertible_to<bool>;
	};

	template<typename TypeA , typename TypeB>
	concept HasNotEqualOperator = requires( const TypeA x , const TypeB y )
	{
		{
			x != y
		} -> std::convertible_to<const bool>;
	};

	template<typename TypeA , typename TypeB>
	concept HasLessOperator = requires( const TypeA x , const TypeB y )
	{
		{
			x < y
		} -> std::convertible_to<bool>;
	};

	template<typename TypeA , typename TypeB>
	concept HasLessOperatorOrEqual = requires( const TypeA x , const TypeB y )
	{
		{
			x <= y
		} -> std::convertible_to<bool>;
	};

	template<typename TypeA , typename TypeB>
	concept HasMoreOperator = requires( const TypeA x , const TypeB y )
	{
		{
			x > y
		} -> std::convertible_to<bool>;
	};

	template<typename TypeA , typename TypeB>
	concept HasMoreOperatorOrEqual = requires( const TypeA x , const TypeB y )
	{
		{
			x >= y
		} -> std::convertible_to<bool>;
	};

	template<typename IterableType>
	concept IsIterable = requires ( IterableType instance )
	{
		{
			instance.begin( )
		};
		{
			instance.end( )
		};
	};

	template<typename IterableType , typename IteratedType>
	concept IsIterableWith = requires ( IterableType instance )
	{
		{
			*( instance.begin( ))
		} -> std::convertible_to<IteratedType>;
		{
			*( instance.end( ))
		} -> std::convertible_to<IteratedType>;
	};	

	template<typename HashableType>
	concept IsStandardHashable = requires( const HashableType instance )
	{
		{
			std::hash<HashableType>( instance )
		}->std::convertible_to<size_t>;
	};

	template<typename ClearableType>
	concept IsStandardClearable = requires ( ClearableType instance )
	{
		instance.clear( );
	};

	template<typename CountableType>
	concept IsStandardCountable = requires ( const CountableType instance )
	{
		{
			instance.size( )
		}->std::convertible_to<size_t>;
	};

	template<typename ClearableType>
	concept HasClearFunction = requires ( ClearableType instance )
	{
		instance.Clear( );
	};

	template<typename CountableType>
	concept HasCountFunction = requires ( const CountableType instance )
	{
		{
			instance.Count( )
		}->std::convertible_to<unsigned int>;
	};

	template<typename CollectionType , typename ElementType>
	concept HasContainFunction = requires ( const CollectionType collection , const ElementType element )
	{
		{
			collection.Contains( element )
		}->std::convertible_to<bool>;
	};

	template<typename TestedType>
	concept HasGetHashFunction = requires( const TestedType instance )
	{
		{
			instance.GetHash( )
		}->std::convertible_to<unsigned int>;
	};
}
