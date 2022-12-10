module;

#include "../../../../Macros/Macros.h"

export module AtlasFunctionalTraits:Invokable;
import AtlasDefinitions;
import AtlasInterfaces;

export namespace Atlas::Trait
{
	template<typename ReturnType, typename DerivedType, typename... TArgs>
	class DLLApi Invokable :
		public Interface::IInvokable<ReturnType, TArgs...>
	{
		public:
		constexpr ReturnType operator()( TArgs&&... args )
		{
			return This( ).Invoke( std::forward<TArgs&&>( TArgs )... );
		}

		private:
		constexpr inline DerivedType& This( )
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}