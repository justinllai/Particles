#include "Matrices.h"


namespace Matrices
{
    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols)
    : Matrix(2, nCols)
  {
        for (int j = 0; j < nCols; ++j)
        {
            a[0][j] = xShift;
        }

         for (int j = 0; j < nCols; ++j)
        {
            a[1][j] = yShift;
        }
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        a[0][0] = cos(theta);
        a[0][1] = -sin(theta);
        a[1][0] = sin(theta);
        a[1][1] = cos(theta);
    }

    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        a[0][0] = scale;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = scale;
    }

    Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols)
    {
        // Resize the vector to contain the specified number of rows
        a.resize(rows);


        // Loop through each row and resize it to contain the specified number of columns
        for (int i = 0; i < rows; ++i)
        {
            a[i].resize(cols, 0.0); // Initialize each element to 0
        }
    }




    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            throw runtime_error("Error: dimensions must agree");
        }


        Matrix result(a.getRows(), a.getCols());


        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                result(i, j) = a(i, j) + b(i, j);
            }
        }


        return result;
    }


    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }


        Matrix result(a.getRows(), b.getCols());


        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int k = 0; k < b.getCols(); ++k)
            {
                double sum = 0.0;
                for (int j = 0; j < a.getCols(); ++j)
                {
                    sum += a(i, j) * b(j, k);
                }
                result(i, k) = sum;
            }
        }


        return result;
    }


    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        {
            return false;
        }


        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                // Compare elements within 0.001
                if (abs(a(i, j) - b(i, j)) >= 0.001)
                {
                    return false;
                }
            }
        }


        return true;
    }


    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a == b);
    }


    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); ++i)
        {
            for (int j = 0; j < a.getCols(); ++j)
            {
                os << setw(10) << a(i, j);
                if (j < a.getCols() - 1) {
                    os << " ";
                }
            }
            os << "\n"; // Separate rows by newline
        }


        return os;
    }
}
