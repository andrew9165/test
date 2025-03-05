#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *constr16to2(int a, char *str) ;
const char *con16to2(char str);
void checknull(void *ptr);
char *constr2to16(int a, char *str);
char con2to16(char *str);
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
    char *ca25S;
    char *ca25E;
    char *ca25M;
    char *ca25type;
    char *fp32strs16;
    char *fp32strs2;
    char *fp32S;
    char *fp32E;
    char *fp32M;
    char *fp32type;
};


int main()
{
    struct ca25 **str = NULL;
    int count = 0;
    char input[17];


    //
    FILE *fp = fopen("testcase.txt", "r");
    // 读取输入
    while (fgets(input, 17, fp) != NULL)
    {
        if (input[0] == '\n')
        {
            continue;
        }
        input[strcspn(input, "\n")] = '\0';

        str = realloc(str, (count + 1) * sizeof(struct ca25 *));
        checknull(str);
        // 分配内存
        {
            str[count] = malloc(sizeof(struct ca25));
            checknull(str[count]);
            str[count]->ca25strs16 = malloc(17 * sizeof(char));
            str[count]->ca25strs2 = malloc(65 * sizeof(char));
            str[count]->ca25S = malloc(2 * sizeof(char));
            str[count]->ca25E = malloc(9 * sizeof(char));
            str[count]->ca25M = malloc(11 * sizeof(char));
            str[count]->ca25type = malloc(10 * sizeof(char));
            str[count]->fp32strs16 = malloc(9 * sizeof(char));
            str[count]->fp32strs2 = malloc(33 * sizeof(char));
            str[count]->fp32S = malloc(2 * sizeof(char));
            str[count]->fp32E = malloc(3 * sizeof(char));
            str[count]->fp32M = malloc(7 * sizeof(char));
            str[count]->fp32type = malloc(10 * sizeof(char));
            checknull(str[count]->ca25strs16);
            checknull(str[count]->ca25strs2);
            checknull(str[count]->ca25S);
            checknull(str[count]->ca25E);
            checknull(str[count]->ca25M);
            checknull(str[count]->fp32strs16);
            checknull(str[count]->fp32strs2);
            checknull(str[count]->fp32S);
            checknull(str[count]->fp32E);
            checknull(str[count]->fp32M);
        };

        // 复制输入的字符串到新分配的内存中
        strncpy(str[count]->ca25strs16, input, 16);
        str[count]->ca25strs16[16] = '\0'; // 以'\0'结尾

        
        count++;
        //printf("count:%d\n", count);
    }

    // 处理每个字符串
    struct ca25 *cur = NULL;
    for (int i = 0; i < count; i++)
    {
        cur = str[i];
        cur->ca25strs2 = constr16to2(16, str[i]->ca25strs16);

        // ca25S
        cur->ca25S[0] = cur->ca25strs2[0];
        cur->ca25S[1] = '\0';
        
        // ca25E
        char ca25Estr[33];
        strncpy(ca25Estr, cur->ca25strs2 + 1, 32);
        ca25Estr[32] = '\0';
        cur->ca25E = constr2to16(32, ca25Estr);
        
        // ca25M, ca25type
        cur->ca25M[1] = '.';
        cur->ca25M[10] = '\0';
        char ca25Mstr[33];
        strncpy(ca25Mstr, cur->ca25strs2 + 33, 31);
        ca25Mstr[31] = '0';
        ca25Estr[32] = '\0';
        
        if (strcmp(cur->ca25E, "00000000") == 0) {
            if (strcmp(ca25Mstr, "00000000000000000000000000000000") == 0) {
                // ca25 zero
                cur->ca25type = "zero";
                strncpy(cur->ca25M + 2, constr2to16(32, ca25Mstr), 8);
                cur->ca25M[0] = '0';
            } else {
                // ca25 subnormal
                cur->ca25type = "subnormal";
                strncpy(cur->ca25M + 2, constr2to16(32, ca25Mstr), 8);
                cur->ca25M[0] = '0';
            }
        } else if (strcmp(cur->ca25E, "ffffffff") == 0) {
            if (strcmp(ca25Mstr, "00000000000000000000000000000000") == 0) {
                // ca25 infinity
                cur->ca25type = "inf";
                strncpy(cur->ca25M + 2, constr2to16(32, ca25Mstr), 8);
                cur->ca25M[0] = '1';
            } else {
                // ca25 NaN
                cur->ca25type = "nan";
                strncpy(cur->ca25M + 2, constr2to16(32, ca25Mstr), 8);
                cur->ca25M[0] = '1';
            }
        } else {
            // normal
            cur->ca25type = "normal";
            strncpy(cur->ca25M + 2, constr2to16(32, ca25Mstr), 8);
            cur->ca25M[0] = '1';
        }
        
        // cs25strs2 snip
        // sign
        char ca_s_snip[2];
        strncpy(ca_s_snip, cur->ca25strs2, 1);
        ca_s_snip[1] = '\0';
        // exponent 1
        char ca_e_snip1[9];
        strncpy(ca_e_snip1, cur->ca25strs2 + 1, 8);
        ca_e_snip1[8] = '\0';
        // exponent 2
        char ca_e_snip2[25];
        strncpy(ca_e_snip2, cur->ca25strs2 + 9, 24);
        ca_e_snip2[24] = '\0';
        // mantissa 1
        char ca_m_snip1[24];
        strncpy(ca_m_snip1, cur->ca25strs2 + 33, 23);
        ca_m_snip1[23] = '\0';
        // mantissa 2
        char ca_m_snip2[9];
        strncpy(ca_m_snip2, cur->ca25strs2 + 56, 8);
        ca_m_snip2[8] = '\0';

        // fp32S
        cur->fp32strs2[0] = cur->ca25strs2[0];
        cur->fp32strs2[32] = '\0';

        if (strcmp(cur->ca25type, "zero") == 0){
            // zero
            strncpy(cur->fp32strs2 + 1, "0000000000000000000000000000000", 32);
            cur->fp32type = cur->ca25type;
        } else if (strcmp(cur->ca25type, "inf") == 0) {
            // infinity
            strncpy(cur->fp32strs2 + 1, "1111111100000000000000000000000", 32);
            cur->fp32type = cur->ca25type;
        } else if (strcmp(cur->ca25type, "subnormal") == 0) {
            // subnormal
            strncpy(cur->fp32strs2 + 1, "0000000000000000000000000000001", 32);
            cur->fp32type = cur->ca25type;
        } else if (strcmp(cur->ca25type, "nan") == 0) {
            // nan
            strncpy(cur->fp32strs2 + 1, "11111111", 9);
            strncpy(cur->fp32strs2 + 9, ca_m_snip1, 24);
            cur->fp32type = cur->ca25type;
        } else {
            // normal
            
        }
    
    }








    // 打印ca25strs16
    for (int i = 0; i < count; i++)
    {
        printf("ca25 S=%s E=%s M=%s %s\n\n\n", str[i]->ca25S, str[i]->ca25E, str[i]->ca25M, str[i]->ca25type);
    }

    // 释放内存
    for (int i = 0; i < count; i++)
    {
        free(str[i]->ca25strs16);
        free(str[i]->ca25strs2);
        free(str[i]->ca25S);
        free(str[i]->ca25E);
        free(str[i]->ca25M);
        free(str[i]->fp32strs16);
        free(str[i]->fp32strs2);
        free(str[i]->fp32S);
        free(str[i]->fp32E);
        free(str[i]->fp32M);
    }
    free(str);

    return 0;
}

