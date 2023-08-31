module;

#include "../../../../../Macros/Macros.h"

export module AtlasAdapters:CopyAdapters;

import AtlasDefinitions;
import AtlasConfiguration;
import AtlasValidation;
import AtlasConcepts;
import AtlasAPI;

export namespace Atlas
{
	template<typename TSource , typename TTarget> requires
		( !Concept::IsIndexable<TSource> ) &&
		( !Concept::IsIndexable<TTarget> ) &&
		Concept::HasIterator<TSource>&&
		Concept::HasIterator<TTarget>&&
		Concept::AreCompatibleCollections<TTarget , TSource>
	class DLLApi CopyCollectionToCollectionAdapter<TSource, TTarget> :
		public std::true_type
	{

	private:
		
		using SourceIterator = typename CollectionTraits<TSource>::ConstIteratorType;
		using TargetIterator = typename CollectionTraits<TTarget>::IteratorType;
		
	public:

		constexpr static inline void Copy( 
			TSource source, 
			unsigned int sourceStart,
			unsigned int sourceEnd, 
			TTarget target,
			unsigned int targetStart
		)
		{
			return ManipulationAPI::Copy
			(
				IteratorAPI::ConstAt( source, sourceStart ) ,
				IteratorAPI::ConstAt( source, sourceEnd ) ,
				IteratorAPI::At( target, targetStart )
			);
		}
	};
		
	template<typename TIteratorSource , typename TIteratorTarget> requires
		Concept::AreCompatibleIterators<TIteratorTarget, TIteratorSource>
	class DLLApi CopyIteratorToIteratorAdapter<TIteratorSource , TIteratorTarget> :
		public std::true_type
	{
	
	private:
		
		using ElementType = typename IteratorTraits<TIteratorSource>::IteratedType;
		
	public:

		constexpr static inline void Copy( 
			TIteratorSource start , 
			TIteratorSource end , 
			TIteratorTarget target 
		)
		{
			while ( start != end )
			{
				IteratorAPI::Current( target ) = IteratorAPI::Current( start );
				IteratorAPI::Next( start );
				IteratorAPI::Next( target );
			}
		}
	};

	template<typename TIteratorSource , typename TTargetCollection> requires
		Concept::IsIndexable<TTargetCollection> &&
		Concept::IsCompatibleIteratorFor<TIteratorSource , TTargetCollection>
	class DLLApi CopyIteratorToCollectionAdapter<TIteratorSource , TTargetCollection> :
		public std::true_type
	{
		
	private:

		using ElementType = typename IteratorTraits<TIteratorSource>::IteratedType;

	public:

		constexpr static inline void Copy( 
			TIteratorSource start , 
			TIteratorSource end , 
			TTargetCollection target 
		)
		{
			unsigned int i = 0;
			while ( start != end )
			{
				 target[i++] = IteratorAPI::Current( start );
				
				IteratorAPI::Next( start );
			}
		}
	};

	template<typename TSourceCollection , typename TTargetCollection> requires
		Concept::IsIndexable<TTargetCollection>&&
		Concept::IsIndexable<TSourceCollection>&&
		Concept::AreCompatibleCollections<TTargetCollection , TSourceCollection>
	class DLLApi CopyCollectionToCollectionAdapter<TSourceCollection, TTargetCollection> :
		public std::true_type
	{
		
	private:

		using ElementType = typename CollectionTraits<TTargetCollection>::IteratedType;
		
	public:

		constexpr static inline void Copy( 
			TSourceCollection source ,
			unsigned int sourceStart, 
			unsigned int sourceEnd, 
			TTargetCollection target,
			unsigned int targetStart
		)
		{
			for ( unsigned int i = sourceStart , j = targetStart; i < sourceEnd;  )
			{
				target[j++] = source[i++];
			}
		}
	};

	template<typename TSourceCollection , typename TIteratorTarget> requires
		Concept::IsIndexable<TSourceCollection> &&
		Concept::IsCompatibleIteratorFor<TIteratorTarget , TSourceCollection>
		class DLLApi CopyCollectionToIteratorAdapter<TSourceCollection, TIteratorTarget> :
		public std::true_type
	{

	private:

		using ElementType = typename IteratorTraits<TIteratorTarget>::IteratedType;

	public:

		constexpr static inline void Copy(
			TSourceCollection source ,
			unsigned int sourceStart ,
			unsigned int sourceEnd ,
			TIteratorTarget target
		)
		{
			for ( unsigned int i = sourceStart; i < sourceEnd; )
			{
				IteratorAPI::Current( target ) = source[i++];
				IteratorAPI::Next( target );
			}
		}
	};
}