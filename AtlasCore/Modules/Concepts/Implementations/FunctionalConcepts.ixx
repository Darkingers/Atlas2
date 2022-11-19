module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <string>

export module AtlasConcepts:FunctionalConcepts;
import AtlasDefinitions;

export namespace Atlas::Concept
{
	template<typename ReturnType , typename TestedType , typename... Args>
	concept IsInvokable = std::is_invocable_r<ReturnType , TestedType , Args...>::value;

	template<typename ReturnType , typename TestedType>
	concept IsExecutable = std::is_invocable_r<ReturnType , TestedType>::value;

	template<typename TestedType>
	concept HasToString = requires ( TestedType testInstance )
	{
		{
			testInstance.ToString( )
		} -> std::convertible_to<const char*>;	
	};

	template<typename TestedType , typename IndexType, typename IndexedType>
	concept HasIndexOperator = requires( TestedType instance , const IndexType index )
	{
		{
			instance[index]
		} -> std::convertible_to<IndexedType>;
	};

	template<typename TypeA , typename TypeB>
	concept HasEqualOperator = requires( const TypeA x , const TypeB y )
	{
		{
			x == y
		} -> std::convertible_to<const bool>;
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
		} -> std::convertible_to<const bool>;
	};

	template<typename TypeA , typename TypeB>
	concept HasLessOperatorOrEqual = requires( const TypeA x , const TypeB y )
	{
		{
			x <= y
		} -> std::convertible_to<const bool>;
	};

	template<typename TypeA , typename TypeB>
	concept HasMoreOperator = requires( const TypeA x , const TypeB y )
	{
		{
			x > y
		} -> std::convertible_to<const bool>;
	};

	template<typename TypeA , typename TypeB>
	concept HasMoreOperatorOrEqual = requires( const TypeA x , const TypeB y )
	{
		{
			x >= y
		} -> std::convertible_to<const bool>;
	};

	template<typename TestedType>
	concept IsIterable = requires ( TestedType testInstance )
	{
		{
			testInstance.begin( )
		};
		{
			testInstance.end( )
		};
	};

	template<typename TestedType , typename DataType>
	concept IsIterableWith = requires ( TestedType testInstance )
	{
		{
			*(testInstance.begin( ))
		} -> std::convertible_to<DataType>;
		{
			*(testInstance.end( ))
		} -> std::convertible_to<DataType>;
	};	

	template<typename TestedType>
	concept IsStandardHashable = requires( const TestedType testInstance )
	{
		{
			std::hash<TestedType>( testInstance )
		}->std::convertible_to<size_t>;
	};

	template<typename TestedType>
	concept IsStandardClearable = requires ( TestedType testInstance )
	{
		testInstance.clear( );
	};

	template<typename TestedType>
	concept IsStandardCountable = requires ( const TestedType testInstance )
	{
		{
			testInstance.size( )
		}->std::convertible_to<size_t>;
	};

	template<typename TestedType>
	concept HasClearFunction = requires ( TestedType testInstance )
	{
		testInstance.Clear( );
	};

	template<typename TestedType>
	concept HasCountFunction = requires ( const TestedType testInstance )
	{
		{
			testInstance.Count( )
		}->std::convertible_to<const unsigned int>;
	};

	template<typename TestedType , typename DataType>
	concept HasContainFunction = requires ( const TestedType testInstance , const DataType data )
	{
		{
			testInstance.Contains( data )
		}->std::convertible_to<const bool>;
	};

	template<typename TestedType>
	concept HasGetHashFunction = requires( const TestedType testInstance )
	{
		{
			testInstance.GetHash( )
		}->std::convertible_to<unsigned int>;
	};

	template<template<typename...> typename AdapterType , typename... AdapterArguments>
	concept HasAdapter = AdapterType<AdapterArguments...>::value;

	template<typename CollectionType>
	concept IsNoexceptBegin = noexcept( std::begin( CollectionType( ) ) );

	template<typename CollectionType>
	concept IsNoexceptConstBegin = noexcept( std::cbegin( CollectionType( ) ) );

	template<typename CollectionType>
	concept IsNoexceptEnd = noexcept( std::end( CollectionType( ) ) );

	template<typename CollectionType>
	concept IsNoexceptConstEnd = noexcept( std::cend( CollectionType( ) ) );

	template<typename CollectionType>
	concept IsNoexceptIterable = 
		IsNoexceptBegin<CollectionType> &&
		IsNoexceptConstEnd<CollectionType> &&
		noexcept( std::advance( std::declval<Deduce::BeginIteratorType<CollectionType>>( ) , std::declval<unsigned int>( ) ) );
		
	template<typename CollectionType, typename DataType>
	concept IsNoexceptIterableWith = IsNoexceptIterable<CollectionType> && IsIterableWith<CollectionType , DataType>;

	template<typename CollectionType1, typename CollectionType2>
	concept IsSameContainedDataType = std::is_same<Deduce::CollectionContainedType<CollectionType1> ,Deduce::CollectionContainedType<CollectionType2>>::value;
}