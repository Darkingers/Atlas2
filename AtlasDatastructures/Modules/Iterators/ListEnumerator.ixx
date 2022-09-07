module;

#include "../../../Macros/Macros.h"

export module AtlasIterators:ListEnumerator;
import AtlasInterfaces;

export namespace Atlas
{
	template<typename DataType, typename NodeType>
	class DLLApi ListEnumerator :
        public IIterator<DataType>
	{
        private: using IteratorType = ListEnumerator<DataType, NodeType>;

        public: using iterator_category = std::bidirectional_iterator_tag;
        public: using difference_type = std::ptrdiff_t;
        public: using value_type = DataType;
        public: using pointer = DataType*;
        public: using reference = DataType&;




        private: NodeType* _current;


        public:
        ListEnumerator( NodeType* current ) :
            _current( current )
        {

        }

        public:
        ~ListEnumerator( ) final
        {}

        public:
        DataType& operator*( ) final
        {
            return _current->Data;
        }

        public:
        DataType* operator->( ) final
        {
            return &(_current->Data);
        }

        public:
        IteratorType& operator++( ) final
        {
            _current = _current->Next;
            return *this;
        }

        public:
        IteratorType& operator++( int) final
        {
            IteratorType tmp = *this;
            _current = _current->Next;
            return tmp;
        }

        public:
        IteratorType& operator--( ) final
        {
            _current = _current->Previous;
            return *this;
        }

        public:
        IteratorType operator--( int ) final
        {
            IteratorType tmp = *this; 
            _current = _current->Previous;
            return tmp;
        }

        friend bool operator== ( const IteratorType& a , const IteratorType& b )
        {
            return a._current == b._current;
        };

        friend bool operator!= ( const IteratorType& a , const IteratorType& b )
        {
            return a._current != b._current;
        };
	};
}