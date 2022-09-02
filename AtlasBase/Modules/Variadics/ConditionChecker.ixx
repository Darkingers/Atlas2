module;

#include "../../../Macros/Macros.h"

export module AtlasVariadics:ConditionChecker;

export namespace Atlas::Variadics
{
	template<typename DataType>
	class DLLApi ConditionChecker
	{
		public: template<typename ConditionType, typename... Args>
		inline static bool AnyFulfills( const DataType& data, const ConditionType& condition, const Args&... arguments ) 
		{
			const bool fulfills = condition( data );

			if constexpr ( sizeof...( arguments )>0 )
			{
				return fulfills || ConditionChecker<DataType>::AnyFulfills( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return fulfills;
			}
		}

		public: template<typename ConditionType, typename... Args>
		inline static bool AllFulfills( const DataType& data, const ConditionType& condition, const Args&... arguments ) 
		{
			const bool fulfills = condition( data );

			if constexpr ( sizeof...( arguments )>0 )
			{
				return fulfills && ConditionChecker<DataType>::AllFulfills( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return fulfills;
			}
		}
	};
}