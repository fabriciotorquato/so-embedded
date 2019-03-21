#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    write(fd, "36", 2);
    close(fd);

    fd = open("/sys/class/gpio/gpio36/direction", O_WRONLY);
    write(fd, "out", 3);
    close(fd);

    fd = open("/sys/class/gpio/gpio36/value", O_WRONLY);
    write(fd, "1", 1);
    close(fd);

    return 0;
}
