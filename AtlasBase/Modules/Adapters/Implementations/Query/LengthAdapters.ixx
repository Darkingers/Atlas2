module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:LengthtAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection> requires 
		Concept::HasIterator<TCollection>
	class DLLApi LengthAdapter<TCollection> :
		public std::true_type
	{

	public:

		constexpr static inline auto Length
			( 
				TCollection collection 
			)
			noexcept( Concept::HasNoexceptConstIterator<TCollection> )
		{
			auto start = IteratorAPI::ConstBegin( collection );
			const auto end = IteratorAPI::ConstEnd( collection );

			auto count = 0;

			while ( start != end )
			{
				count++;
			}

			return count;
		}
	};

	template<typename TCollection> requires 
		Concept::HasLength<TCollection>
	class DLLApi LengthAdapter<TCollection> :
		public std::true_type
	{

	public:

		constexpr static inline auto Length
			(
				TCollection collection
			)
			noexcept( noexcept( collection.Length() ) )
		{
			return collection.Length( );
		}
	};

	template<typename TCollection> requires 
		Concept::Standard::HasLength<TCollection>
	class DLLApi LengthAdapter<TCollection> :
		public std::true_type
	{

	public:

		constexpr static inline auto Length
			(
				TCollection collection 
			)
			noexcept( noexcept( collection.size( ) ) )
		{
			return collection.size( );
		}
	};

	template<typename TCollection> requires 
		Concept::IsArray<TCollection>
	class DLLApi LengthAdapter<TCollection*> :
		public std::true_type
	{
	
	public:

		template<unsigned int Size>
		constexpr static inline auto Count
			(
				TCollection( &collection )[Size] 
			)
			noexcept
		{
			return Size;
		}
	};

	template<>
	class DLLApi LengthAdapter<char*> :
		public std::true_type
	{
	
	public:

		constexpr static inline auto Length
			(
				char* collection 
			)
			noexcept
		{
			if ( collection == nullptr )
			{
				return 0;
			}

			auto count = 0;

			while ( collection[count] != '\0' )
			{
				count++;
			}

			return count;
		}
	};
}