#ifndef MATRIX_
#define MATRIX_

#include <iostream>
#include "defines.h"

class Matrix
{
public:
    Matrix(size_t r, size_t c);             // 非方阵构造
    Matrix(size_t r, size_t c, double val); // 赋初值val
    Matrix(size_t n);                       // 方阵构造
    Matrix(const Matrix &rhs);
    ~Matrix();

    status input();
    status from_str(string str);

    void set_value(double val, size_t i, size_t j);

    double *operator[](size_t i);

    Matrix &operator=(const Matrix &);

    friend std::ostream &operator<<(std::ostream &out, Matrix &obj);

    friend Matrix operator+(const Matrix &, const Matrix &);
    friend Matrix operator-(const Matrix &, const Matrix &);

    friend Matrix operator*(const Matrix &, const Matrix &);
    friend Matrix operator*(double, const Matrix &);
    friend Matrix operator*(const Matrix &, double);

    friend Matrix operator/(const Matrix &, double);

    size_t row() const { return m_row; }
    size_t col() const { return n_col; }

    Matrix get_row(size_t index);
    Matrix get_col(size_t index);

    Matrix cov(bool flag = true); // 协方差阵
    double det();                 // 行列式
    Matrix diag();                // 返回对角线元素

    Matrix T() const; // 转置

    Matrix adjoint(); // 伴随阵
    Matrix inverse(); // 逆矩阵

    void QR(Matrix &Q, Matrix &R) const;

    Matrix eig_val(size_t _iters = 1000);  // 特征值
    Matrix eig_vect(size_t _iters = 1000); // 特征向量

private:
    size_t m_row;
    size_t n_col;
    size_t size;
    size_t m_curIndex;
    double *data;
};

static double calcDet(size_t n, double *&aa)
{
    if (n == 1)
        return aa[0];
    double *bb = new double[(n - 1) * (n - 1)]; //创建n-1阶的代数余子式阵bb
    double sum = 0.0;
    for (size_t Ai = 0; Ai < n; Ai++)
    {
        for (size_t Bi = 0; Bi < n - 1; Bi++) //把aa阵第一列各元素的代数余子式存到bb
        {
            size_t offset = Bi < Ai ? 0 : 1; //bb中小于Ai的行，同行赋值，等于的错过，大于的加一
            for (size_t j = 0; j < n - 1; j++)
            {
                bb[Bi * (n - 1) + j] = aa[(Bi + offset) * n + j + 1];
            }
        }
        int flag = (Ai % 2 == 0 ? 1 : -1);             //因为列数为0，所以行数是偶数时候，代数余子式为1.
        sum += flag * aa[Ai * n] * calcDet(n - 1, bb); //aa第一列各元素与其代数余子式积的和即为行列式
    }
    delete[] bb;
    return sum;
}

// 返回代数余子式
static double CalcAlgebraicCofactor(Matrix &srcMat, size_t ai, size_t aj)
{
    size_t temMatLen = srcMat.row() - 1;
    Matrix temMat(temMatLen);
    for (size_t bi = 0; bi < temMatLen; bi++)
    {
        for (size_t bj = 0; bj < temMatLen; bj++)
        {
            size_t rowOffset = bi < ai ? 0 : 1;
            size_t colOffset = bj < aj ? 0 : 1;
            temMat[bi][bj] = srcMat[bi + rowOffset][bj + colOffset];
        }
    }
    int flag = (ai + aj) % 2 == 0 ? 1 : -1;
    return flag * temMat.det();
}

status Matrix::input()
{
    string raw;
    std::getline(std::cin, raw);
    return from_str(raw);;
}

status Matrix::from_str(string raw)
{
    size_t p = 0, pos = 0;
    int row = 0, col = 0, size_ = 0;
    double num = 0;

    assert(raw[0] == '[');
    raw = raw.substr(1);

    while (raw.length() > 0)
    {
        if (std::isspace(raw[0]))
        {
            raw = raw.substr(1);
        }
        else if (ISDIGIT(raw[0]) || raw[0] == '-') // number
        {
            num = std::stod(raw, &pos);
            data[p++] = num;
            raw = raw.substr(pos);
        }
        else if (raw[0] == ';')
        {
            row ++;
            size_ ++;
            raw = raw.substr(1);
        }
        else if (raw[0] == ',')
        {
            size_ ++;
            raw = raw.substr(1);
        }
        else if (raw[0] == ']')
        {
            row ++;
            size_ ++;
            break;
        }
        else
        {
            printf("[ERROR] Invalid input,\n");
            return INVALID_INPUT;
        }
        
    }
    if (size_ % row != 0)
    {
        printf("[ERROR] Not a legal matrix.\n");
        return INVALID_INPUT;
    }
    col = size_ / row;

    if (this->m_row != row || this->n_col != col || this->size != size_)
    {
        printf("[ERROR] Matrix's row number or col number is not correct.\n");
        return INVALID_INPUT;
    }

    return SUCCESS;
}

