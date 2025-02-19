#include "io-thpt-writeMod.hpp"
#include <iostream>
#include <cstdlib> // Для функции rand()
#include "cache.hpp"

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
    int fd = lab2_open(filename.c_str());
    if (fd < 0) {
        throw std::ios_base::failure("Не удалось открыть файл для записи.");
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < numBlocks; ++i) {
        if (lab2_write(fd, buffer, blockSize) < 0) {
            lab2_close(fd);
            throw std::ios_base::failure("Ошибка записи в файл.");
        }
    }

    if (lab2_fsync(fd) < 0) {
        lab2_close(fd);
        throw std::ios_base::failure("Ошибка синхронизации файла.");
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    elapsedTime = endTime - startTime;
     // Получаем количество cache miss
     //size_t cacheMissCount = get_cache_miss_count(fd);
     //std::cout << "Количество кеш-промахов: " << cacheMissCount << std::endl;

    lab2_close(fd);
}

double FileLoader::getElapsedTime() const {
    return elapsedTime.count();
}

double FileLoader::getThroughput(size_t numBlocks) const {
    return (numBlocks * blockSize) / 1024.0 / 1024.0 / elapsedTime.count();
}
