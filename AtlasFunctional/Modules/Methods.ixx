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
		public: template<typename ReturnType , typename... TArgs>
			inline static auto BindValidates( Definition::LambdaFunction<ReturnType , TArgs...> invoker , TArgs&&... arguments )
		{
			return BoundMethod<ReturnType , TArgs...>( invoker , std::forward<TArgs&&>( TArgs )... );
		}

		public:  template<typename ReturnType , typename ClassType , typename... TArgs>
			inline static auto Create( ClassType* instance , Definition::MemberFunction<ReturnType , ClassType , TArgs...> invoked )
		{
			return MemberMethod<ReturnType , ClassType , TArgs...>( instance , invoked );
		}
	};
}