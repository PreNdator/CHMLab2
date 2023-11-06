#pragma once
#include "MatrixCoords.h"
#include <vector>

namespace MatrixSolver {
	/// <summary>
	/// Решаем уравнение Mx=f методом холецкого
	/// </summary>
	/// <param name="matrix">Симмметричная матрица M, которая хранится в векторе NxL</param>
	/// <param name="f">Вектор f</param>
	/// <returns>Решение - вектор x</returns>
	std::vector<float> SolveMatrix(std::vector<std::vector<float>>& matrix, std::vector<float>& f) {

		std::vector<float> x;
		std::vector<float> y;

		int N = matrix.size();
		int L = matrix.empty() ? 0 : matrix[0].size();

		x.resize(N);
		y.resize(N);

		std::vector<std::vector<float>> B(N);
		
		for (int i = 0; i < N; ++i) {
			B[i].resize(L);
			for (int j = 0; j < L; ++j) {
				B[i][j] = 0;
			}
		}

		{
			auto c = MatrixCoords::To_B_Matrix(0, 0, L);
			B[c.first][c.second] = matrix[0][0];
		}

		for (int j = 0; j < N; ++j) {
			int end = j + L;
			if (end > N) end = N;
			for (int i = j; i < end; ++i) {
					float sum = 0;

					int start = i - L + 1;
					if (start < 0) start = 0;

					for (int k = start; k < j; ++k) {
						auto c1 = MatrixCoords::To_B_Matrix(i, k, L);
						auto c2 = MatrixCoords::To_B_Matrix(j, k, L);
						auto c3 = MatrixCoords::To_B_Matrix(k, k, L);
						sum += B[c1.first][c1.second] * B[c2.first][c2.second] / B[c3.first][c3.second];
					}

					auto c1 = MatrixCoords::To_B_Matrix(i, j, L);
					auto c2 = MatrixCoords::To_NxL_Matrix(i, j);
					B[c1.first][c1.second] = matrix[c2.first][c2.second] - sum;
			}
		}

		for (int i = 0; i < N; ++i) {
			float sum = 0;
			int start = i - L + 1;
			if (start < 0) start = 0;
			for (int k = start; k < i; ++k) {
				auto c = MatrixCoords::To_B_Matrix(i, k, L);
				sum += B[c.first][c.second] * y[k];
			}
			auto c = MatrixCoords::To_B_Matrix(i, i, L);
			y[i] = (f[i] - sum) / B[c.first][c.second];
		}

		for (int i = N-1; i >= 0; --i) {
			float sum = 0;
			int end = i + L;
			if (end > N) end = N;
			for (int k = i + 1; k < end; ++k) {
				auto c = MatrixCoords::To_B_Matrix(k, i, L);
				sum += B[c.first][c.second] * x[k];
			}
			auto c = MatrixCoords::To_B_Matrix(i, i, L);
			x[i] = y[i] - sum / B[c.first][c.second];
		}


		return x;
	}

	// <summary>
	/// Умножаем симметричную матрицу, которая хранится в векторе NxL, на вектор x
	/// </summary>
	/// <param name="matrix">Матрица</param>
	/// <param name="x">Вектор x</param>
	/// <returns>Результат умножения</returns>
	std::vector<float> Get_f_Vector(std::vector<std::vector<float>>& matrix, std::vector<float>& x) {
		int N = matrix.size();
		int L = matrix.empty() ? 0 : matrix[0].size();

		std::vector<float> f(N);

		for (int i = 0; i < N; ++i) {
			float sum = 0;
			int start = i - L+1;
			int end = i + L;
			if (start < 0) start = 0;
			if (end > N) end = N;

			for (int j = start; j < end; ++j) {
				auto coords = MatrixCoords::To_NxL_Matrix(i, j);
				sum += matrix[coords.first][coords.second] * x[j];
			}

			f[i] = sum;
		}

		return f;
	}


	/// <param name="N">Размерность вектора</param>
	/// <returns>Вектор состоящий из едениц</returns>
	std::vector<float> GetOnesVector(int N) {
		std::vector<float> onesVector(N);

		for (int i = 0; i < N; ++i) {
			onesVector[i] = 1;
		}
		return onesVector;
	}

}