Matrix::Matrix(size_t r, size_t c) : m_row(r), n_col(c)
{
    size = r * c;
    if (size > 0)
    {
        data = new double[size];
        for (int i = 0; i < size; i++)
            data[i] = 0;
    }
    else
        data = NULL;
};

Matrix::Matrix(size_t r, size_t c, double val) : m_row(r), n_col(c)
{
    size = r * c;
    if (size > 0)
    {
        data = new double[size];
        for (int i = 0; i < size; i++)
            data[i] = val;
    }
    else
        data = NULL;
};

Matrix::Matrix(size_t n) : m_row(n), n_col(n)
{
    size = n * n;
    if (size > 0)
    {
        data = new double[size];
        for (int i = 0; i < size; i++)
            data[i] = 0;
    }
    else
        data = NULL;
}

Matrix::Matrix(const Matrix &rhs)
{
    *this = rhs;
}

Matrix::~Matrix()
{
    if (data != NULL)
    {
        delete[] data;
        data = NULL;
    }
}

Matrix &Matrix::operator=(const Matrix &rhs)
{
    if (this != &rhs)
    {
        m_row = rhs.m_row;
        n_col = rhs.n_col;
        size = rhs.size;
        // if (data != NULL)
        //     delete[] data;
        data = new double[size];
        for (size_t i = 0; i < size; i++)
            data[i] = rhs.data[i];
    }
    return *this;
}

double *Matrix::operator[](size_t i)
{
    return data + i * n_col;
}

Matrix Matrix::get_row(size_t index)
{
    Matrix ret(1, n_col); //一行的返回值
    for (size_t i = 0; i < n_col; i++)
        ret[0][i] = data[(index)*n_col + i];
    return ret;
}

Matrix Matrix::get_col(size_t index)
{
    Matrix ret(m_row, 1); //一列的返回值
    for (size_t i = 0; i < m_row; i++)
        ret[i][0] = data[i * n_col + index];
    return ret;
}

double Matrix::det()
{
    if (n_col == m_row)
        return calcDet(m_row, data);
    else
    {
        std::cout << ("行列不相等无法计算") << std::endl;
        return 0;
    }
}

std::ostream &operator<<(std::ostream &out, Matrix &obj)
{
    for (size_t i = 0; i < obj.m_row; i++)
    {
        for (size_t j = 0; j < obj.n_col; j++)
        {
            out << (obj[i][j]) << "\t";
        }
        out << std::endl;
    }
    return out;
}

Matrix operator+(const Matrix &lm, const Matrix &rm)
{
    if (lm.n_col != rm.n_col || lm.m_row != rm.m_row)
    {
        Matrix temp(0, 0);
        temp.data = NULL;
        std::cout << "operator+(): 矩阵shape 不合适,n_col:"
                  << lm.n_col << "," << rm.n_col << ".  m_row:" << lm.m_row << ", " << rm.m_row << std::endl;
        return temp; //数据不合法时候，返回空矩阵
    }
    Matrix ret(lm.m_row, lm.n_col);
    for (size_t i = 0; i < ret.size; i++)
    {
        ret.data[i] = lm.data[i] + rm.data[i];
    }
    return ret;
}

Matrix operator-(const Matrix &lm, const Matrix &rm)
{
    if (lm.n_col != rm.n_col || lm.m_row != rm.m_row)
    {
        Matrix temp(0, 0);
        temp.data = NULL;
        std::cout << "operator-(): 矩阵shape 不合适,n_col:"
                  << lm.n_col << "," << rm.n_col << ".  m_row:" << lm.m_row << ", " << rm.m_row << std::endl;
        return temp; //数据不合法时候，返回空矩阵
    }
    Matrix ret(lm.m_row, lm.n_col);
    for (size_t i = 0; i < ret.size; i++)
    {
        ret.data[i] = lm.data[i] - rm.data[i];
    }
    return ret;
}

