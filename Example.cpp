#include "Console.hpp"
int main()
{
    System::Console::SetCursorPosition(10, 5);
    System::Console::WriteLine(U8("你好世界😄😜"));
    return 0;
}