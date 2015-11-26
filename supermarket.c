#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/notifier.h>

extern int register_publisher_notifier(struct notifier_block *nb);
extern int unregister_publisher_notifier(struct notifier_block *nb);

static int supermarket_supply_goods(struct notifier_block *nb, unsigned long action, void *data)
{
	switch (action)
	{
		case 0:					// water event.
			printk(KERN_INFO "[SUPER MARKET] water supply\n");
			return NOTIFY_OK;
		case 1:					// bread event.
			printk(KERN_INFO "[SUPER MARKET] bread supply\n");
			return NOTIFY_OK;
		case 2:					// milk event.
			printk(KERN_INFO "[SUPER MARKET] milk supply\n");
			return NOTIFY_OK;
		case 3:					// magazine event.
			printk(KERN_INFO "[SUPER MARKET] magazine supply\n"); 
			return NOTIFY_STOP;
		case 4:					// paper event.
			printk(KERN_INFO "[SUPER MARKET] paper supply\n");
			return NOTIFY_OK;
		case 5:					// literature event.
			printk(KERN_INFO "[SUPER MARKET] literature supply\n");
			return NOTIFY_OK;
		default:
			return NOTIFY_DONE;
	}

	return NOTIFY_DONE;
}

static struct notifier_block all_notifier = 
{
	.notifier_call = supermarket_supply_goods,
	.priority = 3,
};

static int __init supermarket_init(void)
{
	int err;
	printk(KERN_INFO "[SUPER MARKET] register all_notifier response to publisher!\n");

	err = register_publisher_notifier(&all_notifier);
	if (err)
	{
		printk(KERN_INFO "[SUPER MARKET] register failed.\n");
		return -1;
	}

	return 0;
}

static void __exit supermarket_exit(void)
{
	unregister_publisher_notifier(&all_notifier);
	printk(KERN_INFO "[SUPER MARKET] unregister all_notifier.\n");
}

module_init(supermarket_init);
module_exit(supermarket_exit);
MODULE_AUTHOR("Cloud Huang");
MODULE_DESCRIPTION("SuperMarket module");
MODULE_LICENSE("GPL v2");
