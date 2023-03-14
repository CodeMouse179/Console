//      +--------------------------------------------------------------------------------+
//      |                                     Console                                    |
//      |  Modified Date : 2023/3/14                                                     |
//      |  Introduction : System.Console in C++                                          |
//      |  License : MIT                                                                 |
//      |  Platform : Windows, Linux, macOS                                              |
//      |  C++ Required Version : C++ 11                                                 |
//      |  API Family : https://github.com/CodeMouse179/System                           |
//      |  Repository : https://github.com/CodeMouse179/Console                          |
//      |                                                                                |
//      |                             Designer : CodeMouse179                            |
//      |  Email : codemouse179@gmail.com                                                |
//      |  Github : https://github.com/CodeMouse179                                      |
//      |  Bilibili : https://space.bilibili.com/3461577785215838                        |
//      +--------------------------------------------------------------------------------+

#ifndef SYSTEM_CONSOLE_HPP
#define SYSTEM_CONSOLE_HPP

#define SYSTEM_CONSOLE_VERSION_MAJOR 0
#define SYSTEM_CONSOLE_VERSION_MINOR 0
#define SYSTEM_CONSOLE_VERSION_PATCH 0
#define SYSTEM_CONSOLE_VERSION (SYSTEM_CONSOLE_VERSION_MAJOR << 16 | SYSTEM_CONSOLE_VERSION_MINOR << 8 | SYSTEM_CONSOLE_VERSION_PATCH)
#define SYSTEM_CONSOLE_VERSION_STRING "0.0.0"

//--------------------System.hpp START--------------------

//Windows Platform:
#if defined(WIN32) || defined(_WIN32)
#define SYSTEM_WINDOWS 1
#endif

//Linux Platform:
#if defined(__linux__)
#define SYSTEM_LINUX 1
#endif

//macOS Platform:
#if defined(__APPLE__) && defined(__MACH__)
#define SYSTEM_MACOS 1
#elif defined(__APPLE__)
#define SYSTEM_MACOS 2
#endif

//POSIX Platform:
#if defined(SYSTEM_LINUX) || defined(SYSTEM_MACOS)
#define SYSTEM_POSIX 1
#endif

//C++ Language:
#if defined(__cplusplus)
#define SYSTEM_CXX 1
#endif

//C++ Version Definition(Windows):
#if defined(SYSTEM_WINDOWS) && defined(_MSVC_LANG)
#if (_MSVC_LANG >= 199711L)
#define SYSTEM_CXX_98 1
#endif
#if (_MSVC_LANG >= 201103L)
#define SYSTEM_CXX_11 1
#endif
#if (_MSVC_LANG >= 201402L)
#define SYSTEM_CXX_14 1
#endif
#if (_MSVC_LANG >= 201703L)
#define SYSTEM_CXX_17 1
#endif
#if (_MSVC_LANG >= 202002L)
#define SYSTEM_CXX_20 1
#endif
#endif

//C++ Version Definition(POSIX):
#if defined(SYSTEM_POSIX) && defined(__cplusplus)
#if (__cplusplus >= 199711L)
#define SYSTEM_CXX_98 1
#endif
#if (__cplusplus >= 201103L)
#define SYSTEM_CXX_11 1
#endif
#if (__cplusplus >= 201402L)
#define SYSTEM_CXX_14 1
#endif
#if (__cplusplus >= 201703L)
#define SYSTEM_CXX_17 1
#endif
#if (__cplusplus >= 202002L)
#define SYSTEM_CXX_20 1
#endif
#endif

//--------------------System.hpp END--------------------

#include "String.hpp"       //System.String for C++
#include "Singleton.hpp"    //CodeMouse.Singleton for C++

#ifndef ESC
#define ESC "\033"   //00011011 = 033 = 27 = 0x1b
#endif

namespace System
{
    struct ConsoleKeyInfo
    {
    public:
        int KeyChar;

        ConsoleKeyInfo()
        {
            this->KeyChar = 0;
        }
    };

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
        static bool GetCursorVisible()
        {
            int outputHandle = Console::OutputHandle();
            if (outputHandle == 0) return false;
#ifdef SYSTEM_WINDOWS
            HANDLE stdOutputHandle = (HANDLE)outputHandle;
            if (stdOutputHandle == NULL) return false;
            if (stdOutputHandle == INVALID_HANDLE_VALUE) return false;
            CONSOLE_CURSOR_INFO cci;
            BOOL bGetConsoleCursorInfo = GetConsoleCursorInfo(stdOutputHandle, &cci);
            if (!bGetConsoleCursorInfo) return false;
            return cci.bVisible;
#endif
        }

