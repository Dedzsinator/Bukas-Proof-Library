#pragma once

#include <iostream>

template <typename T>
class Matrix {
private:
    T** data;
    int rows;
    int cols;

public:
    Matrix();
    Matrix(int rows, int cols);
    ~Matrix();
    void set(int row, int col, T value);
    T get(int row, int col);
    int getRows();
    int getCols();
    void clear();
    void copy(const Matrix<T>& other);
    void copy(Matrix<T>&& other);
    void resize();
    void swap(Matrix<T>& other);
    bool operator==(const Matrix<T>& other);
    bool operator!=(const Matrix<T>& other);
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);
    template <typename U>
    friend std::istream& operator>>(std::istream& is, Matrix<U>& matrix);
};

template <typename T>
class sparseMatrix : public Matrix<T> {
  private :
    int* row;
    int* col;
    T* val;
    int* nextInd;
    int* rowPtr;
    int* colPtr;

  public:
    sparseMatrix() {
        this->rows = 0;
        this->cols = 0;
        row = nullptr;
        col = nullptr;
        val = nullptr;
        nextInd = nullptr;
        rowPtr = nullptr;
        colPtr = nullptr;
    }
    sparseMatrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        row = new int[rows * cols];
        col = new int[rows * cols];
        val = new T[rows * cols];
        nextInd = new int[rows * cols];
        rowPtr = new int[rows + 1];
        colPtr = new int[cols + 1];
        for (int i = 0; i < rows * cols; i++) {
            row[i] = -1;
            col[i] = -1;
            val[i] = 0;
            nextInd[i] = -1;
        }
        for (int i = 0; i < rows + 1; i++) {
            rowPtr[i] = i * cols;
        }
        for (int i = 0; i < cols + 1; i++) {
            colPtr[i] = i * rows;
        }
    }
    ~sparseMatrix() {
        clear();
    }

    void set(int row, int col, T value) {
        int index = rowPtr[row];
        int prevIndex = -1;
        while (index != -1) {
            if (this->col[index] == col) {
                this->val[index] = value;
                return;
            }
            if (this->col[index] > col) {
                break;
            }
            prevIndex = index;
            index = this->nextInd[index];
        }
        if (prevIndex == -1) {
            this->nextInd[rowPtr[row]] = this->nextInd[rowPtr[row]];
            this->row[rowPtr[row]] = row;
            this->col[rowPtr[row]] = col;
            this->val[rowPtr[row]] = value;
            this->nextInd[rowPtr[row]] = index;
            rowPtr[row]++;
        } else {
            this->nextInd[prevIndex] = this->nextInd[prevIndex];
            this->row[prevIndex] = row;
            this->col[prevIndex] = col;
            this->val[prevIndex] = value;
            this->nextInd[prevIndex] = index;
        }
    }

    T get(int row, int col) {
        int index = rowPtr[row];
        while (index != -1) {
            if (this->col[index] == col) {
                return this->val[index];
            }
            index = this->nextInd[index];
        }
        return 0;
    }

    void clear() {
        delete[] row;
        delete[] col;
        delete[] val;
        delete[] nextInd;
        delete[] rowPtr;
        delete[] colPtr;
        row = nullptr;
        col = nullptr;
        val = nullptr;
        nextInd = nullptr;
        rowPtr = nullptr;
        colPtr = nullptr;
    }

    void copy(const sparseMatrix<T>& other) {
        this->row = new int[other.getRows() * other.getCols()];
        this->col = new int[other.getRows() * other.getCols()];
        this->val = new T[other.getRows() * other.getCols()];
        this->nextInd = new int[other.getRows() * other.getCols()];
        this->rowPtr = new int[other.getRows() + 1];
        this->colPtr = new int[other.getCols() + 1];
        for (int i = 0; i < other.getRows() * other.getCols(); i++) {
            this->row[i] = other.row[i];
            this->col[i] = other.col[i];
            this->val[i] = other.val[i];
            this->nextInd[i] = other.nextInd[i];
        }
        for (int i = 0; i < other.getRows() + 1; i++) {
            this->rowPtr[i] = other.rowPtr[i];
        }
        for (int i = 0; i < other.getCols() + 1; i++) {
            this->colPtr[i] = other.colPtr[i];
        }
    }

    void copy(sparseMatrix<T>&& other) {
        this->row = other.row;
        this->col = other.col;
        this->val = other.val;
        this->nextInd = other.nextInd;
        this->rowPtr = other.rowPtr;
        this->colPtr = other.colPtr;
        other.row = nullptr;
        other.col = nullptr;
        other.val = nullptr;
        other.nextInd = nullptr;
        other.rowPtr = nullptr;
        other.colPtr = nullptr;
    }

    void resize() {
        delete[] row;
        delete[] col;
        delete[] val;
        delete[] nextInd;
        delete[] rowPtr;
        delete[] colPtr;
        row = new int[this->getRows() * this->getCols()];
        col = new int[this->getRows() * this->getCols()];
        val = new T[this->getRows() * this->getCols()];
        nextInd = new int[this->getRows() * this->getCols()];
        rowPtr = new int[this->getRows() + 1];
        colPtr = new int[this->getCols() + 1];
    }

    void operator =(sparseMatrix<T>& other) {
        this->copy(other);
    }
    bool operator==(const sparseMatrix<T>& other) {
        if (this->getRows() != other.getRows() || this->getCols() != other.getCols()) {
            return false;
        }
        for (int i = 0; i < this->getRows(); i++) {
            for (int j = 0; j < this->getCols(); j++) {
                if (this->get(i, j) != other.get(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const sparseMatrix<T>& other) {
        return !(*this == other);
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const sparseMatrix<U>& matrix) {
        os << matrix.getRows() << " " << matrix.getCols() << std::endl;
        for (int i = 0; i < matrix.getRows(); i++) {
            for (int j = 0; j < matrix.getCols(); j++) {
                os << matrix.get(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, sparseMatrix<U>& matrix) {
        int rows, cols;
        is >> rows >> cols;
        matrix = sparseMatrix<U>(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                U value;
                is >> value;
                matrix.set(i, j, value);
            }
        }
        return is;
    }
};

template <typename T, typename TYPE>
class TriangleMatrix : public Matrix<T> {
    T* data;
    int size;
    TYPE type;

  public:
    TriangleMatrix() {
        this->rows = 0;
        this->cols = 0;
        data = nullptr;
        size = 0;
        type = TYPE::UPPER;
    }

    TriangleMatrix(int size, TYPE type) {
        this->rows = size;
        this->cols = size;
        this->size = size;
        this->type = type;
        data = new T[size * (size + 1) / 2];
    }

    ~TriangleMatrix() {
        clear();
    }

    void set(int row, int col, T value) {
        if (type == TYPE::UPPER) {
            if (row <= col) {
                data[row * (row + 1) / 2 + col] = value;
            }
        } else {
            if (row >= col) {
                data[row * (row + 1) / 2 + col] = value;
            }
        }
    }

    T get(int row, int col) {
        if (type == TYPE::UPPER) {
            if (row <= col) {
                return data[row * (row + 1) / 2 + col];
            }
        } else {
            if (row >= col) {
                return data[row * (row + 1) / 2 + col];
            }
        }
        return 0;
    }

    void clear() {
        delete[] data;
        data = nullptr;
    }

    void copy(const TriangleMatrix<T, TYPE>& other) {
        this->data = new T[other.size * (other.size + 1) / 2];
        this->size = other.size;
        this->type = other.type;
        for (int i = 0; i < other.size * (other.size + 1) / 2; i++) {
            this->data[i] = other.data[i];
        }
    }

    void copy(TriangleMatrix<T, TYPE>&& other) {
        this->data = other.data;
        this->size = other.size;
        this->type = other.type;
        other.data = nullptr;
    }

    void resize() {
        delete[] data;
        data = new T[size * (size + 1) / 2];
    }

    void operator =(TriangleMatrix<T, TYPE>& other) {
        this->copy(other);
    }

    bool operator==(const TriangleMatrix<T, TYPE>& other) {
        if (this->size != other.size || this->type != other.type) {
            return false;
        }
        for (int i = 0; i < this->size * (this->size + 1) / 2; i++) {
            if (this->data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const TriangleMatrix<T, TYPE>& other) {
        return !(*this == other);
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const TriangleMatrix<U, TYPE>& matrix) {
        os << matrix.size << " " << static_cast<int>(matrix.type) << std::endl;
        for (int i = 0; i < matrix.size; i++) {
            for (int j = 0; j < matrix.size; j++) {
                os << matrix.get(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, TriangleMatrix<U, TYPE>& matrix) {
        int size;
        int type;
        is >> size >> type;
        matrix = TriangleMatrix<U, TYPE>(size, static_cast<TYPE>(type));
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                U value;
                is >> value;
                matrix.set(i, j, value);
            }
        }
        return is;
    }
};
