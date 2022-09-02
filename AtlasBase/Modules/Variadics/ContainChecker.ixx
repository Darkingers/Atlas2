module;

#include "../../../Macros/Macros.h"

export module AtlasVariadics:ContainChecker;
import AtlasAdapters;
import AtlasConcepts;

export namespace Atlas::Variadics
{
	template<typename DataType>
	class DLLApi ContainChecker
	{
		public: template<typename... Args> requires IsSame<Args, DataType>
		inline static bool AnyContains(const DataType& data, const DataType& current, const Args&... arguments) 
		{
			const bool equals = (data == current);

			if constexpr ( sizeof...( arguments )>0)
			{
				return equals || ContainChecker<DataType>::AnyContains( data , std::forward<const Args&>(arguments)... );
			}
			else
			{
				return equals;
			}
		}

		public: template<typename CollectionType, typename... Args> requires IsSame<Args, DataType>
		inline static bool AllContains(const DataType& data, const DataType& current , const Args&... arguments ) 
		{
			const bool equals = ( data == current );		

			if constexpr ( sizeof...( arguments ) >0)
			{
				return equals && ContainChecker<DataType>::AllContains( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return equals;
			}
		}

		public: template<typename CollectionType, typename... Args> requires Adapters::ContainAdapter<CollectionType, DataType>::value
		inline static bool AnyContains(const DataType& data, const CollectionType& collection, const Args&... arguments )
		{
			const bool contains = Adapter::Contains( collection , data );

			if constexpr ( sizeof...( arguments ) >0)
			{
				return contains || ContainChecker<DataType>::AnyContains( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return contains;
			}
		}

		public: template<typename CollectionType, typename... Args>requires  Adapters::ContainAdapter<CollectionType , DataType>::value
		inline static bool AllContains(const DataType& data , const CollectionType& collection , const Args&... arguments )
		{
			const bool contains = Adapter::Contains( collection , data );

			if constexpr ( sizeof...( arguments )>0 )
			{
				return contains && ContainChecker<DataType>::AllContains( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return contains;
			}
		}
	};
}