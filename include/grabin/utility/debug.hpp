/* Данный файл -- часть библиотеки grabin
Распространяется по лицензии GNU Public License версии 3 или выше.
Никакие гарантии не предоставляются, в том числе гарантия пригодности для любой конкретной цели.
Автор: (c) 2018 Галушин Павел Викторович, galushin@gmail.com
*/

#ifndef Z_GRABIN_UTILITY_DEBUG_HPP_INCLUDED
#define Z_GRABIN_UTILITY_DEBUG_HPP_INCLUDED

/** @file grabin/utility/debug.hpp
 @brief Возможности отладки и вывода диагностических сообщений
*/

#include <grabin/config.hpp>

#ifdef GRABIN_COMPILER_GCC_OR_MINGW
    #include <cxxabi.h>
    #include <cstdlib>
#endif
// GRABIN_COMPILER_GCC_OR_MINGW

#include <memory>
#include <string>

namespace grabin
{
inline namespace v0
{
namespace debug
{
#ifdef GRABIN_COMPILER_GCC_OR_MINGW
    std::string demangle(char const * str)
    {
        using Holder = std::unique_ptr<char, void(*)(void*)>;

        int status = 0;
        Holder holder(abi::__cxa_demangle(str, 0, 0, &status), &std::free);

        if(status == 0)
        {
            return {holder.get()};
        }
        else
        {
            return {str};
        }
    }
#else
    std::string demangle(char const * str)
    {
        return {str};
    }
#endif
// GRABIN_COMPILER_GCC_OR_MINGW
}
// namespace debug
}
// namespace v0
}
// namespace grabin

#endif
// Z_GRABIN_UTILITY_DEBUG_HPP_INCLUDED
