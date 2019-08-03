#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define PTE(_x) ((DWORD *)(0xc0000000 + ((_x>>12)<<3)))
#define PDE(_x) ((DWORD *)(0xc0600000 + ((_x>>21)<<3)))

//global
DWORD g_var = 0x12345678;
DWORD g_zero;
//进入内核
void __declspec(naked) IdtEntry0x20()
{
	PTE(0)[0] = PTE(0x403018)[0];
	PTE(0)[1] = PTE(0x403018)[1]; 
	g_zero = *(DWORD *)0x0;
	__asm
	{
		iretd
	}
}

//触发0x20号中断
void go()
{
	__asm
	{
		int 0x20
	}
}

int main()
{
	if ((DWORD)IdtEntry0x20 != 0x00401040)
	{
		printf("address error ! address:%p", IdtEntry0x20);
		return 0;
	}
	go();
	printf("g_zero:%p\n", g_zero);
	printf("g_var:%p", g_var);
	system("pause");
}