#include <stdio.h>
#include <stdlib.h>

// 函数声明
char *constr16to2(char *str);
const char *con16to2(char str);
void checknull(void *ptr);


int main() {
    // 示例输入
    char *ca25strs16[] = {
        "0123456789ABCDEF",
        "FEDCBA9876543210"
    };
    char *ca25strs2[2];  // 存储转换后的结果

    // 转换每个字符串
    for (int i = 0; i < 2; i++) {
        ca25strs2[i] = constr16to2(ca25strs16[i]);
        printf("Input: %s\n", ca25strs16[i]);
        printf("Output: %s\n\n", ca25strs2[i]);
    }

    // 释放内存
    for (int i = 0; i < 2; i++) {
        free(ca25strs2[i]);
    }

    return 0;
}

// 函数定义
char *constr16to2(char *str) {
    // 分配内存：64 个二进制字符 + 1 个结束符 '\0'
    char *result = malloc(65 * sizeof(char));
    checknull(result);

    // 将每个字符转换为 4 个二进制字符
    for (int i = 0; i < 16; i++) {
        const char *c = con16to2(str[i]);
        for (int j = 0; j < 4; j++) {
            result[i * 4 + j] = c[j];
            printf("%c", result[i * 4 + j]);
        }
        printf("\n");
    }
    result[64] = '\0';  // 添加字符串结束符

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
        default: return ""; // 如果输入不合法，返回空字符串
    }
}


void checknull(void *ptr) {
    if (ptr == NULL) {
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}