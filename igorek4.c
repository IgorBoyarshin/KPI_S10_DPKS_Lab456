/* #define DEBUG */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/ktime.h>
#include <linux/types.h>
#include <linux/slab.h>

static LIST_HEAD(my_list_head);

struct my_time {
	ktime_t start;
	ktime_t finish;
	struct list_head the_list;
};


static unsigned int times = 1;
module_param(times, uint, S_IRUGO);
MODULE_PARM_DESC(times, "Specifies the amount of times to print the greeting.");


static int __init igorek_init(void)
{
	unsigned int i;
	struct my_time *ptr;

	BUG_ON(times > 10);

	if (times == 0 || (times >= 5 && times <= 10)) {
		pr_warn("Inserting with %d greeting calls...\n", times);
	}

	for (i = 0; i < times; i++) {
		ptr = kmalloc(sizeof(struct my_time), GFP_KERNEL);
		list_add(&ptr->the_list, &my_list_head);
		ptr->start = ktime_get_ns();
		pr_info("Hello, igorek!\n");
		ptr->finish = ktime_get_ns();
	}

	return 0;
}

static void __exit igorek_exit(void)
{
	struct list_head *pos;
	struct list_head *temp;
	struct my_time *entry;

	pr_info(":> Removing the module...\n");

	pr_debug("Before list print\n");
	list_for_each_safe(pos, temp, &my_list_head) {
		entry = list_entry(pos, struct my_time, the_list);
		pr_debug("Started at %lldns and finished at %lldns, delta = %lldns.\n",
			entry->start, entry->finish,
			entry->finish - entry->start);
		list_del(pos);
		kfree(entry);
	}
	pr_debug("After list print\n");
}

module_init(igorek_init);
module_exit(igorek_exit);


MODULE_AUTHOR("Igor Boyarshin");
MODULE_DESCRIPTION("Prints time of hellos in ns upon module unloading");
MODULE_LICENSE("Dual BSD/GPL");
