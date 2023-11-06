#include <iostream>
#include "MatrixIO.h"
#include "MatrixSolver.h"

int main() {
    std::vector<std::vector<float>> matrix;
    std::vector<float> f;

    std::ifstream inFile("input.txt");
    if (!inFile) {
        std::cerr << "Не получилось открыть файл :(" << std::endl;
        return 1;
    }
    MatrixIO::LoadFromFile(inFile, matrix, f);
    inFile.close();

    auto vec = MatrixSolver::GetOnesVector(matrix.size());
    f = MatrixSolver::Get_f_Vector(matrix, vec);

    std::ofstream outFile("output.txt");
    if (!outFile) {
        std::cerr << "Не получилось открыть файл :(" << std::endl;
        return 1;
    }
    MatrixIO::SaveVectorToFile(outFile, MatrixSolver::SolveMatrix(matrix, f));
    outFile.close();

}