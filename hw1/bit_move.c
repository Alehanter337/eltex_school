#include <stdio.h>


int main(){
	int a = 0x00DDAABB;
	int b = 0x00CCAABB;
	unsigned char c;
	for (int i = 0; i < sizeof(a); i++) {
		c = (a & 0xFF);
		printf("%d bite a = %x\n", i, c);
		a = a >> 8;
	}
	a = 0xDDAABB;	
	printf("default a - 0x00%X", a);
	a^= 0x11 << 16;
	printf("\nit's a after bite move - 0x00%X",a);
	
	printf("\nmust be - 0x00%X", b);
	return 0;
	
}
