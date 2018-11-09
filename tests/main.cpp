/* Данный файл -- часть библиотеки grabin
Распространяется по лицензии GNU Public License версии 3 или выше.
Никакие гарантии не предоставляются, в том числе гарантия пригодности для любой конкретной цели.
Автор: (c) 2018 Галушин Павел Викторович, galushin@gmail.com
*/

#include <grabin/defs.hpp>

#include <grabin/utility/debug.hpp>

// @todo Перенести в подходящий заголовочный файл
namespace grabin
{
inline namespace v0
{
namespace test
{
    template <class OStream, class Testable>
    void run(OStream & os, Testable testable)
    {
        try
        {
            testable();
            os << "[PASSED]\n";
        }
        catch(std::exception & ex)
        {
            os << "[FAILED]: throws exception [" << ex.what() << "]"
               << " of type [" << grabin::debug::demangle(typeid(ex).name()) << "]\n";
        }
        catch(...)
        {
            os << "[FAILED]: throws exception of unknown type\n";
        }
    }
}
// namespace debug
}
// namespace v0
}
// namespace grabin

#include <iostream>

namespace grabin
{
inline namespace v0
{
namespace test
{
    template <class T1, class T2>
    void terminate_if_not_equal(char const * file, std::size_t line,
                                T1 const & expected, char const * expected_str,
                                T2 const & actual, char const * actual_str)
    {
        if(expected != actual)
        {
            std::cerr << "Critical failure in " << file << ":" << line << "\n"
                      << "Equality failed : " << expected_str << " == " << actual_str << "\n"
                      << "Expanded to     : [" << expected << "] != [" << actual << "]"
                      << std::endl;
            std::terminate();
        }
    }
}
// namespace test
}
// namespace v0
}
// namespace grabin

/* Если Actual != Expected, то в std::cerr выводится диагностическое сообщение и вызывается функция
std::terminate. В противном случае ничего не делает.

Это базовый "диагностический" макрос, его корректность для случая Actual != Expected не покрывается
тесами, поведение должно проверяться вручную.
*/
#define GRABIN_TERMINATE_IF_NOT_EQUAL(Actual, Expected)\
    do { ::grabin::test::terminate_if_not_equal(__FILE__, __LINE__,\
                                                (Expected), GRABIN_STRINGIFY(Expected),\
                                                (Actual), GRABIN_STRINGIFY(Actual));\
    } while(false)

int main_impl()
{
    // ОШИБКА компиляции - нет точки с запятой в конце:
    // GRABIN_TERMINATE_IF_NOT_EQUAL(0, 0)
    GRABIN_TERMINATE_IF_NOT_EQUAL(0, 0);

    for(auto i = 1; i < argc; ++ i)
    {
        {
            auto const option = std::string("--test_terminate_if_not_equal");

            if(option.compare(argv[i]) == 0)
            {
                GRABIN_TERMINATE_IF_NOT_EQUAL(0, 1);
            }
        }
    }

    grabin::test::run(std::cout, [](){});
    grabin::test::run(std::cout, [](){ struct Local{}; throw Local{}; });
    grabin::test::run(std::cout, [](){ throw std::runtime_error("Intentional error");});

    // @todo Автоматизировать проверку

    return 0;
}

#include <cstdlib>

/* Эта функция запускает "настоящую" основную функцию (main_impl) и перехватывает все возникающие
в ней исключения.

Корректность этой функции проверяется обзором, а не тестируется.
*/
int main()
{
    try
    {
        return main_impl();
    }
    catch(std::exception & ex)
    {
        std::cerr << "Uncaught exception: [" << ex.what() << "]"
                  << " of type [" << grabin::debug::demangle(typeid(ex).name()) << "]\n";
        return EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "Uncaught exception of unknown type\n";
        return EXIT_FAILURE;
    }
}
