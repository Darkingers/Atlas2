module;

#include "../../../../Macros/Macros.h"

export module AtlasFunctionalTraits:Executable;
import AtlasDefinitions;
import AtlasInterfaces;

export namespace Atlas::Trait
{
	template<typename ReturnType , typename DerivedType>
	class DLLApi Executable :
		public Interface::IExecutable<ReturnType>,
		public Interface::IInvokable<ReturnType>
	{
		public: ReturnType operator()( )
		{
			return This( ).Execute();
		}

		public: ReturnType Invoke( ) final
		{
			return This( ).Execute( );
		}

		private:
		inline DerivedType& This( )
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}