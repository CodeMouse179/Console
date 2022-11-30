#define SYSTEM_CONSOLE_FORCE_VT
#define SYSTEM_CONSOLE_ONLY_UTF8
#include "Console.hpp"
int main()
{
    System::Console::SetCursorVisible(false);
    System::Console::SetCursorPosition(1, 1);
    System::Console::WriteLine(U8("你好世界😄😜"));
    return 0;
}