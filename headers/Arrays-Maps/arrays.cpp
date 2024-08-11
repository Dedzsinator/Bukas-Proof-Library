#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>

template<class T>
class SparseVector;

template<class T>
class Vector
{
public:
	Vector();
    Vector(size_t size);
    Vector(size_t size, const T& val);
    Vector(const Vector<T>& other);
    Vector<T>& operator=(const Vector<T>& other);
    ~Vector();

    void push_back(const T& value);
    void pop_back();
    size_t size() const;
    size_t capacity() const;
    void resize(size_t newSize, T val = T());

    const T& operator[](size_t index) const;
    T& operator[](int index);
    Vector<T> operator+(const Vector<T>& other);
    Vector<T> operator-(const Vector<T>& other);
    double operator*(const Vector<T>& other);
    double operator~();
    double operator%(const Vector<T>& other);
    T operator[](int index) const;

    void print();
    operator SparseVector<T>();
	template<class U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& v);

private:
	T*  m_t;
	int m_dim;
    
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
        for (int i = 0; i < v.m_dim; i++) {
            os << v.m_t[i] << " ";
        }
        return os;
}

template < class T >
struct nonZero
{
	T elem;
	int index;
};


template<class T>
class SparseVector
{
public:

	operator Vector<T>();
	SparseVector();
	SparseVector(int dim);
	SparseVector(T *t, int dim);
	SparseVector(const SparseVector&);
    ~SparseVector();
	int getDim() const;

	void push(T elem, int index);
	SparseVector operator+(const SparseVector&);
	SparseVector operator-(const SparseVector&);
	SparseVector<T>& operator=(const SparseVector<T>&);
	void pop();
	double operator*(const SparseVector&);
	double operator~();
	double operator%(const SparseVector&);
	template<class U>
	friend std::ostream& operator<<(std::ostream& os, const SparseVector<U>& v);
	T      operator[](int) const;
	void print();


private:


	nonZero <T> * vektor;
	int nZeroDim;
	int dim;
};

template<class T>
std::ostream& operator<<(std::ostream& os, const SparseVector<T>& rv) {
    for (int i = 0; i < rv.nZeroDim; i++) {
        os << "(" << rv.vektor[i].elem << ", " << rv.vektor[i].index << ") ";
    }
    return os;
}

template<class T>
Vector<T>::Vector() {
    m_dim = 0;
    m_t = nullptr;
}

template<class T>
Vector<T>::Vector(size_t size) {
    m_dim = size;
    m_t = new T[m_dim]();
    for(int i = 0; i < m_dim; i++) {
        m_t[i] = 1;
    }
}

template<class T>
Vector<T>::Vector(size_t size, const T& val) {
    m_dim = size;
    m_t = new T[m_dim];
    std::fill(m_t, m_t + m_dim, val);
}

template<class T>
Vector<T>::Vector(const Vector<T>& other) {
    m_dim = other.m_dim;
    m_t = new T[m_dim];
    std::copy(other.m_t, other.m_t + m_dim, m_t);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        delete[] m_t;
        m_dim = other.m_dim;
        m_t = new T[m_dim];
        std::copy(other.m_t, other.m_t + m_dim, m_t);
    }
    return *this;
}

template<class T>
void Vector<T>::push_back(const T& value) {
    T* new_t = new T[m_dim + 1];
    std::copy(m_t, m_t + m_dim, new_t);
    delete[] m_t;
    m_t = new_t;
    m_t[m_dim++] = value;
}

template<class T>
void Vector<T>::pop_back() {
    if (m_dim > 0) {
        T* new_t = new T[--m_dim];
        std::copy(m_t, m_t + m_dim, new_t);
        delete[] m_t;
        m_t = new_t;
    }
}

template<class T>
size_t Vector<T>::size() const {
    return m_dim;
}

template<class T>
void Vector<T>::resize(size_t newSize, T val) {
    T* new_t = new T[newSize];
    size_t minSize = m_dim < newSize ? m_dim : newSize;
    std::copy(m_t, m_t + minSize, new_t);
    if (newSize > m_dim) {
        std::fill(new_t + m_dim, new_t + newSize, val);
    }
    delete[] m_t;
    m_t = new_t;
    m_dim = newSize;
}

template<class T>
Vector<T>::~Vector() {
    delete[] m_t;
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) {
    if (m_dim != other.m_dim) {
        throw "Hiba! A vektorok dimenziója nem egyezik!";
    }

    Vector<T> result(m_dim);
    for (int i = 0; i < m_dim; i++) {
        result.m_t[i] = m_t[i] + other.m_t[i];
    }

    return result;
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) {
    if (m_dim != other.m_dim) {
        throw "Hiba! A vektorok dimenziója nem egyezik!";
    }

    Vector<T> result(m_dim);
    for (int i = 0; i < m_dim; i++) {
        result.m_t[i] = m_t[i] - other.m_t[i];
    }

    return result;
}

