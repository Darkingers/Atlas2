module;

#include "../../../Macros/Macros.h"
#include <vector>
#include <map>
#include <algorithm>

export module AtlasExtensions:Vector;
import AtlasDefinitions;
import AtlasConcepts;

export namespace Atlas::Extensions
{
	class DLLApi Vector
	{
		public: template<typename DataType>
		static void Remove( std::vector<DataType>& vector , const DataType& element )
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
		static void RemoveIf( std::vector<DataType>& vector , Definition::Condition<DataType> condition )
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
		static auto FindIterator( std::vector<DataType>& vector , const DataType& element )
		{
			return std::find( std::begin( vector ) , std::cend( vector ) , element );
		}

		public: template<typename DataType>
		static void Sort( std::vector<DataType>& vector )
		{
			std::sort( std::begin( vector ) , std::end( vector ) );
		}

		public: template<typename DataType>
		static void SortBy( std::vector<DataType>& vector , Definition::Comparator<DataType> comparator )
		{
			std::sort( std::begin( vector ) , std::end( vector ) , comparator );
		}	

		public: template<typename DataType , typename KeyType>
		static auto GroupBy( const std::vector<DataType>& vector , Definition::KeyGenerator<DataType, KeyType> keyGenerator )
		{
			std::map<KeyType , std::vector<DataType>> map;

			for ( const auto& element : vector )
			{
				map[keyGenerator( element )].push_back( element );
			}

			return map;
		}	

		public: template<typename DataType>
		static auto Count( const std::vector<DataType>& vector , const DataType& element )
		{
			return std::count( std::cbegin( vector ) , std::cend( vector ) , element );
		}

		public: template<typename DataType>
		static auto CountIf( const std::vector<DataType>& vector , Definition::Condition<DataType> condition )
		{
			return std::count_if( std::cbegin( vector ) , std::cend( vector ) , condition );
		}

		public: template<typename DataType>
		static auto Contains( const std::vector<DataType>& vector , const DataType& element )
		{
			return std::find( std::cbegin( vector ) , std::cend( vector ) , element ) != std::cend( vector );
		}

		public: template<typename DataType>
		static auto ContainsIf( const std::vector<DataType>& vector , Definition::Condition<DataType> condition )
		{
			return std::find_if( std::cbegin( vector ) , std::cend( vector ) , condition ) != std::cend( vector );
		}

		public: template<typename DataType>
		static auto ContainsAll( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
		{
			return std::all_of( std::cbegin( elements ) , std::cend( elements ) , [ &vector ]( const auto& element )
			{
				return Contains( vector , element );
			} );
		}

		public: template<typename DataType>
		static auto ContainsAny( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
		{
			return std::any_of( std::cbegin( elements ) , std::cend( elements ) , [ &vector ]( const auto& element )
			{
				return Contains( vector , element );
			} );
		}

		public: template<typename DataType>
		static auto ContainsNone( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
		{
			return std::none_of( std::cbegin( elements ) , std::cend( elements ) , [ &vector ]( const auto& element )
			{
				return Contains( vector , element );
			} );
		}
			
		public: template<typename DataType>
		static auto Difference( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
		{
			std::vector<DataType> result;

			for ( const auto& element : vector )
			{
				if ( !Vector::Contains( elements , element ) )
				{
					result.push_back( element );
				}
			}

			return result;
		}

		public: template<typename DataType>
		static auto Union( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
		{
			std::vector<DataType> result;

			for ( const auto& element : vector )
			{
				if ( !Vector::Contains( result , element ) )
				{
					result.push_back( element );
				}
			}

			for ( const auto& element : elements )
			{
				if ( !Vector::Contains( result , element ) )
				{
					result.push_back( element );
				}
			}

			return result;
		}

		public: template<typename DataType>
		static auto Intersection( const std::vector<DataType>& vector , const std::vector<DataType>& elements )
		{
			std::vector<DataType> result;

			for ( const auto& element : vector )
			{
				if ( Vector::Contains( elements , element ) )
				{
					result.push_back( element );
				}
			}

			return result;
		}			
	};
}
