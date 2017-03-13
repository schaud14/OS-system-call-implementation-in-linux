#include <linux/linkage.h>
#include <linux/export.h>
#include <linux/time.h>
#include <asm/uaccess.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/timekeeping.h>

asmlinkage int sys_my_xtime(struct timespec *current_time,int choice)
{	
	int return_value = 0;
	struct timespec ccurrent;
	switch (choice)
	{
	case 1:
		{
			if(!access_ok(VERIFY_WRITE, current_time, sizeof(struct timespec)))
			{
				return -EFAULT;	
			}
			if(copy_from_user(&ccurrent, current_time ,sizeof(struct timespec)))
			{
				printk(KERN_ALERT "Invalid Memory Access from user");
				return -EFAULT;				
			}	
		
		getnstimeofday(&ccurrent);
		ccurrent.tv_nsec = (ccurrent.tv_sec * 1000000000)+ccurrent.tv_nsec;		
		
			if(copy_to_user(current_time, &ccurrent,sizeof(struct timespec)))
			{
				printk(KERN_ALERT "Invalid Memory Access to user");
				return -EFAULT;				
			}
	
		
		printk(KERN_ALERT "The Current Time in Seconds is : %li\n",current_time->tv_sec);	
		printk(KERN_ALERT "The Current Time in NanoSeconds is : %li\n",current_time->tv_nsec);
		return_value = 1;
		break;
		}	
	case 2:
		{
			char * in;
			int size;
			size = 1;
			while (1)
			{
				size = size * 5;
				in = kmalloc(size,GFP_KERNEL);	
				printk(KERN_ALERT "Size Allocated is : %d",size);
			}
			kfree(in);
			break;
		}
	case 3:
		{
			int i;			
			while (1)
			{
				i = sys_my_xtime(current_time,choice);	
				printk(KERN_ALERT "Return value : %d",i);			
			}				
		
			break;		
		}
	case 4:
		{
			int x=0;
			int y=1;
			int z;
			z = 1/0;
			printk(KERN_ALERT "Value of z : %d",z);			
			return_value = z;
			break;		
		}
	case 5: 
		{
			int * in;
			in = NULL;
			printk(KERN_ALERT " Value of Null Pointer : %d ",*in );
			kfree(in);			
			break;		
		}
	case 6:
		{	
			char return_str[10] = "WrongTYPE";
			printk(KERN_ALERT  "Returning Wrong data type");			
			return return_str;
		}
	case 7:
		{
			char return_str[10] = "WrongTYPE";
			printk(KERN_ALERT  "Printing string as integer\n" );
			printk(KERN_ALERT  "Printing %d", return_str );
			return_value = 0;		
		}
		
	}	
	return return_value;
}	
EXPORT_SYMBOL(sys_my_xtime);
