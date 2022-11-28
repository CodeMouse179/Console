//     +--------------------------------------------------------------------------------+
//     |                                  Console v0.2.0                                |
//     |  Introduction : System.Console in C++                                          |
//     |  Modified date : 2022/11/28                                                    |
//     |  License : MIT                                                                 |
//     |  Source Code : https://github.com/CodeMouse179/Console                         |
//     |  Readme : https://github.com/CodeMouse179/Console/blob/main/README.md          |
//     |                                                                                |
//     |                             Designer : CodeMouse179                            |
//     |  Email : codemouse179@gmail.com                                                |
//     |  Github : https://github.com/CodeMouse179                                      |
//     |  Bilibili : https://space.bilibili.com/3461577785215838                        |
//     +--------------------------------------------------------------------------------+

#ifndef SYSTEM_CONSOLE_HPP
#define SYSTEM_CONSOLE_HPP

//Versioning refer to Semantic Versioning 2.0.0 : https://semver.org/

#define SYSTEM_CONSOLE_VERSION_MAJOR 0
#define SYSTEM_CONSOLE_VERSION_MINOR 2
#define SYSTEM_CONSOLE_VERSION_PATCH 0
#define SYSTEM_CONSOLE_VERSION (SYSTEM_CONSOLE_VERSION_MAJOR << 16 | SYSTEM_CONSOLE_VERSION_MINOR << 8 | SYSTEM_CONSOLE_VERSION_PATCH)

#include "String.hpp"

namespace System
{
    class Console
    {
    public:
        static void Write(const std::string& value)
        {
            //TODO
        }

        static void WriteLine(const std::string& value)
        {
            Console::Write(value + "\n");
        }
    };
}

#endif