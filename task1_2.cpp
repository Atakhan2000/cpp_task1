#include <iostream>
using namespace std;

template <typename T>
struct NodeStack
{
  T item;
  NodeStack<T>* next;
};

template <typename T>
class StackList
{
private:
  NodeStack<T>* pTop;

public:
  StackList() { pTop = nullptr; }

  StackList(const StackList& SL)
  {
    NodeStack<T>* p;
    NodeStack<T>* p2;
    NodeStack<T>* p3;

    pTop = nullptr;
    p3 = nullptr;

    p = SL.pTop;
    while (p != nullptr)
    {
      try {
        p2 = new NodeStack<T>;
      }
      catch (bad_alloc e)
      {
        cout << e.what() << endl;
        return;
      }
      p2->item = p->item;
      p2->next = nullptr;

      if (pTop == nullptr)
      {
        pTop = p2;
        p3 = p2;
      }
      else
      {
        p3->next = p2;
        p3 = p3->next;
      }

      p = p->next;
    }
  }

  void Push(T item)
  {
    NodeStack<T>* p;

    try {
      p = new NodeStack<T>;
    }
    catch(bad_alloc e)
    {
      cout << e.what() << endl;
      return;
    }
    p->item = item;
    p->next = pTop;

    pTop = p;
  }

  // Количество элементов в стеке
  int Count()
  {
    if (pTop == nullptr)
      return 0;
    else
    {
      NodeStack<T>* p = pTop;
      int count = 0;

      while (p != nullptr)
      {
        count++;
        p = p->next;
      }
    }
  }

  // очищает стек - удаляет все элементы из стека
  void Empty()
  {
    NodeStack<T>* p;
    NodeStack<T>* p2;

    p = pTop;

    while (p != nullptr)
    {
      p2 = p;
      p = p->next;
      delete p2;
    }
    pTop = nullptr;
  }

  // оператор копирования
  StackList<T>& operator=(const StackList<T>& LS)
  {
    if (pTop != nullptr) Empty();

    NodeStack<T>* p;
    NodeStack<T>* p2;
    NodeStack<T>* p3;

    pTop = nullptr;
    p3 = nullptr;

    p = LS.pTop;
    while (p != nullptr)
    {
      try {
        p2 = new NodeStack<T>;
      }
      catch (bad_alloc e)
      {

        cout << e.what() << endl;
        return *this;
      }
      p2->item = p->item;
      p2->next = nullptr;


      if (pTop == nullptr)
      {
        pTop = p2;
        p3 = p2;
      }
      else
      {
        p3->next = p2;
        p3 = p3->next;
      }

      p = p->next;
    }
    return *this;
  }

  void Print(const char* objName)
  {
    cout << "Object: " << objName << endl;
    if (pTop == nullptr)
      cout << "stack is empty." << endl;
    else
    {
      NodeStack<T>* p;
      p = pTop;
      while (p != nullptr)
      {
        cout << p->item << "\t";
        p = p->next;
      }
      cout << endl;
    }
  }

  ~StackList()
  {
    Empty();
  }

  T Pop()
  {
    if (pTop == nullptr)
      return 0;

    NodeStack<T>* p2;
    T item;
    item = pTop->item;

    p2 = pTop;
    pTop = pTop->next;

    delete p2;

    return item;
  }
};

int main()
{
  StackList<int> SL;
  SL.Print("SL");

  SL.Push(8);
  SL.Push(5);
  SL.Push(10);
  SL.Push(7);
  SL.Print("SL");

  StackList<int> SL2 = SL;
  SL2.Print("SL2");

  SL.Empty();
  SL.Print("SL");

  SL = SL2;
  SL.Print("SL = SL2");

  StackList<int> SL3;
  SL3.Push(1);
  SL3.Push(2);
  SL3.Push(3);
  SL3.Print("SL3");

  SL = SL2 = SL3;
  SL.Print("SL");
  SL2.Print("SL2");

  int d = SL2.Pop();

  cout << "d = " << d << endl;
  SL2.Print("SL2-1");

  d = SL2.Pop();
  SL2.Print("SL2-2");

  d = SL2.Pop();
  SL2.Print("SL2-3");

  d = SL2.Pop();
  cout << "d = " << d << endl;
  SL2.Print("SL2----");
  return 0;
}

