#pragma once
#include <tuple>

namespace MatrixCoords {

	std::pair<int, int> To_NxL_Matrix(int i, int j) {
		if (j < i) {
			std::swap(i, j);
		}

		int newJ = j - i;
		return std::make_pair(i, newJ);
	}

	std::pair<int, int> To_B_Matrix(int i, int j, int L) {

		int newJ = j - i + L - 1;
		return std::make_pair(i, newJ);
	}
}