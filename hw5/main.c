#include <stdio.h>
#include "calc.h"

typedef enum
{
    false,
    true
} bool;

int main()
{
	int choose;
	int a;
	int b;
	int result;
	printf("Choose operation: \n1.Plus\n2.Minus\n3.Multiply\n4.Division\n5.End\n");
	
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
				scanf("%d", &a);				
				printf("Send me second number: ");
				scanf("%d", &b);
				result = plus(a, b);
				printf("Result = %d \n", result);
				break;
			}

			case 2:
			{
				printf("-Minus operation-\n");
				printf("Send me first number: ");
				scanf("%d", &a);
				printf("Send me second number: ");
				scanf("%d", &b);
				result = minus(a, b);
				printf("Result = %d \n", result);
				break;
			}

			case 3:
			{
				printf("-Multiply operation-\n");
				printf("Send me first number: ");
				scanf("%d", &a);
				printf("Send me second number: ");
				scanf("%d", &b);
				result = multiply(a, b);
				printf("Result = %d\n", result);
				break;
			}

			case 4:
			{
				printf("-Division operation-\n");
				printf("Send me first number: ");
				scanf("%d", &a);
				printf("Send me second number: ");
				scanf("%d", &b);
				result = div(a, b);
				printf("Result= %d \n", result);
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

	return 0;
}
