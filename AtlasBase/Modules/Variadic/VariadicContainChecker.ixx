module;

#include "../../../Macros/Macros.h"

export module AtlasVariadic:VariadicContainChecker;
import AtlasAdapters;
import AtlasConcepts;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi VariadicContainChecker
	{
		public: template<typename... Args> requires IsSame<Args, DataType>
		inline static bool Any(const DataType& data, const DataType& current, const Args&... arguments) 
		{
			using Checker = VariadicContainChecker<DataType>;

			const bool equals = (data == current);

			if constexpr ( sizeof...( arguments )>0)
			{
				return equals || Checker::Any( data , std::forward<const Args&>(arguments)... );
			}
			else
			{
				return equals;
			}
		}

		public: template<typename CollectionType, typename... Args> requires IsSame<Args, DataType>
		inline static bool All(const DataType& data, const DataType& current , const Args&... arguments ) 
		{
			using Checker = VariadicContainChecker<DataType>;

			const bool equals = ( data == current );		

			if constexpr ( sizeof...( arguments ) >0)
			{
				return equals && Checker::All( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return equals;
			}
		}

		public: template<typename CollectionType, typename... Args> requires ContainAdapter<CollectionType, DataType>::value
		inline static bool Any(const DataType& data, const CollectionType& collection, const Args&... arguments ) 
		{
			using Checker = VariadicContainChecker<DataType>;

			const bool contains = collection.Contains( data );

			if constexpr ( sizeof...( arguments ) >0)
			{
				return contains || Checker::Any( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return contains;
			}
		}

		public: template<typename CollectionType, typename... Args>requires ContainAdapter<CollectionType , DataType>::value
		inline static bool All(const DataType& data , const CollectionType& collection , const Args&... arguments ) 
		{
			using Checker = VariadicContainChecker<DataType>;

			const bool contains = collection.Contains( data );

			if constexpr ( sizeof...( arguments )>0 )
			{
				return contains && Checker::All( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return contains;
			}
		}
	};
}