module;

#include "../../Macros/Macros.h"
#include <tuple>

export module AtlasInvokers:BoundInvoker;
import AtlasDefinitions;
import AtlasValidation;
import AtlasConfiguration;
import AtlasFunctionalTraits;
import AtlasMeta;

export namespace Atlas
{
	template<typename ReturnType , typename... Args>
	class DLLApi BoundInvoker :
		public Trait::Invokable<ReturnType, BoundInvoker<ReturnType, Args...>, Args...>
	{
		private: using BoundInvokerType = BoundInvoker<ReturnType , Args...>;
		private: using FunctionType = Definition::LambdaFunction<ReturnType , Args...>;	
		private: using ArgumentHolder = std::tuple<Args...>;
			   
			   
		private: ArgumentHolder _arguments;
		private: FunctionType _invoked;


		public:
		BoundInvoker( FunctionType invoked ) noexcept :
			_invoked( invoked )
		{}	
		
		public:
		BoundInvoker( FunctionType invoked, Args&&... args ) noexcept :
			_invoked( invoked ),
			_arguments(std::forward<Args&&>(args )... )
		{}

		public:
		BoundInvokerType& Rebind( Args&&... args )
		{
			Meta::Tuple::Reassign( _arguments , std::forward<Args&&>( args )... );
		}

		public:
		ReturnType Invoke()
		{
			return std::apply( _invoked , _arguments );
		}
	};

	template<typename ReturnType, typename... Args>
	auto BindInvoker( Definition::LambdaFunction<ReturnType, Args...> invoker, Args&&... arguments )
	{
		return BoundInvoker<ReturnType , Args...>( invoker , std::forward<Args&&>( arguments )... );	
	}
}