Matrix operator*(const Matrix &lm, const Matrix &rm)
{
    if (lm.size == 0 || rm.size == 0 || lm.n_col != rm.m_row)
    {
        Matrix temp(0, 0);
        temp.data = NULL;
        std::cout << "operator*(): 矩阵shape 不合适,n_col:"
                  << lm.n_col << "," << rm.n_col << ".  m_row:" << lm.m_row << ", " << rm.m_row << std::endl;
        return temp; //数据不合法时候，返回空矩阵
    }
    Matrix ret(lm.m_row, rm.n_col);
    for (size_t i = 0; i < lm.m_row; i++)
    {
        for (size_t j = 0; j < rm.n_col; j++)
        {
            for (size_t k = 0; k < lm.n_col; k++) //lm.n_col == rm.m_row
            {
                ret.data[i * rm.n_col + j] += lm.data[i * lm.n_col + k] * rm.data[k * rm.n_col + j];
            }
        }
    }
    return ret;
}

Matrix operator*(double val, const Matrix &rm)
{
    return rm * val;
}

Matrix operator*(const Matrix &lm, double val)
{
    Matrix ret(lm.m_row, lm.n_col);
    for (size_t i = 0; i < ret.size; i++)
        ret.data[i] = val * lm.data[i];
    return ret;
}

Matrix operator/(const Matrix &lm, double val)
{
    return lm * (1 / val);
}

Matrix Matrix::diag()
{
    if (m_row != n_col)
    {
        Matrix m(0);
        std::cout << "diag():m_row != n_col" << std::endl;
        return m;
    }
    Matrix m(1, m_row);
    for (size_t i = 0; i < m_row; i++)
    {
        m.data[i] = data[i * m_row + i];
    }
    return m;
}

Matrix Matrix::T() const
{
    Matrix t(n_col, m_row);
    for (size_t i = 0; i < m_row; i++)
    {
        for (size_t j = 0; j < n_col; j++)
        {
            t[j][i] = data[i * n_col + j];
        }
    }
    return t;
}

void Matrix::QR(Matrix &Q, Matrix &R) const
{
    //如果A不是一个二维方阵，则提示错误，函数计算结束
    if (m_row != n_col)
    {
        printf("ERROE: QR() parameter A is not a square matrix!\n");
        return;
    }
    const size_t N = m_row;
    double *a = new double[N];
    double *b = new double[N];

    for (size_t j = 0; j < N; ++j) //(Gram-Schmidt) 正交化方法
    {
        for (size_t i = 0; i < N; ++i) //第j列的数据存到a，b
            a[i] = b[i] = data[i * N + j];

        for (size_t i = 0; i < j; ++i) //第j列之前的列
        {
            R.data[i * N + j] = 0; //
            for (size_t m = 0; m < N; ++m)
            {
                R.data[i * N + j] += a[m] * Q.data[m * N + i]; //R[i,j]值为Q第i列与A的j列的内积
            }
            for (size_t m = 0; m < N; ++m)
            {
                b[m] -= R.data[i * N + j] * Q.data[m * N + i]; //
            }
        }

        double norm = 0;
        for (size_t i = 0; i < N; ++i)
        {
            norm += b[i] * b[i];
        }
        norm = (double)sqrt(norm);

        R.data[j * N + j] = norm; //向量b[]的2范数存到R[j,j]

        for (size_t i = 0; i < N; ++i)
        {
            Q.data[i * N + j] = b[i] / norm; //Q 阵的第j列为单位化的b[]
        }
    }
    delete[] a;
    delete[] b;
}

Matrix Matrix::eig_val(size_t _iters)
{
    if (size == 0 || m_row != n_col)
    {
        std::cout << "矩阵为空或者非方阵！" << std::endl;
        Matrix rets(0);
        return rets;
    }
    if (det() == 0)
    {
     std::cout << "非满秩矩阵没法用QR分解计算特征值！" << std::endl;
     Matrix rets(0);
     return rets;
    }
    const size_t N = m_row;
    Matrix matcopy(*this); //备份矩阵
    Matrix Q(N), R(N);
    // 当迭代次数足够多时,A 趋于上三角矩阵，上三角矩阵的对角元就是A的全部特征值
    for (size_t k = 0; k < _iters; ++k)
    {
        //std::cout<<"this:\n"<<*this<<std::endl;
        QR(Q, R);
        *this = R * Q;
        // std::cout << "Q:\n" << Q << std::endl;
        // std::cout << "R:\n" << R << std::endl;
    }
    Matrix val = diag();
    *this = matcopy; //恢复原始矩阵；
    return val;
}

