module;

#include "../../../Macros/Macros.h"

export module AtlasMethods:MemberMethod;
import AtlasDefinitions;
import AtlasValidation;
import AtlasConfiguration;
import AtlasFunctionalTraits;

export namespace Atlas
{
	template<typename ReturnType, typename ClassType, typename... Args>
	class DLLApi MemberMethod :
		public Trait::Invokable<ReturnType, MemberMethod<ReturnType , ClassType , Args...>, Args...>
	{
		private: using MemberMethodType = MemberMethod<ReturnType , ClassType , Args...>;
		private: using InvokedType = Definition::MemberFunction<ReturnType , ClassType , Args...>;
		

		private: ClassType* _instance;
		private: InvokedType _invoked;

			
		public: 
		MemberMethod( ClassType* instance , InvokedType invoked ) :
			_instance( instance ) ,
			_invoked( invoked )
		{
			Validate<true>::IsNotNull( instance );
		}	

		public: 
		ReturnType Invoke( Args&&... arguments )
		{
			return ( _instance->*_invoked )( std::forward<Args&&>( arguments )... );
		}
	};
}