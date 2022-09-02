module;

#include "../../../Macros/Macros.h"

export module AtlasVariadics:Variadic;
import :ConditionChecker;
import :ConditionCounter;
import :ContainChecker;
import :Counter;

export namespace Atlas
{
	class DLLApi Variadic
	{
		public: template<typename... Args>
		inline static auto Count( const Args&... arguments )
		{
			return Variadics::Counter::Count( std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		inline static auto CountAny( const CollectionType& collection , const Args&... arguments )
		{
			return Variadics::ConditionCounter<CollectionType>::CountAny( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename CollectionType , typename... Args>
		inline static auto CountAll( const CollectionType& collection , const Args&... arguments )
		{
			return Variadics::ConditionCounter<CollectionType>::CountAll( collection , std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType, typename... Args>
		inline static bool AnyFulfills( const DataType& data, const Args&... arguments )
		{
			return Variadics::ConditionChecker<DataType>::AnyFulfills( data , std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType , typename... Args>
		inline static bool AllFulfills( const DataType& data , const Args&... arguments )
		{
			return Variadics::ConditionChecker<DataType>::AllFulfills( data , std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType , typename... Args>
		inline static bool AnyContains( const DataType& data , const Args&... arguments )
		{
			return Variadics::ContainChecker<DataType>::AnyContains( data , std::forward<const Args&>( arguments )... );
		}

		public: template<typename DataType , typename... Args>
		inline static bool AllContains( const DataType& data , const Args&... arguments )
		{
			return Variadics::ContainChecker<DataType>::AllContains( data , std::forward<const Args&>( arguments )... );
		}
	};
}