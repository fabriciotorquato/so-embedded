#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioport.h>
#include <asm/io.h>

#define AUTHOR 	""
#define DESC   	""
#define VERSION	""
#define DRIVER "mydriver"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_VERSION(VERSION);


static int __init init_mydriver(void);
static void __exit cleanup_mydriver(void);

static int mydriver_open(struct inode *i, struct file *f);
static int mydriver_close(struct inode *i, struct file *f);
static ssize_t mydriver_read(struct file *f, char __user *buf, size_t len, loff_t *off);


static void GPIO_Digital_Input(void);
static int GPIO_Read(void);

static struct file_operations fops = {
  .owner = THIS_MODULE,
  .open = mydriver_open,
  .release = mydriver_close,
  .read = mydriver_read,
};

static dev_t mydriver_dev;
static struct cdev mydriver_cdev;
static void __iomem * gpio_addr; /*região de memória mapeada*/

#define IO_ADDR(n) (0x01000000 + (0x1000*(n)))
#define GPIOE_BASE IO_ADDR(115)


static void GPIO_Digital_Input(void)
{
     unsigned int val;

     val = readl(gpio_addr);
     val = val & ~(1 << 9);
     writel(val, gpio_addr);
}

static int GPIO_Read(void)
{
     unsigned int val;

    val = readl(gpio_addr+4);

    if (val & (uint32_t)(1 << 0)) {
        val = 1;
    }
    else{
        val = 0;
    }

     return val;
}

static int mydriver_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "mydriver: open()\n");
    return 0;
}

static int mydriver_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "mydriver: close()\n");
    return 0;
}

static ssize_t mydriver_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    int status;
    int slen;

    printk(KERN_INFO "mydriver: read()\n");

    /*Se posição for diferente de 0 (EOF)....nenhum valor será escrito*/
    if (*off != 0)
	    return 0;

    status = GPIO_Read();

    if(status){
        slen = 3;
	      status = copy_to_user(buf, "ON\n", slen);    
    }
    else{
        slen = 4;
	      status = copy_to_user(buf, "OFF\n", slen);    
    }

    /*atualiza posição do arquivo*/
    *off += 1;

    if (status != 0)
        return -EFAULT;
    
    return slen;
}


static int __init init_mydriver(void)
{
  int code;

  /*Requisita a região de memória iniciada em GPIOE_BASE com tamanho de 8 bytes*/
  
  struct resource * res = request_mem_region(GPIOE_BASE, 8, DRIVER);

  if (res == NULL) {
    printk(KERN_ALERT "Error requesting GPIOE! DRIVER: %s\n", DRIVER);
    //code = -EBUSY;
    //goto error_request_mem_region;
  }
  

  /*Mapeia o endereço físico do registrador requisitado*/
  gpio_addr = ioremap(GPIOE_BASE, 8);

  if (gpio_addr == NULL) {
    printk(KERN_ALERT "Error mapping GPIOE! %s\n", DRIVER);
    code = -ENOMEM;
    goto error_ioremap;
  }


  /*Tenta obter um device number*/
  code = alloc_chrdev_region(&mydriver_dev, 0, 1, DRIVER);

  /*código 0: sucesso*/
  if (code) {
    printk(KERN_ALERT "Allocating device number failed! DRIVER: %s\n", DRIVER);
    goto error_alloc_chrdev_region;
  }

  /*determina as funções de callback para as operações do driver*/
  cdev_init(&mydriver_cdev, &fops);

  mydriver_cdev.owner = THIS_MODULE;
  
  /*tenta adicionar o driver no sistema - com apenas 1 minor*/
  code = cdev_add(&mydriver_cdev, mydriver_dev, 1);

  if (code) {
    printk(KERN_ALERT "Registering driver device failed!  DRIVER: %s\n", DRIVER);
    goto error_cdev_add;
  }

  printk(KERN_ALERT "Assigned major number %d! DRIVER: %s\n", MAJOR(mydriver_cdev.dev), DRIVER);

  /*ok, configurao pino como entrada digital*/
  GPIO_Digital_Input();
  
  return 0;


  /*error*/
error_cdev_add:
  unregister_chrdev_region(mydriver_dev, 1);

error_alloc_chrdev_region:

error_ioremap:
  release_mem_region(GPIOE_BASE, 8);

error_request_mem_region:

  return code;
}

static void __exit cleanup_mydriver(void)
{
  cdev_del(&mydriver_cdev);
  unregister_chrdev_region(mydriver_cdev.dev, 1);

  iounmap(gpio_addr);

  release_mem_region(GPIOE_BASE, 8);

  printk(KERN_ALERT "driver stopped\n");
}

module_init(init_mydriver);
module_exit(cleanup_mydriver);