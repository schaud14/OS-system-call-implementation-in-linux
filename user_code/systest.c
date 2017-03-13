#include <stdio.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
#include <linux/time.h>
int main ()
{
	int choice,result;
	struct timespec current_time;
	
	printf("\t1. Get Current Time in Nano Seconds\n\t2. Test Bad Code : Heap OverFlow (System will hang)\n\t3. Test Bad Code : Stack OverFlow (System will hang)\n\t4. Test Bad Code : Divide by Zero\n\t5. Test Bad Code : Null Pointer\n\t6.Test Bad Code : Wrong Return Value\n\t7.Test Bad Code : Referencing Wrong DataType\n");	
	
	do
	{
		printf("\nEnter Choice :  " );
		scanf("%d",&choice);
	}while ( choice > 7 || choice < 1 );
	
	result = syscall(326,&current_time,choice);
	if (result == 1)
	{
		printf("%s %li\n","Current Time in Seconds :",current_time.tv_sec);
		printf("%s %li\n","Current Time in NanoSeconds :",current_time.tv_nsec);
	}
	else if (result = -14)
	{
		printf("%s\n","Invalid memory access at kernel level");

	}
	else
	{
		printf("%s %d\n","Result Value from syscall :",result);
	}
	return 0;
}
