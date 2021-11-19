#include <stdio.h>


int main()
{
	int a= 270533154;
	printf("a = %x\n", a);
	char *ptr;
	ptr = (char*)&a;
	for(int i = 0; i < sizeof(a); i++)
	{
		printf("%d byte of a = %x\n", i, *ptr); 
		if (i == 2)
			*ptr = 16;
		ptr++;
	}

	printf("a after replace 3 byte to 16 = %x\n", a);
	return 0;
}