template<class T>
double Vector<T>::operator*(const Vector<T>& other) {
    if (m_dim != other.m_dim) {
        throw "Hiba! A vektorok dimenziója nem egyezik!";
    }

    double result = 0;
    for (int i = 0; i < m_dim; i++) {
        result += m_t[i] * other.m_t[i];
    }

    return result;
}

template<class T>
double Vector<T>::operator~() {
    double result = 0;

    for (int i = 0; i < m_dim; i++) {
        result += m_t[i] * m_t[i];
    }

    return sqrt(result);
}

template<class T>
double Vector<T>::operator%(const Vector<T>& other) {
    return ~(*this - other);
}

template<class T>
T& Vector<T>::operator[](int index) {
    if (index < 0 || index >= this->m_dim) {
        throw "Rossz index!";
    }
    return this->m_t[index];
}

template<class T>
T Vector<T>::operator[](int index) const {
    if (index < 0 || index >= m_dim) {
        throw "Hiba! Rossz index!";
    }

    return m_t[index];
}

template<class T>
void Vector<T>::print() {
    std::cout << *this;
}

template<class T>
Vector<T>::operator SparseVector<T>() {
    SparseVector<T> rv;
    
    for (size_t i = 0; i < this->m_dim; i++) {
        if (this->m_t[i] != 0) {
            rv.push(this->m_t[i], i);
        }
    }
    return rv;
}

template<class T>
SparseVector<T>::operator Vector<T>() {
    int max_index = 0;
    for (int i = 0; i < this->nZeroDim; i++) {
        if (this->vektor[i].index > max_index) {
            max_index = this->vektor[i].index;
        }
    }

    Vector<T> v(max_index + 1);
    for (int i = 0; i <= max_index; i++) {
        v[i] = 0;
    }
    for (int i = 0; i < this->nZeroDim; i++) {
        v[this->vektor[i].index] = this->vektor[i].elem;
    }
    return v;
}

template<class T>
SparseVector<T>::SparseVector() {
    this->dim = 0;
    this->nZeroDim = 0;
    this->vektor = new nonZero<T>[0];
}

template<class T>
SparseVector<T>::SparseVector(int dim) {
    this->dim = dim;
    this->nZeroDim = 1;
    this->vektor = new nonZero<T>[dim];
    this->vektor[0].index = 0;
    this->vektor[0].elem = 1;
    for (int i = 1; i < dim; i++) {
        this->vektor[i].index = i;
        this->vektor[i].elem = 0;
    } 
}

template<class T>
SparseVector<T>::SparseVector(T *t, int dim) {
    this->dim = dim;
    for (int i = 0; i < dim; i++) {
        if (t[i] != 0) {
            this->data[i] = t[i];
        }
    }
}

template<class T>
SparseVector<T>::SparseVector(const SparseVector<T>& other) {
    this->dim = other.dim;
    this->nZeroDim = other.nZeroDim;
    this->vektor = new nonZero<T>[this->dim];
    for (int i = 0; i < this->nZeroDim; i++) {
        this->vektor[i] = other.vektor[i];
    }
}

template<class T>
SparseVector<T>::~SparseVector() {
    delete[] vektor;
}

template<class T>
int SparseVector<T>::getDim() const {
    return this->dim;
}

template<class T>
void SparseVector<T>::push(T elem, int index) {

    if (elem == 0) {
        return;
    }

    if (this->nZeroDim >= this->dim || this->vektor == nullptr) {
        this->dim = (this->dim == 0) ? 1 : this->dim * 2;
        nonZero<T>* newVektor = new nonZero<T>[this->dim];
        for (int i = 0; i < this->nZeroDim; i++) {
            newVektor[i] = this->vektor[i];
        }
        delete[] this->vektor;
        this->vektor = newVektor;
    }

    int i = this->nZeroDim - 1;
    while (i >= 0 && this->vektor[i].index > index) {
        this->vektor[i + 1] = this->vektor[i];
        i--;
    }
    this->vektor[i + 1].index = index;
    this->vektor[i + 1].elem = elem;
    this->nZeroDim++;
}

template<class T>
void SparseVector<T>::pop() {
    if (this->nZeroDim == 0) {
        return;
    }
    this->nZeroDim--;
}

template<class T>
SparseVector<T>& SparseVector<T>::operator=(const SparseVector<T>& other) {
    if (this == &other) {
        return *this;
    }

    this->dim = other.dim;
    this->nZeroDim = other.nZeroDim;
    delete[] this->vektor;
    this->vektor = new nonZero<T>[this->dim];
    for (int i = 0; i < this->nZeroDim; i++) {
        this->vektor[i] = other.vektor[i];
    }
    return *this;
}

