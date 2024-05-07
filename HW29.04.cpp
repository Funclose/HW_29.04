#include <iostream>
using namespace std;

template <typename T, int maxSize>
class List
{
    T _element[maxSize];        // массив для хранения элементов списка
    int _nextIndices[maxSize];  // массив для хранеия индексов следующих элементов
    int _headIndex;             // индекс главного елемента
    int _freeIndex;             // индекс свободного елемента

public:

    List() : _headIndex(-1), _freeIndex(0)
    {
        for (int i = 0; i < maxSize - 1; i++)
        {
            _nextIndices[i] = i + 1;
        }
        _nextIndices[maxSize - 1] = -1;
    }

    // добавить новый элемент в начало списка
    void addToHead(const T& newData)
    {
        if (_freeIndex == -1)
        {
            cout << "error";
            return;
        }
        _element[_freeIndex] = newData;       
        int nextIndex = _nextIndices[_freeIndex];  


        _nextIndices[_freeIndex] = _headIndex;
        _headIndex = _freeIndex;

        _freeIndex = nextIndex;
    }

    //добавляет элемент в конец списка
    void addToTail(const T& newData)
    {
        int currentIndex = _headIndex;
        //поиск последнего элемента списка
        while (_nextIndices[currentIndex] != -1)
        {
            currentIndex = _nextIndices[currentIndex];
        }
        _element[_freeIndex] = newData;
        int nextFreeIndex = _nextIndices[_freeIndex];

        _nextIndices[currentIndex] = _freeIndex;
        _nextIndices[_freeIndex] = -1;

        _freeIndex = nextFreeIndex;
    }

    // удалить первый элемент со списка
    void deleteFromHead()
    {
        int nextHeadIndex = _nextIndices[_headIndex];
        _nextIndices[_headIndex] = _freeIndex;
        _freeIndex = _headIndex;

        _headIndex = nextHeadIndex;
    }

    // удалить последний элемент со списка
    void deleteFromTail()
    {
        int prevIndex = -1;
        int currentIndex = _headIndex;
        while (_nextIndices[currentIndex] != -1)
        {
            prevIndex = currentIndex;
            currentIndex = _nextIndices[currentIndex];  
        }
        if (prevIndex == -1)
        {
            deleteFromHead();
        }
        else
        {
            _nextIndices[prevIndex] = -1;
            _nextIndices[currentIndex] = _freeIndex;
            _freeIndex = currentIndex;
        }
    }

    // удалить все элементы со списка
    void deleteAll()
    {
        _headIndex = -1;
        _freeIndex = 0;

        
        for (int i = 0; i < maxSize - 1; i++)
        {
            _nextIndices[i] = i + 1;
        }
        _nextIndices[maxSize - 1] = -1;
    }


    void show()
    {
        int currentIndex = _headIndex;
        while (currentIndex != -1)
        {
            cout << _element[currentIndex] << " ";
            currentIndex = _nextIndices[currentIndex];
        }
        cout << endl;
    }
};

int main()
{
    const int maxSize = 5;
    List<int, maxSize> list;
    list.addToHead(3);
    list.addToHead(2);
    list.addToHead(4);
    list.show();
    list.deleteFromHead();
    list.show();
    list.deleteFromTail();
    list.show();
    list.deleteAll();
    list.show();

    return 0;
}