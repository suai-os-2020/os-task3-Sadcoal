#include "lab3.h"
#include <windows.h> 
#include <stdio.h>
using namespace std;
#define THREADCOUNT 5
HANDLE Thread[THREADCOUNT];
HANDLE Mutex;
HANDLE SemB, SemC, SemD;
unsigned int lab3_thread_graph_id()
{
	return 6;
}
const char* lab3_unsynchronized_threads()
{
	return "deg";
}
const char* lab3_sequential_threads()
{
	return "bcd";
}
DWORD WINAPI threads_unsynchronized(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
	}
	return 0;
}
DWORD WINAPI thread_b(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(SemB, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemC, 1, NULL);
	}
	return 0;
}
DWORD WINAPI thread_c(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(SemC, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemD, 1, NULL);
	}
	return 0;
}
DWORD WINAPI thread_d(LPVOID text)
{
	for (int i = 0; i < 3; ++i)
	{
		WaitForSingleObject(SemD, INFINITE);
		WaitForSingleObject(Mutex, INFINITE);
		cout << (char const*)text << flush;
		ReleaseMutex(Mutex);
		computation();
		ReleaseSemaphore(SemB, 1, NULL);
	}
	return 0;
}
int lab3_init()
{
	DWORD ThreadID;
	Mutex = CreateMutex(NULL, FALSE, NULL);
	if (Mutex == NULL)
	{
		cout << "CreateMutex error " << GetLastError() << endl;
		return 1;
	}
	SemB = CreateSemaphore(NULL, 1, 1, NULL);
	if (SemB == NULL)
	{
		cout << "CreateSemaphore error: SemE" << GetLastError() << endl;
		return 1;
	}
	SemC = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemC == NULL)
	{
		cout << "CreateSemaphore error: SemH " << GetLastError() << endl;
		return 1;
	}
	SemD = CreateSemaphore(NULL, 0, 1, NULL);
	if (SemD == NULL)
	{
		cout << "CreateSemaphore error: SemI" << GetLastError() << endl;
		return 1;
	}

	char const* textsA = "a";
	Thread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsA, 0, &ThreadID);
	if (Thread[0] == NULL)
	{
		cout << "CreateThread error: " << textsA << GetLastError() << endl;
		return 1;
	}
	WaitForSingleObject(Thread[0], INFINITE);

	char const* textsBCD[] = { "b", "c", "d" };
	Thread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_b, (void*)textsBCD[0], 0, &ThreadID);
	if (Thread[0] == NULL)
	{
		cout << "CreateThread error:  " << textsA[0] << GetLastError() << endl;
		return 1;
	}
	Thread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_c, (void*)textsBCD[1], 0, &ThreadID);
	if (Thread[1] == NULL)
	{
		cout << "CreateThread error:  " << textsA[1] << GetLastError() << endl;
		return 1;
	}
	Thread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_d, (void*)textsBCD[2], 0, &ThreadID);
	if (Thread[2] == NULL)
	{
		cout << "CreateThread error:  " << textsA[2] << GetLastError() << endl;
		return 1;
	}
	for (int i = 0; i < 3; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	int count = 0; 
	char const* textsDEG[] = { "d","e","g" };
	for (int i = 0; i < 3; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsDEG[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsDEG[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}
	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;
	char const* textsGFH[] = { "g", "f","h" };
	for (int i = 0; i < 3; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsGFH[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsGFH[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}
	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}
	count = 0;
	char const* textsHIK[] = { "h", "i","k" };
	for (int i = 0; i < 3; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsHIK[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsHIK[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}
	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	count = 0;
	char const* textsKM[] = { "k","m" };
	for (int i = 0; i < 2; ++i)
	{
		Thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threads_unsynchronized, (void*)textsKM[i], 0, &ThreadID);
		if (Thread[i] == NULL)
		{
			cout << "CreateThread error: " << textsKM[i] << GetLastError() << endl;
			return 1;
		}
		else ++count;
	}
	for (int i = 0; i < count; ++i) {
		WaitForSingleObject(Thread[i], INFINITE);
	}

	CloseHandle(SemB);
	CloseHandle(SemC);
	CloseHandle(SemD);
	CloseHandle(Mutex);
	cout << endl;

	return 0;
}