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


		public: template<typename... Arguments>
		constexpr bool Contains( const Arguments&... arguments ) const  final
		{
			return DataFunctions::Contains( This( ) , std::forward<const Arguments&>( arguments )... );
		}

		public: template< typename... Arguments>
		constexpr unsigned int Count( const Arguments&... arguments ) const  final
		{
			return DataFunctions::Count( This( ) , std::forward<const Arguments&>( arguments )... );
		}

		public: 
		constexpr unsigned int Count( ) const  final
		{
			return This( ).GetSize( );
		}

		public: template<typename... Arguments>
		constexpr bool All(  const Arguments&... arguments ) const  final
		{
			return DataFunctions::All( This( ) , std::forward<const Arguments&>( arguments )... );
		}

		public: template<typename... Arguments>
		constexpr bool Any( const Arguments&... arguments ) const  final
		{
			return DataFunctions::Any( This( ) , std::forward<const Arguments&>( arguments )... );
		}

		public: template<typename... Arguments>
		constexpr DataType& First(  const Arguments&... arguments )const final
		{
			return DataFunctions::First( This() , std::forward<const Arguments&>( arguments )... );
		}

		public: template<typename... Arguments>
		constexpr DataType* FirstOrNullptr(  const Arguments&... arguments )const  final
		{
			return DataFunctions::FirstOrNullptr( This( ) , std::forward<const Arguments&>( arguments )... );
		}

		private:
		constexpr inline const DerivedType& This( ) const
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}