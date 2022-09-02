module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:HashAdapter;
import AtlasConcepts;
import AtlasExceptions;

export namespace Atlas
{
	template<typename DataType>
	class DLLApi HashAdapter :
		public std::false_type
	{
	    public:
		inline static auto GetHash(const DataType& instance)
		{
			throw AdapterResolveException( "Could not resolve HashAdapter", &instance);
		}
	};

	template<typename DataType>
		requires IsStandardHashable<DataType>
	class DLLApi HashAdapter<DataType> :
		public std::true_type
	{
		private: static constexpr bool NoExcept = noexcept( std::declval<std::hash<DataType>>( )( std::declval<DataType>( ) ) );

		private: static std::hash<DataType> Hash;


		public:
		inline static auto GetHash(const DataType& instance) noexcept( NoExcept )
		{
			return Hash(instance);
		}
	};

	template<typename DataType>
		requires HasGetHashFunction<DataType>
	class DLLApi HashAdapter<DataType> :
		public std::true_type
	{
		private: static constexpr bool NoExcept = noexcept ( std::declval<DataType>( ).GetHash( ) );
			
	    public:
		inline static auto GetHash(const DataType& instance)  noexcept( NoExcept )
		{
			return instance.GetHash();
		}
	};
}