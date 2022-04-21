#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <cstddef>
#include <utility>

//template <typename T>
using T = double;
class Vector
{
public:
    Vector() = default;

    Vector(const T* rawArray, const size_t size, float coef = 2.0):
            _size(size), _multiplicativeCoef(coef) {
        if (size == 0)
        {
            _capacity = int(coef);
        }
        else
        {
            _capacity = int(float(_size) * _multiplicativeCoef);
        }

//        _data = new T[_capacity];
//        for (size_t i = 0; i < _size; ++i)
//        {
//            _data[i] = rawArray[i];
//        }
         _data = copyWithAlloc(rawArray, _size, _capacity);
    }

    Vector(const Vector& other):
            Vector(other._data, other._size, other._multiplicativeCoef) {}

    Vector& operator=(const Vector& other)
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] _data;

        _data = new T[other._capacity];
        for (int i = 0; i < other._size; ++i)
        {
            _data[i] = std::move(other._data[i]);
        }
//        _data = copyWithAlloc(other._data, other._size, other._capacity);

        _size = other._size;
        _capacity = other._capacity;
        return *this;
    }

    Vector(Vector&& other) noexcept
    {
        *this = std::move(other);
    }

    Vector& operator=(Vector&& other) noexcept
    {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
        std::swap(_multiplicativeCoef, other._multiplicativeCoef);

        return *this;
    }

    ~Vector()
    {
        delete[] _data;
    }

    void pushBack(const T& value)
    {
        insert(value, _size);
    }

    void pushFront(const T& value)
    {
        insert(value, 0);
    }

    void insert(const T& value, size_t pos)
    {
//        if (!(pos <= _size))
//        {
//            return;
//        }
//        ++_size;
//        if (_capacity <= _size)
//        {
//            if (_capacity == 0)
//            {
//                _capacity = 1;
//            }
//            _capacity *= _multiplicativeCoef;
//
////        T* newData = new T[_capacity];
////        for (int i = _size - 2; i >= pos && i != -1; --i) {
////            newData[i + 1] = std::move(_data[i]);
////        }
////        for (int i = 0; i < pos; ++i) {
////            newData[i] = std::move(_data[i]);
////        }
////        delete[] _data;
////        _data = newData;
//            insertReAllocCopyToPos(_size - 2, pos, 1);
//        }
//        else {
//            for (int i = _size - 2; i >= pos && i != -1; --i) {
//                _data[i + 1] = std::move(_data[i]);
//            }
//        }
//        _data[pos] = std::move(value);

        T arr[]{value};
        insert(arr, 1, pos);
    }

    void insert(const T* values, size_t size, size_t pos)
    {
        if (!(pos <= _size))
        {
            return;
        }
        _size += size;
        if (_capacity <= _size)
        {
            _capacity += size;
            _capacity *= _multiplicativeCoef;
//        T* newData = new T[_capacity];
//        for (int i = _size - 2; i >= pos && i != -1; --i) {
//            newData[i + size] = std::move(_data[i]);
//        }
//        for (int i = 0; i < pos; ++i) {
//            newData[i] = _data[i];
//        }
//        delete[] _data;
//        _data = newData;
            insertReAllocCopyToPos(_size - 2, pos, size);
        }
        else {
            for (int i = _size - 2; i >= pos && i != -1; --i) {
                _data[i + size] = std::move(_data[i]);
            }
        }
        for (int i = pos; i < pos + size; ++i)
        {
            _data[i] = std::move(values[i - pos]);
        }
    }

    void insert(const Vector& vector, size_t pos)
    {
//        if (pos <= _size)
//        {
//            int size = vector._size;
//            T* values = vector._data;
//            _size += size;
//            if (_capacity <= _size)
//            {
//                _capacity += size;
//                _capacity *= _multiplicativeCoef;
////            T* newData = new T[_capacity];
////            for (int i = _size - size - 1; i >= pos && i != -1; --i)
////            {
////                newData[i + size] = std::move(_data[i]);
////            }
////            for (int i = 0; i < pos; ++i)
////            {
////                newData[i] = std::move(_data[i]);
////            }
////            delete[] _data;
////            _data = newData;
//                insertReAllocCopyToPos(_size - size - 1, pos, size);
//            }
//            else {
//                for (int i = _size - size - 1; i >= pos && i != -1; --i)
//                {
//                    _data[i + size] = std::move(_data[i]);
//                }
//            }
//            for (int i = pos; i < pos + size; ++i)
//            {
//                _data[i] = std::move(values[i - pos]);
//            }
//        }
        insert(vector._data, vector._size, pos);
    }

    void popBack()
    {
        isEmpty();
        --_size;
    }

    void popFront()
    {
        isEmpty();
        --_size;

        T* newData = new T[_capacity];
        for (int i = 0; i < _size; ++i)
        {
            newData[i] = _data[i + 1];
        }
//        T* newData = copyWithAlloc(_data, _size, _capacity);

        delete[] _data;
        _data = newData;
    }


    void erase(size_t pos, size_t count) {

        isEmpty();

        size_t end = pos + count;
        if (end > _size)
        {
            end = _size;
        }

        size_t k = 0;
        for (size_t i = end; i < _size; ++i)
        {
            _data[pos + k] = _data[i];
            ++k;
        }

        _size -= end - pos;
    }

