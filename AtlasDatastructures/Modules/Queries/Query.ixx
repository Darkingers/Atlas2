module;

#include "../../../Macros/Macros.h"

export module AtlasQueries:SelectionQuery;


export namespace Atlas
{
	/*
	template<typename DataType>
	class DLLApi SelectionQuery
	{
		private: using QueryType = SelectionQuery<DataType>;
		private: using ConditionType = Lambda<bool, const DataType&>;

		private: SpeedFriendlyMemoryHandler<ConditionType> _conditions;
		private: SpeedFriendlyMemoryHandler<DataType> _results;


		public:
		SelectionQuery( DataType* initialResults, unsigned int resultCount )  :
			_results( initialResults, resultCount )
		{

		}

		public:
		~SelectionQuery() 
		{

		}

		private:
		void Evaluate() 
		{
			if ( _conditions == 0 )
			{
				return;
			}

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				bool remove = false;

				for ( auto condition : _conditions )
				{
					if ( !condition( _results[i] ) )
					{
						remove = true;
						break;
					}
				}

				if ( remove )
				{
					removed++;
				}
				else
				{
					_results[i - removed] = _results[i];
				}
			}

			_results.Resize( _results - removed );
			_conditions.Resize( 0 );
		}

		public:
		const unsigned int Count() 
		{
			Evaluate();

			return _results;
		}

		public: template<typename... Arguments>
		QueryType& Where( Arguments&&... arguments ) 
		{
			const unsigned int index = _conditions;

			_conditions.Resize( _conditions + VariadicCounter<DataType>::Count( arguments... ) );

			Memory::ReplaceFrom( &_conditions[index], index, std::forward<Arguments>( arguments )... );

			return *this;
		}

		private: template<typename... Arguments>
		const unsigned int UnionConcat( unsigned int distinctCount, const DataType& data,const Arguments&... arguments )
		{
			assert( distinctCount >= 0 );

			bool distinct = true;
			for ( unsigned int i=0; i< distinctCount; )
			{
				if ( _results[i++] == data )
				{
					distinct = false;
					break;
				}
			}

			if ( distinct )
			{
				_results[distinctCount++] = data;
			}

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				return UnionConcat( distinctCount, arguments... );
			}
			else
			{
				return distinctCount;
			}
		}

		private: template<typename CollectionType, typename... Arguments> requires IsIterableWith<CollectionType, DataType>
		const unsigned int UnionConcat( unsigned int distinctCount, const CollectionType& collection, const Arguments&... arguments )
		{
			assert( distinctCount >= 0 );

			bool distinct;

			for ( auto data : collection )
			{
				distinct = true;

				for ( unsigned int i = 0; i < distinctCount;)
				{
					if ( _results[i++] == data )
					{
						distinct = false;
						break;
					}
				}

				if ( distinct )
				{
					_results[distinctCount++] = data;
				}
			}

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				return UnionConcat( distinctCount, arguments... );
			}
			else
			{
				return distinctCount;
			}
		}

		public: template<typename... Arguments>
		QueryType& Union( const Arguments&... arguments ) 
		{
			Distinct();

			_results.Resize( _results, VariadicCounter<DataType>::Count( arguments... ) );

			_results.Resize( UnionConcat( _results, _results, arguments... ) );

			return *this;
		}

		public: template<typename... Arguments>
		QueryType& Intersect( const Arguments&... arguments ) 
		{
			Evaluate();

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				if ( VariadicContainChecker<DataType>::All( _results[i], arguments... ) )
				{
					_results[i - removed] = _results[i];
				}
				else
				{
					++removed;
				}
			}

			_results.Resize( _results - removed );

			return *this;
		}

		public: template<typename... Arguments>
		QueryType& Except( const Arguments&... arguments ) 
		{
			Evaluate();

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				if ( !VariadicContainChecker<DataType>::Any( _results[i], arguments... ) )
				{
					_results[i - removed] = _results[i];
				}
				else
				{
					++removed;
				}
			}

			_results.Resize( _results - removed );

			return  *this;
		}

		public: template<typename... Arguments>
		QueryType& Concat( const Arguments&... arguments ) 
		{
			Evaluate();

			const unsigned int index = _results;

			_results.Resize( _results + VariadicCounter::Count( arguments... ) );

			Memory::ReplaceFrom( _results, index, arguments... );

			return *this;
		}

		public: template<typename ComparatorType, typename... Arguments>
		QueryType& Distinct( const ComparatorType comparator = DefaultComparator<const DataType&> ) 
		{
			Evaluate();

			bool distinct;
			unsigned int distinctCount = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				distinct = true;

				for ( unsigned int j = 0; j < distinctCount; ++j )
				{
					if ( comparator( _results[i], _results[j] ) == 0 )
					{
						distinct = false;
						break;
					}
				}

				if ( distinct )
				{
					_results[distinctCount++] = _results[i];
				}
			}

			_results.Resize( distinctCount );

			return *this;
		}

		public: template<typename... Arguments>
		QueryType& Between( const unsigned int from, const unsigned int to ) 
		{
			assert( from >= 0 && to >= 0 && from <= to );

			Evaluate();

			const unsigned int newSize = to - from + 1;

			for ( unsigned int i = 0; i < newSize; )
			{
				_results[i] = _results[i + from];
			}

			_results.Resize( newSize );

			return *this;
		}

		public: template<typename TargetDataType,typename ConverterType>
		SelectionQuery<TargetDataType>& Select( const ConverterType converter )const 
		{
			Evaluate();

			TargetDataType* resultSet = new TargetDataType[_results];

			unsigned int i = 0;
			for ( auto data : _results )
			{
				resultSet[i++] = converter( ( *data ) );
			}

			return new SelectionQuery( resultSet, _results );
		}

		public:
		DataType* begin() 
		{
			Evaluate();

			return _results.begin();
		}

		public:
		DataType* end() 
		{
			Evaluate();

			return _results.end();
		}

		public:
		DataType& operator[]( const unsigned int index ) 
		{
			assert( index >= 0 );

			Evaluate();

			assert( index <= _results );

			return _results[index];
		}
	};

	template<typename SourceCollectionType, typename DataType>
	class DLLApi Query
	{
		private: using QueryType = Query<SourceCollectionType, DataType>;

		class Iterator
		{
			private: SpeedFriendlyMemoryHandler<DataType*>& _results;
			private: unsigned int _current;

			public:
			Iterator( SpeedFriendlyMemoryHandler<DataType*>& results, const unsigned int current = 0 )  :
				_results(results),
				_current(current)
			{

			}

			public:
			Iterator& operator++() 
			{
				++_current;

				return *this;
			}

			public:
			Iterator& operator--() 
			{
				--_current;

				return *this;
			}


			public:
			operator DataType& ( ) 
			{
				return (*_results[_current]);
			}

			public:
			operator DataType* ( ) 
			{
				return ( *_results[_current] );
			}

			public:
			const bool operator==( const DataType& data ) const 
			{
				return (*_results[_current]) == data;
			}

			public:
			const bool operator!=( const DataType& data ) const 
			{
				return (*_results[_current]) != data;
			}

			public:
			const bool operator==( const DataType* data ) const 
			{
				return _results[_current] == data;
			}

			public:
			const bool operator!=( const DataType* data ) const 
			{
				return _results[_current] != data;
			}
		};


		private: SourceCollectionType* _sourceCollection;

		private: SpeedFriendlyMemoryHandler<ConditionType> _conditions;
		private: SpeedFriendlyMemoryHandler<DataType*> _results;

		private: bool _deleteSource;


		public:
		Query( SourceCollectionType* sourceCollection )  :
			_sourceCollection( sourceCollection ),
			_results( SizeAdapter<SourceCollectionType>::Count( *sourceCollection ) ),
			_deleteSource(false)
		{
		}

		public:
		Query( SourceCollectionType& sourceCollection )  :
			_sourceCollection( &sourceCollection ),
			_results( SizeAdapter<SourceCollectionType>::Count( sourceCollection ) ),
			_deleteSource( false )
		{
		}

		public:
		Query( SourceCollectionType&& sourceCollection )  :
			_sourceCollection( sourceCollection ),
			_results( SizeAdapter<SourceCollectionType>::Count( sourceCollection ) ),
			_deleteSource( true )
		{
		}

		public:
		~Query() 
		{
			if ( _deleteSource && _sourceCollection != nullptr)
			{
				delete _sourceCollection;
			}
		}

		private:
		void Evaluate() 
		{
			if ( _conditions == 0 )
			{
				return;
			}

			if ( _sourceCollection != nullptr )
			{
				bool add;
				unsigned int i = 0;

				for ( auto data : ( *_sourceCollection ) )
				{
					add = true;

					for ( auto condition : _conditions )
					{
						if ( !condition( data ) )
						{
							add = false;
							break;
						}
					}

					if ( add )
					{
						_results[i++] = &data;
					}
				}

				if ( _deleteSource )
				{
					delete _sourceCollection;
				}

				_sourceCollection = nullptr;
			}
			else
			{
				unsigned int removed = 0;

				for ( unsigned int i= 0, limit = _results; i < limit; ++i )
				{
					bool remove = false;

					for ( auto condition : _conditions )
					{
						if ( !condition( *_results[i] ) )
						{
							removed = true;
							break;
						}
					}

					if ( remove )
					{
						removed++;
					}
					else
					{
						_results[i - removed] = _results[i];
					}
				}

				_results.Resize( _results - removed );
			}

			_conditions.Resize( 0 );
		}

		public:
		const unsigned int Count() 
		{
			Evaluate();

			return _results;
		}

		public: template<typename... Arguments>
		QueryType& Where( Arguments&&... arguments ) 
		{
			const unsigned int index = _conditions;

			_conditions.Resize( _conditions + VariadicCounter<DataType>::Count( arguments... ) );

			Memory::ReplaceFrom( &_conditions[index], index, std::forward<Arguments>( arguments )... );

			return *this;
		}

		private: template<typename... Arguments>
		unsigned int UnionConcat (unsigned int distinctCount, const DataType& data, Arguments&... arguments )
		{
			assert( distinctCount >= 0 );

			bool distinct = true;
			for ( unsigned int i = 0; i < distinctCount; )
			{
				if ( ( *_results[i++] ) == data )
				{
					distinct = false;
					break;
				}
			}

			if ( distinct )
			{
				_results[distinctCount++] = &data;
			}

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				return UnionConcat( distinctCount, arguments... );
			}
			else
			{
				return distinctCount;
			}
		}

		private: template<typename CollectionType, typename... Arguments> requires IsIterableWith<const CollectionType, const DataType>
		unsigned int UnionConcat(unsigned int distinctCount, const CollectionType& collection, Arguments&... arguments )
		{
			assert( distinctCount >= 0 );

			bool distinct;

			for ( auto data : collection )
			{
				distinct = true;

				for ( unsigned int i = 0; i < distinctCount; ++i )
				{
					if ( ( *_results[i] ) == data )
					{
						distinct = false;
						break;
					}
				}

				if ( distinct )
				{
					_results[distinctCount++] = &data;
				}
			}

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				return UnionConcat( distinctCount, arguments... );
			}
			else
			{
				return distinctCount;
			}
		}

		public: template<typename... Arguments>
		QueryType& Union( const Arguments&... arguments ) 
		{
			Distinct();

			_results.Resize( _results, VariadicCounter::Count( arguments... ) );

			_results.Resize( UnionConcat( _results, _results, arguments...) );

			return *this;
		}

		public: template<typename... Arguments>
		QueryType& Intersect( const Arguments&... arguments ) 
		{
			Evaluate();

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit = _results; i < limit; ++i )
			{
				if ( VariadicContainChecker<DataType>::All( _results[i], arguments... ) )
				{
					_results[i - removed] = _results[i];
				}
				else
				{
					++removed;
				}
			}

			_results.Resize( _results - removed );

			return *this;
		}

		public: template<typename... Arguments>
		QueryType& Except( const Arguments&... arguments ) 
		{
			Evaluate();

			unsigned int removed = 0;

			for ( unsigned int i = 0, limit=_results; i < limit; ++i )
			{
				if ( !VariadicContainChecker<DataType>::Any( _results[i], arguments... ) )
				{
					_results[i - removed] = _results[i];
				}
				else
				{
					++removed;
				}
			}

			_results.Resize( _results - removed );

			return  *this;
		}

		private: template<typename... Arguments>
		void ReplaceFrom( unsigned int index, const DataType& data, Arguments&... arguments )
		{
			assert( index >= 0 );

			_results[index++] = &data;

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				ReplaceFrom( index, arguments... );
			}
		}

		private: template<typename CollectionType, typename... Arguments> requires IsIterable<const CollectionType, const DataType>
		void ReplaceFrom( unsigned int index, const CollectionType& collection, Arguments&... arguments )
		{
			assert( index >= 0 );

			for ( auto data : collection )
			{
				_results[index++] = &data;
			}

			if constexpr ( sizeof...( arguments ) > 0 )
			{
				ReplaceFrom( index, arguments... );
			}
		}

		public: template<typename... Arguments>
		QueryType& Concat( const Arguments&... arguments ) 
		{
			Evaluate();

			const unsigned int index = _results;

			_results.Resize( _results + VariadicCounter::Count( arguments... ) );

			ReplaceFrom( index, arguments... );

			return *this;
		}

		public: template<typename ComparatorType typename... Arguments>
		QueryType& Distinct( const ComparatorType comparator = DefaultComparator<const DataType&> ) 
		{
			bool distinct;
			unsigned int distinctCount = 0;

			for ( unsigned int i = 0, limit=_results; i < limit; ++i )
			{
				distinct = true;

				for ( unsigned int j = 0; j < distinctCount; ++j )
				{
					if ( comparator( (*_results[i]), (*_results[j]) ) == 0 )
					{
						distinct = false;
						break;
					}
				}

				if ( distinct )
				{
					_results[distinctCount++] = _results[i];
				}
			}

			_results.Resize( distinctCount );

			return *this;
		}

		public: template<typename... Arguments>
		QueryType& Between( const unsigned int from, const unsigned int to ) 
		{
			assert( from >= 0 && to >= 0 && from <= to );

			const unsigned int newSize = to - from + 1;

			for ( unsigned int i = 0; i<newSize; )
			{
				_results[i] = _results[i + from];
			}

			_results.Resize( newSize );

			return *this;
		}

		public: template<typename TargetDataType, typename ConverterType>
		SelectionQuery<TargetDataType>& Select( const ConverterType converter )const 
		{
			TargetDataType* resultSet = new TargetDataType[_results];

			unsigned int i = 0;
			for ( auto data : _results )
			{
				resultSet[i++] = converter( ( *data ) );
			}

			return (*new SelectionQuery( resultSet, _results ));
		}

		public:
		Iterator begin() 
		{
			Evaluate();

			return Iterator( _results );
		}

		public:
		Iterator end() 
		{
			Evaluate();

			return Iterator( _results, _results );
		}

		public:
		DataType& operator[]( const unsigned int index ) 
		{
			assert( index >= 0 );

			Evaluate();

			assert( index <= _results );

			return (*_results[index]);
		}
	};
}
*/
}