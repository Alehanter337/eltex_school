#include <stdio.h>
#include <dlfcn.h>


typedef enum
{
    false,
    true
} bool;

int main()
{
	int choose;
	int c;
	int d;
	int *result;
	void *library_handler;

	printf("Choose operation: \n1.Plus\n2.Minus\n3.Multiply\n4.Division\n5.End\n");

	library_handler = dlopen("/home/eltex/eltex_school/hw7/libcalc.so", RTLD_LAZY);
	

	int (*plus)(int *a, int *b) = dlsym(library_handler, "plus");
	int (*minus)(int *a, int *b) = dlsym(library_handler, "minus");
	int (*div)(int *a, int *b) = dlsym(library_handler, "div");
	int (*multiply)(int *a, int *b) = dlsym(library_handler, "multiply");


	do
	{
		printf("Send me number of operation: ");
		scanf("%d", &choose);
		
		switch(choose)
		{
			case 1:
			{
				printf("-Plus operation-\n");
				printf("Send me first number: ");
				scanf("%d", &c);				
				printf("Send me second number: ");
				scanf("%d", &d);
				result = (*plus)(c, d);
				printf("Result = %d \n", result);
				break;
			}

			case 2:
			{
				printf("-Minus operation-\n");
				printf("Send me first number: ");
				scanf("%d", &c);
				printf("Send me second number: ");
				scanf("%d", &d);
				result = (*minus)(c, d);
				printf("Result = %d \n", result);
				break;
			}

			case 3:
			{
				printf("-Multiply operation-\n");
				printf("Send me first number: ");
				scanf("%d", &c);
				printf("Send me second number: ");
				scanf("%d", &d);
				*result = (*multiply)(c, d);
				printf("Result = %d\n", &result);
				break;
			}

			case 4:
			{
				printf("-Division operation-\n");
				printf("Send me first number: ");
				scanf("%d", &c);
				printf("Send me second number: ");
				scanf("%d", &d);
				result = (*div)(c, d);
				printf("Result= %d\n", result);
				break;
			}

			case 5:
				break;
		
			default:
				printf("wrong operation\n");
				break;
		} 
	}
	while (choose != 5);
	
	dlclose(library_handler);
	return 0;
}
