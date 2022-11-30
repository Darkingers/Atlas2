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
	template<typename ReturnType , typename... TArgs>
	class DLLApi BoundMethod :
		public Trait::Invokable<ReturnType, BoundMethod<ReturnType, TArgs...>, TArgs...>
	{
		private: using BoundMethodType = BoundMethod<ReturnType , TArgs...>;
		private: using FunctionType = Definition::LambdaFunction<ReturnType , TArgs...>;	
		private: using ValidateHolder = std::tuple<TArgs...>;
					   
		
		private: FunctionType _invoked;
		private: ValidateHolder _TArgs;


		public:
		BoundMethod( FunctionType invoked ) noexcept :
			_invoked( invoked )
		{}	
		
		public:
		BoundMethod( FunctionType invoked, TArgs&&... args ) noexcept :
			_invoked( invoked ),
			_TArgs(std::forward<TArgs&&>(args )... )
		{}

		public:
		BoundMethodType& Rebind( TArgs&&... args )
		{
			Tuple::Reassign( _TArgs , std::forward<TArgs&&>( args )... );
		}

		public:
		ReturnType Invoke()
		{
			return std::apply( _invoked , _TArgs );
		}
	};

}