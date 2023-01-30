module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:ReplaceFromAdapters;

import AtlasDefinitions;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TCollection, typename... TArgs> requires
		( !Concept::IsIndexable<TCollection> ) &&
		Concept::HasIterator<TCollection>
	class DLLApi ReplaceFromAdapter<TCollection , const unsigned int, TArgs...> :
		public std::true_type
	{

	private: 
	
		using IteratorType = typename CollectionTraits<TCollection>::IteratorType;
	
	public:

		constexpr static inline void ReplaceFrom
			(
				TCollection collection , 
				unsigned int start, 
				TArgs... args 
			)
			noexcept
			(
				Concept::IsNoexceptIterator<IteratorType> &&
				Concept::IsNoexceptLength<TCollection>&&
				Concept::IsNoexceptLength<TArgs...> &&
				Concept::IsNoexceptReplaceFrom<IteratorType ,TArgs...>
			)
		{
			ManipulationAPI::ReplaceFrom
			( 
				IteratorAPI::Begin( collection ) , 
				std::forward<TArgs>( args )... 
			);
		}
	};

	template<typename TIterator , typename TCollection , typename... TArgs> requires
		( !Concept::IsIndexable<TCollection> ) &&
		Concept::IsIteratorForType<TIterator, typename CollectionTraits<TCollection>::ElementType> &&
		Concept::HasIterator<TCollection>
	class DLLApi ReplaceFromAdapter<TIterator , TCollection , TArgs...> :
		public std::true_type
	{

	private:
		
		using ConstIteratorType = typename CollectionTraits<TCollection>::ConstIteratorType;
	
	public:

		constexpr static inline void ReplaceFrom
			(
				TIterator iterator ,
				TCollection collection ,
				TArgs... args 
			)
			noexcept
			(
				Concept::HasNoexceptConstIterator<TCollection>&&
				Concept::IsNoexceptIterator<TIterator>&&
				Concept::IsNoexceptReplaceFrom<TIterator, ConstIteratorType , ConstIteratorType , TArgs...>
			)
		{
			ManipulationAPI::ReplaceFrom
			(
				iterator ,
				IteratorAPI::ConstBegin( collection ) ,
				IteratorAPI::ConstEnd( collection ) ,
				std::forward<TArgs>( args )... 
			);
		}
	};

	template<typename TIterator , typename TIteratorSource , typename... TArgs> requires
		Concept::IsIterator<TIterator>&&
		Concept::IsIteratorForType<TIteratorSource, typename IteratorTraits<TIterator>::IteratedType>
	class DLLApi ReplaceFromAdapter<TIterator , TIteratorSource , TIteratorSource , TArgs...> :
		public std::true_type
	{

	private:

		using ElementType = typename IteratorTraits<TIterator>::IteratedType;

	public:

		constexpr static inline void ReplaceFrom
			(
				TIterator iterator ,
				TIteratorSource start, 
				TIteratorSource end , 
				TArgs... args
			)
			noexcept
			( 
				Concept::IsNoexceptAssignable<ElementType , ElementType>&&
				Concept::IsNoexceptIterator<TIterator>&& 
				Concept::IsNoexceptIterator<TIteratorSource> && 
				Concept::IsNoexceptReplaceFrom<TIterator, TArgs>
			)
		{
			while ( start != end )
			{
				IteratorAPI::Current( iterator ) = IteratorAPI::Current( start );

				IteratorAPI::Next( iterator );
				IteratorAPI::Next( start );
			}

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				ManipulationAPI::ReplaceFrom
				(
					iterator , 
					std::forward<TArgs>( args )... 
				);
			}
		}
	};

	template<typename TIterator , typename TElement , typename... TArgs> requires
		Concept::IsIteratorForType<TIterator , TElement>
	class DLLApi ReplaceFromAdapter<TIterator , TElement , TArgs...> :
		public std::true_type
	{

	public:

		constexpr static inline void ReplaceFrom
			(
				TIterator iterator ,
				TElement element ,
				TArgs... args
			)
			noexcept
			(
				Concept::IsNoexceptAssignable<TElement , TElement>&&
				Concept::IsNoexceptIterator<TIterator>&&
				Concept::IsNoexceptReplaceFrom<TIterator , TArgs...>
			)
		{
			IteratorAPI::Current( iterator ) = element;

			if constexpr ( sizeof...( TArgs ) > 0 )
			{
				IteratorAPI::Next( iterator );

				ManipulationAPI::ReplaceFrom
				(
					iterator ,
					std::forward<TArgs>( args )...
				);
			}
		}
	};

}