        static bool SetCursorVisible(bool visible)
        {
#ifdef SYSTEM_WINDOWS
#ifdef SYSTEM_CONSOLE_FORCE_VT
            std::string s;
            if (visible)
            {
                s = StringA::Format(U8("{0}[?25h"), U8(ESC));
            }
            else
            {
                s = StringA::Format(U8("{0}[?25l"), U8(ESC));
            }
            return Console::Write(s);
#else
            int outputHandle = Console::OutputHandle();
            if (outputHandle == 0) return false;
            HANDLE stdOutputHandle = (HANDLE)outputHandle;
            if (stdOutputHandle == NULL) return false;
            if (stdOutputHandle == INVALID_HANDLE_VALUE) return false;
            CONSOLE_CURSOR_INFO cci;
            BOOL bGetConsoleCursorInfo = GetConsoleCursorInfo(stdOutputHandle, &cci);
            if (!bGetConsoleCursorInfo) return false;
            cci.bVisible = visible;
            BOOL bSetConsoleCursorInfo = SetConsoleCursorInfo(stdOutputHandle, &cci);
            return bSetConsoleCursorInfo;
#endif
#endif
#ifdef SYSTEM_LINUX
            std::string s;
            if (visible)
            {
                s = StringA::Format(U8("{0}[?25h"), U8(ESC));
            }
            else
            {
                s = StringA::Format(U8("{0}[?25l"), U8(ESC));
            }
            return Console::Write(s);
#endif
        }

        static int InputHandle()
        {
            return ConsoleIO::GetInstance().GetInputHandle();
        }

        static int OutputHandle()
        {
            return ConsoleIO::GetInstance().GetOutputHandle();
        }

        static std::string GetTitle()
        {
            std::string title;
#ifdef SYSTEM_WINDOWS
            wchar_t titleBuffer[MAX_PATH];
            DWORD ret = GetConsoleTitleW(titleBuffer, MAX_PATH);
            if (ret > 0)
            {
                title = StringA::WstringToString(titleBuffer, System::StringEncoding::UTF8);
            }
#endif
            return title;
        }

        static bool SetTitle(const std::string& title)
        {
#ifdef SYSTEM_WINDOWS
            std::wstring titleW;
#ifdef SYSTEM_CONSOLE_ONLY_UTF8
            titleW = StringA::StringToWstring(title, System::StringEncoding::UTF8);
#else
            if (StringA::IsValidUTF8(title))
            {
                titleW = StringA::StringToWstring(title, System::StringEncoding::UTF8);
            }
            else
            {
                titleW = StringA::StringToWstring(title, System::StringEncoding::ANSI);
            }
#endif
            BOOL ret = SetConsoleTitleW(titleW.c_str());
            return ret;
#endif
#ifdef SYSTEM_LINUX
            return false;
#endif
        }

    public: //Methods:
        static bool SetCursorPosition(int left, int top)
        {
            if (left < 0) return false;
            if (top < 0) return false;
            int outputHandle = Console::OutputHandle();
            if (outputHandle == 0) return false;
#ifdef SYSTEM_WINDOWS
#ifdef SYSTEM_CONSOLE_FORCE_VT
            std::string s = StringA::Format("{0}[{1};{2}H", U8(ESC), top + 1, left + 1);
            return Console::Write(s);
#else
            HANDLE stdOutputHandle = (HANDLE)outputHandle;
            if (stdOutputHandle == NULL) return false;
            if (stdOutputHandle == INVALID_HANDLE_VALUE) return false;
            COORD position;
            position.X = left;
            position.Y = top;
            BOOL bSetConsoleCursorPosition = SetConsoleCursorPosition(stdOutputHandle, position);
            return bSetConsoleCursorPosition;
#endif
#endif
#ifdef SYSTEM_LINUX
            std::string s = StringA::Format("{0}[{1};{2}H", U8(ESC), top + 1, left + 1);
            return Console::Write(s);
#endif
        }

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
#ifdef SYSTEM_CONSOLE_ONLY_UTF8
            outputBuffer = StringA::StringToWstring(value, System::StringEncoding::UTF8);
#else
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
#endif
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