module;

#include "../../../../Macros/Macros.h"

export module AtlasAPI:IteratorAPI;

import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	/// <summary>
	/// An API that calls the appropriate iterator adapter
	/// </summary>
	class DLLApi IteratorAPI
	{
	
	public:
		
		/// <summary>
		/// Returns the element the iterator is on
		/// </summary>
		template<typename TIterator>
		constexpr static inline auto Current( const TIterator& iterator )
			noexcept ( Concept::IsNoexceptCurrent<const TIterator&> )
		{
			return IteratorCurrentAdapter<const TIterator&>::Current( iterator );
		}

	    /// <summary>
		///Moves the iterator the specified steps
		/// </summary>
		template<typename TIterator>
		constexpr static inline bool Move( TIterator& iterator ,const int step )
			noexcept ( Concept::IsNoexceptMove<TIterator&> )
		{
			return IteratorMoveAdapter<TIterator&>::Move( iterator , step );
		}

		/// <summary>
	    /// Moves the iterator to the next element
	    /// </summary>
		template<typename TIterator>
		constexpr static inline bool Next( TIterator& iterator )
			noexcept ( Concept::IsNoexceptMove<TIterator&> )
		{
			return IteratorAPI::Move( iterator , 1 );
		}
		
		/// <summary>
		/// Moves the iterator to the previous element
		/// </summary>
		template<typename TIterator>
		constexpr static inline bool Previous( TIterator& iterator )
			noexcept ( Concept::IsNoexceptMove<TIterator&> )
		{
			return IteratorAPI::Move( iterator , -1 );
		}
		
		/// <summary>
		/// Returns an iterator standing at 'step'
		/// </summary>
		template<typename TCollection>
		constexpr static inline auto At( const TCollection& collection, const unsigned int step )
			noexcept ( Concept::IsNoexceptAt<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::At( collection , step );
		}

		/// <summary>
		/// Returns a read-only iterator standing at 'step'
		/// </summary>
		template<typename TCollection>
		constexpr static inline auto ConstAt( const TCollection& collection , const unsigned int step )
			noexcept ( Concept::IsNoexceptConstAt<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::ConstAt( collection , step );
		}

		/// <summary>
		/// Get the begin iterator of the collection
		/// </summary>
		template<typename TCollection>
		constexpr static inline auto Begin( const TCollection& collection )
			noexcept ( Concept::IsNoexceptBegin<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::Begin( collection );
		}

		/// <summary>
		/// Get the read-only begin iterator of the collection
		/// </summary>
		template<typename TCollection>
		constexpr static inline auto ConstBegin( const TCollection& collection )
			noexcept ( Concept::IsNoexceptConstBegin<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::ConstBegin( collection );
		}

		/// <summary>
		/// Get the end iterator of the collection
		/// </summary>
		template<typename TCollection>
		constexpr static inline auto End( const TCollection& collection )
			noexcept ( Concept::IsNoexceptEnd<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::End( collection );
		}

		/// <summary>
		/// Get the read-only end iterator of the collection
		/// </summary>
		template<typename TCollection>
		constexpr static inline auto ConstEnd( const TCollection& collection )
			noexcept ( Concept::IsNoexceptConstEnd<const TCollection&> )
		{
			return IterableAdapter<const TCollection&>::ConstEnd( collection );
		}
	};
}
