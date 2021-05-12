#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define SIZE 10000

int format (FILE * fr, FILE * fw)
{
    int i = 0;
    int k = 0;
    char c[2];
    int tab = 0;
    while (1)
    {
        for (i = 0; i < 2; i++) c[i] = fgetc(fr);
        if (c[0] == '#')
        {
            fputc(10,fw);
            fputc(c[0],fw);
        }
        else if (c[0] == '{')
        {
            tab++;
            fputc(c[0],fw);
            fputc(10,fw);

            for (k = 0; k <= tab; k++)
            {
                fputc(9,fw);
            }
        } else if (c[0] == '}' && c[1] != ';')
        {
            tab--;
            fputc(c[0],fw);
            fputc(10,fw);
            for (k = 0; k <= tab; k++)
            {
                fputc(9,fw);
            }
        } else if (c[0] == ';' && c[1] != ' ')
        {
            fputc(c[0],fw);
            fputc(10,fw);
            for (k = 0; k <= tab; k++)
            {
                fputc(9,fw);
            }
        }
        else fputc(c[0], fw);
        fseek(fr,-1,1);
        if (c[1] == EOF) break;
    }

    return 0;
}

int main() {


    FILE *fw_temp = fopen("/Users/matveygarbuzov/Desktop/Cfiles/temp.c", "w");


    FILE *fr_temp = fopen("/Users/matveygarbuzov/Desktop/Cfiles/test.c", "r");
    

    
    format (fr_temp, fw_temp);
    fclose(fr_temp);
    fclose(fw_temp);
    FILE *fr = fopen("/Users/matveygarbuzov/Desktop/Cfiles/temp.c", "r");
    FILE *fw = fopen("/Users/matveygarbuzov/Desktop/Cfiles/output.c", "w");
    char str[SIZE] = {0};
    int stackInd = 0;
    int vl = 0;
    int maxVl = 0;
    int commentCheck = 0;
    int varCheck = 0;
    int recursive = 0;
    int k = 0;
    char s[4] = {0};
    
    while (!feof(fr)) {
        fgets(str, SIZE, fr);

//переменные
        for (int i = 0; i < strlen(str); ++i) {
            if ((str[i] == 'i') && (str[i + 1] == 'n') && (str[i + 2] == 't') && (str[i + 3] != 'f') && (str[strlen(str) - 2] == ';')) {
                ++varCheck;

                for (int j = 0; j < strlen(str); ++j) {
                    if (str[j] == '=') {
                        --varCheck;
                    }
                    if (str[j] == ',') {
                        ++varCheck;
                    }
                }
            } else if ((str[i] == 'c') && (str[i + 1] == 'h') && (str[i + 2] == 'a') && (str[i + 3] == 'r') && (str[strlen(str) - 2] == ';')) {
                ++varCheck;

                for (int j = 0; j < strlen(str); ++j) {
                    if (str[j] == '=') {
                        --varCheck;
                    }
                    if (str[j] == ',') {
                        ++varCheck;
                    }
                }
            } else if ((str[i] == 'f') && (str[i + 1] == 'l') && (str[i + 2] == 'o') && (str[i + 3] == 'a') && (str[i + 4] == 't') && (str[strlen(str) - 2] == ';')) {
                ++varCheck;

                for (int j = 0; j < strlen(str); ++j) {
                    if (str[j] == '=') {
                        --varCheck;
                    }
                    if (str[j] == ',') {
                        ++varCheck;
                    }
                }
            }
        }

//комментарии
        if ((str[0] == '/') && (str[1] == '*')) {
            commentCheck = 1;
            str[0] = '/';
            str[1] = '/';
        } else if ((str[0] == '*') && (str[1] == '/')) {
            commentCheck = 0;
            str[0] = '/';
            str[1] = '/';
        }
        if (commentCheck == 1) {
            str[0] = '/';
            str[1] = '/';
        }
        fprintf(fw, "%s", str);
//вложенность
        int prov = 0;
        for (int j = 0; j < strlen(str); ++j) {
            if (((str[j] == 'f') && (str[j+1] == 'o') && (str[j+2] == 'r')) || ((str[j] == 'w') && (str[j+1] == 'h') && (str[j+2] == 'i'))) {
                ++prov;
            }
        }

        if ((prov == 1) && (stackInd == 0)) {
            ++stackInd;
        } else if ((prov == 1) && (stackInd != 0)) {
            ++vl;
        }
        if ((stackInd != 0) && (str[strlen(str) - 2] == '{') && (prov != 1)) {
            ++stackInd;
        } else if ((stackInd != 0) && (str[strlen(str) - 2] == '}') && (prov != 1)) {
            --stackInd;
        }
        if (stackInd == 0) {
            vl = 0;
        }

        if (vl > maxVl) {
            maxVl = vl;
        }

//рекурсивная функция
        if (str[0]=='i' && str[1]=='n' && str[2]=='t' && (str[4]!='m' || str[5]!='a' || str[6]!='i' || str[7]!='n')) {
            s[0] = str[4];
            s[1] = str[5];
            s[2] = str[6];
            s[3] = str[7];
            k=1;
        }
        else if (k==1) {
            int j=0;
            while (str[j]!='}' && j < strlen(str)-1) {
                if (str[j]==s[0] && str[j+1]==s[1] && str[j+2]==s[2] && str[j+3]==s[3])
                    recursive = 1;
                j+=1;
            }
            if (str[0]=='}')
                k=2;
        }
    }

    printf("Nesting loops сount: %d\n", maxVl);
    
    if (recursive == 1)
        printf("There is a recursive function\n");
    else
        printf("There is NO recursive function\n");
    
    //printf("%d\n", varCheck); // все ли переменные получюат начальные значения
    if (varCheck == 0)
        printf("All values have initialization.");
    else
        printf("Not all values have initialization. Count: %d\n", varCheck);
    
    
    unlink ("/Users/matveygarbuzov/Desktop/Cfiles/temp.c");

    fclose(fr);
    return 0;
}


/*
     FILE *fr = fopen("/Users/D/Documents/HSE/prog/Cfiles/test.c", "r");
     FILE *fw = fopen("/Users/D/Documents/HSE/prog/Cfiles/testout.c", "w");
     FILE *fr = fopen("/Users/matveygarbuzov/Desktop/Cfiles/test.c", "r");
     FILE *fw = fopen("/Users/matveygarbuzov/Desktop/Cfiles/output.c", "w");
     FILE *fw_temp = fopen("/Users/matveygarbuzov/Desktop/Cfiles/temp.c", "w+");
 
 
 */
