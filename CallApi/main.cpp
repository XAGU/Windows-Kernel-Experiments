#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef ULONG (*DBGPRINT)(const char* Format, ...);

DBGPRINT DbgPrint = (DBGPRINT)0x83C2C41F;
//进入内核
void __declspec(naked) IdtEntry0x20()
{
	__asm
	{
		//修改fs
		push 0x30
		pop fs
		//开中断
		sti
	}
	//CALL API

	DbgPrint("hello");

	__asm
	{
		//关中断
		cli
		//恢复fs
		push 0x3b
		pop fs
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
	system("pause");
}