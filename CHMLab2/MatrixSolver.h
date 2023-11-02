#pragma once
#include "MatrixCoords.h"
#include <vector>

namespace MatrixSolver {
	void SolveMatrix(std::vector<std::vector<float>>& matrix, std::vector<float>& f) {

		int N = matrix.size();
		int L = matrix.empty() ? 0 : matrix[0].size();

		std::vector<std::vector<float>> B(N);


		for (int i = 0; i < N; ++i) {
			B[i].resize(L);
			for (int j = 0; j < L; ++j) {
				B[i][j] = 0;
			}
		}

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < L; ++j) {
				B[i][j] = 0;
			}
		}
	}



}