//     +--------------------------------------------------------------------------------+
//     |                                 Singleton v1.1.0                               |
//     |  Introduction : Generic Singleton for C++                                      |
//     |  Modified Date : 2022/11/26                                                    |
//     |  License : MIT                                                                 |
//     |  Source Code : https://github.com/CodeMouse179/Singleton                       |
//     |  Readme : https://github.com/CodeMouse179/Singleton/blob/main/README.md        |
//     |                                                                                |
//     |                             Designer : CodeMouse179                            |
//     |  Email : codemouse179@gmail.com                                                |
//     |  Github : https://github.com/CodeMouse179                                      |
//     |  Bilibili : https://space.bilibili.com/3461577785215838                        |
//     +--------------------------------------------------------------------------------+

#ifndef CODEMOUSE_SINGLETON_HPP
#define CODEMOUSE_SINGLETON_HPP

//Versioning refer to Semantic Versioning 2.0.0 : https://semver.org/

#define CODEMOUSE_SINGLETON_VERSION_MAJOR 1
#define CODEMOUSE_SINGLETON_VERSION_MINOR 1
#define CODEMOUSE_SINGLETON_VERSION_PATCH 0
#define CODEMOUSE_SINGLETON_VERSION (CODEMOUSE_SINGLETON_VERSION_MAJOR << 16 | CODEMOUSE_SINGLETON_VERSION_MINOR << 8 | CODEMOUSE_SINGLETON_VERSION_PATCH)
#define CODEMOUSE_SINGLETON_VERSION_STRING "1.1.0"

#include <memory>   //std::shared_ptr<T>, std::make_shared<T>
#include <utility>  //std::forward<T>

#define SINGLETON_CLASS(class_name) class class_name : public CodeMouse::Singleton<class_name>

namespace CodeMouse
{
    //Generic Singleton <static class>
    template<typename T>
    class Singleton
    {
    protected: //Allow subclasses to access the constructor.
        Singleton()
        {
        }

    public:
        static T& GetInstance()
        {
            static T instance;
            return instance;
        }

        template<typename...Args>
        static T& GetInstance(Args&&...args)
        {
            static std::shared_ptr<T> instance = std::make_shared<T>(std::forward<Args>(args)...);
            return *(instance.get());
        }
    };
}

#endif