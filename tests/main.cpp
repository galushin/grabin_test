/* Данный файл -- часть библиотеки grabin
Распространяется по лицензии GNU Public License версии 3 или выше.
Никакие гарантии не предоставляются, в том числе гарантия пригодности для любой конкретной цели.
Автор: (c) 2018 Галушин Павел Викторович, galushin@gmail.com
*/

#include <grabin/defs.hpp>

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
    { ::grabin::test::terminate_if_not_equal(__FILE__, __LINE__,\
                                             (Expected), GRABIN_STRINGIFY(Expected),\
                                             (Actual), GRABIN_STRINGIFY(Actual)); }

int main()
{
    GRABIN_TERMINATE_IF_NOT_EQUAL(0, 0);
    // Will FAIL: GRABIN_TERMINATE_IF_NOT_EQUAL(0, 1);

    return 0;
}
