module;

#include "../../../Macros/Macros.h"
#include <tuple>

export module AtlasMethods:MethodExtensions;
import AtlasDefinitions;
import :BoundMethod;
import :MemberMethod;


export namespace Atlas
{
	class DLLApi Method
	{
		public: template<typename ReturnType , typename... Args>
		inline static auto BindArguments( Definition::LambdaFunction<ReturnType , Args...> invoker , Args&&... arguments )
		{
			return BoundMethod<ReturnType , Args...>( invoker , std::forward<Args&&>( arguments )... );
		}

		public:  template<typename ReturnType , typename ClassType , typename... Args>
		inline static auto Create( ClassType* instance , Definition::MemberFunction<ReturnType , ClassType , Args...> invoked )
		{
			return MemberMethod<ReturnType , ClassType , Args...>( instance , invoked );
		}
	};
}