module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:HashAdapter;
import AtlasConcepts;
import AtlasExceptions;

export namespace Atlas::Adapters
{
	template<typename DataType>
	class DLLApi HashAdapter :
		public std::false_type
	{
		public:
		inline static auto GetHash( const DataType& instance )
		{
			Throw<AdapterResolveException>( "Could not resolve HashAdapter for" + typeid( DataType ).name( ) );
		}
	};
	
	template<typename DataType>
		requires Concept::IsStandardHashable<DataType>
	class DLLApi HashAdapter<DataType> :
		public std::true_type
	{
		private: static constexpr bool IsNoExcept = noexcept( std::declval<std::hash<DataType>>( )( std::declval<DataType>( ) ) );

		private: static std::hash<DataType> Hash;


		public:
		constexpr inline static auto GetHash(const DataType& instance) noexcept( IsNoExcept )
		{
			return Hash(instance);
		}
	};

	template<typename DataType>
		requires Concept::HasGetHashFunction<DataType>
	class DLLApi HashAdapter<DataType> :
		public std::true_type
	{
		private: static constexpr bool IsNoExcept = noexcept ( std::declval<DataType>( ).GetHash( ) );
			
	    public:
		constexpr inline static auto GetHash(const DataType& instance)  noexcept( IsNoExcept )
		{
			return instance.GetHash();
		}
	};
}