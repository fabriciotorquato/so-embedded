#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <signal.h>

static int OpenFileWr(char const * const path, int * file_descriptor);
static int OpenFileRd(char const * const path, int * file_descriptor);
static int CloseFile(int file_descriptor);
static int SetParameter(char const * const path, char const * const info);
static int GetInputDescriptor(int * file_descriptor);
static void sig_handler(int signum);


static volatile sig_atomic_t flag = 1;


int main()
{
	struct pollfd p_request;
	char aux;
	int fd;

	/* install signal handler */
    signal(SIGINT, sig_handler);
	
	if(EXIT_SUCCESS != GetInputDescriptor(&fd)){
		SetParameter("/sys/class/gpio/unexport", "115");
		return EXIT_FAILURE;
	}	
	
	p_request.fd = fd;
	/*declara os eventos que serão monitorados em revents*/
	p_request.events = POLLPRI | POLLERR;
	
	
	while(flag) {

		/*Inicia procedimento de polling - bloqueia até ocorrer o evento*/
		int status = poll(&p_request, 1, -1);

		if(status > 0){
			/*verifica se existe algum dado para leitura*/
			if (p_request.revents & POLLPRI){
				lseek(p_request.fd, 0, SEEK_SET);
				read(p_request.fd, &aux, 1);
				printf("Estado do botão:%c\r\n",aux);
			}
		}
	}


	SetParameter("/sys/class/gpio/unexport", "115");

    return 0;
}

static void sig_handler(int signum){
    if (signum == SIGINT) {
        fprintf(stdout, "Exiting...\n");
        flag = 0;
    }
}

static int OpenFileWr(char const * const path, int * file_descriptor){
	int fd;
	
	if(file_descriptor == NULL){
		return EXIT_FAILURE;
	}

	fd = open(path, O_WRONLY);

	if(fd <= 0){
		perror("Unable to open file:");
		perror(path);
		return EXIT_FAILURE;
	}
	printf("File descriptor: %i\n", fd);
	*file_descriptor = fd;
	return EXIT_SUCCESS;
}

static int OpenFileRd(char const * const path, int * file_descriptor){
	int fd;
	
	if(file_descriptor == NULL){
		return EXIT_FAILURE;
	}

	fd = open(path, O_RDONLY);

	if(fd <= 0){
		perror("Unable to open file:");
		perror(path);
		return EXIT_FAILURE;
	}

	*file_descriptor = fd;
	return EXIT_SUCCESS;
}

static int CloseFile(int file_descriptor){
	int fd;
	
	printf("Closing: %i\n", file_descriptor);

	fd = close(file_descriptor);

	if(fd < 0){
		perror("Unable to close file.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

static int Write(int file_descriptor, char const * const info){
	int fd;
	int sz = strlen(info);

	printf("Writing: %s\n", info);
	
	fd = write(file_descriptor, info, sz);

	if(fd < 0){
		perror("Unable to write.");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

static int SetParameter(char const * const path, char const * const info){
	int fd;
	printf("Setting: %s\n", path);

	if(EXIT_SUCCESS != OpenFileWr(path, &fd)){
		goto error_open;
	}

	if(EXIT_SUCCESS != Write(fd, info)){
		goto error_write;
	}

	if(EXIT_SUCCESS != CloseFile(fd)){
		goto error_close;
	}

	return EXIT_SUCCESS;

error_open:
error_write:
error_close:
	return EXIT_FAILURE;
}

static int GetInputDescriptor(int * file_descriptor){
	if(EXIT_SUCCESS != SetParameter("/sys/class/gpio/export", "115")){
		goto error;
	}

    if(EXIT_SUCCESS != SetParameter("/sys/class/gpio/gpio115/direction", "in")){
		goto error;
	}
 
	if(EXIT_SUCCESS != OpenFileRd("/sys/class/gpio/gpio115/value", file_descriptor)){
		goto error;
	}

	return EXIT_SUCCESS;

error:
	return EXIT_FAILURE;

}