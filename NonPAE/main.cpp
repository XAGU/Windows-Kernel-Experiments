#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//global
DWORD g_num = 0x12345678;
DWORD g_cr3;

//进入内核
void __declspec(naked) IdtEntry0x20()
{
	__asm
	{
		mov eax,cr3
		mov g_cr3,eax
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
	printf("addr:%p\n", &g_num);
	printf("cr3:%p\n", g_cr3);
	system("pause");
}