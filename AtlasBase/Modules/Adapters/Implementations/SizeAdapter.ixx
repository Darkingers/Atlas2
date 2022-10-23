module;

#include "../../../../Macros/Macros.h"

export module AtlasAdapters:SizeAdapter;

import AtlasConcepts;
import AtlasTypeInfo;
import AtlasIntegration;

export namespace Atlas
{
	
	template<typename DataType>
		requires Concept::IsStandardCountable<DataType>
	class DLLApi SizeAdapter<DataType> :
		public std::true_type
	{
	    public:
		constexpr static inline auto Size(const DataType& instance)
			noexcept( noexcept ( instance.size( ) ) )
		{
			return instance.size( );
		}
	};

	template<typename DataType>
		requires Concept::HasCountFunction<DataType>
	class DLLApi SizeAdapter<DataType> :
		public std::true_type
	{	
	    public:
		constexpr static inline auto Size(const DataType& instance)
			noexcept( noexcept ( instance.Count( ) ) )
		{
			return instance.Count();
		}
	};

	template<>
	class DLLApi SizeAdapter<std::string> :
		public std::true_type
	{
		public:
		constexpr static inline auto Size( const std::string& instance )
			noexcept( noexcept ( instance.length( ) ) )
		{
			return instance.length( );
		}
	};

	template<>
	class DLLApi SizeAdapter<char*> :
		public std::true_type
	{
		public:
		constexpr static inline auto Size( const char* instance )
			noexcept
		{
			unsigned int i = 0;

			while ( instance[i++] != '\0' )
			{
				i++;
			}

			return i;
		}

		public: template<unsigned int Size>
		constexpr static inline auto Size( const char( &instance )[Size] )
			noexcept
		{
			return Size;
		}
	};
}
