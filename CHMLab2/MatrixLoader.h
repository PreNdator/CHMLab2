#pragma once
#include <fstream>
#include <vector>
#include "MatrixCoords.h"

namespace MatrixIO {

	void SaveVectorToFile(std::ofstream& file, const std::vector<float>& vect) {
		int size = vect.size();
		for (int i = 0; i < size; ++i) {
			file << vect[i] << '\n';
		}
	}

	void LoadFromFile(std::ifstream& file, std::vector<std::vector<float>>& matrix, std::vector<float>& f) {
		int N, L;
		file >> N >> L;
		matrix.resize(N);
		f.resize(N);
		float temp;

		for (int i = 0; i < N; ++i) {
			matrix[i].resize(L);
			for (int j = 0; j < L; ++j) {
				matrix[i][j] = 0;
			}

			for (int j = 0; j < N; ++j) {
				file >> temp;
				if(j>=i && j-i < L){
					std::pair<int, int> newCoords = MatrixCoords::To_NxL_Matrix(i, j);
					matrix[newCoords.first][newCoords.second] = temp;
				}
			}
		}

		for (int i = 0; i < N; ++i) {
			file >> f[i];
		}
	}

	void SaveToFile(std::ofstream& file, const std::vector<std::vector<float>>& matrix, const std::vector<float>& f) {
		int N = matrix.size();
		int L = matrix.empty() ? 0 : matrix[0].size();

		file << N << ' ' << L << '\n';

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				
				if (j >= i && j - i < L || j < i && i - j< L) {
					std::pair<int, int> newCoords = MatrixCoords::To_NxL_Matrix(i, j);
					file << matrix[newCoords.first][newCoords.second];
				}
				else {
					file << 0;
				}
				file << ' ';
			}
			file << '\n';
		}

		SaveVectorToFile(file, f);
	}

	

}

