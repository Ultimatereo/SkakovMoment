#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
void f(int n) {
  // Если вдруг мы знаем, что чаще всего размер массива меньше 101, но иногда может быть и больше, то оптимально сделать вот так
  int arr_static[100];
  int *arr;
  if (n <= sizeof(arr_static)/sizeof(*arr_static)) {
    arr = arr_static;
  } else {
    arr = malloc(sizeof(int) * n);
  }
  // Работа с массивом
  if (arr != arr_static) {
    free(arr);
  }
}
int main(void) {
  f(5);
  int *a, *b;
  int c, d[10];
  c = 1;
  a = &c;
  b = &d[3];
  *b = 2; // d[3] = 2
  *(b + 1) = 5;
  int *dd = (b + 3);
  //d[4] = 5. По факту, мы смещаем на следующий элемент. Имеет смысл двигать так,
  // когда у нас непрерывный кусок памяти идёт, то есть, например, в массивах или структурках.
  *(b - *a) = 3; //d[3 - c] = 3. В нашем случае d[2] = 3
  printf("%i %i %i\n", d[2], d[3], d[4]);

  b = &d[3];
  a = &d[9] + 1;
  for (; b < a; b++) {
    *b = 10;
  }
  for (int i = 0; i < 100; i++) {
    printf("%i ", d[i]);
    // Можно поэлементно обращаться с помощью указателей. Мем, что после 10 элемента идёт мусор
  }

  void *v;
  // Указатель на "я не знаю, что такое". Например, malloc возвращает void *v, так как он просто выделяет память
  // Арифметика не работает по понятным причинам, так как мы не знаем размера элемента. Но можем сравнивать на равенство.
  // void *v может указать и на float *v, int *v
  // В С работает и наоборот, но это не работает в плюсах, так как из-за религиозных причин это запретило. В плюсах надо кастить ручками
  // Никогда не получается создать указатель на 0 адресную ячейку <=> можно сделать из этого nullptr, чтобы показать, что нет адреса
  // Нет неявного приведения между базовыми типами и типами указателей
  // nullptr в плюсах нужны для перегрузки каким-то чудом
  int *g = NULL;
  // Отличия массива от указателей. Массив сразу инициализирует данные, а указатель нет.
  // Также массив намертво связан со своим диапазаном памяти
  // Когда массивом больше не пользуются, память освобождается самим компилятором, а при указателях это надо ручками сделать
  // Указатель от указателя выведет честно указатель от указателя. А вот указатель от массива ничем не отличается от указателя массива
  // sizeof от указателя даст размер указателя, а sizeof от массива размер массива

  // break; continue; goto;
  // Когда мы хотим выйти из всех вложенных циклов, то goto идеальный кандидат на место нескольких break'ов на каждом уровне
  // До этого goto переходил по строкам, причём каждая строчка отделялась одна от другой на 10 строчек, чтобы можно было понаставить goto
  // Но сейчас есть метки и мы радуемся жизни
label : a = &c;
  if (a == b)
    goto label;
  // goto это неплохой способ сделать код более приятным для чтения. Для ошибок ещё прикольно использовать.
  // Ну, как работает for через while понятно...

  // Препроцессор. Работа какого-то языка перед С.
  // Сначала программа обрабаывается препроцессором, а потом обрабатывается всё компилятор
  // Всё, что начинается с #, относится к препроцессингу
//#include <fileapi.h>
  // include просто вставляет весь код из вставляемого кода, как правило все прототипы, описание структур и так далее
//#define false true // тупая текстовая замена true на false
//#define abc(a, b) a + b // Продвинутая штука. Теперь abc(a, b) заменяется на a + b, но никак функция, а как текстовая замена
#define max(a, b) ((a) > (b) ? (a) : (b)) // Прикольно но нужно аккуратно пользоваться
  // Пример бед с макросами:
  int aa = 2;
  int bb = 4;
  int cc = max(aa--, bb++);
  printf("\n%i %i %i", aa, bb, cc);
  // Поэтому пишут макросы с большой буквы, чтобы отличать от функций
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Если условие выполняется, то что внутри выполняется, иначе нет. Причём проверка происходит во время компиляции, а не работы кода
  // Банально для компиляторозависимых костылей
#if aa == 1
  printf("\nBruh");
#endif
#if aa == 0
  printf("\nMegaBruh");
#endif
  // Когда инклудим как решать проблему того, что несколько один и тот же каталог инклудится. Есть два варика решить проблему
  // #indef FILE_H
  // #define FILE_H
  // ...
  // #endif
  // Или
  // #pragma once
  // Что не надо делать?
  // Впихивать union, так как мы этого знаем
  // Писать exit() процесс умирает сразу, поэтому exit это зло
}