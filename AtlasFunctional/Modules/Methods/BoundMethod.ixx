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
	template<typename ReturnType , typename... Arguments>
	class DLLApi BoundMethod :
		public Trait::Invokable<ReturnType, BoundMethod<ReturnType, Arguments...>, Arguments...>
	{
		private: using BoundMethodType = BoundMethod<ReturnType , Arguments...>;
		private: using FunctionType = Definition::LambdaFunction<ReturnType , Arguments...>;	
		private: using ValidateHolder = std::tuple<Arguments...>;
					   
		
		private: FunctionType _invoked;
		private: ValidateHolder _arguments;


		public:
		BoundMethod( FunctionType invoked ) noexcept :
			_invoked( invoked )
		{}	
		
		public:
		BoundMethod( FunctionType invoked, Arguments&&... args ) noexcept :
			_invoked( invoked ),
			_arguments(std::forward<Arguments&&>(args )... )
		{}

		public:
		BoundMethodType& Rebind( Arguments&&... args )
		{
			Tuple::Reassign( _arguments , std::forward<Arguments&&>( args )... );
		}

		public:
		ReturnType Invoke()
		{
			return std::apply( _invoked , _arguments );
		}
	};

}