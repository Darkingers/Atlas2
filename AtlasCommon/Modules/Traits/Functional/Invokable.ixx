module;

#include "../../../../Macros/Macros.h"

export module AtlasFunctionalTraits:Invokable;
import AtlasDefinitions;
import AtlasInterfaces;

export namespace Atlas::Trait
{
	template<typename ReturnType, typename DerivedType, typename... Args>
	class DLLApi Invokable :
		public Interface::IInvokable<ReturnType, Args...>
	{
		public: ReturnType operator()( Args&&... arguments )
		{
			return This( ).Invoke( std::forward<Args&&>( arguments )... );
		}

		private:
		inline DerivedType& This( )
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}