module;

#include "../../../../Macros/Macros.h"
#include <vector>
#include <map>
#include <algorithm>

export module AtlasExtensions:Vector;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas
{
	class DLLApi Vector
	{
		private: template<typename DataType>
		constexpr static bool IsNoexceptBegin = noexcept ( std::begin( std::vector<DataType>( ) ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptEnd = noexcept ( std::cend( std::vector<DataType>( ) ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptErase = noexcept (std::vector<DataType>( ).erase( std::declval<typename std::vector<DataType>::iterator>( ) ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptFindif = noexcept ( std::find_if( std::declval<typename std::vector<DataType>::iterator>( ) , std::declval<typename std::vector<DataType>::iterator>( ) , DataType( ) ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptFind = noexcept ( std::find( std::declval<typename std::vector<DataType>::iterator>( ) , std::declval<typename std::vector<DataType>::iterator>( ) , DataType( ) ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptInsert = noexcept (std::vector<DataType>( ).insert( std::declval<typename std::vector<DataType>::iterator>( ) ,DataType( ) ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptPushback = noexcept ( std::declval<std::vector<DataType>>( ).push_back(DataType( ) ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptSort = noexcept ( std::sort( std::declval<typename std::vector<DataType>::iterator>( ) , std::declval<typename std::vector<DataType>::iterator>( ) ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptSize = noexcept (std::vector<DataType>( ).size( ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptEmpty = noexcept ( std::declval<std::vector<DataType>>( ).empty( ) );
		private: template<typename DataType>
		constexpr static bool IsNoexceptCount = noexcept ( std::count( std::declval<typename std::vector<DataType>::iterator>( ) , std::declval<typename std::vector<DataType>::iterator>( ) ,DataType( ) ) );
			
			
		public: template<typename DataType>
		constexpr static void Remove( std::vector<DataType>& vector , const DataType& element )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType>&& IsNoexceptErase<DataType> )
		{
			const auto end = std::cend( vector );
			auto begin = std::begin( vector );
			
			auto iterator = std::find( begin , end , element );
			if ( iterator != end )
			{
				vector.erase( iterator );
			}
		}

		public: template<typename DataType>
		constexpr static void RemoveIf( std::vector<DataType>& vector , Definition::Condition<DataType> condition )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptErase<DataType> && IsNoexceptFindif<DataType> )
		{
			const auto end = std::cend( vector );
			auto begin = std::begin( vector );

			auto iterator = std::find_if( begin , end , condition );
			if ( iterator != end )
			{
				vector.erase( iterator );
			}
		}

		public: template<typename DataType>
		constexpr static auto FindIterator( std::vector<DataType>& vector , const DataType& element )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptFind<DataType> )
		{
			return std::find( std::begin( vector ) , std::cend( vector ) , element );
		}

		public: template<typename DataType>
		constexpr static void Sort( std::vector<DataType>& vector )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptSort<DataType> )
		{
			std::sort( std::begin( vector ) , std::end( vector ) );
		}

		public: template<typename DataType>
		constexpr static void SortBy( std::vector<DataType>& vector , Definition::Comparator<DataType> comparator )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType>&& IsNoexceptSort<DataType> && noexcept ( std::declval<Definition::Comparator<DataType>>()( DataType( ) ,DataType( ) ) ) )
		{
			std::sort( std::begin( vector ) , std::end( vector ) , comparator );
		}	

		public: template<typename DataType , typename KeyType>
		constexpr static auto GroupBy( const std::vector<DataType>& vector , Definition::KeyGenerator<DataType, KeyType> keyGenerator )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptPushback<DataType> && noexcept ( std::declval<Definition::KeyGenerator<DataType , KeyType>>( )( DataType( ) ) ) && noexcept ( std::declval<std::map<KeyType , std::vector<DataType>>>( ).insert( std::pair<KeyType , std::vector<DataType>>( ) ) ) )
		{
			std::map<KeyType , std::vector<DataType>> map;

			for ( const auto& element : vector )
			{
				map[keyGenerator( element )].push_back( element );
			}

			return map;
		}	

		public: template<typename DataType>
		constexpr static auto Count( const std::vector<DataType>& vector , const DataType& element )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptCount<DataType> )
		{
			return std::count( std::cbegin( vector ) , std::cend( vector ) , element );
		}

		public: template<typename DataType>
		constexpr static auto CountIf( const std::vector<DataType>& vector , Definition::Condition<DataType> condition )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && noexcept ( std::declval<Definition::Condition<DataType>>( )( DataType( ) ) ) && noexcept ( std::count_if( std::declval<typename std::vector<DataType>::iterator>( ) , std::declval<typename std::vector<DataType>::iterator>( ) , Definition::Condition<DataType>( ) ) ) )
		{
			return std::count_if( std::cbegin( vector ) , std::cend( vector ) , condition );
		}

		public: template<typename DataType>
		constexpr static auto Contains( const std::vector<DataType>& vector , const DataType& element )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptFind<DataType> )
		{
			return std::find( std::cbegin( vector ) , std::cend( vector ) , element ) != std::cend( vector );
		}

		public: template<typename DataType>
		constexpr static auto ContainsIf( const std::vector<DataType>& vector , Definition::Condition<DataType> condition )
			noexcept ( IsNoexceptBegin<DataType>&& IsNoexceptEnd<DataType> && noexcept ( std::declval<Definition::Condition<DataType>>( ) ( DataType ( ) ) ) && noexcept ( std::find_if( std::declval<typename std::vector<DataType>::iterator>( ) , std::declval<typename std::vector<DataType>::iterator>( ) , Definition::Condition<DataType>( ) ) ) )
		{
			return std::find_if( std::cbegin( vector ) , std::cend( vector ) , condition ) != std::cend( vector );
		}

		public: template<typename DataType>
		constexpr static auto ContainsAll( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptFind<DataType> )
		{
			return std::all_of( std::cbegin( elements ) , std::cend( elements ) , [ &vector ]( const auto& element )
			{
				return Contains( vector , element );
			} );
		}

		public: template<typename DataType>
		constexpr static auto ContainsAny( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptFind<DataType> )
		{
			return std::any_of( std::cbegin( elements ) , std::cend( elements ) , [ &vector ]( const auto& element )
			{
				return Contains( vector , element );
			} );
		}

		public: template<typename DataType>
		constexpr static auto ContainsNone( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptFind<DataType> )
		{
			return std::none_of( std::cbegin( elements ) , std::cend( elements ) , [ &vector ]( const auto& element )
			{
				return Contains( vector , element );
			} );
		}
			
		public: template<typename DataType>
		constexpr static auto Difference( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptPushback<DataType> )
		{
			std::vector<DataType> difference;

			for ( const auto& element : vector )
			{
				if ( !Contains( elements , element ) )
				{
					difference.push_back( element );
				}
			}

			return difference;
		}

		public: template<typename DataType>
		constexpr static auto Union( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptPushback<DataType> )
		{
			std::vector<DataType> unionVector;

			for ( const auto& element : vector )
			{
				if ( !Contains( unionVector , element ) )
				{
					unionVector.push_back( element );
				}
			}

			for ( const auto& element : elements )
			{
				if ( !Contains( unionVector , element ) )
				{
					unionVector.push_back( element );
				}
			}

			return unionVector;
		}

		public: template<typename DataType>
		constexpr static auto Intersection( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
			noexcept ( IsNoexceptBegin<DataType> && IsNoexceptEnd<DataType> && IsNoexceptPushback<DataType> )
		{
			std::vector<DataType> intersection;

			for ( const auto& element : vector )
			{
				if ( Contains( elements , element ) && !Contains( intersection , element ) )
				{
					intersection.push_back( element );
				}
			}

			return intersection;
		}		
	};
}
