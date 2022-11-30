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
//		public: template<typename... TArgs> 
//		List( TArgs... arguments )  :
//			_size(0),
//			_start(nullptr),
//			_last(nullptr)
//		{
//			if constexpr ( sizeof...( TArgs ) > 0 )
//			{
//				this->Add( TArgs... );
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
//		public: template<typename... TArgs>
//		ListType& Add( TArgs... arguments )
//		{
//			_size += Helpher::Count( TArgs... );
//			this->Add( TArgs... );
//		}
//
//		public: template<typename... TArgs>
//		ListType& Add(DataType& data, TArgs... arguments )
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
//			if constexpr ( sizeof...( TArgs ) > 0 )
//			{
//				this->Add( TArgs... );
//			}
//
//			return *this;
//		}
//
//		public: template<typename TCollection, typename... TArgs> requires AtlasIterableCollection<TCollection, DataType, void( * )( DataType& ), bool( * )( DataType& )>
//		ListType& Add( TCollection& collection, TArgs... arguments )
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
//		public: template<typename TCollection, typename... TArgs> requires StandardIterableCollection<TCollection>
//		ListType& Add( TCollection& collection, TArgs... arguments )
//		{
//
//		}
//	};
//}