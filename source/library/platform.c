#include "platform.h"

#ifdef _WIN32
    #define WINDOWS_OS
    #include <windows.h>
#else
    #error
#endif

PLATFORM_API bool PlatformAllocateMemory(void **Memory, uptr Size)
{
    bool Result = 0;

#ifdef WINDOWS_OS
    *Memory = VirtualAlloc(0, Size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if(!*Memory)
    {
        Log("VirtualAlloc() failed: 0x%X\n", GetLastError());
        return Result;
    }
#else
    #error
#endif

    return 1;
}

PLATFORM_API bool PlatformFreeMemory(void **Memory)
{
    bool Result = 0;

#ifdef WINDOWS_OS
    if(!VirtualFree(*Memory, 0, MEM_RELEASE))
    {
        Log("VirtualFree() failed: 0x%X\n", GetLastError());        
        return Result;
    }

    *Memory = 0;
#else
    #error
#endif

    return 1;
}

PLATFORM_API bool PlatformGetFileSize(char *FileName, uptr *Size)
{
    bool Result = 0;

#ifdef WINDOWS_OS
    HANDLE FileHandle = CreateFileA(FileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if(FileHandle == INVALID_HANDLE_VALUE)
    {
        Log("CreateFileA() failed: 0x%X\n", GetLastError());
        return Result;
    }

    LARGE_INTEGER FileSize = {0};

    if(!GetFileSizeEx(FileHandle, &FileSize))
    {
        Log("GetFileSizeEx() failed: 0x%X\n", GetLastError());
        CloseHandle(FileHandle);
        return Result;
    }

    *Size = FileSize.QuadPart;
    CloseHandle(FileHandle);
#else
    #error
#endif

    return 1;
}

PLATFORM_API bool PlatformReadFile(char *FileName, void *Buffer, u32 BufferSize)
{
    bool Result = 0;

    HANDLE FileHandle = CreateFileA(FileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if(FileHandle == INVALID_HANDLE_VALUE)
    {
        Log("CreateFileA() failed: 0x%X\n", GetLastError());
        return Result;
    }
    
    DWORD BytesRead = 0;

    if(!ReadFile(FileHandle, Buffer, BufferSize, &BytesRead, 0))
    {
        DWORD Error = GetLastError();

        if(Error != ERROR_IO_PENDING)
        {
            Log("ReadFile() failed: 0x%X\n", GetLastError());
            CloseHandle(FileHandle);
            return Result;
        }
    }

    if(BytesRead != BufferSize)
    {
        Log("File %s bytes read %u is different from buffer size %u\n", FileName, BytesRead, BufferSize);
        CloseHandle(FileHandle);
        return Result;
    }

    CloseHandle(FileHandle);

    return 1;
}

PLATFORM_API bool PlatformWriteFile(char *FileName, void *Buffer, u32 BufferSize)
{
    bool Result = 0;

#ifdef WINDOWS_OS
    HANDLE FileHandle = CreateFileA(FileName, GENERIC_WRITE, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

    if(FileHandle == INVALID_HANDLE_VALUE)
    {
        Log("CreateFileA() failed: 0x%X\n", GetLastError());
        return Result;
    }
    
    DWORD BytesWritten = 0;

    if(!WriteFile(FileHandle, Buffer, BufferSize, &BytesWritten, 0))
    {
        DWORD Error = GetLastError();

        if(Error != ERROR_IO_PENDING)
        {
            Log("WriteFile() failed: 0x%X\n", GetLastError());
            CloseHandle(FileHandle);
            return Result;
        }
    }

    if(BytesWritten != BufferSize)
    {
        Log("File %s bytes written %u is different from buffer size %u\n", FileName, BytesWritten, BufferSize);
        CloseHandle(FileHandle);
        return Result;
    }

    CloseHandle(FileHandle);
#else
    #error
#endif

    return 1;
}

PLATFORM_API bool PlatformReallocateMemory(void **Memory, uptr NewSize, uptr OldSize)
{
    bool Result = 0;

    if(NewSize < OldSize)
    {
        Log("New size %llu is less than old size %llu\n", NewSize, OldSize);
        return Result;
    }

    void *ReallocatedMemory = 0;
    
    if(!PlatformAllocateMemory(&ReallocatedMemory, NewSize))
    {
        return Result;
    }

    u8 *destination = ReallocatedMemory;
    u8 *source = *Memory;

    for(uptr Index = 0; Index < OldSize; Index++)
    {
        *destination++ = *source++;
    }

    if(!PlatformFreeMemory(Memory))
    {
        PlatformFreeMemory(&ReallocatedMemory);
        return Result;
    }

    *Memory = ReallocatedMemory;

    return 1;
}