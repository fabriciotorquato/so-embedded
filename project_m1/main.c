#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <assert.h>

char getButton();
void blinkLed();
void writeFile(char value);
void readRTC();
static inline int bcd_decimal(uint8_t hex);

int main()
{
	while (1)
	{
		sleep(1);
		readRTC();
		blinkLed();

		if (getButton() == '1')
			break;
	}

	return 0;
}

char getButton()
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

void blinkLed()
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
}

void readRTC()
{

	int file, file2;
	char *filename2 = "rtc_write";
	char *filename = "/dev/i2c-1"; /*barramento que será utilizado*/
	int addr = 0x68;			   /*endereço do dispositivo*/
	char rtc_data[8];			   /*buffer para acessar os dados*/

	if ((file = open(filename, O_RDWR)) < 0)
	{
		printf("Erro 1");
		/*não foi possível acessar o arquivo*/
	}

	if ((file2 = open(filename2, O_RDWR)) < 0)
	{
		printf("Erro 3");
	}

	if (ioctl(file, I2C_SLAVE, addr) < 0)
	{
		printf("Erro 2");
		/*não foi possível acessar o dispositivo*/
	}
	/*Exemplo: Configurando o RTC para 18/05/2017 21:20:00*/

	rtc_data[0] = 0;	//a escrita ocorrerá a partir do endereço 0
	rtc_data[1] = 0x00; //seconds
	rtc_data[2] = 0x20; //minutes
	rtc_data[3] = 0x19; //hours
	rtc_data[4] = 0x05; //day
	rtc_data[5] = 0x18; //date
	rtc_data[6] = 0x05; //month
	rtc_data[7] = 0x17; //year

	if (write(file, rtc_data, 8) != 8)
	{
		/*A operação não foi realizada com sucesso*/
	}
	else
	{
		printf("SUCESSO \n");
	}

	rtc_data[0] = 1;

	if (read(file, rtc_data, sizeof(rtc_data)) != sizeof(rtc_data))
	{
		printf("Erro 4");
	}

	for (int i = 0; i < 8; i++)
	{
		rtc_data[i] = bcd_decimal(rtc_data[i]);
	}

	if (write(file2, rtc_data, 8) != 8)
	{
		printf("Erro 5");
	}

	printf("%i\n", rtc_data[0]);

	close(file);
	close(file2);
}

static inline int bcd_decimal(uint8_t hex)
{
	int dec = ((hex & 0xF0) >> 4) * 10 + (hex & 0x0F);
	return dec;
}