#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include "igorek.h"

void print_hello(unsigned int count) {
    unsigned int i;
    for (i = 0; i < count; i++) pr_info("Hello, igorek!\n");
}
EXPORT_SYMBOL(print_hello);

static int __init igorek_init(void) {
    pr_info("Will export the function!\n");
    return 0;
}

static void __exit igorek_exit(void) {
    pr_info("Will no longer export the function...\n");
}

module_init(igorek_init);
module_exit(igorek_exit);


MODULE_AUTHOR("Igor Boyarshin");
MODULE_DESCRIPTION("Exports a function that greets the user");
MODULE_LICENSE("Dual BSD/GPL");
