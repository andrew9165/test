#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *constr16to2(char *str) ;
const char *con16to2(char str);
void checknull(void *ptr);

int main()
{
    char **ca25strs16 = NULL;
    char **ca25strs2 = NULL;
    int count = 0;
    char input[17];

    while (fgets(input, 17, stdin) != NULL)
    {

        input[strcspn(input, "\n")] = '\0';

        ca25strs16 = realloc(ca25strs16, (count + 1) * sizeof(char *));
        checknull(ca25strs16);

        ca25strs16[count] = malloc(17 * sizeof(char));
        checknull(ca25strs16[count]);

        // 复制输入的字符串到新分配的内存中
        strncpy(ca25strs16[count], input, 16);
        ca25strs16[count][17 - 1] = '\0'; // 以'\0'结尾

        count++;
    }
    ca25strs2 = malloc(count * sizeof(char *));
    checknull(ca25strs2);

    // 打印ca25strs16
    for (int i = 0; i < count; i++)
    {
        ca25strs2[i] = constr16to2(ca25strs16[i]);
        printf("%s\t%s\n", ca25strs16[i], ca25strs2[i]);
    }
    // 释放内存
    for (int i = 0; i < count; i++)
    {
        free(ca25strs16[i]);
    }
    free(ca25strs16);

    return 0;
}

char *constr16to2(char *str) {
    // 64 个二进制字符 + 1 个结束符 '\0'
    char *result = malloc(65 * sizeof(char));
    checknull(result);

    // 转换每个十六进制字符
    for (int i = 0; i < 16; i++) {
        const char *c = con16to2(str[i]);
        for (int j = 0; j < 4; j++) {
            result[i * 4 + j] = c[j];
            // printf("%c", result[i * 4 + j]);
        }
        // printf("\n");
    }
    result[64] = '\0';  // 字符串结束符

    return result;
}

const char *con16to2(char str) {
    switch (str) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': case 'a': return "1010";
        case 'B': case 'b': return "1011";
        case 'C': case 'c': return "1100";
        case 'D': case 'd': return "1101";
        case 'E': case 'e': return "1110";
        case 'F': case 'f': return "1111";
        default: return ""; 
    }
}


void checknull(void *ptr) {
    if (ptr == NULL) {
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}