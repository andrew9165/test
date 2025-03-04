#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *constr16to2(char *str) ;
const char *con16to2(char str);
void checknull(void *ptr);
enum strtype{
    normal,
    subnormal,
    zero,
    inf,
    nan
};
struct ca25{
    char *ca25strs16;
    char *ca25strs2;
    char *S;
    char *E;
    char *M;
    enum strtype ca25type;
};


int main()
{
    struct ca25 **str = NULL;
    int count = 0;
    char input[17];

    while (fgets(input, 17, stdin) != NULL)
    {

        input[strcspn(input, "\n")] = '\0';

        str = realloc(str, (count + 1) * sizeof(struct ca25 *));
        checknull(str);
        // 分配内存
        str[count] = malloc(sizeof(struct ca25));
        checknull(str[count]);
        str[count]->ca25strs16 = malloc(17 * sizeof(char));
        str[count]->ca25strs2 = malloc(65 * sizeof(char));
        str[count]->E = malloc(2 * sizeof(char));
        str[count]->M = malloc(9 * sizeof(char));
        str[count]->S = malloc(9 * sizeof(char));
        checknull(str[count]->ca25strs16);
        checknull(str[count]->ca25strs2);
        checknull(str[count]->E);
        checknull(str[count]->M);
        checknull(str[count]->S);


        // 复制输入的字符串到新分配的内存中
        strncpy(str[count]->ca25strs16, input, 16);
        str[count]->ca25strs16[16] = '\0'; // 以'\0'结尾

        count++;
    }

    // 打印ca25strs16
    for (int i = 0; i < count; i++)
    {
        str[i]->ca25strs2 = constr16to2(str[i]->ca25strs16);
        printf("%s\t%s\n", str[i]->ca25strs16, str[i]->ca25strs2);
    }
    // 释放内存
    for (int i = 0; i < count; i++)
    {
        free(str[i]->ca25strs16);
        free(str[i]->ca25strs2);
        free(str[i]->S);
        free(str[i]->E);
        free(str[i]->M);
    }
    free(str);

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