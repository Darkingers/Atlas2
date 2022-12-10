module;

#include "../../../Macros/Macros.h"

export module AtlasMethods:MemberMethod;
import AtlasDefinitions;
import AtlasValidation;
import AtlasConfiguration;
import AtlasFunctionalTraits;

export namespace Atlas
{
	template<typename ReturnType, typename ClassType, typename... TArgs>
	class DLLApi MemberMethod :
		public Trait::Invokable<ReturnType, MemberMethod<ReturnType , ClassType , TArgs...>, TArgs...>
	{
		private: using MemberMethodType = MemberMethod<ReturnType , ClassType , TArgs...>;
		private: using InvokedType = Definition::MemberFunction<ReturnType , ClassType , TArgs...>;
		

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
		ReturnType Invoke( TArgs&&... args )
		{
			return ( _instance->*_invoked )( std::forward<TArgs&&>( TArgs )... );
		}
	};
}