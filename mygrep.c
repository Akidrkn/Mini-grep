#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    char *word = NULL;
    char *filename = NULL;
    char *line = NULL;
    size_t word_capacity = 0;
    size_t filename_capacity = 0;
    size_t line_capacity = 0;
    ssize_t chars_read;
    int line_number = 0;
    int found_lines[100] = {0};
    int found_count = 0;
    bool found = false;

    printf("My grep\n");

    printf("Введите слово для поиска: ");
    if (getline(&word, &word_capacity, stdin) == -1) {
        printf("Ошибка: не удалось прочитать слово.\n");
        free(word);
        return 1;
    }
    word[strcspn(word, "\r\n")] = '\0';

    printf("Введите имя файла: ");
    if (getline(&filename, &filename_capacity, stdin) == -1) {
        printf("Ошибка: не удалось прочитать имя файла.\n");
        free(word);
        free(filename);
        return 1;
    }
    filename[strcspn(filename, "\r\n")] = '\0';

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка: файл не существует или недоступен.\n");
        free(word);
        free(filename);
        return 1;
    }

    while ((chars_read = getline(&line, &line_capacity, file)) != -1) {
        line_number++;

        if (strstr(line, word) != NULL) {
            printf("Слово найдено на строке %d: %s", line_number, line);
            found = true;
            if (found_count < 100) {
                found_lines[found_count++] = line_number;
            }
        }
    }

    printf("Поиск завершен.\n");
    printf("Проверено %d строк.\n", line_number);

    if (line_number == 0) {
        printf("Файл пуст.\n");
    } else if (found) {
        printf("Слово найдено на строках: ");
        for (int i = 0; i < found_count; i++) {
            printf("%d ", found_lines[i]);
        }
        printf("\n");
    } else {
        printf("Слово не найдено.\n");
    }

    free(word);
    free(filename);
    free(line);
    fclose(file);

    return 0;
}