template<class T>
SparseVector<T> SparseVector<T>::operator+(const SparseVector<T>& other) {
    if (this->dim != other.dim) {
        throw "Eltero dimenziok!";
    }

    SparseVector<T> result(this->dim);
    result.nZeroDim = 0;

    int i = 0, j = 0;
    while (i < this->nZeroDim && j < other.nZeroDim) {
        if (this->vektor[i].index < other.vektor[j].index) {
            result.push(this->vektor[i].elem, this->vektor[i].index);
            i++;
        } else if (this->vektor[i].index > other.vektor[j].index) {
            result.push(other.vektor[j].elem, other.vektor[j].index);
            j++;
        } else {
            T sum = this->vektor[i].elem + other.vektor[j].elem;
            if (sum != 0) {
                result.push(sum, this->vektor[i].index);
            }
            i++;
            j++;
        }
    }

    while (i < this->nZeroDim) {
        result.push(this->vektor[i].elem, this->vektor[i].index);
        i++;
    }

    while (j < other.nZeroDim) {
        result.push(other.vektor[j].elem, other.vektor[j].index);
        j++;
    }

    return result;
}

template<class T>
SparseVector<T> SparseVector<T>::operator-(const SparseVector<T>& other) {
    if (this->dim != other.dim) {
        throw "Eltero dimenziok!";
    }

    SparseVector<T> result(this->dim);
    result.nZeroDim = 0;

    int i = 0, j = 0;
    while (i < this->nZeroDim && j < other.nZeroDim) {
        if (this->vektor[i].index < other.vektor[j].index) {
            result.push(this->vektor[i].elem, this->vektor[i].index);
            i++;
        } else if (this->vektor[i].index > other.vektor[j].index) {
            result.push(-other.vektor[j].elem, other.vektor[j].index);
            j++;
        } else {
            T diff = this->vektor[i].elem - other.vektor[j].elem;
            if (diff != 0) {
                result.push(diff, this->vektor[i].index);
            }
            i++;
            j++;
        }
    }

    while (i < this->nZeroDim) {
        result.push(this->vektor[i].elem, this->vektor[i].index);
        i++;
    }

    while (j < other.nZeroDim) {
        result.push(-other.vektor[j].elem, other.vektor[j].index);
        j++;
    }

    return result;
}

template<class T>
double SparseVector<T>::operator*(const SparseVector& rv) {
    if (this->dim != rv.dim) {
        throw "Eltero dimenziok!";
    }
    double result = 0;
    int i = 0, j = 0;
    while (i < this->nZeroDim && j < rv.nZeroDim) {
        if (this->vektor[i].index < rv.vektor[j].index) {
            i++;
        } else if (this->vektor[i].index > rv.vektor[j].index) {
            j++;
        } else {
            result += this->vektor[i].elem * rv.vektor[j].elem;
            i++;
            j++;
        }
    }
    return result;
}

template<class T>
double SparseVector<T>::operator%(const SparseVector& rv) {
    if (this->dim != rv.dim) {
        throw "Eltero dimenziok!";
    }

    double result = 0;

    int i = 0, j = 0;
    while (i < this->nZeroDim && j < rv.nZeroDim) {
        if (this->vektor[i].index < rv.vektor[j].index) {
            result += this->vektor[i].elem * this->vektor[i].elem;
            i++;
        } else if (this->vektor[i].index > rv.vektor[j].index) {
            result += rv.vektor[j].elem * rv.vektor[j].elem;
            j++;
        } else {
            double diff = this->vektor[i].elem - rv.vektor[j].elem;
            result += diff * diff;
            i++;
            j++;
        }
    }

    while (i < this->nZeroDim) {
        result += this->vektor[i].elem * this->vektor[i].elem;
        i++;
    }

    while (j < rv.nZeroDim) {
        result += rv.vektor[j].elem * rv.vektor[j].elem;
        j++;
    }

    return std::sqrt(result);
}

template<class T>
double SparseVector<T>::operator~() {
    double result = 0;
    for (int i = 0; i < this->nZeroDim; i++) {
        result += this->vektor[i].elem * this->vektor[i].elem;
    }
    return std::sqrt(result);
}

template<class T>
T SparseVector<T>::operator[](int index) const {
    if (index >= this->dim) {
        throw "Nincs ilyen index!";
    }
    for (int i = 0; i < this->nZeroDim; i++) {
        if (this->vektor[i].index == index) {
            return this->vektor[i].elem;
        }
    }
    return 0;
}

template<class T>
void SparseVector<T>::print() {
    std::cout << *this;
}
