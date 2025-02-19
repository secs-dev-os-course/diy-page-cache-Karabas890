#include <iostream>
#include <cstring>
#include <windows.h>
#include "cache.hpp"  // Подключаем файл с методами

#define FILE_PATH "testfile.txt"

// Функция для тестирования работы с файлом
void test_lab2_operations() {
    // Открытие файла
    int fd = lab2_open(FILE_PATH);
    if (fd == -1) {
        std::cerr << "Ошибка при открытии файла" << std::endl;
        return;
    }
    std::cout << "Файл успешно открыт. Desriptor: " << fd << std::endl;

    // Запись в файл
    const char *write_data = "Hello, world! This is a test wow.";
    ssize_t bytes_written = lab2_write(fd, write_data, std::strlen(write_data));
    if (bytes_written == -1) {
        std::cerr << "Ошибка при записи в файл" << std::endl;
        lab2_close(fd);
        return;
    }
    std::cout << "Записано " << bytes_written << " байт." << std::endl;

    // Перемещение по файлу
    int64_t new_pos = lab2_lseek(fd, 0, SEEK_SET);
    if (new_pos == -1) {
        std::cerr << "Ошибка при перемещении по файлу" << std::endl;
        lab2_close(fd);
        return;
    }
    std::cout << "Перемещены в начало файла. Новая позиция: " << new_pos << std::endl;

    // Чтение из файла
    char buffer[256];
    ssize_t bytes_read = lab2_read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        std::cerr << "Ошибка при чтении из файла" << std::endl;
        lab2_close(fd);
        return;
    }
    buffer[bytes_read] = '\0';  // Завершаем строку нулевым символом
    std::cout << "Прочитано " << bytes_read << " байт: " << buffer << std::endl;

    // Синхронизация (сохранение изменений)
    if (lab2_fsync(fd) == -1) {
        std::cerr << "Ошибка при синхронизации файла" << std::endl;
        lab2_close(fd);
        return;
    }
    std::cout << "Изменения успешно синхронизированы." << std::endl;

    // Закрытие файла
    if (lab2_close(fd) == -1) {
        std::cerr << "Ошибка при закрытии файла" << std::endl;
    } else {
        std::cout << "Файл успешно закрыт." << std::endl;
    }
}

int main() {
    // Запуск теста
    test_lab2_operations();
    return 0;
}
