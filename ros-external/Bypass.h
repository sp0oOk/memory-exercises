#include <Windows.h>

#pragma once

class Bypass
{
private:
	HANDLE m_hProcess;
public:
	Bypass()
	{
		// ...
	}

	~Bypass()
	{
		if (m_hProcess != NULL)
		{
			CloseHandle(m_hProcess);
		}
	}

	BOOL Attach(DWORD pid)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		if (hProcess == NULL)
		{
			return FALSE;
		}
		
		m_hProcess = hProcess;
		
		return TRUE;
	}

	BOOL Read(uintptr_t lpBaseAddress, LPVOID  lpBuffer, SIZE_T nSize)
	{
		if (ReadProcessMemory(m_hProcess, (LPCVOID)lpBaseAddress, lpBuffer, nSize, NULL) == NULL)
		{
			return FALSE;
		}
		
		return TRUE;
	}
	
	BOOL Write(uintptr_t lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T lpNumberOfBytesWritten)
	{
		if (WriteProcessMemory(m_hProcess, (LPVOID)lpBaseAddress, lpBuffer, nSize, &lpNumberOfBytesWritten) == NULL)
		{
			return FALSE;
		}

		return TRUE;
	}
	
};

