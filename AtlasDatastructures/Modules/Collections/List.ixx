module;

#include "../../../Macros/Macros.h"

export module AtlasCollections:List;
//
//export namespace Atlas
//{
//	template<typename DataType, Integer NumberType = int>
//	class DLLApi List :
//		public Object<List<DataType, NumberType>>
//	{
//		private: using LinkType = Link<DataType>;
//		private: using EnumeratorType = ListEnumerator<DataType, NumberType>;
//		private: using ListType = List<DataType, NumberType>;
//
//
//		protected: NumberType _size;
//		protected: LinkType* _start;
//		protected: LinkType* _last;
//
//
//		public: template<typename... Args> 
//		List( Args... arguments )  :
//			_size(0),
//			_start(nullptr),
//			_last(nullptr)
//		{
//			if constexpr ( sizeof...( arguments ) > 0 )
//			{
//				this->Add( arguments... );
//			}
//		}
//		
//		public: 
//		~List() 
//		{
//			if ( _start != nullptr )
//			{
//				_start->DeleteFollowingLinks();
//				delete _start;
//			}
//		}
//
//		public: template<typename... Args>
//		ListType& Add( Args... arguments )
//		{
//			_size += Helpher::Count( arguments... );
//			this->Add( arguments... );
//		}
//
//		public: template<typename... Args>
//		ListType& Add(DataType& data, Args... arguments )
//		{
//			if ( _first == nullptr )
//			{
//				_first = new LinkType( data );
//				_last = _first;
//			}
//			else
//			{
//				_last->Add( new LinkType( data ) );
//				_last = _last->Next;
//			}
//
//			if constexpr ( sizeof...( arguments ) > 0 )
//			{
//				this->Add( arguments... );
//			}
//
//			return *this;
//		}
//
//		public: template<typename CollectionType, typename... Args> requires AtlasIterableCollection<CollectionType, DataType, void( * )( DataType& ), bool( * )( DataType& )>
//		ListType& Add( CollectionType& collection, Args... arguments )
//		{
//			if ( _first == nullptr )
//			{
//				_first = new LinkType( data );
//				_last = _first;
//			}
//			else
//			{
//				LinkType* created = new LinkType();
//				collection.ForEach( [&created] ( DataType& data ) mutable
//				{
//					created->Add( data );
//					created = created->Next;
//				} );
//
//
//			}
//		}
//
//		public: template<typename CollectionType, typename... Args> requires StandardIterableCollection<CollectionType>
//		ListType& Add( CollectionType& collection, Args... arguments )
//		{
//
//		}
//	};
//}