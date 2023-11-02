#include <iostream>
#include "MatrixLoader.h"

int main() {
    std::vector<std::vector<float>> matrix;
    std::vector<float> f;

    std::ifstream inFile("input.txt");
    if (!inFile) {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return 1;
    }
    MatrixIO::LoadFromFile(inFile, matrix, f);
    inFile.close();


    std::ofstream outFile("output.txt");
    if (!outFile) {
        std::cerr << "Error: Unable to open the output file." << std::endl;
        return 1;
    }
    MatrixIO::SaveToFile(outFile, matrix, f);
    outFile.close();

}