char *constr16to2(int a, char *str) {
    // 64 个二进制字符 + 1 个结束符 '\0'
    char *result = malloc((4 * a + 1) * sizeof(char));
    checknull(result);

    // 转换每个十六进制字符
    for (int i = 0; i < a; i++) {
        const char *c = con16to2(str[i]);
        for (int j = 0; j < 4; j++) {
            result[i * 4 + j] = c[j];
            // printf("%c", result[i * 4 + j]);
        }
        // printf("\n");
    }
    result[4 * a] = '\0';  // 字符串结束符

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

char *constr2to16(int a, char *str) {
    // 分配内存
    char *result = malloc((a / 4 + 1) * sizeof(char));
    checknull(result);
    char block[5];
    // 转换每 4 个二进制字符
    for (int i = 0; i < a / 4; i++) {
        strncpy(block, str + i * 4, 4);
        block[4] = '\0';
        result[i] = con2to16(block);
    }
    result[a / 4] = '\0';  // 字符串结束符

    return result;
}

char con2to16(char *str) {
    if (strcmp(str, "0000") == 0) return '0';
    if (strcmp(str, "0001") == 0) return '1';
    if (strcmp(str, "0010") == 0) return '2';
    if (strcmp(str, "0011") == 0) return '3';
    if (strcmp(str, "0100") == 0) return '4';
    if (strcmp(str, "0101") == 0) return '5';
    if (strcmp(str, "0110") == 0) return '6';
    if (strcmp(str, "0111") == 0) return '7';
    if (strcmp(str, "1000") == 0) return '8';
    if (strcmp(str, "1001") == 0) return '9';
    if (strcmp(str, "1010") == 0) return 'a';
    if (strcmp(str, "1011") == 0) return 'b';
    if (strcmp(str, "1100") == 0) return 'c';
    if (strcmp(str, "1101") == 0) return 'd';
    if (strcmp(str, "1110") == 0) return 'e';
    if (strcmp(str, "1111") == 0) return 'f';
    return '\0';
}

void checknull(void *ptr) {
    if (ptr == NULL) {
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}












