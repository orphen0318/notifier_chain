##Notifier Chain

A notifier chain is simply a list of functions to execute when a given event occurs.

>Notifier chain mechanism is a so-called publish-and-subscribe model, thus for each notifier chain there is a passive side(the >**notified**) and an active side(the **notifier**):
>>* The ***notified*** is the subscriber that ask to be notified about the event and that provide a callback function to invoke.
>>* The ***notifier*** is the publisher that experiences an event and calls the callback function.


>There are four types of notifier chain be provided in linux kernel(based on 3.13.0-44):
>>* Raw Notifier chains
>>* Atomic Notifier chains 
>>* Blocking Notifier chains
>>* SRCU Notifier chains

>Please refer to /kernel/include/linux/notifier.h for more details.

This example briefly demonstrates how to use them.  
You could directly run **test.sh**(need root permission) and use **dmesg** to observe to output, or build it by yourself.  
Enjoy it! ☺
