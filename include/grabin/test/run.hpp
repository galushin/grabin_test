/* Данный файл -- часть библиотеки grabin
Распространяется по лицензии GNU Public License версии 3 или выше.
Никакие гарантии не предоставляются, в том числе гарантия пригодности для любой конкретной цели.
Автор: (c) 2018 Галушин Павел Викторович, galushin@gmail.com
*/

#ifndef Z_GRABIN_TEST_RUN_HPP_INCLUDED
#define Z_GRABIN_TEST_RUN_HPP_INCLUDED

/** @file grabin/test/run.hpp
 @brief Простой шаблон функции выполнения тестов. Тест должен представлять собой функцию, не
 требующую аргументов и возвращающую @b void или @b bool. О неудаче теста функция должна сообщать,
 возвращая @b false или порождая исключение.
*/

#include <grabin/utility/debug.hpp>

// @todo Перенести в подходящий заголовочный файл
namespace grabin
{
inline namespace v0
{
namespace test
{
    namespace detail
    {
        template <class R>
        struct run_policy;

        template <>
        struct run_policy<void>
        {
            template <class Ostream, class Testable>
            static void run(Ostream & os, Testable && testable)
            {
                std::forward<Testable>(testable)();
                os << "[PASSED]\n";
            }
        };

        template <>
        struct run_policy<bool>
        {
            template <class Ostream, class Testable>
            static void run(Ostream & os, Testable && testable)
            {
                auto const result = std::forward<Testable>(testable)();
                if(result)
                {
                    os << "[PASSED]\n";
                }
                else
                {
                    os << "[FAILED]: returns [FALSE]\n";
                }
            }
        };
    }
    // namespace detail
    template <class OStream, class Testable>
    void run(OStream & os, Testable && testable)
    {
        try
        {
            using Result = decltype(std::forward<Testable>(testable)());
            detail::run_policy<Result>::run(os, std::forward<Testable>(testable));
        }
        catch(std::exception & ex)
        {
            os << "[FAILED]: throws exception of type ["
               << grabin::debug::demangle(typeid(ex).name()) << "]"
               << " with message [" << ex.what() << "]\n";
        }
        catch(...)
        {
            os << "[FAILED]: throws exception of unknown type\n";
        }
    }
}
// namespace test
}
// namespace v0
}
// namespace grabin

#endif
// Z_GRABIN_TEST_RUN_HPP_INCLUDED
