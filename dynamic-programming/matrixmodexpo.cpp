template<typename T> struct Matrix {
	int sz;
	vector<vector<T>> val;

	Matrix(int _sz, bool isIdentity = false) {
		sz = _sz;
		val.assign(_sz, vector<T>(_sz, 0));
		if (isIdentity) {
			for (int i = 0; i < _sz; i++) {
				val[i][i] = 1;
			}
		}
	}

	Matrix operator * (const Matrix &other) const {
		Matrix ret = Matrix(sz);
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				for (int k = 0; k < sz; k++) {
					maddto<T>(ret.val[i][j], mmul<T>(val[i][k], other.val[k][j], mod), mod);
				}
			}
		}
		return ret;
	}

	void print() {
		for (int i = 0; i < sz; i++) {
			for (int j = 0; j < sz; j++) {
				cout << val[i][j] << " ";
			}
			cout << '\n';
		}
	}
};

template<typename T> Matrix<T> matexpo(Matrix<T> x, ll y) {
	if (!y) {return Matrix<T>(x.sz, 1);}

	Matrix<T> t = matexpo(x, y >> 1);
	t = t * t;
	if (y & 1ll) {t = t * x;}
	return t;
}