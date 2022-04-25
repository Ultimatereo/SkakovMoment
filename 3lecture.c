#include <stdio.h>
int main() {
// 3 lecture 26.02.2022
// Числа с плавающей точкой: bits-exp-mant range
// float = single precision (IEEE-754) 32-8-23 10^(+-38)
// double = double precision (IEEE-754) 64-11-52 10^(+-308)
// long double непонятный зверёк, не договорились люди о нём. Где-то long double = double (в Visual Studio, в компиляторе Microsoft)
// Ещё long double может быть quad precision (IEEE-754) 128-15-112. Реализовано программно => медленная скорость по сравнению с float и double
// Ещё long double может быть extended precision 80-15-64 (аппаратно реализовано на x86), что медленнее float или double, но быстрее long double
// long double лучше использовать, если точно в курсе, как у тебя реализован long double Про совместимость с другими компиляторами можно забыть

// double как минимум вдвое меньше float, потенциально гораздо медленнее

// 10 -> int
// 10u -> unsigned int
// 10llu -> long long unsigned int
// 0.1 -> double
// 0.1f -> float
// Для scanf и printf %f -> float; %lf -> double, но изначально printf он берёт double, а потом в случае чего перевести в float

//        scanf("%i %i", &a, &b);
//        printf("%i\n", a + b);
    int a, b;
    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w"); // "wb" - чтобы открыть в бинарном виде
    // Как проверить, что файл открылся? Да просто сравнить с null

    fscanf(in, "%i %i", &a, &b);
    fprintf(out, "%i\n", a * b + a);

    fclose(in);
    fclose(out);

    // На лекции ещё рассказывали про базовые вещи по типу циклов и других приколюх + про тестирование программ. Было скучно, поэтому ну нахуй.
    // Вместо этого зато настроил Clang.
}