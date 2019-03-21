#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;
    char value;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	write(fd, "115", 3);
	close(fd);

	fd = open("/sys/class/gpio/gpio115/direction", O_WRONLY);
	write(fd, "in", 2);
	close(fd);

    
	fd = open("/sys/class/gpio/gpio115/value", O_RDONLY);
	read(fd,&value,1);
	close(fd);

	printf("Chave: %c\n", value);

	return 0;

}
