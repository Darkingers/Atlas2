module;

#include "../../../../Macros/Macros.h"

export module AtlasFunctionalTraits:Invokable;
import AtlasDefinitions;
import AtlasInterfaces;

export namespace Atlas::Trait
{
	template<typename ReturnType, typename DerivedType, typename... Arguments>
	class DLLApi Invokable :
		public Interface::IInvokable<ReturnType, Arguments...>
	{
		public:
		constexpr ReturnType operator()( Arguments&&... arguments )
		{
			return This( ).Invoke( std::forward<Arguments&&>( arguments )... );
		}

		private:
		constexpr inline DerivedType& This( )
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}