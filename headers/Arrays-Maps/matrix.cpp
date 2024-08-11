#pragma once

#include <iostream>

#include <iostream>
#include <stdexcept>

template <typename T>
class Matrix {
private:
    T** data;

protected:
    int rows;
    int cols;

    void allocateData(int rows, int cols) {
        data = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new T[cols]();
        }
    }

    void deallocateData() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    Matrix<T> strassenMultiply(const Matrix<T>& A, const Matrix<T>& B) const {
        int n = A.rows;
        Matrix<T> result(n, n);

        if (n == 1) {
            result.data[0][0] = A.data[0][0] * B.data[0][0];
        } else {
            int newSize = n / 2;
            Matrix<T> A11(newSize, newSize), A12(newSize, newSize), A21(newSize, newSize), A22(newSize, newSize);
            Matrix<T> B11(newSize, newSize), B12(newSize, newSize), B21(newSize, newSize), B22(newSize, newSize);

            // Dividing the matrices into 4 sub-matrices
            for (int i = 0; i < newSize; ++i) {
                for (int j = 0; j < newSize; ++j) {
                    A11.data[i][j] = A.data[i][j];
                    A12.data[i][j] = A.data[i][j + newSize];
                    A21.data[i][j] = A.data[i + newSize][j];
                    A22.data[i][j] = A.data[i + newSize][j + newSize];

                    B11.data[i][j] = B.data[i][j];
                    B12.data[i][j] = B.data[i][j + newSize];
                    B21.data[i][j] = B.data[i + newSize][j];
                    B22.data[i][j] = B.data[i + newSize][j + newSize];
                }
            }

            // Calculating the 7 products, recursively (p1, p2...p7)
            Matrix<T> P1 = strassenMultiply(A11 + A22, B11 + B22);
            Matrix<T> P2 = strassenMultiply(A21 + A22, B11);
            Matrix<T> P3 = strassenMultiply(A11, B12 - B22);
            Matrix<T> P4 = strassenMultiply(A22, B21 - B11);
            Matrix<T> P5 = strassenMultiply(A11 + A12, B22);
            Matrix<T> P6 = strassenMultiply(A21 - A11, B11 + B12);
            Matrix<T> P7 = strassenMultiply(A12 - A22, B21 + B22);

            // Calculating C11, C12, C21, C22
            Matrix<T> C11 = P1 + P4 - P5 + P7;
            Matrix<T> C12 = P3 + P5;
            Matrix<T> C21 = P2 + P4;
            Matrix<T> C22 = P1 + P3 - P2 + P6;

            // Combining the 4 results into a single matrix
            for (int i = 0; i < newSize; ++i) {
                for (int j = 0; j < newSize; ++j) {
                    result.data[i][j] = C11.data[i][j];
                    result.data[i][j + newSize] = C12.data[i][j];
                    result.data[i + newSize][j] = C21.data[i][j];
                    result.data[i + newSize][j + newSize] = C22.data[i][j];
                }
            }
        }
        return result;
    }

public:
    Matrix() : data(nullptr), rows(0), cols(0) {}

    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        allocateData(rows, cols);
    }

    ~Matrix() {
        clear();
    }

    void set(int row, int col, T value) {
        if (row >= rows || col >= cols || row < 0 || col < 0) {
            throw std::out_of_range("Index out of range");
        }
        data[row][col] = value;
    }

    T get(int row, int col) {
        if (row >= rows || col >= cols || row < 0 || col < 0) {
            throw std::out_of_range("Index out of range");
        }
        return data[row][col];
    }

    int getRows() const{
        return rows;
    }

    int getCols() const{
        return cols;
    }

    void clear() {
        if (data != nullptr) {
            deallocateData();
            data = nullptr;
            rows = 0;
            cols = 0;
        }
    }

    void copy(const Matrix<T>& other) {
        if (this != &other) {
            clear();
            rows = other.rows;
            cols = other.cols;
            allocateData(rows, cols);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
    }

    void copy(Matrix<T>&& other) {
        if (this != &other) {
            clear();
            data = other.data;
            rows = other.rows;
            cols = other.cols;
            other.data = nullptr;
            other.rows = 0;
            other.cols = 0;
        }
    }

    void resize(int newRows, int newCols) {
        Matrix<T> temp(newRows, newCols);
        int minRows = std::min(rows, newRows);
        int minCols = std::min(cols, newCols);
        for (int i = 0; i < minRows; ++i) {
            for (int j = 0; j < minCols; ++j) {
                temp.set(i, j, data[i][j]);
            }
        }
        swap(temp);
    }

    void swap(Matrix<T>& other) {
        std::swap(data, other.data);
        std::swap(rows, other.rows);
        std::swap(cols, other.cols);
    }

    bool operator==(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (data[i][j] != other.data[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix<T>& other) const{
        return !(*this == other);
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                os << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    template <typename U>
    friend std::istream& operator>>(std::istream& is, Matrix<U>& matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                is >> matrix.data[i][j];
            }
        }
        return is;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        return strassenMultiply(*this, other);
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Invalid dimensions");
        }
        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& other) const{
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Invalid dimensions");
        }
        Matrix<T> result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
};

template <typename T>
class sparseMatrix : public Matrix<T> {
  private :
    int rows;
    int cols;
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
    
    bool operator==(const sparseMatrix<T>& other) const {
        if (this->rows != other.rows || this->cols != other.cols) {
            return false;
        }
        for (int i = 0; i < rows * cols; i++) {
            if (this->row[i] != other.row[i] ||
                this->col[i] != other.col[i] ||
                this->val[i] != other.val[i] ||
                this->nextInd[i] != other.nextInd[i]) {
                return false;
            }
        }
        for (int i = 0; i < rows + 1; i++) {
            if (this->rowPtr[i] != other.rowPtr[i]) {
                return false;
            }
        }
        for (int i = 0; i < cols + 1; i++) {
            if (this->colPtr[i] != other.colPtr[i]) {
                return false;
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
