#define SYSTEM_CONSOLE_FORCE_VT
#include "Console.hpp"
int main()
{
    System::Console::SetCursorPosition(1, 1);
    System::Console::WriteLine(U8("你好世界😄😜"));
    return 0;
}