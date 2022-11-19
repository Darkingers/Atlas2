module;

#include "../../Macros/Macros.h"
#include <tuple>

export module AtlasMethods;
export import :BoundMethod;
export import :MemberMethod;

import AtlasDefinitions;

export namespace Atlas
{
	class DLLApi Method
	{
		public: template<typename ReturnType , typename... Arguments>
			inline static auto BindValidates( Definition::LambdaFunction<ReturnType , Arguments...> invoker , Arguments&&... arguments )
		{
			return BoundMethod<ReturnType , Arguments...>( invoker , std::forward<Arguments&&>( arguments )... );
		}

		public:  template<typename ReturnType , typename ClassType , typename... Arguments>
			inline static auto Create( ClassType* instance , Definition::MemberFunction<ReturnType , ClassType , Arguments...> invoked )
		{
			return MemberMethod<ReturnType , ClassType , Arguments...>( instance , invoked );
		}
	};
}