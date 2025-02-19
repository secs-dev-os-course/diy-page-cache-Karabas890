#include "io-thpt-writeMod.hpp"
#include <iostream>
#include "cache.hpp"
#include <cstdlib> // Для std::atoi

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        std::cerr << "Ошибка: Укажите количество блоков в качестве аргумента командной строки." << std::endl;
        return 1;
    }

    size_t numBlocks = std::atoi(argv[1]);
    if (numBlocks <= 0) {
        std::cerr << "Ошибка: Некорректное значение количества блоков." << std::endl;
        return 1;
    }

    const size_t blockSize = 16 * 1024; // 16 KB
    const std::string filename = "output.dat";

    try {
        FileLoader loader(blockSize, filename);
        loader.writeFile(numBlocks);

        std::cout << "Количество блоков: " << numBlocks << std::endl;
        std::cout << "Размер блока: " << blockSize << " байт" << std::endl;
        std::cout << "Общее время записи с кешем: " << loader.getElapsedTime() << " секунд" << std::endl;
        std::cout << "Пропускная способность с кешем: " << loader.getThroughput(numBlocks) << " MB/s" << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}