Matrix Matrix::eig_vect(size_t _iters)
{
    if (size == 0 || m_row != n_col)
    {
        std::cout << "矩阵为空或者非方阵！" << std::endl;
        Matrix rets(0);
        return rets;
    }
    if (det() == 0)
    {
        std::cout << "非满秩矩阵没法用QR分解计算特征向量！" << std::endl;
        Matrix rets(0);
        return rets;
    }
    Matrix matcopy(*this); //备份矩阵
    Matrix eigenValue = eig_val(_iters);
    Matrix ret(m_row);
    const size_t NUM = n_col;
    double eValue;
    double sum, midSum, diag;
    Matrix copym(*this);
    for (size_t count = 0; count < NUM; ++count)
    {
        //计算特征值为eValue，求解特征向量时的系数矩阵
        *this = copym;
        eValue = eigenValue[count][count];

        for (size_t i = 0; i < n_col; ++i) //A-lambda*I
        {
            data[i * n_col + i] -= eValue;
        }
        //std::cout<<*this<<std::endl;
        //将 this为阶梯型的上三角矩阵
        for (size_t i = 0; i < m_row - 1; ++i)
        {
            diag = data[i * n_col + i]; //提取对角元素
            for (size_t j = i; j < n_col; ++j)
            {
                data[i * n_col + j] /= diag; //【i,i】元素变为1
            }
            for (size_t j = i + 1; j < m_row; ++j)
            {
                diag = data[j * n_col + i];
                for (size_t q = i; q < n_col; ++q) //消去第i+1行的第i个元素
                {
                    data[j * n_col + q] -= diag * data[i * n_col + q];
                }
            }
        }
        //std::cout<<*this<<std::endl;
        //特征向量最后一行元素置为1
        midSum = ret.data[(ret.m_row - 1) * ret.n_col + count] = 1;
        for (int m = m_row - 2; m >= 0; --m)
        {
            sum = 0;
            for (size_t j = m + 1; j < n_col; ++j)
            {
                sum += data[m * n_col + j] * ret.data[j * ret.n_col + count];
            }
            sum = -sum / data[m * n_col + m];
            midSum += sum * sum;
            ret.data[m * ret.n_col + count] = sum;
        }
        midSum = sqrt(midSum);
        for (size_t i = 0; i < ret.m_row; ++i)
        {
            ret.data[i * ret.n_col + count] /= midSum; //每次求出一个列向量
        }
    }
    *this = matcopy; //恢复原始矩阵；
    return ret;
}

Matrix Matrix::cov(bool flag)
{
    //m_row 样本数，column 变量数
    if (n_col == 0)
    {
        Matrix m(0);
        return m;
    }
    double *mean = new double[n_col]; //均值向量

    for (size_t j = 0; j < n_col; j++) //init
    {
        mean[j] = 0.0;
    }
    Matrix ret(n_col);
    for (size_t j = 0; j < n_col; j++) //mean
    {
        for (size_t i = 0; i < m_row; i++)
        {
            mean[j] += data[i * n_col + j];
        }
        mean[j] /= m_row;
    }
    size_t i, k, j;
    for (i = 0; i < n_col; i++) //第一个变量
    {
        for (j = i; j < n_col; j++) //第二个变量
        {
            for (k = 0; k < m_row; k++) //计算
            {
                ret[i][j] += (data[k * n_col + i] - mean[i]) * (data[k * n_col + j] - mean[j]);
            }
            if (flag == true)
            {
                ret[i][j] /= (m_row - 1);
            }
            else
            {
                ret[i][j] /= (m_row);
            }
        }
    }
    for (i = 0; i < n_col; i++) //补全对应面
    {
        for (j = 0; j < i; j++)
        {
            ret[i][j] = ret[j][i];
        }
    }
    return ret;
}

Matrix Matrix::adjoint()
{
    if (m_row != n_col)
        return Matrix(0);

    Matrix adjointMat(m_row);
    for (size_t ai = 0; ai < m_row; ai++)
    {
        for (size_t aj = 0; aj < m_row; aj++)
        {
            adjointMat.data[aj * m_row + ai] = CalcAlgebraicCofactor(*this, ai, aj);
        }
    }
    return adjointMat;
}

Matrix Matrix::inverse()
{
    double detOfMat = det();
    if (detOfMat == 0)
    {
        std::cout << "行列式为0，不能计算逆矩阵。" << std::endl;
        return Matrix(0);
    }
    return adjoint() / detOfMat;
}

#endif // MATRIX_