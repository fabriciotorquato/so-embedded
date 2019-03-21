#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <signal.h>

#define IO_ADDR(n) (0x01000000 + (0x1000*(n)))
#define GPIOE_ADDR (4+IO_ADDR(115))

static void sig_handler(int signum);

static volatile sig_atomic_t flag = 1;

int main()
{
    /* install signal handler */
    signal(SIGINT, sig_handler);

    int fd = open("/dev/mem",O_RDWR);

    if (fd < 0) {
        perror("db410c mmap: unable to open /dev/mem");
        return EXIT_FAILURE;
    }

    long AddrMask = ~(sysconf(_SC_PAGESIZE)-1);
    long AddrAligned = GPIOE_ADDR & AddrMask;

    printf("Page size: %li\n", sysconf(_SC_PAGESIZE));
    printf("GPIO real: %i\n", GPIOE_ADDR);
    printf("GPIO aligned: %li\n", AddrAligned);

    uint8_t* base_addr =  (uint8_t*) mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, AddrAligned);
    uint32_t offset_addr = GPIOE_ADDR-AddrAligned;
    
    close(fd);

    if(base_addr == NULL){
        perror("NULL pointer mmpa");
        return EXIT_FAILURE;
    }

    uint32_t value;
    

    value = *(volatile uint32_t*) (base_addr + offset_addr);

    if (value & (uint32_t)(1 << 0)) {
        value = 1;
    }
    else{
        value = 0;
    }

    printf("State: %i\n", value);

    munmap(base_addr, 4);
}

static void sig_handler(int signum){
    if (signum == SIGINT) {
        fprintf(stdout, "Exiting...\n");
        flag = 0;
    }
}
