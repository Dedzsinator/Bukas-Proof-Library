#include <iostream>
#include <vector>

//tensor data structure
template <typename T>
class Tensor {
private:
    std::vector<T> data;
    std::vector<std::size_t> shape;

public:
    Tensor(const std::vector<std::size_t>& shape) : shape(shape) {
        std::size_t size = 1;
        for (std::size_t dim : shape) {
            size *= dim;
        }
        data.resize(size);
    }

    T& operator()(const std::vector<std::size_t>& indices) {
        std::size_t offset = 0;
        for (std::size_t i = 0; i < indices.size(); ++i) {
            offset += indices[i];
            if (i < indices.size() - 1) {
                offset *= shape[i + 1];
            }
        }
        return data[offset];
    }

    const T& operator()(const std::vector<std::size_t>& indices) const {
        std::size_t offset = 0;
        for (std::size_t i = 0; i < indices.size(); ++i) {
            offset += indices[i];
            if (i < indices.size() - 1) {
                offset *= shape[i + 1];
            }
        }
        return data[offset];
    }
};