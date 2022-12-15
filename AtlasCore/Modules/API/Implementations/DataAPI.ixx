module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:DataAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	/// <summary>
	/// Calls the appropriate adapter for given objects
	/// </summary>
	class DLLApi DataAPI
	{

	public:

		/// <summary>
		/// Clear the given collection.
		/// </summary>
		template<typename TCollection>
		constexpr static inline void Clear( TCollection& collection )
			noexcept( Concept::IsNoexceptClear<TCollection&> )
		{
			ClearAdapter<TCollection&>::Clear( collection );
		}

		/// <summary>
		/// Returns the size of the given object in bytes
		/// </summary>
		 template<typename TTarget , typename TSource>
		constexpr static inline void Copy( const TSource& sourceStart, const TSource& sourceEnd , TTarget& target )
			noexcept ( Concept::IsNoexceptCopy<const TSource&, TTarget&> )
		{
			CopyAdapter<const TSource& ,TTarget&>::Copy( sourceStart , sourceEnd , target );
		}

		/// <summary>
		/// Returns the size of the given object in bytes
		/// </summary>
		template<typename TTarget , typename TSource>
			requires Concept::IsFundamental<TSource>
		constexpr static inline void Copy( const TSource sourceStart , const TSource sourceEnd , TTarget& target )
			noexcept ( Concept::IsNoexceptCopy<const TSource, TTarget&> )
		{
			CopyAdapter<const TSource, TTarget&>::Copy( sourceStart , sourceEnd , target );
		}

		/// <summary>
		/// Replaces the values pointed by the iterator with the given arguments
		/// </summary>
		template<typename TIterator,typename CurrentSource, typename... TSource>
		constexpr static inline void ReplaceFrom( TIterator& iterator ,const CurrentSource& current, const TSource&... source )
			noexcept ( Concept::IsNoexceptReplaceFrom<TIterator& , const CurrentSource&> && Concept::IsNoexceptReplaceFrom<TIterator& , const TSource&...> )
		{
			ReplaceFromAdapter<TIterator& , const CurrentSource&>::ReplaceFrom( iterator , current );

			if constexpr ( sizeof...( TSource ) > 0 )
			{
				DataAPI::ReplaceFrom( iterator , source... );
			}
		}

		/// <summary>
		/// Replaces the values pointed by the iterator with the given arguments
		/// </summary>
		template<typename TIterator , typename CurrentSource , typename... TSource>
			requires Concept::IsFundamental<CurrentSource>
		constexpr static inline void ReplaceFrom( TIterator& iterator , CurrentSource current , const TSource&... source )
			noexcept ( Concept::IsNoexceptReplaceFrom<TIterator& , CurrentSource>&& Concept::IsNoexceptReplaceFrom<TIterator& , const TSource&...> )
		{
			ReplaceFromAdapter<TIterator& , CurrentSource>::ReplaceFrom( iterator , current );

			if constexpr ( sizeof...( TSource ) > 0 )
			{
				DataAPI::ReplaceFrom( iterator , source... );
			}
		}
	};
}
