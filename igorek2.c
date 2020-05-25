#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include "igorek.h"

static unsigned int times = 1;
module_param(times, uint, S_IRUGO);
MODULE_PARM_DESC(times, "Specifies the amount of times to print the greeting.");

static int __init igorek_init(void) {
    if (times > 10) {
        pr_err("It is forbidden to insert the module with times > 10!\n");
        return -EINVAL;
    }

    if (times == 0 || (5 <= times && times <= 10)) {
        pr_warn("Inserting the module with %d greeting calls...\n", times);
    }

    print_hello(times);
    return 0;
}

static void __exit igorek_exit(void)
{
    pr_info("Bye, igorek!\n");
}

module_init(igorek_init);
module_exit(igorek_exit);


MODULE_AUTHOR("Igor Boyarshin");
MODULE_DESCRIPTION("Greets the user");
MODULE_LICENSE("Dual BSD/GPL");
