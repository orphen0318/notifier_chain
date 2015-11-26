#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/notifier.h>

extern int register_publisher_notifier(struct notifier_block *nb);
extern int unregister_publisher_notifier(struct notifier_block *nb);

static int grocery_supply_goods(struct notifier_block *nb, unsigned long action, void *data)
{
	switch (action)
	{
		case 0:					// water event.
			printk(KERN_INFO "[GROCERY] water supply\n");
			return NOTIFY_OK;
		case 1:					// bread event.
			printk(KERN_INFO "[GROCERY] bread supply\n");
			return NOTIFY_OK;
		case 2:					// milk event.
			printk(KERN_INFO "[GROCERY] milk supply\n");
			return NOTIFY_OK;
		default:
			return NOTIFY_DONE;
	}
	
	return NOTIFY_DONE;
}

static struct notifier_block groceries_notifier = 
{
	.notifier_call = grocery_supply_goods,
	.priority = 4,
};

static int __init grocery_init(void)
{
	int err;
	printk(KERN_INFO "[GROCERY] register groceries_notifier response to Publisher!\n");

	err = register_publisher_notifier(&groceries_notifier);
	if (err)
	{
		printk(KERN_INFO "[GROCERY] register failed.\n");
		return -1;
	}

	return 0;
}

static void __exit grocery_exit(void)
{
	unregister_publisher_notifier(&groceries_notifier);
	printk(KERN_INFO "[GROCERY] unregister groceries_notifier.\n");
}

module_init(grocery_init);
module_exit(grocery_exit);
MODULE_AUTHOR("Cloud Huang");
MODULE_DESCRIPTION("Grocery module");
MODULE_LICENSE("GPL v2");
