//     +--------------------------------------------------------------------------------+
//     |                                  Console v0.3.0                                |
//     |  Introduction : System.Console in C++                                          |
//     |  Modified Date : 2022/11/28                                                    |
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
#define SYSTEM_CONSOLE_VERSION_MINOR 3
#define SYSTEM_CONSOLE_VERSION_PATCH 0
#define SYSTEM_CONSOLE_VERSION (SYSTEM_CONSOLE_VERSION_MAJOR << 16 | SYSTEM_CONSOLE_VERSION_MINOR << 8 | SYSTEM_CONSOLE_VERSION_PATCH)
#define SYSTEM_CONSOLE_VERSION_STRING "0.3.0"

#include "String.hpp" //System.String for C++

namespace System
{
    class Console
    {
    private:
        //static class
        Console()
        {
        }

    private: //I/O Handle:
        static int inputHandle;
        static int outputHandle;

    public: //Properties:
        static int InputHandle()
        {
            return Console::inputHandle;
        }

        static int OutputHandle()
        {
            return Console::outputHandle;
        }

    public: //Methods:
        static bool SetInputHandle(int inputHandle)
        {
            if (inputHandle == 0) return false;
            Console::inputHandle = inputHandle;
            return true;
        }

        static bool SetOutputHandle(int outputHandle)
        {
            if (outputHandle == 0) return false;
            Console::outputHandle = outputHandle;
            return true;
        }

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