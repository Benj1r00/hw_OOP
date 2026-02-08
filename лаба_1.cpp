#include <iostream>
#include <vector>

class Matrix
{
private:
    std::vector<std::vector<float>> multiplication(const std::vector<std::vector<float>>& A, const std::vector<std::vector<float>>& B)
    {
        if (A.empty() || B.empty() || A[0].size() != B.size())
        {
            throw std::invalid_argument("incorrect data entry");
        }

        size_t rows = A.size();
        size_t inner = B.size();
        size_t cols = B[0].size();

        std::vector<std::vector<float>> C (rows, std::vector<float>(cols, 0.0f));

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                for (size_t k = 0; k < inner; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

    float sums_of_the_smallest_elements_of_rows(const std::vector<std::vector<float>>& A)
    {
        if (A.empty() || A[0].empty())
        {
            throw std::invalid_argument("matrix is empty");
        }

        size_t rows = A.size();
        size_t cols = A[0].size();
        float sum = 0.0f;
        
       for (size_t j = 0; j < cols; j++) 
       {
            float min_val = A[0][j]; 
            for (size_t i = 1; i < rows; i++)
            {
                if (A[i][j] < min_val) 
                {
                    min_val = A[i][j];
                }
            }
            sum += min_val;
        }
        return sum;
    }

    void show_martixs(const std::vector<std::vector<float>>& A)
    {
        size_t rows = A.size();
        size_t cols = A[0].size();

        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                std::cout << A[i][j] << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
public:
    void result()
    {
        try
        {
            std::vector<std::vector<float>> matrixA = {
                {1.5f, 2.0f, 3.0f},
                {4.0f, 0.5f, 6.0f}
            };

            std::vector<std::vector<float>> matrixB = {
                {7.0f, 8.0f},
                {9.0f, 1.0f},
                {2.0f, 3.5f}
            };

            std::vector<std::vector<float>> matrixC = multiplication(matrixA, matrixB);

            std::cout << "matrix after multiplication" << "\n";
            show_martixs(matrixC);

            float sumMIN = sums_of_the_smallest_elements_of_rows(matrixC);
            std::cout << "Sum of the smallest elements in each column: " << sumMIN; 
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << e.what() << "\n";
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << "\n";
        }
    }
};

int main()
{
    Matrix test;
    test.result();

    return 0;
}