#include "../../library/base.h"
#include "../../library/string.h"
#include "../../library/platform.h"

int main(int ArgumentCount, char **Argument)
{
    int Result = 1;
    
    char *FileName = "lexical_1.txt";
    uptr FileSize = 0;
    Assert(PlatformGetFileSize(FileName, &FileSize));
    
    void *Memory = 0;
    Assert(PlatformAllocateMemory(&Memory, FileSize));

    Assert(PlatformReadFile(FileName, Memory, (u32)FileSize));
    char *String = "Hello, world!";
    
    Assert(PlatformWriteFile(FileName, String, (u32)StringLength(String)));
    
    Assert(PlatformFreeMemory(&Memory));

    return 0;
}