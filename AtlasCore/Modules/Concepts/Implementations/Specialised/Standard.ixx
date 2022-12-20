module;

#include <algorithm>
#include <functional>
#include <type_traits>
#include <string>

export module AtlasConcepts:StandardConcepts;

import AtlasDefinitions;

export namespace Atlas::Concept::Standard
{
	template<typename T>
	concept IsHashable = requires( const T instance )
	{
		{
			std::hash<T>( instance )
		}->std::convertible_to<size_t>;
	};

	template<typename TCollection>
	concept HasClearFunction = requires ( TCollection instance )
	{
		instance.clear( );
	};

	template<typename TCollection>
	concept HasLength = requires ( const TCollection instance )
	{
		{
			instance.size( )
		}->std::convertible_to<size_t>;
	};
	
	template<typename TIterable>
	concept IsIterable = requires ( TIterable instance )
	{
		std::begin( instance );
		std::end( instance );
		std::cbegin( instance );
		std::cend( instance );
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
}