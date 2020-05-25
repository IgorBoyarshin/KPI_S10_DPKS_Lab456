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


static void print_hello(unsigned int count)
{
	unsigned int i;
	struct my_time *ptr;

	for (i = 0; i < count; i++) {
		ptr = kmalloc(sizeof(struct my_time), GFP_KERNEL);
        if (ptr == NULL) continue;
		ptr->start = ktime_get_ns();
		pr_info("Hello, igorek!\n");
		ptr->finish = ktime_get_ns();
		list_add(&ptr->the_list, &my_list_head);
	}
}

static unsigned int times = 1;
module_param(times, uint, S_IRUGO);
MODULE_PARM_DESC(times, "Specifies the amount of times to print the greeting.");


static int __init igorek_init(void)
{
	if (times > 10) {
		pr_err("It is forbidden to insert the module with times > 10!\n");
		return -EINVAL;
	}

	if (times == 0 || (times >= 5 && times <= 10)) {
		pr_warn("Inserting with %d greeting calls...\n", times);
	}

	print_hello(times);
	return 0;
}

static void __exit igorek_exit(void)
{
	struct list_head *pos;
	struct list_head *temp;
	struct my_time *entry;

	pr_info(":> Remoing the module...\n");

	list_for_each_safe(pos, temp, &my_list_head) {
		entry = list_entry(pos, struct my_time, the_list);
		pr_info("Started at %lldns and finished at %lldns, delta = %lldns.\n",
			entry->start, entry->finish,
			entry->finish - entry->start);
		list_del(pos);
		kfree(entry);
	}
}

module_init(igorek_init);
module_exit(igorek_exit);


MODULE_AUTHOR("Igor Boyarshin");
MODULE_DESCRIPTION("Prints time of hellos in ns upon module unloading");
MODULE_LICENSE("Dual BSD/GPL");
