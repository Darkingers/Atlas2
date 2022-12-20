module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:SizeAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename T> requires
		Concept::HasSize<T>
	class DLLApi SizeAdapter<T> :
		public std::true_type
	{

	public:

		constexpr static inline auto Size( T instance )
			noexcept( noexcept( instance.GetSize( ) ) )
		{
			return instance.GetSize( );
		}
	};

	template<typename TCollection> requires
		Concept::HasIterator<TCollection>
	class DLLApi SizeAdapter<TCollection> :
		public std::true_type
	{

		public:

		constexpr static inline auto Size( TCollection collection )
			noexcept( Concept::IsNoexceptLength<TCollection> )
		{
			return sizeof( TCollection ) + 
				   sizeof( typename CollectionTraits<TCollection>::ElementType ) * QueryAPI::Length( collection );
		}
	};

	template<typename T> requires
		Concept::IsFundamental<T>
	class DLLApi SizeAdapter<T> :
		public std::true_type
	{
		
	public:

		constexpr static inline auto Size( T instance )
			noexcept
		{
			return sizeof( T );
		}
	};
}