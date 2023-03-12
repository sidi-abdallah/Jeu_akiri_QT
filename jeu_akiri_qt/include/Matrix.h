#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix
{

private:
    int _size;
    T * _data;
public:
    Matrix(int size);
    Matrix(Matrix &);
    ~Matrix();
    T & operator()(int row, int col);
    Matrix & operator=(Matrix & );
    int size();
    T * data();
};

template <typename T>
Matrix<T>::Matrix(int size)
{
    _size = size;
    _data = new T[_size * _size];
}

template <typename T>
int Matrix<T>::size() {
    return _size;
}

template <typename T>
T * Matrix<T>::data() {
    return _data;
}

template <typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> & other) {
    if(&other == this) {
       return *this;
    }
    delete [] _data;
    _size = other.size();
    _data = new T[_size * _size];
    memcpy(_data, other.data(), _size * _size * sizeof(T));
    return *this;
}

template <typename T>
T & Matrix<T>::operator()(int row, int col) {
    return _data[(row * _size) + col];
}

template <typename T>
Matrix<T>::~Matrix() {
    delete _data;
}

#endif // MATRIX_H
