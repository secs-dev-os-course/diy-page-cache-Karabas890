#ifndef LOADER_HPP
#define LOADER_HPP

#include <string>
#include <chrono>

class FileLoader {
public:
    FileLoader(size_t blockSize, const std::string& filename);
    ~FileLoader();

    void writeFile(size_t numBlocks);
    double getElapsedTime() const;
    double getThroughput(size_t numBlocks) const;

private:
    size_t blockSize;
    std::string filename;
    char* buffer;
    std::chrono::duration<double> elapsedTime;
};

#endif // LOADER_HPP