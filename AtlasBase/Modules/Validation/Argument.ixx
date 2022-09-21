module;

#include "../../../Macros/Macros.h"

export module AtlasValidation:Argument;
import AtlasConfiguration;
import AtlasDefinitions;
import AtlasAdapters;
import AtlasExceptions;
import :Ensure;

export namespace Atlas
{
	class DLLApi Argument
	{
		public:
		constexpr inline static void IsTrue( const bool a )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsTrue( a );
		}

		public:
		constexpr inline static void IsFalse( const bool a )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsFalse( a );
		}

		public: template<typename DataType>
		constexpr inline static void IsNull( const DataType* pointer )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsNull( pointer );
		}

		public: template<typename DataType>
		constexpr inline static void IsNotNull( const DataType* pointer )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsNotNull( pointer );
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsSame( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsSame( a, b );
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsNotSame( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsNotSame( a, b );
		}

		public: template<typename DataType>
		constexpr inline static void IsPositive( const DataType& a )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsPositive( a );
		}

		public: template<typename DataType>
		constexpr inline static void IsNegative( const DataType& a )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsNegative( a );
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsLess( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsLess( a, b );
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsMore( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsMore( a, b );
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void PositiveRange( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::PositiveRange( a, b );
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsLessOrEqual( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsLessOrEqual( a, b );
		}

		public: template<typename TypeA , typename TypeB>
		constexpr inline static void IsMoreOrEqual( const TypeA& a , const TypeB& b )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsMoreOrEqual( a ,b );
		}

		public: template<typename TypeA , typename TypeB , typename TypeC>
		constexpr inline static void IsInRange( const TypeA& number , const TypeB& inclusiveFrom , const TypeC& exclusiveTo )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsInRange( number, inclusiveFrom, exclusiveTo );
		}

		public: template<typename CollectionType>
		constexpr inline static void IsEmpty( const CollectionType& collection )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsEmpty( collection );
		}

		public: template<typename CollectionType>
		constexpr inline static void IsNotEmpty( const CollectionType& collection )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::IsNotEmpty( collection );
		}

		public: template<typename CollectionType , typename DataType = Deduce::CollectionContainedType<CollectionType>>
		constexpr inline static void Contains( const CollectionType& collection , const DataType& data )
		{
			if constexpr ( !Configuration::EnableArgumentCheck )
			{
				return;
			}

			Ensure::Contains( collection, data );
		}
	};
}