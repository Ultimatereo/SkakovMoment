#include <stdio.h>
int main() {
    printf("%s\n", "4 lecture");
    // Вычисления с double и float происходят приближённо. А почему? Это уже на курс ЭВМ)))
    // Так, например, вместо if (a == b) пишут if (fabs(a - b) < eps)
    // Про лабу. Эпсилон в каждой строчке разные. Может быть такое, что в одной строке значения большие, в другой нет
    // Про точность. Лаба на понимание структуры С и решить проблемы с точностью. Погрешность накапливается. Как это решить?
    // Чтобы получить полный балл, надо подумать про эпсилон и беды с точностью.
    // Надо ещё написать обработку нехватки аргументов. И ещё расписать бы, как работает программа в самом начале в консольку
    // Максимальный размер взодных данных такая, чтобы хватило памяти
    // Ещё нужно напихать проверку на то, что получилось выделить память или нет
    // Ещё не забудь отформатировать файл
    // Массив это кучка однородных данных. Структура это кучка неоднородных данных.

    struct A1 {
        int x;
        double y;
        char z[4];
    } b1;
    struct A1 a1; //В плюсах работает и без struct, но в С надо(((

    //Идейная модификация
    typedef struct {
        int x;
        double y;
        char z[4];
    } A2;
    A2 a2;
    // В С нет модификаторов доступа как таковых. В С++ они есть.
    // Конструкторов в C нет, только в плюсах((( Грустно
    // Обращение к объектам
    a2.x = 5;
    a2.y = 5.5f;
    // Массивы не любят копироваться. Как правило, в функциях и методах передаётся указатель на массив, а не копия массива
    // Но если массив в структурке и передавать структурку, то массив будет по-честному копироваться
    // При создании структурки можно проинициализировать поля структурок.
    // Если при инициализации что-то не присвоилось, то тогда оставшиеся поля заполняются нулями
    // Если мы не инициализируем структурку, то ей даются ячейки памяти, но там мусор.
    A2 aa, bb = {1, 0, {0, 1, 2}};
    // В новом С есть вот такая фича ещё
    A2 aaa, bbb = {.y = 2, .x = 1};

    // Выравнивание на родную границу? Данные располагаются так, чтобы начало данных было кратно размеру данных (например, для интов это 4 байта)
    // То есть в нашем примере с int, double и char[4]. Сначала будет выделено 4 байта под int, потом для double надо чтобы начало было кратно 8, поэтому
    // у нас 4 байта дырок, затем double и под конец char[4] без дырок. Лучше всего располагать всё в порядке убывания размеров данных, чтобы было меньше дырок
    // А что с вложенными структурками? Например есть внутренняя структурка с int и char ...
    // Там мем в том, что мы поля внутренней структурки объединяем с полями внешней структурки. И выходит тот же мем с дырками, с полями внутренней и внешней структурок

    // А что с массивами структур? А что с ними не так? Просто записываем структурку одна за другой, мы ведь знаем, что размер каждой структурки одинаковой. И никаких дырок

    // Теперь немного магии
    // Мы можем с файла сразу читать в структурку. Но дырки мешают((( Поэтому чтобы мы могли сразу прочитать из файла в структуру, нужно как-то отменить дырочки
    // Тогда воспользуемся конструкцией снизу. Что эта конструкция делает?
    // Она просто убивает дырки в структуре, но потенциально медленнее обращение. И эта конструкция компиляторозависимая.
//#pragma pack(push, l) Это заклинание под VisualStudio

    typedef struct __attribute__((packed)) /* А это под clang */ {
        int x;
        double y;
        char z[4];
    } A3;

//#pragma pack(pop)
    // Размер возвращаемого объекта
    printf("%lu\n", sizeof(A3));
    printf("%lu\n", sizeof(A2));
    printf("%lu\n", sizeof(int));
    printf("%lu\n", sizeof(5 + 5.0)); //Даже вот так работает. Он возвращает размер возвращаемого типа
    // Ещё есть typeof, чтобы возвращать тип. Но она компиляторо зависима. А вот sizeof есть в стандарте.

    // Теперь перейдём к union
    typedef union {
        int x;
        double y;
        char z[4];
    } B1;
    typedef union {
        B1 b11;
        int x;
        double y;
        char z[4];
    } B2; // Похоже на что-то бессмысленное, потому что оно и является бессмысленным
    // Логичный вопрос. В чём разница со struct? Мемы с дырками и расположением полей такие же, как у struct, например, но...
    // union - все данные начинаются с 0 и сам union имеет размер наибольшего поля. То есть запись какого-то поля перезаписывает другие
    // Нужно для всякой магии по изменению некоторых байтиков
    printf("%lu\n", sizeof(B2));
    printf("%lu\n", sizeof(B1));

//    typedef int fydy$;
    // Указатели в С типизированны. Указатель на int хранить указатель на int, для float, double всё то же самое
    int x;  //Сам объект
    int ** *** ** *******p;//Указатель на указатель на указатель на указатель на указатель...
    //printf("%d\n", p);
    int *p1, a11; // p1 - указатель, а a11 - это объект
    // & в С не работает. А в С++ это ссылка, которой нет в С
    int y = *p; // y это значение, которое хранится там куда указывает указатель на указатель на указатель на указатель на указатель...
    *p = 2; // x = 2, если бы p = &x

}