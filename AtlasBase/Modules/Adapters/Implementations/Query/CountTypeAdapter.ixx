module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:CountTypeAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TElement, typename TCollection> requires 
		Concept::IsCollectionOf<TCollection , TElement>
	class DLLApi CountTypeAdapter<TCollection , TElement> :
		public std::true_type
	{

	public:

		constexpr static inline auto Count( TCollection collection )
			noexcept( QueryAPI::Length( collection ) )
		{
			return QueryAPI::Length( collection );
		}
	};


	template<typename TElement , typename TCollection> requires
		(!Concept::IsCollectionOf<TCollection , TElement>)
	class DLLApi CountTypeAdapter<TCollection , TElement> :
		public std::true_type
	{

	public:

		constexpr static inline auto Count( TCollection collection )
			noexcept( QueryAPI::Length( collection ) )
		{
			return 0;
		}
	};

	template<typename TCollection , typename TElement> requires 
		Concept::IsSame<TCollection , TElement>
	class DLLApi CountTypeAdapter<TCollection , TElement> :
		public std::true_type
	{

	public:

		constexpr static inline auto Count( TCollection collection  )
			noexcept
		{
			return 1;
		}
	};

	template<typename TCollection , typename TElement> requires 
		(!Concept::IsSame<TCollection , TElement>)
	class DLLApi CountTypeAdapter<TCollection , TElement> :
		public std::true_type
	{

		public:

		constexpr static inline auto Count( TCollection collection )
			noexcept
		{
			return 0;
		}
	};
}