/* Данный файл -- часть библиотеки grabin
Распространяется по лицензии GNU Public License версии 3 или выше.
Никакие гарантии не предоставляются, в том числе гарантия пригодности для любой конкретной цели.
Автор: (c) 2018 Галушин Павел Викторович, galushin@gmail.com
*/

#ifndef Z_GRABIN_DEFS_HPP_INCLUDED
#define Z_GRABIN_DEFS_HPP_INCLUDED

/** @file grabin/defs.hpp
 @brief Оснонвые определения
*/

// Макросы преобразования в строковый литерал
// Подробности: gcc.gnu.org/onlinedocs/gcc-3.4.3/cpp/Stringification.html
#define GRABIN_DETAIL_STRINGIFY2(X) #X
#define GRABIN_STRINGIFY(X) GRABIN_DETAIL_STRINGIFY2(X)

#endif
// Z_GRABIN_DEFS_HPP_INCLUDED
