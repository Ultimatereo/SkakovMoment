//
// Created by 1 on 23.04.2022.
//

#include <cstdio>
#include <new>
static int y = 10;
int abs(int x);
int abs(int x) { return x < 0 ? -x : x; }
struct My {
  int x;
  int z;
  static int y; //Что это за зверь?
                // Это очень похоже на статическую переменную внутри функции.
                // Её видно как локальную, но она одна на всех и живёт как глобальная
                // То есть b.y == a.y. Также можно обращаться к нему снаружи как к My::y = 3;
                // Это просто идейная штука, чтобы можно было привязать статическую переменную к структурке и чтобы оно меньше торчало наружу
                // Но оно до сих пор торчит наружу :)
//  int myAbs(My &a) {
//    return abs(a.x);
//  }
//  int myAbs(My a) {
//    return abs(a.x);
//  }
//    static int myAbs(const My &a) {
//      return abs(a.x);
//    }
  ~My() { // Destructor - метод, который вызывается перед тем, как объект умрёт. Нужно, чтобы закрыть и освободить везде и всё, если что-то было выделено или открыто.
  } // Можно вызвать p->~My(), но с этим аккуратнее, использовать только если не будет автоматического освобождения памяти
  My() { //Конструктор
      My{My(2,4)}; // Но создаётся временный лишний объект, который сразу же умирает
//    x = 0;
//    z = 2;
  }
//  My (const My &a) {}; // конструктор присваивания ещё один дефолтный конструктор
  My(int x, int z = 0) { //Конструктор
    this->x = x;
    this->z = z;
  }
//  My(int a, int b = 0) : x(a), z(b); Какая-то дичь не работающая :(
    static int bruh() { //Статическая функция ведёт себя как обычная функция, но привязанная к структуре. Так же, как и с переменными
      return y;         //Функцию можно вызывать как b.bruh() или My.bruh()
    }
    int myAbs() const {
//      x = 3; // С этим оно не компилится, так как неявный this указывает на My и является не константной. Чтобы это изменить мы используем const
      return abs(/*this->*/x); // this это просто указатель на объект из которого мы вызвались yare yare
    }
    int myAbs(int x) const {
      return x + this->x;
    } // Можно сделать перегрузку функций от разных аргументов
    // Данные внутри структурки устроены так же, как и в С? Да, со всеми пробелами и так далее.
    // Функции выносятся снаружу структур и аналогичны идейно тому что расписать функцию снаружи. Отличия лишь в синтаксисе
    // Как работает статик для функций структуры? Так же, как и для обычных функций? Расписал выше отдельно про функции и отдельно про переменные
    // Почему бы не вынести функцию из структуры? Идейно это одно и то же.
    // Зачем const? Выше расписал
  My operator+ (const My &b) const { //Обязательно надо написать  const, чтобы нельзя было менять элементы структурки
    My res; // Можно не писать {} в данном случае. Посылайте IDE куда подальше
    res.x = x + b.x;
    res.z = z + b.z;
    return res;
  }
  // можно перегрузить operator[] и operator()
  int operator[] (int i) const {
    i = i % 3;
    if (i == 0) {
      return x;
    } else if (i == 1) {
      return y;
    } else if (i == 2) {
      return z;
    }
    return -1;
  }
  My& operator+= (const My &b) {
    x += b.x;
    z += b.z;
    return *this; // Сначала берём сам объект по ссылке this, а потом неявно берём ссылку на объект опять, так что останется this
  }
};
//My operator+ (My a, My b) { // Здесь нельзя ставить ссылки, так как мы поломаемся. Так как объект res умрёт по окончании функции
//  My res{};
//  res.x = a.x + b.x;
//  res.z = a.z + b.z;
//  return res;
//}
//float operator+ (float a, float b) {
//  return a - b;
//} Так нельзя делать(
// Перегрузку операторов с другими типами можно делать только снаружи
// Перегрузку присваивания можно делать только внутри
// Если перегрузить && и ||, то сокращённые вычисления не будут работать
My operator++ (My &x) { // это префиксная дичь ++a
  return My{1, 1};
}
My operator++ (My &x, int) { // это постфиксная дичь a++
  return My{2, 2};
}
int My::y = 10; //Создаём y для всех структурок
class nothrow;
class nothrow;
int main() {
  printf("%lu\n", sizeof(My));
  printf("%d\n", My::y);
  My::y = 2;
  printf("%d\n", My::y);
  My b = {2, 3};
  printf("%d\n", b.bruh());
  printf("%d\n", My::bruh());
  // В С++ можно ещё сделать перегрузку операторов
  My a = {3, 3};
  My c = a + b;
  printf("%d %d\n", c.x, c.z);
  printf("%d %d\n", c[0], c[2]);
  My d {1};
  My z;
  printf("%d %d\n", d[0], d[2]);
  printf("%d %d\n", z[0], z[2]);
  int *p = new int(2);
  delete p;
  int *q = new int[10];
  delete[] q;
  int *tt = new (std::nothrow) int;//Чтобы не кидал исключения, а вместо этого возвращал null
//  My t(); // Похоже на прототип функций, а не просто конструктор без аргументов.
  // Всё, что можно считать прототипом, есть прототип. Поэтому так нельзя писать, если хочется сделать конструктор
}
// Зачем статик переменные, если их можно просто глобально объявить?
// Можно структурку определить в .h и реализовывать метод в .cpp. В .h пишем int myabs();,
// А в .cpp пишем int myabs() { реализация }
// Потенциально можно будет получить 110 баллов за 5 домашек. За пятую домашку будут другие условия проверки и одна попытка
