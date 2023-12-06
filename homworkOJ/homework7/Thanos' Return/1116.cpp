#include <cstring>
const int MOD = 10007;

// Construct an Matrix with row = r and column = c, with all matrix elements equals to 0.
Matrix::Matrix(int r, int c){
	row = r;
    col = c;
    memset(mat, 0, sizeof(mat));
}

//Implement operator[] for Matrix class. Make private member mat can be accessed using [] only. For example, we can access M.mat[x][y] by accessing M[x][y] for a Matrix object M.
int *Matrix::operator[] (const int &x){
	return mat[x];
}

//Perform "addition" operation, then return the result.
Matrix Matrix::operator+ (const Matrix &x) const{
	Matrix res(row, col);
    for(int i = 0; i < row; i++) for(int j = 0; j < col; j++){
    	res[i][j] = ((mat[i][j] + x[i][j]) %MOD +MOD)%MOD;
    }
    return res;
}

//Perform "multiplication" operation, then return the result. Note that this function is declared with friend.
Matrix operator* (const Matrix &x, const Matrix &y){
    Matrix res(x.row, y.col); // !!!
    for(int i=0; i<x.row; i++) for(int j=0; j<x.col; j++) for(int k=0; k<y.col; k++)
    {
        res[i][k] += ((x[i][j] * y[j][k]) % MOD + MOD) % MOD; // !!!
        res[i][k] = (res[i][k] % MOD + MOD) % MOD;
    }
    return res;
}