#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Для замеров времени
#include <time.h>

struct Pair
{
    char *key;
    char *value;
};
class RadixSort
{
public:
    int digit(const Pair &pair, int i)
    {
        char ch = pair.key[i];
        bool isNum = (ch & 0xF0) == 0x30;
        return isNum? ch - '0' : ch - ('a' - 10);
    }

    int *_radixsort(Pair *data, int sz)
    {
        
        int M = 16;

        int *b = (int *)calloc(sz, sizeof(int));
        for (int j = 0; j < sz; j++)
        {
            b[j] = j;
        }

        int *b2 = (int *)calloc(sz, sizeof(int));
        int *c = (int *)calloc(M, sizeof(int));
        int *digitsResults = (int *)malloc(sz * sizeof(int));

        for (int i = 31; i >= 0; i--)
        {
            for (int j = 0; j < M; j++)
            {
                c[j] = 0;
            }

            for (int j = 0; j < sz; j++)
            {

                c[digitsResults[j] = digit(data[j], i)]++;
            }

            for (int j = 1; j < M; j++)
            {

                c[j] += c[j - 1];
            }

            for (int j = sz - 1; j >= 0; j--)
            {
                b2[--c[digitsResults[b[j]]]] = b[j];
            }

            for (int j = 0; j < sz; j++)
            {
                b[j] = b2[j];
            }
        }
        free(c);
        free(digitsResults);
        return b;
    }

    int *radixsort(Pair *data, int n)
    {

        return _radixsort(data, n);
    }
};

int main()
{
/*#pragma region Запуск таймера
    clock_t start, end;
    double cpu_time_used;
    start = clock();
#pragma endregion*/

    FILE *file = fopen("input.txt", "r");

    struct Pair *input = (struct Pair *)malloc(1 * sizeof(struct Pair));
    int size_input = 1;

    int n = 0;
    char *value;
    char *key;
    value = (char *)malloc(sizeof(char) * (2048 + 1));
    key = (char *)malloc(sizeof(char) * (32 + 1));
    while (fscanf(file, "%s\t%s", key, value) != EOF)
    {
        input[n].key = (char *)malloc(sizeof(char) * ((int)strlen(key) + 1));
        input[n].value = (char *)malloc(sizeof(char) * ((int)strlen(value) + 1));
        strcpy(input[n].value, value);
        strcpy(input[n].key, key);
        ++n;
        if (n >= size_input)
        {
            size_input *= 2;
            input = (struct Pair *)realloc(input, (size_input) * sizeof(struct Pair));
        }
    }
    free(value);
    free(key);

    RadixSort rs = RadixSort();
    int *cells = rs.radixsort(input, n);
    for (int j = 0; j < n; j++)
    {
        // std::cout<< input[cells[j]].key << "\t" << input[cells[j]].value << std::endl;
        printf("%s\t%s\n", input[cells[j]].key, input[cells[j]].value);
    }
    free(cells);
    free(input);

/*#pragma region Остановка таймера
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Время выполнения: %f секунд\n", cpu_time_used);
#pragma endregion*/

    return 0;
}