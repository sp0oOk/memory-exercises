#include <iostream>
#include <cstdlib>
#include "Bypass.h"

constexpr uintptr_t ADDRESS_INT = 0x8A46AFFB14;
constexpr DWORD PROCESS_ID = 8336;
constexpr SIZE_T WRITTEN_IN_MEM = 0;

int main()
{
	Bypass bypass = Bypass();
	
	if (!bypass.Attach(PROCESS_ID))
	{
		std::cout << "Failed to attach to process, last error: " << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Attached to process" << std::endl;

	
	int someData = 0;

	if (!bypass.Read(ADDRESS_INT, &someData, sizeof(int)))
	{
		std::cout << "Failed to read process memory, last error: " << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "The data at address " << ADDRESS_INT << " is -> " << someData << std::endl;

	int someRandomData = std::rand() % 100;

	std::cout << "The random integer to write " << someRandomData << std::endl;

	if (!bypass.Write(ADDRESS_INT, &someRandomData, sizeof(int), WRITTEN_IN_MEM))
	{
		std::cout << "Failed to write to process, " << WRITTEN_IN_MEM << " written bytes(s) | last error : " << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Result [Random Data | Read Data | Written Bytes | PID]:" << std::endl;
	std::cout << someRandomData << " | " << someData << " | " << WRITTEN_IN_MEM << " | " << PROCESS_ID << std::endl;

	return EXIT_SUCCESS;
}