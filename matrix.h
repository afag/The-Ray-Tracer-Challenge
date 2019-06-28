#ifndef MATRIXH
#define MATRIXH
#include "tuple.h"

class Matrix2d
{

public:
    double data[4];

    Matrix2d(double a, double b, double c, double d)
    {
        data[0] = a;
        data[1] = b;
        data[2] = c;
        data[3] = d;
    }
    Matrix2d(double *data)
    {
        for (int i = 0; i < 4; i++)
        {
            this->data[i] = data[i];
        }
    }
    double operator()(int i, int j)
    {
        return data[i * 2 + j];
    }

    Matrix2d operator*(Matrix2d rhs)
    {

        double res[4];
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                res[i * 2 + j] = 0;
                for (int x = 0; x < 2; x++)
                {
                    res[i * 2 + j] = res[i * 2 + j] + data[i * 2 + x] * rhs.data[j + x * 2];
                }
            }
        }

        return Matrix2d(res);
    }

    double det()
    {
        return data[0] * data[3] - data[1] * data[2];
    }

    Matrix2d inverse()
    { // do not test whether it is invertable or not

        double iv0 = data[3];
        double iv1 = data[2];
        double iv2 = data[1];
        double iv3 = data[0];

        return Matrix2d(iv0 / det(), iv1 / det(), iv2 / det(), iv3 / det());
    }
};

class Matrix3d
{
public:
    double data[9];
    Matrix3d(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22)
    {
        data[0] = m00;
        data[1] = m01;
        data[2] = m02;

        data[3] = m10;
        data[4] = m11;
        data[5] = m12;

        data[6] = m20;
        data[7] = m21;
        data[8] = m22;
    }
    Matrix3d(double *data)
    {
        for (int i = 0; i < 9; i++)
        {
            this->data[i] = data[i];
        }
    }
    double operator()(int i, int j)
    {
        return data[i * 3 + j];
    }

    Matrix3d operator*(Matrix3d rhs)
    {

        double res[9];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                res[i * 3 + j] = 0;
                for (int x = 0; x < 3; x++)
                {
                    res[i * 3 + j] = res[i * 3 + j] + data[i * 3 + x] * rhs.data[j + x * 3];
                }
            }
        }

        return Matrix3d(res);
    }

    Matrix3d transpose()
    {
        double res[9];
        for (int i = 0; i < 3; i++)
        {

            for (int j = 0; j < 3; j++)
            {
                res[i * 3 + j] = data[i + j * 3];
            }
        }

        return Matrix3d(res);
    }

    Matrix2d submatrix(int x, int y)
    {
        double res[4];
        int index = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {

                if (x == i || y == j)
                    continue;
                res[index] = data[i * 3 + j];
                index++;
            }
        }

        return Matrix2d(res);
    }

    double mirror(int x, int y)
    {
        return submatrix(x, y).det();
    }

    double cofactor(int x, int y)
    {
        if ((x + y) % 2 == 1)
            return -mirror(x, y);
        return mirror(x, y);
    }

    double det()
    {
        double res = 0;
        for (int i = 0; i < 3; i++)
        {

            res = res + data[i] * cofactor(0, i);
        }
        return res;
    }
    Matrix3d inverse()
    {
        double res[9];
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                res[i + j * 3] = cofactor(i, j) / det();
            }
        }

        return Matrix3d(res);
    }
};

class Matrix4d
{

public:
Matrix4d(){};
    double data[16];
    Matrix4d(double *data)
    {
        for (int i = 0; i < 16; i++)
        {
            this->data[i] = data[i];
        }
    }
    double operator()(int i, int j)
    {
        return data[i * 4 + j];
    }

    Matrix4d operator*(Matrix4d rhs)
    {

        double res[16];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res[i * 4 + j] = 0;
                for (int x = 0; x < 4; x++)
                {
                    res[i * 4 + j] = res[i * 4 + j] + data[i * 4 + x] * rhs.data[j + x * 4];
                }
            }
        }

        return Matrix4d(res);
    }
    tuple operator*(tuple rhs)
    {

        double res[4];
        for (int i = 0; i < 4; i++)
        {
            res[i] = 0;
            for (int j = 0; j < 4; j++)
            {
                res[i] = res[i] + data[i * 4 + j] * rhs[j];
            }
        }

        return tuple(res[0], res[1], res[2], res[3]);
    }

    Matrix4d transpose()
    {
        double res[16];

        for (int i = 0; i < 4; i++)
        {

            for (int j = 0; j < 4; j++)
            {
                res[i * 4 + j] = res[i + j * 4];
            }
        }

        return Matrix4d(res);
    }

    Matrix3d submatrix(int x, int y)
    {
        double res[9];
        int index = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {

                if (x == i || y == j)
                    continue;
                res[index] = data[i * 4 + j];
                index++;
            }
        }

        return Matrix3d(res);
    }

    double mirror(int x, int y)
    {
        return submatrix(x, y).det();
    }

    double cofactor(int x, int y)
    {
        if ((x + y) % 2 == 1)
            return -mirror(x, y);
        return mirror(x, y);
    }
    double det()
    {
        double res = 0;
        for (int i = 0; i < 4; i++)
        {

            res = res + data[i] * cofactor(0, i);
        }
        return res;
    }

    Matrix4d inverse()
    {
        double res[16];
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                res[i + j * 4] = cofactor(i, j) / det();
            }
        }

        return Matrix4d(res);
    }
};

inline std::ostream &operator<<(std::ostream &os, Matrix2d m)
{
    os << m(0, 0) << " " << m(0, 1) << std::endl;
    os << m(1, 0) << " " << m(1, 1) << std::endl;

    return os;
}

inline std::ostream &operator<<(std::ostream &os, Matrix3d m)
{
    os << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << std::endl;
    os << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << std::endl;
    os << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << std::endl;
    return os;
}

inline std::ostream &operator<<(std::ostream &os, Matrix4d m)
{
    os << m(0, 0) << " " << m(0, 1) << " " << m(0, 2) << " " << m(0, 3) << std::endl;
    os << m(1, 0) << " " << m(1, 1) << " " << m(1, 2) << " " << m(1, 3) << std::endl;
    os << m(2, 0) << " " << m(2, 1) << " " << m(2, 2) << " " << m(2, 3) << std::endl;
    os << m(3, 0) << " " << m(3, 1) << " " << m(3, 2) << " " << m(3, 3) << std::endl;

    return os;
}

 Matrix4d Identity()
 {
    double data[16]={1,0,0,0, 0,1,0,0,    0,0,1,0,    0,0,0,1      };
     return Matrix4d(data);
 }



#endif