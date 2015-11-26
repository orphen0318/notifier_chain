#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/notifier.h>
#include <linux/kthread.h>
#include <linux/random.h>
#include <linux/sched.h>
#include <linux/completion.h>

enum requests {
	WATER = 0,
	BREAD,
	MILK,
	MAGAZINE,
	PAPER,
	LITERATURE,
	ALL
};

static struct task_struct *requirements_thread = NULL;

/* Define different type of notifier_chain, default is raw_notifier_chain */
static RAW_NOTIFIER_HEAD(requirement_chain);
//static ATOMIC_NOTIFIER_HEAD(requirement_chain);
//static BLOCKING_NOTIFIER_HEAD(requirement_chain);
//static struct srcu_notifier_head requirement_chain;

static DECLARE_COMPLETION(cmpl);

/* Use this function to register if someome want to get the notify. */
int register_publisher_notifier(struct notifier_block *nb)
{
	return raw_notifier_chain_register(&requirement_chain, nb);
	//return atomic_notifier_chain_register(&requirement_chain, nb);
	//return blocking_notifier_chain_register(&requirement_chain, nb);
	//return srcu_notifier_chain_register(&requirement_chain, nb);
}
EXPORT_SYMBOL(register_publisher_notifier);

/* Use this function to unregister if someone DO NOT want to get the notify. */
int unregister_publisher_notifier(struct notifier_block *nb)
{
	return raw_notifier_chain_unregister(&requirement_chain, nb);
	//return atomic_notifier_chain_unregister(&requirement_chain, nb);
	//return blocking_notifier_chain_unregister(&requirement_chain, nb);
	//return srcu_notifier_chain_unregister(&requirement_chain, nb);
}
EXPORT_SYMBOL(unregister_publisher_notifier);

/* Send notify. */
int call_publisher_notifier_chain(unsigned long val, void *v)
{
	return raw_notifier_call_chain(&requirement_chain, val, v);
	//return atomic_notifier_call_chain(&requirement_chain, val, v);
	//return blocking_notifier_call_chain(&requirement_chain, val, v);
	//return srcu_notifier_call_chain(&requirement_chain, val, v);
}
EXPORT_SYMBOL(call_publisher_notifier_chain);

static int create_requirement_thread(void *data)
{
	int loop = 15;
	unsigned int requirement_type = 0;
	printk(KERN_INFO "[Publisher] requirements thread starting!\n");

	while((loop--) > 0)
	{
		wait_for_completion_timeout(&cmpl, 3*HZ);
		get_random_bytes(&requirement_type, sizeof(requirement_type));	// Create a random number.
		requirement_type %= ALL;										// Create number from 0~5.
		printk(KERN_INFO "[Publisher] requirement type: %d\n", requirement_type);

		call_publisher_notifier_chain(requirement_type, NULL);
	}
	printk(KERN_INFO "[Publisher] requirements thread end!\n");
	return 0;
}

static int __init publisher_init(void)
{
	printk(KERN_INFO "[Publisher] publisher init\n");

	/* You will need this when using srcu notifier chain */
	//srcu_init_notifier_head(&requirement_chain);
	requirements_thread = kthread_run(create_requirement_thread, NULL, "publisher requirement thread");
	return 0;
}

static void __exit publisher_exit(void)
{
	printk(KERN_INFO "[Publisher] publisher exit\n");
}

module_init(publisher_init);
module_exit(publisher_exit);
MODULE_AUTHOR("Cloud Huang");
MODULE_DESCRIPTION("Publisher module");
MODULE_LICENSE("GPL v2");
