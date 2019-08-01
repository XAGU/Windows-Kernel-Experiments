#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


/*
利用中断进入内核，修改内核IDT第0x20号中断到IdtEntry0x20() eq 80b95500 0040ee00`00081040
为了基地址固定，所以需要修改配置：编译器-》高级-》随机地址：否，固定地址：是！
并且需要以release编译
*/

DWORD g_R0Addr;

//进入内核
void __declspec(naked) IdtEntry0x20()
{
	__asm
	{
		//读内核地址
		mov eax, ds:[0x80b95500]
		mov g_R0Addr,eax
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
	printf("%x", g_R0Addr);
	system("pause");
}