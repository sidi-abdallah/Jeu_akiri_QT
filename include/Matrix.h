#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix
{

private:
    /**
     * @brief _size Size of matrix
     */
    int _size;

    /**
     * @brief _data Data of matrix
     */
    T * _data;
public:
    /**
     * @brief Matrix Constructor
     * @param size
     */
    Matrix(int size);

    /**
     * @brief Matrix Copy constructor
     */
    Matrix(Matrix &);

    ~Matrix();

    /**
     * @brief operator () Defines brackets operator
     * @param row
     * @param col
     * @return (row, col) matrix's element
     */
    T & operator()(int row, int col);

    /**
     * @brief operator = Copy assignment operator
     * @return matrix
     */
    Matrix & operator=(Matrix & );

    /**
     * @brief size Getter of _size
     * @return size of matrix
     */
    int size();

    /**
     * @brief data Getter of _data
     * @return _data
     */
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
