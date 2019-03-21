#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int getButton();
void changeStateLed();

int main()
{
	while (1)
	{
		sleep(1);

		if (getButton() == 1)
			changeStateLed();
	}

	return 0;
}

int getButton()
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
	read(fd, &value, 1);
	close(fd);
	return value;
}

void changeStateLed()
{
	int fd;
	char value;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	write(fd, "36", 2);
	close(fd);

	fd = open("/sys/class/gpio/gpio36/direction", O_WRONLY);
	write(fd, "out", 3);
	close(fd);

	fd = open("/sys/class/gpio/gpio36/value", O_WRONLY);
	write(fd, "1", 1);
	close(fd);

	sleep(1);

	fd = open("/sys/class/gpio/gpio36/value", O_WRONLY);
	write(fd, "0", 1);
	close(fd);

	printf("Chave: %c\n", value);
}
