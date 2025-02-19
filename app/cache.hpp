#include <windows.h>
#include <stdint.h>
#ifdef _WIN32
    #include <BaseTsd.h>  // Добавляем этот заголовок для определения SSIZE_T
    typedef SSIZE_T ssize_t; // Определяем ssize_t для Windows
#endif

int lab2_open(const char *path);

int lab2_close(int fd);

ssize_t lab2_read(int fd, void *buf, size_t count);

ssize_t lab2_write(int fd, const void *buf, size_t count);

int64_t lab2_lseek(int fd, int64_t offset, int whence);

int lab2_fsync(int fd);