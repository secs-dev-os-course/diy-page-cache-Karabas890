#include "io-thpt-write.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib> // Для функции rand()

FileLoader::FileLoader(size_t blockSize, const std::string& filename)
    : blockSize(blockSize), filename(filename), buffer(nullptr), elapsedTime(0) {
    buffer = new char[blockSize];
    for (size_t i = 0; i < blockSize; ++i) {
        buffer[i] = static_cast<char>(rand() % 256);
    }
}

FileLoader::~FileLoader() {
    delete[] buffer;
}

void FileLoader::writeFile(size_t numBlocks) {
    // Открываем файл с флагом std::ios::trunc, чтобы очистить его перед записью
    std::ofstream outFile(filename, std::ios::binary | std::ios::trunc);
    if (!outFile) {
        throw std::ios_base::failure("Не удалось открыть файл для записи.");
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < numBlocks; ++i) {
        outFile.write(buffer, blockSize);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = endTime - startTime;

    outFile.close();
}


double FileLoader::getElapsedTime() const {
    return elapsedTime.count();
}

double FileLoader::getThroughput(size_t numBlocks) const {
    return (numBlocks * blockSize) / 1024.0 / 1024.0 / elapsedTime.count();
}