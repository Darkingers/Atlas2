module;

#include "../../../../Macros/Macros.h"

export module AtlasCollectionTraits:Enumerable;
import AtlasDefinitions;
import AtlasDataFunctions;
import AtlasInterfaces;

export namespace Atlas::Trait
{
	template<typename DerivedType>
	class DLLApi Enumerable : 
		public Interface::IEnumerable<Deduce::CollectionContainedType<DerivedType>>
	{
		private: using DataType = Deduce::CollectionContainedType<DerivedType>;


		public: template<typename... Args>
		bool Contains( const Args&... arguments ) const  final
		{
			return DataFunctions::Contains( This( ) , std::forward<const Args&>( arguments )... );
		}

		public: template< typename... Args>
		unsigned int Count( const Args&... arguments ) const  final
		{
			return DataFunctions::Count( This( ) , std::forward<const Args&>( arguments )... );
		}

		public: 
		unsigned int Count( ) const  final
		{
			return This( ).GetSize( );
		}

		public: template<typename... Args>
		bool All(  const Args&... arguments ) const  final
		{
			return DataFunctions::All( This( ) , std::forward<const Args&>( arguments )... );
		}

		public: template<typename... Args>
		bool Any( const Args&... arguments ) const  final
		{
			return DataFunctions::Any( This( ) , std::forward<const Args&>( arguments )... );
		}

		public: template<typename... Args>
		DataType& First(  const Args&... arguments )const final
		{
			return DataFunctions::First( This() , std::forward<const Args&>( arguments )... );
		}

		public: template<typename... Args>
		DataType* FirstOrNullptr(  const Args&... arguments )const  final
		{
			return DataFunctions::FirstOrNullptr( This( ) , std::forward<const Args&>( arguments )... );
		}

		private:
		inline const DerivedType& This( ) const 
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}