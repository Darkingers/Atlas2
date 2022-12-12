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
		/// <summary>
		/// Returns the size of the given object in bytes
		/// </summary>
		public: template<typename TTarget , typename TSource>
		constexpr static inline void Copy( TTarget& target , const TSource& source )
			noexcept ( Concept::IsNoexceptCopy<TTarget&, const TSource&> )
		{
			CopyAdapter<TTarget& , const TSource&>::Copy( target , source );
		}

		/// <summary>
		/// Returns the size of the given object in bytes
		/// </summary>
		public: template<typename TTarget , typename TSource>
			requires Concept::IsFundamental<TSource>
		constexpr static inline void Copy( TTarget& target , TSource source )
			noexcept ( Concept::IsNoexceptCopy<TTarget& , TSource> )
		{
			CopyAdapter<TTarget& , const TSource&>::Copy( target , source );
		}

		/// <summary>
		/// Replaces the values pointed by the iterator with the given arguments
		/// </summary>
		public: template<typename TIterator,typename CurrentSource, typename... TSource>
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
		public: template<typename TIterator , typename CurrentSource , typename... TSource>
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
