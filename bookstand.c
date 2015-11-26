#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/notifier.h>

extern int register_publisher_notifier(struct notifier_block *nb);
extern int unregister_publisher_notifier(struct notifier_block *nb);

static int bookstand_supply_goods(struct notifier_block *nb, unsigned long action, void *data)
{
	switch (action)
	{
		case 3:					// magazine event.
			printk(KERN_INFO "[BOOKSTAND] magazine supply.\n");
			return NOTIFY_OK;
		case 4:					// paper event.
			printk(KERN_INFO "[BOOKSTAND] paper supply.\n");
			return NOTIFY_OK;
		case 5:					// literature event.
			printk(KERN_INFO "[BOOKSTAND] literature supply.\n");
			return NOTIFY_OK;
		default:
			return NOTIFY_DONE;	
	}

	return NOTIFY_DONE;
}

static struct notifier_block reading_notifier = 
{
	.notifier_call = bookstand_supply_goods,
	.priority = 2,
};

static int __init bookstand_init(void)
{
	int err;
	printk(KERN_INFO "[BOOKSTAND] register reading_notifier response to Publisher!\n");

	err = register_publisher_notifier(&reading_notifier);
	if (err)
	{
		printk(KERN_INFO "[BOOKSTAND] register fail.\n");
		return -1;
	}

	return 0;
}

static void __exit bookstand_exit(void)
{
	unregister_publisher_notifier(&reading_notifier);
	printk(KERN_INFO "[BOOKSTAND] unregister reading_notifier.\n");
}

module_init(bookstand_init);
module_exit(bookstand_exit);
MODULE_AUTHOR("Cloud Huang");
MODULE_DESCRIPTION("Bookstand module");
MODULE_LICENSE("GPL v2");
