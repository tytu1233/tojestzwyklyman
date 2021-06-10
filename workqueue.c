#include<linux/module.h>
#include<linux/workqueue.h>

DESCRIPTION
       These macros define and operate on  three  types  of  data  structures:
       lists,  tail queues, and circular queues.  All three structures support
       the following functionality:

           *   Insertion of a new entry at the head of the list.
           *   Insertion of a new entry after any element in the list.
           *   Removal of any entry in the list.
           *   Forward traversal through the list.

       Lists are the simplest of the three data structures  and  support  only
       the above functionality.

       Tail queues add the following functionality:

           *   Entries can be added at the end of a list.

       However:

           1.  All  list  insertions and removals must specify the head of the
               list.
           2.  Each head entry requires two pointers rather than one.
           3.  Code size is about 15% greater and  operations  run  about  20%
               slower than lists.

       Circular queues add the following functionality:

static struct workqueue_struct *queue;

static void normal_work_handler(struct work_struct *work) 
{
	pr_info("Hi! I'm handler of normal work!\n");
}

static void delayed_work_handler(struct work_struct *work) 
{
	pr_info("Hi! I'm handler of delayed work!\n");
}



static DECLARE_WORK(normal_work, normal_work_handler);
static DECLARE_DELAYED_WORK(delayed_work, delayed_work_handler);

static int __init workqueue_module_init(void) 
{ 
	queue = create_singlethread_workqueue("works");
	if(IS_ERR(queue)) {
		pr_alert("[workqueue_module] Error creating a workqueue: %ld\n",PTR_ERR(queue));
		return -ENOMEM;
	}
	
	if(!queue_work(queue,&normal_work))
		pr_info("The normal work was already queued!\n");
	if(!queue_delayed_work(queue,&delayed_work,10*HZ))
		pr_info("The delayed work was already queued!\n");

	return 0; 
}

However:

           1.  All  list  insertions and removals must specify the head of the
               list.
           2.  Each head entry requires two pointers rather than one.
           3.  Code size is about 15% greater and  operations  run  about  20%
               slower than lists.

       Circular queues add the following functionality:

           *   Entries can be added at the end of a list.
           *   Entries can be added before another entry.
           *   They may be traversed backward, from tail to head.

       However:

           1.  All  list  insertions and removals must specify the head of the
               list.
           2.  Each head entry requires two pointers rather than one.
           3.  The termination condition for traversal is more complex.
           4.  Code size is about 40% greater and  operations  run  about  45%
               slower than lists.

       In the macro definitions, TYPE is the name of a user-defined structure,
       that must contain a field of  type  LIST_ENTRY,  TAILQ_ENTRY,  or  CIR‐
       CLEQ_ENTRY,  named  NAME.  The argument HEADNAME is the name of a user-
       defined structure that must be declared  using  the  macros  LIST_HEAD,
       TAILQ_HEAD, or CIRCLEQ_HEAD.  See the examples below for further expla‐
       nation of how these macros are used

static void __exit workqueue_module_exit(void) 
{
	if(!IS_ERR(queue)) {
		if(cancel_work_sync(&normal_work))
			pr_info("The normal work has not been done yet!\n");
		if(cancel_delayed_work_sync(&delayed_work))
			pr_info("The delayed work has not been done yet!\n");
		destroy_workqueue(queue);
	}
}

module_init(workqueue_module_init);
module_exit(workqueue_module_exit);
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
