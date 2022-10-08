module;

#include "../../../Macros/Macros.h"

export module AtlasAdapters:HashAdapter;

import AtlasTypeInfo;
import AtlasConcepts;
import AtlasExceptions;

export namespace Atlas::Adapters
{
	template<typename DataType>
	class DLLApi HashAdapter :
		public std::false_type
	{
	};
	
	template<typename DataType>
		requires Concept::IsStandardHashable<DataType>
	class DLLApi HashAdapter<DataType> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = noexcept( std::declval<std::hash<DataType>>( )( std::declval<DataType>( ) ) );

			
		private: static std::hash<DataType> Hash;

		public:
		constexpr inline static auto GetHash(const DataType& instance) 
			noexcept( IsNoexcept )
		{
			return Hash(instance);
		}
	};

	template<typename DataType>
		requires Concept::HasGetHashFunction<DataType>
	class DLLApi HashAdapter<DataType> :
		public std::true_type
	{
		public: constexpr static bool IsNoexcept = noexcept ( std::declval<DataType>( ).GetHash( ) );
			
			
	    public:
		constexpr inline static auto GetHash(const DataType& instance) 
			noexcept( IsNoexcept )
		{
			return instance.GetHash();
		}
	};
}