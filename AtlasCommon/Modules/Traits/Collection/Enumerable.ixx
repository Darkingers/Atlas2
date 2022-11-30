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


		public: template<typename... TArgs>
		constexpr bool Contains( const TArgs&... arguments ) const  final
		{
			return DataFunctions::Contains( This( ) , std::forward<const TArgs&>( TArgs )... );
		}

		public: template< typename... TArgs>
		constexpr unsigned int Count( const TArgs&... arguments ) const  final
		{
			return DataFunctions::Count( This( ) , std::forward<const TArgs&>( TArgs )... );
		}

		public: 
		constexpr unsigned int Count( ) const  final
		{
			return This( ).GetSize( );
		}

		public: template<typename... TArgs>
		constexpr bool All(  const TArgs&... arguments ) const  final
		{
			return DataFunctions::All( This( ) , std::forward<const TArgs&>( TArgs )... );
		}

		public: template<typename... TArgs>
		constexpr bool Any( const TArgs&... arguments ) const  final
		{
			return DataFunctions::Any( This( ) , std::forward<const TArgs&>( TArgs )... );
		}

		public: template<typename... TArgs>
		constexpr DataType& First(  const TArgs&... arguments )const final
		{
			return DataFunctions::First( This() , std::forward<const TArgs&>( TArgs )... );
		}

		public: template<typename... TArgs>
		constexpr DataType* FirstOrNullptr(  const TArgs&... arguments )const  final
		{
			return DataFunctions::FirstOrNullptr( This( ) , std::forward<const TArgs&>( TArgs )... );
		}

		private:
		constexpr inline const DerivedType& This( ) const
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}