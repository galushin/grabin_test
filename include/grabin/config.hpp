/* Данный файл -- часть библиотеки grabin
Распространяется по лицензии GNU Public License версии 3 или выше.
Никакие гарантии не предоставляются, в том числе гарантия пригодности для любой конкретной цели.
Автор: (c) 2018 Галушин Павел Викторович, galushin@gmail.com
*/

/** @file grabin/config.hpp
 @breif Общая конфигурация библиотеки

 Этот файл должны включать все остальные заголовочные файлы библиотеки grabin причём до включения
 любого другого заголовочного файла этой библиотеки.
*/

#ifndef Z_GRABIN_CONFIG_HPP_INCLUDED
#define Z_GRABIN_CONFIG_HPP_INCLUDED

// Определение компилятора
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
    #define GRABIN_COMPILER_GCC_OR_MINGW
#endif


#endif
// Z_GRABIN_CONFIG_HPP_INCLUDED