//    void erase(size_t pos, size_t count)
//    {
//        if (_size == 0)
//        {
//            return;
//        }
//
//        size_t eraseSize = pos + count;
//
//        if (eraseSize > _size)
//        {
//            count -= eraseSize - _size;
//        }
//
//        for (int i = 0; i < _size - eraseSize; ++i)
//        {
//            _data[pos + i] = _data[eraseSize + i];
//        }
//        _size -= count;
//    }

    void eraseBetween(size_t beginPos, size_t endPos)
    {
        if (!(beginPos < _size && endPos <= _size) || beginPos >= endPos)
        {
            return;
        }
        isEmpty();

        int toErase = endPos - beginPos;
        for (int i = _size - 1; i >= endPos; --i)
        {
            _data[i - toErase] = std::move(_data[i]);
        }
        _size -= toErase;
    }
    // erase by eraseBetween

    T& operator[](size_t idx)
    {
        return _data[idx];
    }

    const T& operator[](size_t idx) const
    {
        return _data[idx];
    }

    [[nodiscard]] size_t size() const
    {
        return _size;
    }

    [[nodiscard]] size_t capacity() const
    {
        return _capacity;
    }

    [[nodiscard]] double loadFactor() const
    {
        return _multiplicativeCoef;
    }

    long long find(const T& value) const
    {
        for (int i = 0; i < _size; ++i)
        {
            if (_data[i] == value)
            {
                return i;
            }
        }
        return -1;
    }

    void reserve(size_t capacity)
    {
        if (capacity <= _capacity)
        {
            return;
        }
        _capacity = capacity;
        T* newData = new T[_capacity];
        for (int i = 0; i < _size; ++i)
        {
            newData[i] = std::move(_data[i]);
        }
//        T* newData = copyWithAlloc(_data, _size, _capacity);
        delete[] _data;
        _data = newData;
    }

    void shrinkToFit() {
        if (_size == _capacity)
        {
            return;
        }
        _capacity = _size;
        T* newData = new T[_capacity];
        for (int i = 0; i < _size; ++i)
        {
            newData[i] = std::move(_data[i]);
        }
//        T* newData = copyWithAlloc(_data, _size, _capacity);
        delete[] _data;
        _data = newData;
    }

    class Iterator {
    public:
        explicit Iterator(T* ptr) : _ptr(ptr) {}

        T & operator*() {
            return *_ptr;
        }

        const T& operator*() const {
            return *_ptr;
        }

        T* operator->() {
            return _ptr;
        }

        const T* operator->() const {
            return _ptr;
        }

        Iterator operator++() {
            ++_ptr;
            return *this;
        }

        Iterator operator++(int) {
            T* bufPtr = _ptr;
            ++_ptr;
            return Iterator(bufPtr);
        }

        Iterator operator--() {
            --_ptr;
            return *this;
        }

        Iterator operator--(int) {
            T* bufPtr = _ptr;
            --_ptr;
            return Iterator(bufPtr);
        }

        bool operator==(const Iterator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        T* _ptr;
    };

    Iterator begin() {
        return Iterator(&(_data[0]));
    }

    Iterator end() {
        return Iterator(&_data[_size]);
    }

private:
    T* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
    float _multiplicativeCoef = 2.0f;

    T* copyWithAlloc(const T*& source, size_t n, size_t capacity)
    {
        T* buf = new T[capacity];
        for (int i = 0; i < n; ++i)
        {
            buf[i] = std::move(source[i]);
        }
        return buf;
    }

    void insertReAllocCopyToPos(int from, int pos, int shift)
    {
        T* newData = new T[_capacity];
        for (int i = from; i >= pos && i != -1; --i)
        {
            newData[i + shift] = std::move(_data[i]);
        }
        for (int i = 0; i < pos; ++i)
        {
            newData[i] = std::move(_data[i]);
        }
        delete[] _data;
        _data = newData;
    }
    //Why i cant do that thing:
    // T* copyData(const T*& source, const size_t n,
    //                const size_t capacity = _capacity);

    void isEmpty() {
        if (_size == 0) {
            throw std::out_of_range("Empty vector popBack");
        }
    }
};



#endif //VECTOR_VECTOR_H
