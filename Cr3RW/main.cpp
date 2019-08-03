#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//global

void SystemCallEntry();
//进入内核
void __declspec(naked) IdtEntry0x20()
{
	memcpy((void*)0x80b95180, SystemCallEntry, 128);
	__asm
	{
		mov eax, 0x80b95180
		call eax
		iretd
	}
}

void __declspec(naked) SystemCallEntry()
{
	__asm
	{
		mov eax, cr3
		mov ds : [0x80b95100], eax
		//切换cr3
		mov eax, 0x7ee103c0
		mov cr3, eax

		mov ecx, 0x12345678
		mov ds : [0x004980C8], ecx
		mov eax, ds : [0x80b95100]
		mov cr3, eax
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
	printf("address error ! address:%p", IdtEntry0x20);
	system("pause");
}