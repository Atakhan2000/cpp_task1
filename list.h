#ifndef TEMPLATES_LIST_2021_02_11
#define TEMPLATES_LIST_2021_02_11
#include <exception>
#include <stdexcept>

namespace lab618
{
    template<class T>
    class CSingleLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf * pnext;
            leaf(T& _data = T(), leaf * _pnext = nullptr)
            {
            	data = _data;
            	pnext = _pnext;
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator()
                : m_pCurrent(nullptr), m_pBegin(nullptr)
            {
            }

            CIterator(leaf *p)
            {
            	m_pBegin = nullptr;
            	m_pCurrent = p;
            }

            CIterator(const CIterator &src)
            {
            	this->m_pBegin = src.m_pBegin;
            	this->m_pCurrent = src.m_pCurrent;
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
            	this->m_pBegin = src.m_pBegin;
            	this->m_pCurrent = src.m_pCurrent;
            	return *this;
            }

            bool operator != (const CIterator&  it) const
            {
            	return (this->m_pCurrent != it.m_pCurrent) || (this->m_pBegin != it.m_pBegin);
            }

            void operator++()
            {
            	m_pCurrent = m_pCurrent->pnext;
            }

            T& getData()
            {
                return m_pCurrent->data;
            }

            T& operator* ()
            {
                return m_pCurrent->data;
            }

            leaf* getLeaf()
            {
                return m_pCurrent;
            }

            void setLeaf(leaf* p)
            {
                m_pBegin = nullptr;
                m_pCurrent = p;
            }

            void setLeafPreBegin(leaf* p)
            {
                m_pBegin = p;
                m_pCurrent = p;
            }

            bool isValid()
            {
                return m_pCurrent != nullptr;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
        };

    public:

        CSingleLinkedList(): m_pBegin(nullptr), m_pEnd(nullptr)
        {
        }

        virtual ~CSingleLinkedList()
        {
        	this->clear();
        }

        void pushBack(T& data)
        {
    		leaf *current = this->m_pBegin;
    		while (current->pnext != nullptr)
    		{
    			current = current->pnext;
    		}
    		current->pnext = new leaf(data);
    		current->pnext->pnext = m_pEnd;
        }

        void pushFront(T& data)
        {
            leaf* head = new leaf(data, nullptr);
            head->pnext = m_pBegin->pnext;
            m_pBegin->pnext = head;
        }

        T popFront()
        {
            if (m_pBegin->pnext == m_pEnd)
            {
                throw std::invalid_argument("Empty list"); //m_pBegin и m_pEnd всегда есть в листе
            }

            T data_h = m_pBegin->pnext->data;
            leaf* head = m_pBegin->pnext;
            m_pBegin->pnext = head->pnext;
            delete head;
            return data_h;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            leaf* s = m_pBegin;
            leaf* pRemoveLeaf = it.getLeaf();
            while (s->pnext != pRemoveLeaf) {
            	s = s->pnext;
            }
            it.setLeaf(s);
            s->pnext = pRemoveLeaf->pnext;
            delete pRemoveLeaf;
        }

        //не считает мнимые узлы m_pBegin и m_pEnd
        int getSize()
        {
            int size = 0;
            for (CIterator it = this->begin(); it.isValid(); ++it) {
                ++size;
            }
            return size;
        }

        void clear()
        {
            while (m_pBegin->pnext != m_pEnd)
            {
                leaf* pOldhead = m_pBegin->pnext;
                m_pBegin->pnext = pOldhead->pnext;
                delete pOldhead;
            }
        }

        CIterator begin()
        {
            return CIterator(m_pBegin->pnext); //head
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };

//DUAL LINKED list
    template<class T>
    class CDualLinkedList
    {
    private:
        struct leaf
        {
            T data;
            leaf * pnext, *pprev;
            leaf(T& _data = T(), leaf * _pprev = nullptr, leaf * _pnext = nullptr)
            {
            	data = _data;
            	pnext = _pnext;
            	pprev = _pprev;
            }
        };
    public:
        class CIterator
        {
        public:
            CIterator(): m_pCurrent(nullptr), m_pBegin(nullptr), m_pEnd(nullptr)
            {
            }

            CIterator(leaf *p)
            {
                m_pBegin = nullptr;
                m_pCurrent = p;
                m_pEnd = nullptr;
            }

            CIterator(const CIterator &src)
            {
            	this->m_pCurrent = src.m_pCurrent;
            	this->m_pBegin = src.m_pBegin;
            	this->m_pEnd = src.m_pEnd;
            }

            ~CIterator()
            {
            }

            CIterator& operator = (const CIterator&  src)
            {
            	this->m_pBegin = src.m_pBegin;
            	this->m_pCurrent = src.m_pCurrent;
            	this->m_pEnd = src.m_pEnd;
            	return *this;
            }

            bool operator != (const CIterator&  it) const
            {
            	return (this->m_pCurrent != it.m_pCurrent) ||(m_pBegin != it.m_pBegin)|| (m_pEnd != it.m_pEnd);
            }

            void operator++()
            {
                if (m_pCurrent == m_pEnd)
                {
                	throw std::invalid_argument("cur == end");
                }
            	m_pCurrent = m_pCurrent->pnext;
            }

            void operator--()
            {
                if (m_pCurrent == m_pBegin)
                {
                	throw std::invalid_argument("cur == begin");
                }
            	m_pCurrent = m_pCurrent->pprev;
            }

            T& getData()
            {
                return m_pCurrent->data;
            }

            T& operator* ()
            {
                return m_pCurrent->data;
            }

            leaf* getLeaf()
            {
                return m_pCurrent;
            }

            // применяется в erase и eraseAndNext
            void setLeaf(leaf* p)
            {
                m_pBegin = nullptr;
                m_pCurrent = p;
                m_pEnd = nullptr;
            }

            // применяется в erase и eraseAndNext
            void setLeafPreBegin(leaf* p)
            {
                m_pBegin = p;
                m_pCurrent = p;
                m_pEnd = nullptr;
            }

            // применяется в erase и eraseAndNext
            void setLeafPostEnd(leaf* p)
            {
                m_pBegin = nullptr;
                m_pCurrent = p;
                m_pEnd = p;
            }

            bool isValid()
            {
                return m_pCurrent != nullptr;
            }

        private:
            //храним голову списка, если мы находимся перед началом
            leaf* m_pBegin;
            // храним текущее положение
            leaf* m_pCurrent;
            //храним конец списка, если мы находимся после конца
            leaf* m_pEnd;
        };

    public:

        CDualLinkedList(): m_pBegin(nullptr), m_pEnd(nullptr)
        {
        };

        virtual ~CDualLinkedList()
        {
        	this->clear();
        };

        void pushBack(T& data)
        {
        	leaf* s = new leaf(data, nullptr, nullptr);
        	s->data = data;
        	s->pprev = m_pEnd->pprev;
        	s->pnext = m_pEnd;
        	m_pEnd->pprev->pnext = s;
        	m_pEnd->pprev = s;
        }

        T popBack()
        {
            T data = m_pEnd->pprev->data;
            if (m_pBegin->pnext == m_pEnd)
            {
            	throw std::invalid_argument("empty list");
            } else {
            	leaf* pOldTail = m_pEnd->pprev;
            	m_pEnd->pprev = pOldTail->pprev;
            	pOldTail->pprev->pnext = m_pEnd;
            	delete pOldTail;
            	return data;
            }
        }

        void pushFront(T& data)
        {
            leaf* pNewHead = new leaf(data, nullptr, nullptr);
            pNewHead->pnext = m_pBegin->pnext;
            //pNewHead->pprev = m_pBegin;
            m_pBegin->pnext = pNewHead;
            m_pBegin->pprev = nullptr;
            pNewHead->pnext->pprev = pNewHead;
        }

        T popFront()
        {
            if (m_pBegin->pnext == m_pEnd) {
            	throw std::invalid_argument("empty list");
            }

            T data = m_pBegin->pnext->data;
            leaf* pOldHead = m_pBegin->pnext;
            //pOldHead->pnext->pprev = m_pBegin;
            m_pBegin->pnext = pOldHead->pnext;
            delete pOldHead;
            return data;
        }

        // изменяет состояние итератора. выставляет предыдущую позицию.
        void erase(CIterator& it)
        {
            if (m_pBegin->pnext == m_pEnd) {
            	throw std::invalid_argument("empty list");
            }

            leaf* pOldLeaf = it.getLeaf();
            it.setLeaf(pOldLeaf->pprev);
            it.getLeaf()->pnext = pOldLeaf->pnext;
            pOldLeaf->pnext->pprev = it.getLeaf();
            delete pOldLeaf;
        }

        // изменяет состояние итератора. выставляет следующую позицию.
        void eraseAndNext(CIterator& it)
        {
            if (m_pBegin->pnext == m_pEnd) {
            	throw std::invalid_argument("empty list");
            }
            leaf* pOldLeaf = it.getLeaf();
            it.setLeaf(pOldLeaf->pnext);
            it.getLeaf()->pprev = pOldLeaf->pprev;
            pOldLeaf->pprev->pnext = it.getLeaf();
            delete pOldLeaf;
        }

        int getSize()
        {
            int size = 0;
            for (CIterator it = this->begin(); it.isValid(); ++it) {
                ++size;
            }
            return size;
        }

        void clear()
        {
            while (m_pBegin->pnext != m_pEnd) {
                leaf* pOldLeaf = m_pBegin->pnext;
                m_pBegin->pnext = m_pBegin->pnext->pnext;
                delete pOldLeaf;
            }
        }

        CIterator begin()
        {
            return CIterator(m_pBegin->pnext);
        }

        CIterator end()
        {
            return CIterator(m_pEnd);
        }

    private:
        leaf* m_pBegin, *m_pEnd;
    };
};
#endif //#ifndef TEMPLATES_LIST_2021_02_11
