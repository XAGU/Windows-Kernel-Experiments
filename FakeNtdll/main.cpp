//¼ÙµÄNtdll
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

DWORD ReadMemory(DWORD Address);
DWORD AllocMemory(DWORD size);


DWORD __declspec(naked) ReadMemory(DWORD Address)
{
	__asm
	{
		mov eax,0
		int 0x21
		ret
	}
}


DWORD __declspec(naked) AllocMemory(DWORD size)
{
	__asm
	{
		mov eax, 1
		int 0x21
		ret
	}
}

int main()
{
	printf("%p/n", ReadMemory(0x80b95400));
	printf("%p/n", AllocMemory(102400000));
	system("pause");
	return 0;
}