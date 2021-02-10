#include <iostream>
#include <new>
using namespace std;

template <typename T>
class Queue
{
private:
  T* p;
  int count;

public:
  Queue()
  {
    count = 0;
  }

  Queue(const Queue& obj)
  {

    count = obj.count;

    try {
      p = new T[count];
      for (int i = 0; i < count; i++)
        p[i] = obj.p[i];
    }
    catch (bad_alloc e)
    {
      cout << e.what() << endl;
      count = 0;
    }
  }

  void push(T item)
  {
    T* p2;
    p2 = p;

    try {
      p = new T[count + 1];

      for (int i = 0; i < count; i++)
        p[i] = p2[i];

      p[count] = item;

      count++;

      if (count > 1)
        delete[] p2;
    }
    catch (bad_alloc e)
    {
      cout << e.what() << endl;

      p = p2;
    }
  }

  T pop()
  {
    if (count == 0)
      return 0;

    T item;

    item = p[0];

    try {
      T* p2;

      p2 = new T[count - 1];

      count--;


      for (int i = 0; i < count; i++)
        p2[i] = p[i + 1];


      if (count > 0)
        delete[] p;


      p = p2;

      return item;
    }
    catch (bad_alloc e)
    {

      cout << e.what() << endl;
      return 0;
    }
  }


  Queue& operator=(const Queue& obj)
  {
    T* p2;

    try {
      p2 = new T[obj.count];

      if (count > 0)
        delete[] p;

      p = p2;
      count = obj.count;

      for (int i = 0; i < count; i++)
        p[i] = obj.p[i];
    }
    catch (bad_alloc e)
    {
      cout << e.what() << endl;
    }
    return *this;
  }

  ~Queue()
  {
    if (count > 0)
      delete[] p;
  }

  T GetItem()
  {
    if (count > 0)
      return p[0];
    else
      return 0;
  }

  void clear()
  {
    if (count > 0)
    {
      delete[] p;
      count = 0;
    }
  }

  bool IsEmpty()
  {
    return count == 0;
  }

  int GetN()
  {
    return count;
  }

  void print(const char* objName)
  {
    cout << "Object: " << objName << endl;
    for (int i = 0; i < count; i++)
      cout << p[i] << "\t";
    cout << endl;
    cout << "---------------------" << endl;
  }
};

int main()
{
  Queue<int> Q1;
  Q1.print("Q1");

  Q1.push(5);
  Q1.print("Q1");

  Q1.push(8);
  Q1.push(11);
  Q1.push(17);
  Q1.print("Q1");

  int d;
  d = Q1.GetItem();
  cout << "d = " << d << endl;

  Q1.print("Q1");

  Queue<int> Q2 = Q1;
  Q2.print("Q2");

  Queue<int> Q3;
  Q3 = Q1 = Q2;
  Q1.push(333);
  Q2.push(555);

  Q1.print("Q1");
  Q2.print("Q2");
  Q3.print("Q3");

  Q2.clear();
  if (Q2.IsEmpty())
    cout << "OK" << endl;
  else
    cout << "NO" << endl;

  cout << "n = " << Q3.GetN() << endl;
  return 0;
}


