module;
#include "../../../../Macros/Macros.h"

export module AtlasAPI:CollectionAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	/// <summary>
	/// An API that calls the appropriate adapter for the collection.
	/// </summary>
	class DLLApi CollectionAPI
	{
		/// <summary>
		/// Clear the given collection.
		/// </summary>
		public: template<typename TCollection>
		constexpr static inline void Clear( TCollection& collection )
			noexcept( Concept::IsNoexceptClear<TCollection&> )
		{
			ClearAdapter<TCollection&>::Clear( collection );
		}

		/// <summary>
		/// Check if the collection contains the given element
		/// </summary>
		public: template<typename TCollection , typename TElement>
		constexpr static inline bool Contains( const TCollection& collection , const TElement& element )
			noexcept ( Concept::IsNoexceptContain<const TCollection& , const TElement&> )
		{
			return ContainAdapter<const TCollection&,const TElement&>::Contains( collection , element );
		}

	    /// <summary>
	    /// Check if the collection contains the given element
	    /// </summary>
		public: template<typename TCollection , typename TElement>
			requires Concept::IsFundamental<TElement>
		constexpr static inline bool Contains( const TCollection& collection , TElement element )			
			noexcept ( Concept::IsNoexceptContain<const TCollection& , TElement> )
		{
			return ContainAdapter<const TCollection& , TElement>::Contains( collection , element );
		}

		/// <summary>
		/// Count the elements with TExpected type in the given collection
		/// </summary>
		public: template<typename TExpected, typename TActual>
		constexpr static inline auto Count( const TActual& data )
			noexcept ( Concept::IsNoexceptCount<TExpected , const TActual&> )
		{
			return CountAdapter<TExpected, const TActual&>::Count( data );
		}

		/// <summary>
		/// Count the elements with TExpected type in the given collection
		/// </summary>
		public: template<typename TExpected , typename TActual>
			requires Concept::IsFundamental<TActual>
		constexpr static inline auto Count( TActual data )
			noexcept ( Concept::IsNoexceptCount<TExpected , TActual> )
		{
			return CountAdapter<TExpected ,TActual>::Count( data );
		}

		/// <summary>
		/// Get the begin iterator of the collection
		/// </summary>
		public: template<typename TCollection>
		constexpr static inline auto Begin( const TCollection& collection )
			noexcept ( Concept::IsNoexceptBegin<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::Begin( collection );
		}

		/// <summary>
		/// Get the read-only begin iterator of the collection
		/// </summary>
		public: template<typename TCollection>
		constexpr static inline auto ConstBegin( const TCollection& collection )
			noexcept ( Concept::IsNoexceptConstBegin<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::ConstBegin( collection );
		}
		
		/// <summary>
		/// Get the end iterator of the collection
		/// </summary>
		public: template<typename TCollection>
		constexpr static inline auto End( const TCollection& collection )
			noexcept ( Concept::IsNoexceptEnd<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::End( collection );
		}

		/// <summary>
		/// Get the read-only end iterator of the collection
		/// </summary>
		public: template<typename TCollection>
		constexpr static inline auto ConstEnd( const TCollection& collection )
			noexcept ( Concept::IsNoexceptConstEnd<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::ConstEnd( collection );
		}
	};
}
