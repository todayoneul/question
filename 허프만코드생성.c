#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // strcpy 사용

// 트리 노드 정의
typedef struct node
{
    char alphabet;      // 알파벳
    int freq;           // 빈도수
    struct node *left;  // 왼쪽 자식 노드
    struct node *right; // 오른쪽 자식 노드
} node;

// 새 노드 생성(입력 알파벳, 빈도수, 왼쪽 및 오른똑 자식 노드)
node *makenode(char alphabet, int freq, struct node *left, struct node *right)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->alphabet = alphabet;
    new_node->freq = freq;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

node *makehuffmantree(char input[])
{
    int i = 0;
    int j;
    int temp_n = 0;
    int min = 0;  // 제일 빈도수가 작은 index
    int min2 = 0; // 두 번째로 빈도수가 작은 index
    int freq[6] = {0, 0, 0, 0, 0, 0};    // A, B, C, D, E, F 빈도 수
    int check[6] = {0, 0, 0, 0, 0, 0};   // 합쳐졌는지 확인(합쳐져서 살펴 볼 필요가 없으면 -1)
    node *tree[6];// 비교할 노드 배열
    node *new_node;// 새 노드

    while (input[i] != '\0')
    {
        // 빈도수 구하기
        switch (input[i])
        {
        case 'a':
            freq[0]++;
            break;
        case 'b':
            freq[1]++;
            break;
        case 'c':
            freq[2]++;
            break;
        case 'd':
            freq[3]++;
            break;
        case 'e':
            freq[4]++;
            break;
        case 'f':
            freq[5]++;
            break;
        default:
            break;
        }
        i++;
    }

    tree[0] = makenode('a', freq[0], NULL, NULL); // a
    tree[1] = makenode('b', freq[1], NULL, NULL); // b
    tree[2] = makenode('c', freq[2], NULL, NULL); // c
    tree[3] = makenode('d', freq[3], NULL, NULL); // d
    tree[4] = makenode('e', freq[4], NULL, NULL); // e
    tree[5] = makenode('f', freq[5], NULL, NULL); // f

    for (i = 0; i < 5; i++){
        // 가장 작은 수 찾기
        j = 0;
        while (check[j] == -1)
            j++; // 합쳐진 노드를 제외한 배열 중 가장 앞 index
        min = j; // 우선 제일 작다고 가정

        for (j = min; j < 6; j++){ // 모든 배열을 검사
            if (check[j] != -1){ // 이미 합쳐진 노드가 아니면
                if (tree[min]->freq > tree[j]->freq){// min인덱스 빈도수 보다 빈도수가 작은 경우
                    min = j;
                }
            }
        }
        // 두번째로 작은 수 찾기
        j = 0;
        while (check[j] == -1 || j == min)
            j++; // 합쳐진 노드와 최소 노드 제외한 배열 중 가장 앞 index
        min2 = j; // 두번째로 작다고 가정
        for (j = min2; j < 6; j++){
            if (check[j] != -1){ // 이미 합쳐진 노드가 아니면
                if (tree[min2]->freq > tree[j]->freq){
                    // min2인덱스 빈도수 보다 빈도수가 작은 경우
                    if (j != min){ // 가장 작은 index가 아닌 경우
                        min2 = j;
                    }
                }
            }
        }
        tree[min] = makenode(NULL, tree[min]->freq + tree[min2]->freq, tree[min], tree[min2]);// min과 min2인덱스의 빈도수를 합친 빈도수로 새 노드 생성
        // 새로 만든 노드를 min인덱스 자리에 넣는다.
        check[min2] = -1; // min2인덱스는 min인덱스 자리의 노드에 합쳐졌으므로
    }
    return tree[min]; // 만들어진 트리의 루트 노드
}

// 알파멧마다 가변 길이 코드 제공함수(n은 루트 노드)
void make_code(node *n, char str[], int len, char *code[])
{
    if (n->left == NULL && n->right == NULL){ // n이 단노드인 경우
        str[len] = '\0'; // 문장의 끝을 str끝에 넣어주고 단 노드의 알파벳을 확인하여 code의 적절한 위치에 str문자열을 넣음
        switch (n->alphabet)
        {
        case ('a'):
            strcpy(code[0], str);
            break;
        case ('b'):
            strcpy(code[1], str);
            break;
        case ('c'):
            strcpy(code[2], str);
            break;
        case ('d'):
            strcpy(code[3], str);
            break;
        case ('e'):
            strcpy(code[4], str);
            break;
        case ('f'):
            strcpy(code[5], str);
            break;
        }
    }
    else // 단 노드가 아닌 경우
    {
        if (n->left != NULL) // 왼쪽 자식이 있는 경우
        {
            str[len] = '0'; // 문자열에 0 삽입
            make_code(n->left, str, len + 1, code);// 재귀호출(문자열에 들어갈 위치에 +1)
        }
        if (n->right != NULL) // 오른쪽 자식이 있는 경우
        {
            str[len] = '1'; // 문자열에 1 삽입
            make_code(n->right, str, len + 1, code);// 재귀호출(문자열에 들어갈 위치에 +1)
        }
    }
}

int main()
{
    char input[22];  // 압축하고자 하는 문자열(input)
    char *code[6];   // 각 알파벳에 대한 가변길이 코드 배열
    char str[22];    // 문자열 변수
    node *root;      // 트리의 루트 초기화

    for (int i = 0; i < 6; i++){
        code[i] = (char *)malloc(sizeof(char) * 20);
    }
    scanf("%s", input); // 압축하고자 하는 문자열 입력

    root = makehuffmantree(input);   // 허프만코드를 이용한 트리 생성
    make_code(root, str, 0, code);  // 트리를 사용한 알파벳 별 가변길이 코드 생성

    printf("%s-> %c\n\n", code[0], 'a');
    printf("%s-> %c\n\n", code[5], 'f');
    printf("%s-> %c\n\n", code[4], 'e');
    printf("%s-> %c\n\n", code[3], 'd');
    printf("%s-> %c\n\n", code[2], 'c');
    printf("%s-> %c\n\n", code[1], 'b');

    for (int i = 0; i < 6; i++){
        free(code[i]);
    }
}
