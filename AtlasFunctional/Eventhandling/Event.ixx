module;

#include "../../Macros/Macros.h"
#include <vector>

export module AtlasInvokers:BoundInvoker;
import AtlasDefinitions;
import AtlasFunctionalTraits;
import AtlasInvokers;

export namespace Atlas
{
	template<typename... Args>
	class DLLApi Event :
		public Trait::Invokable<void , Event<Args...>, Args...>
	{
		private: using LambdaType = Definition::LambdaFunction<void , Args...>;
		private: using StaticType = Definition::StaticFunction<void , Args...>;

		private: std::vector<LambdaType> _permanentInvokers;
		private: 

		public:
		BoundInvoker( FunctionType invoked ) noexcept :
			_invoked( invoked )
		{}

		public:
		BoundInvoker( FunctionType invoked , Args&&... args ) noexcept :
			_invoked( invoked ) ,
			_arguments( std::forward<Args&&>( args )... )
		{}

		public:
		BoundInvokerType& Rebind( Args&&... args )
		{
			Meta::Tuple::Reassign( _arguments , std::forward<Args&&>( args )... );
		}

		public:
		ReturnType Invoke( )
		{
			return std::apply( _invoked , _arguments );
		}
	};

	template<typename ReturnType , typename... Args>
	auto BindInvoker( Definition::LambdaFunction<ReturnType , Args...> invoker , Args&&... arguments )
	{
		return BoundInvoker<ReturnType , Args...>( invoker , std::forward<Args&&>( arguments )... );
	}
}