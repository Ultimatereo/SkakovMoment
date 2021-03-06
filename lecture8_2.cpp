//
// Created by 1 on 16.04.2022.
//

//int myabs(int x) {
//  return x < 0 ? -x : x;
//}
//float myabs(float x) {
//  return x < 0 ? -x : x;
//}
// Копипаста. Больно? Больно. Будет больнее? Да. Добавили шаблоны templates
//template<class T> //Аналогичная запись нижней, но это криндж по религиозным причинам
template<typename T> // Шаблоны это именно про типы либо целочисленные константы
T myabs(T x) {
  return x < 0 ? -x : x;
}

template<class T>
T mymax(T x, T y) {
  return x > y ? x : y;
}
// Но вот mymax(-2, 4.0) не будет компилиться, так как разные типы у аргументов
template<typename T, typename G>
T mymax(T x, G y) {
  return x > y ? x : y;
} // Не очень хорошее решение, так как возвращаем T
// Кстати, в таком случае будут беды с mymax(2, 69), так как есть два подходящих под это шаблона
// Иначе можно сделать mymax<float>(-2, 4.0) и по-честному всё будет преобразовано во float
// Чтобы сделать статическую функцию (чтобы не ссорилась с одноимёнными функциями), но так чтобы видно было на несколько файлов нужно сделать namespace:
namespace my {
   int abs(int x) {
     return 42;
   }
}
// my::abs
// std::abs. Чтобы не пересекалось со стандартной функцией следует подключать не math, а cmath
// В namespace std вкладывается include <math.h>
// Ещё есть using namespace std;, чтобы не писать std::abs всегда
// Если написал несколько using namespace, у которых есть общая функция, то очень жаль, вы проиграли
namespace {
  int f() {
    return 0;
  }
} // Анонимный namespace виден только внутри файла
// А обычный namespace виден как глобальная переменная на уровне пакета (?)

int g();
int c = g();
int f(int a) {
  static int b = a + 2; // Инициализация происходит один раз в момент первого входа в функцию,
                        // беды начинаются, когда появляются несколько тредов и они все пытаются инициализировать первыми
                        // как это решать? Какими-то страшными и нетривиальными приколюхами, о которых нам расскажут
                        // на параллельном программировании на курсе этак 3-4
                        // Тут возникает критическая секция по стандарту.
                        // Ещё автоматически есть if, который проверяет, инициализирована перменная

  return b;
}

void ff(int &a) {
  a += 3;
}
void rvaluef(int &&a) {
  a += 3;
}
void whatTheFuckF(const int &a) { //передаём ссылку на значение, но само значение нельзя менять
  return;
  //a += 3; Но менять значение нельзя
}

// Пара слов про передачу значения и указателя в функцию. Всё так же как в плюсах, но есть ещё третий способ (синтаксический сахар для варианта с указателем)
int main() {
  int x = f(3);
  int y = f(4);
  f(x);
  rvaluef(x + 1);
  int &xx = x; // Ссылка на x, через xx можно получить значение x. Ссылка обязательно указывает на значение, поэтому ссылка на ссылку = ссылка
  // Это value ссылка
  // А теперь другой зверёк rvalue ссылка &&a, она связывается со значениями, а не с объектами
  auto pp = 2; // auto - данные идут в стек. Это старое значение
  // есть static - данные идут в секцию данных, register - данные идут в секцию регистров, но ничего не работает в современных компиляторов. Для auto такая же история
  // Поэтому решили использовать auto для новой фичи. Теперь auto заменяется на тип, который стоит после =
}
auto fff(int x) {
  return x + 0.69;
} // Хуйня, а не решение. Так как сложно читать подобное
// auto работает во время компиляции. Поэтому нельзя писать auto от чего-то неизвестного (например, введённого через консоль)
//