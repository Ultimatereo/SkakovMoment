int g();
//int c = g(3); // Не работает по причине иди нахуй (так как в С всё по-пацански и ты его не сломаешь)
int c = 3;
int f(int a) {
  int b = a + 2;
  return b;
}
int g(int a) {
  //  static int bb = c + 2; Не работает по причине иди нахуй (Тут можно вставлять только значения, известные во время компиляции)
  //  static int bb = a + 2; Не работает по причине иди нахуй
  static int bb = 3;
  return bb;
}
static int ff(int fff) {
  return fff;
}
int main(void) {
  // Есть соглашение называть глобальные переменные через G_..., чтобы можно было визуально их выделять
  // Пустые скобочки на С это аргументы не указаны, а не аргументы отсутствуют. То есть в прототипе можно не указывать аргументы, а при компиляции он заполнится
  // В плюсах пустые скобочки эквивалентны пустым скобочкам
  // По историческим событиям в С изначально не было прототипов, поэтому была такая реализация пустых скобок

  // Про static
  // Они живут как глобальные переменные, но видимость к ним только через функции
  // И статик переменные не дерутся как глобальные переменные за имена

  int x = f(3);
  int y = f(4);
  x = g(3);
  y = g(4);
  // Ещё рассказали про extern. Это короче объявление статической переменной для функции
}