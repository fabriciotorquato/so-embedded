#include <linux/module.h>
#include <linux/init.h> // entry/exit macros
#include <linux/kernel.h> // printk() definition

#define AUTHOR "..."
#define DESC "..."
#define VERSION "0.1"

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_VERSION(VERSION);

static int __init init_mymodule(void)
{
    printk(KERN_ALERT "module init\n");
    return 0;
}

static void __exit cleanup_mymodule(void)
{
    printk(KERN_ALERT "module stopped\n");
}

module_init(init_mymodule);
module_exit(cleanup_mymodule);