module;

#include "../../../Macros/Macros.h"

export module AtlasVariadic:VariadicConditionChecker;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi VariadicConditionChecker
	{
		public: template<typename ConditionType, typename... Args>
		inline static bool Any( const DataType& data, const ConditionType& condition, const Args&... arguments ) 
		{
			using Checker = VariadicConditionChecker<DataType>;

			const bool fulfills = condition( data );

			if constexpr ( sizeof...( arguments )>0 )
			{
				return fulfills || Checker::Any( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return fulfills;
			}
		}

		public: template<typename ConditionType, typename... Args>
		inline static bool All( const DataType& data, const ConditionType& condition, const Args&... arguments ) 
		{
			using Checker = VariadicConditionChecker<DataType>;

			const bool fulfills = condition( data );

			if constexpr ( sizeof...( arguments )>0 )
			{
				return fulfills && Checker::All( data , std::forward<const Args&>( arguments )... );
			}
			else
			{
				return fulfills;
			}
		}
	};
}