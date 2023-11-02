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

	std::pair<int, int> To_NxN_Matrix(int i, int j) {
		int newJ = j + i;
		return std::make_pair(i, newJ);
	}
}