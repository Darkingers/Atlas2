module;

#include "../../../Macros/Macros.h"

export module AtlasInvokers:MemberInvoker;
import AtlasDefinitions;
import AtlasValidation;
import AtlasConfiguration;
import AtlasFunctionalTraits;
import :BoundInvoker;

export namespace Atlas
{
	template<typename ReturnType, typename ClassType, typename... Args>
	class DLLApi MemberInvoker :
		public Trait::Invokable<ReturnType, MemberInvoker<ReturnType , ClassType , Args...>, Args...>
	{
		private: using MemberInvokerType = MemberInvoker<ReturnType , ClassType , Args...>;
		private: using InvokedType = Definition::MemberFunction<ReturnType , ClassType , Args...>;
		

		private: ClassType* _instance;
		private: InvokedType _invoked;

			
		public: 
		MemberInvoker( ClassType* instance , InvokedType invoked ) :
			_instance( instance ) ,
			_invoked( invoked )
		{
			if constexpr ( Configuration::EnableArgumentCheck )
			{
				Ensure::IsNotNull( instance );
			}
		}	

		public: 
		ReturnType Invoke( Args&&... arguments )
		{
			return ( _instance->*_invoked )( std::forward<Args&&>( arguments )... );
		}

		public:
		auto BindArguments( Args&&... arguments )
		{
			return BindInvoker( *this , std::forward<Args&&>( arguments )... );
		}
	};

	template<typename ReturnType , typename ClassType , typename... Args>	
	auto CreateInvoker( ClassType* instance , Definition::MemberFunction<ReturnType , ClassType , Args...> invoked ) 
	{
		return MemberInvoker<ReturnType , ClassType , Args...>( instance , invoked );
	}
}