module;

#include "../../../Macros/Macros.h"

export module AtlasTraits:Enumerable;
import AtlasDefinitions;
import AtlasDataFunctions;
import AtlasInterfaces;

export namespace Atlas
{
	template<typename DerivedType>
	class DLLApi Enumerable : 
		public IEnumerable<DeduceCollectionContainedType<DerivedType>>
	{
		private: using DataType = DeduceCollectionContainedType<DerivedType>;


		public: template<typename... Args>
		bool Contains( const Args&&... arguments ) const  final
		{
			return DataFunctions::Contains( This( ) , std::forward<Args>( arguments )... );
		}

		public: template< typename... Args>
		unsigned int Count( const Args&... arguments ) const  final
		{
			return DataFunctions::Count( This( ) , std::forward<Args>( arguments )... );
		}

		public: 
		unsigned int Count( ) const  final
		{
			return This( ).GetSize( );
		}

		public: template<typename... Args>
		bool All(  const Args&... arguments ) const  final
		{
			return DataFunctions::All( This( ) , std::forward<Args>( arguments )... );
		}

		public: template<typename... Args>
		bool Any( const Args&... arguments ) const  final
		{
			return DataFunctions::Any( This( ) , std::forward<Args>( arguments )... );
		}

		public: template<typename... Args>
		DataType& First(  const Args&... arguments )const final
		{
			return DataFunctions::First( This() , std::forward<Args>( arguments )... );
		}

		public: template<typename... Args>
		DataType* FirstOrNullptr(  const Args&... arguments )const  final
		{
			return DataFunctions::FirstOrNullptr( This( ) , std::forward<Args>( arguments )... );
		}

		private:
		DerivedType& This( ) const  final
		{
			return static_cast<DerivedType&>( *this );
		}
	};
}