#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void maketruthtable(int op, int table[][op+1], int numCombinations) {
    for (int i = 0; i < numCombinations; i++) {
        int val = i;
        for (int j = 0; j < op; j++) {
            table[i][j] = val & 1;
            val = val >> 1;
        }
    }
}

int main() {
    int var_num, op, total;
    char c[16];
    char PQR[3] = {0, 0, 0};

    scanf("%d %d %d", &var_num, &op, &total);
    getchar(); // \n 읽어들이기

    fgets(c, 16, stdin); // 한 줄 통째로 읽기

    // 문자열에서 공백과 개행 문자 제거하기
    int len = strlen(c);
    for (int i = 0; i < len; i++) {
        if (c[i] == ' ' || c[i] == '\n') {
            for (int j = i; j < len - 1; j++) {
                c[j] = c[j+1];
            }
            c[len-1] = '\0';
            len--;
            i--;
        }
    }

    for (int j = 0; j < len; j++) {
        if (c[j] == 'P') {
            PQR[0] = 1;
        } else if (c[j] == 'Q') {
            PQR[1] = 1;
        } else if (c[j] == 'R') {
            PQR[2] = 1;
        }
    }

    int numCombinations = 1 << (PQR[0]+PQR[1]+PQR[2]); // 2^(number of variables)
    int table[numCombinations][var_num+1];
    maketruthtable(var_num, table, numCombinations);

    // print header
    if (PQR[0] == 1) {
        printf("P ");
    }
    if (PQR[1] == 1) {
        printf("Q ");
    }
    if (PQR[2] == 1) {
        printf("R ");
    }
    printf("RESULT\n\n");

    // print truth table
    for (int i = 0; i < numCombinations; i++) {
        int result = 1;
        for (int j = 0; j < len; j++) {
            if (c[j] == 'n') { // not
                result = !table[i][c[j+1]-'P'];
                j++;
            } else if (c[j] == 'a') { // and
                result = result && table[i][c[j+1]-'P'];
                j++;
            } else if (c[j] == 'o') { // or
                result = result || table[i][c[j+1]-'P'];
                j++;
            } else if (c[j] == 'i') { // if-then
                if (table[i][c[j-1]-'P']) {
                    result = table[i][c[j+1]-'P'];
                }
                j++;
            }
        }

        // print variable values
for (int j = 0; j < var_num; j++) {
    if (table[i][j] == 0) {
        printf("F ");
    } else {
        printf("T ");
    }
}
if (result == 0) {
    printf("F\n\n");
} else {
    printf("T\n\n");
}

}
}
