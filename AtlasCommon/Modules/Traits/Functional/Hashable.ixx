module;

#include "../../../../Macros/Macros.h"

export module AtlasFunctionalTraits:Hashable;
import AtlasDefinitions;
import AtlasInterfaces;

export namespace Atlas::Trait
{
	template<typename DerivedType>
	class DLLApi Hashable :
		public Interface::IHashable
	{
		public: bool operator== (const DerivedType& a )
		{
			return This( ).GetHash( ) == a.GetHash( );
		};

		public: bool operator!= ( const DerivedType& a )
		{
			return This( ).GetHash( ) != a.GetHash( );
		};

		private: 
		inline DerivedType& This( )
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}