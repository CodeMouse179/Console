﻿//     +--------------------------------------------------------------------------------+
//     |                                  Console v0.4.0                                |
//     |  Introduction : System.Console in C++                                          |
//     |  Modified Date : 2022/11/29                                                    |
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
#define SYSTEM_CONSOLE_VERSION_MINOR 4
#define SYSTEM_CONSOLE_VERSION_PATCH 0
#define SYSTEM_CONSOLE_VERSION (SYSTEM_CONSOLE_VERSION_MAJOR << 16 | SYSTEM_CONSOLE_VERSION_MINOR << 8 | SYSTEM_CONSOLE_VERSION_PATCH)
#define SYSTEM_CONSOLE_VERSION_STRING "0.4.0"

#include "String.hpp"       //System.String for C++
#include "Singleton.hpp"    //CodeMouse.Singleton for C++

namespace System
{
    class ConsoleIO : public CodeMouse::Singleton<ConsoleIO>
    {
    private:
        int inputHandle;
        int outputHandle;

    public:
        ConsoleIO()
        {
#ifdef SYSTEM_WINDOWS
            this->inputHandle = (int)GetStdHandle(STD_INPUT_HANDLE);
            this->outputHandle = (int)GetStdHandle(STD_OUTPUT_HANDLE);
#endif
#ifdef SYSTEM_LINUX
            this->inputHandle = STDIN_FILENO;
            this->outputHandle = STDOUT_FILENO;
#endif
        }

        int GetInputHandle()
        {
            return this->inputHandle;
        }

        int GetOutputHandle()
        {
            return this->outputHandle;
        }

        void SetInputHandle(int inputHandle)
        {
            this->inputHandle = inputHandle;
        }

        void SetOutputHandle(int outputHandle)
        {
            this->outputHandle = outputHandle;
        }
    };

    class Console
    {
    private:
        //static class
        Console()
        {
        }

    public: //Properties:
        static int InputHandle()
        {
            return ConsoleIO::GetInstance().GetInputHandle();
        }

        static int OutputHandle()
        {
            return ConsoleIO::GetInstance().GetOutputHandle();
        }

    public: //Methods:
        static bool SetInputHandle(int inputHandle)
        {
            if (inputHandle == 0) return false;
            ConsoleIO::GetInstance().SetInputHandle(inputHandle);
            return true;
        }

        static bool SetOutputHandle(int outputHandle)
        {
            if (outputHandle == 0) return false;
            ConsoleIO::GetInstance().SetOutputHandle(outputHandle);
            return true;
        }

        static bool Write(const std::string& value)
        {
            if (value.empty()) return false;
            int outputHandle = Console::OutputHandle();
            if (outputHandle == 0) return false;
#ifdef SYSTEM_WINDOWS
            HANDLE stdOutputHandle = (HANDLE)outputHandle;
            if (stdOutputHandle == NULL) return false;
            if (stdOutputHandle == INVALID_HANDLE_VALUE) return false;
            //output buffer:
            std::wstring outputBuffer;
            //check value encoding:
            if (StringA::IsValidUTF8(value))
            {
                outputBuffer = StringA::StringToWstring(value, System::StringEncoding::UTF8);
            }
            //try ANSI codepage:
            //Note : Some emoji/characters are not included in the ANSI code page, they cannot be encoded correctly.
            //In any case it is recommended to use U8 macro.
            else
            {
                outputBuffer = StringA::StringToWstring(value, System::StringEncoding::ANSI);
            }
            //output to console:
            DWORD written;
            BOOL bWriteConsoleW = WriteConsoleW(stdOutputHandle, outputBuffer.c_str(), outputBuffer.size(), &written, NULL);
            return bWriteConsoleW;
#endif
#ifdef SYSTEM_LINUX
            //In Linux, strings are encoded as UTF8 by default, so no detection is required.
            ssize_t ret = write(outputHandle, value.c_str(), value.size());
            return ret != -1;
#endif
        }

        static bool WriteLine(const std::string& value)
        {
            return Console::Write(value + U8("\n"));
        }
    };
}

#endif