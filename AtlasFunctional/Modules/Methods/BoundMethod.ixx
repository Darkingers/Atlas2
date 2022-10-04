module;

#include "../../../Macros/Macros.h"
#include <tuple>

export module AtlasMethods:BoundMethod;
import AtlasDefinitions;
import AtlasValidation;
import AtlasConfiguration;
import AtlasFunctionalTraits;
import AtlasExtensions;

export namespace Atlas
{
	template<typename ReturnType , typename... Args>
	class DLLApi BoundMethod :
		public Trait::Invokable<ReturnType, BoundMethod<ReturnType, Args...>, Args...>
	{
		private: using BoundMethodType = BoundMethod<ReturnType , Args...>;
		private: using FunctionType = Definition::LambdaFunction<ReturnType , Args...>;	
		private: using ArgumentHolder = std::tuple<Args...>;
					   
		
		private: FunctionType _invoked;
		private: ArgumentHolder _arguments;


		public:
		BoundMethod( FunctionType invoked ) noexcept :
			_invoked( invoked )
		{}	
		
		public:
		BoundMethod( FunctionType invoked, Args&&... args ) noexcept :
			_invoked( invoked ),
			_arguments(std::forward<Args&&>(args )... )
		{}

		public:
		BoundMethodType& Rebind( Args&&... args )
		{
			Extensions::Tuple::Reassign( _arguments , std::forward<Args&&>( args )... );
		}

		public:
		ReturnType Invoke()
		{
			return std::apply( _invoked , _arguments );
		}
	};

}