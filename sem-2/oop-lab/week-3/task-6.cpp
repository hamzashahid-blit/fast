#include <vector>
#include <iostream>

class Matrix {
    size_t rows, cols;
    std::vector<std::vector<int>> data;
public:
    Matrix(size_t rows, size_t cols, const std::vector<std::vector<int>>& data)
        : rows{rows}, cols{cols}, data{data} {};
    Matrix(size_t rows, size_t cols)
        : rows{rows}, cols{cols},
          data{std::vector<std::vector<int>>(rows, std::vector<int>(cols, 0))} {};
    size_t get_rows() { return rows; }
    size_t get_cols() { return cols; }
    void set_at(size_t i, size_t j, int new_value) { data[i][j] = new_value; };
    void print() {
        std::cout << "[\n";
        for (auto& rows : data) {
            std::cout << "  ";
            for (int elem : rows) {
                std::cout << elem << ' ';
            }
            std::cout << "\n";
        }
        std::cout << "]\n";
    }
    Matrix operator+(Matrix& other) {
        Matrix result = other;
        if (rows != other.rows || cols != other.cols) {
            std::cerr << "Matrix (" << rows << ", " << cols
                      << "), and Matrix (" << other.rows << ", " << other.cols
                      << ") cannot be added.\n";
            return other;
        }
        for (size_t i = 0; i < cols; i++) {
            for (size_t j = 0; j < rows; j++) {
                result.data[i][j] += data[i][j];
            }
        }
        return result;
    }
    Matrix operator*(Matrix& other) {
        Matrix result = Matrix(rows, other.cols);
        if (cols != other.rows) {
            std::cerr << "Matrix (" << rows << ", " << cols
                      << "), and Matrix (" << other.rows << ", " << other.cols
                      << ") cannot be multiplied.\n";
            return other;
        }
        
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < other.cols; j++) {
                for (size_t k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
};

int main(int argc, char *argv[])
{
    Matrix m1 = Matrix(2, 3, {
            { 1, 2, 3 },
            { 4, 5, 6 },
        });
    Matrix m2 = Matrix(3, 3, {
            { 3, 2, 1 },
            { 8, 4, 2 },
            { 9, 2, 6 },
        });
    std::cout << "M1: \n";
    m1.print();
    std::cout << "M2: \n";
    m2.print();
    Matrix m3 = m1 + m2;
    std::cout << "M1 + M2: \n";
    m3.print();
    Matrix m4 = m1 * m2;
    std::cout << "M1 * M2: \n";
    m4.print();
    
    return 0;
}

