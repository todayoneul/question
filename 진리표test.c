#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//명재 연산을 위한 스택 구현
#define MAX_STACK_SIZE 8
 
char stack[MAX_STACK_SIZE];
int top=-1;
 
int IsEmpty(){
    if(top<0)
        return true;
    else
        return false;
    }
int IsFull(){
    if(top>=MAX_STACK_SIZE-1)
        return true;
    else
        return false;
}
 
void push(char value){
    if(IsFull()==true)
        printf("스택이 가득 찼습니다.");
    else
        stack[++top]=value; 
}
 
int pop(){
    if(IsEmpty()==true)
        printf("스택이 비었습니다.");
    else 
        return stack[top--];
}


int negation(a){
    return !a;
}
int conjunction(a,b){
    return a&&b;
}

int disjuction(a,b){
    return a || b;
}

int implicaiton(a,b){
    return (!a) || b;
}


int main(){
    int var_num, op, total;
    char c[16];
    char PQR[3] = {0, 0, 0};

    //input 
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

        // 입력받은 명제변수에 따른 결과 출력
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

    int result = 0;
    int P,Q,R;
    int pstackarr[2];
    int pstackcount =0;
    // 명제변수가 1개일 경우
    if(var_num ==1){
        for(int r=1 ; r<2; r++){
        if(r/2==0){
            P=1,Q=1,R=1; 
            }else{
            P=0,Q=0,R=0;}
        //pstackarr[0]=P;
        //pstackarr[1]=P;
        int opcount =0;
        int PQRcount = 0;
        int table1[2][2]={{1,0},{0,0}};
        
        //
        for(int i=0; i<total; i++){
            
        if(c[i]=='a'||c[i]=='i'||c[i]=='o'){
            opcount++;
        }
        if(opcount!=0 && (opcount % 2==0 || IsFull || i==total-1)){
            while (IsEmpty)
            {   
                if(stack[top]=='o'){
                    pop();
                    if(pop()=='P'){
                    pstackarr[PQRcount] = P;
                    //PQRcount++;
                    }else if(pop()=='Q'){
                    pstackarr[PQRcount] = Q;
                    //PQRcount++;
                    }else if(pop()=='R'){
                    pstackarr[PQRcount] = R;
                    //PQRcount++;
                    }/*else if(pop()=='n'){
                    pstackarr[PQRcount-1] = !pstackarr[PQRcount-1];
                    }*/
                    result = disjuction(pstackarr[0],pstackarr[1]);
                    opcount--;
                }else if (stack[top]=='i')
                {   
                    pop();
                    if(pop()=='P'){
                    pstackarr[PQRcount] = P;
                    //PQRcount++;
                    }else if(pop()=='Q'){
                    pstackarr[PQRcount] = Q;
                    //PQRcount++;
                    }else if(pop()=='R'){
                    pstackarr[PQRcount] = R;
                    //PQRcount++;
                    }/*else if(pop()=='n'){
                    pstackarr[PQRcount-1] = !pstackarr[PQRcount-1];
                    }*/
                    result = implicaiton(pstackarr[0],pstackarr[1]);
                    opcount--;

                    }else if(stack[top]=='a'){
                    pop();
                    if(pop()=='P'){
                    pstackarr[PQRcount] = P;
                    //PQRcount++;
                    }else if(pop()=='Q'){
                    pstackarr[PQRcount] = Q;
                    //PQRcount++;
                    }else if(pop()=='R'){
                    pstackarr[PQRcount] = R;
                    //PQRcount++;
                    }/*else if(pop()=='n'){
                    pstackarr[PQRcount-1] = !pstackarr[PQRcount-1];
                    }*/
                    result = conjunction(pstackarr[0],pstackarr[1]);
                    opcount--;
                    }
            else{
            pop();
            if(pop()=='P'){
                    pstackarr[PQRcount] = P;
                    PQRcount++;
                }else if(pop()=='Q'){
                    pstackarr[PQRcount] = Q;
                    PQRcount++;
                }else if(pop()=='R'){
                    pstackarr[PQRcount] = R;
                    PQRcount++;
                }else if(pop()=='n'){
                    pstackarr[PQRcount-1] = !pstackarr[PQRcount-1];

                }
            }
        }
        }
        push(c[i]);
        }
        table1[r][2]=result;
    }
    }


    //명제 변수가 2개일 경우
    else if(var_num ==2){
        int table2[4][3]={{1,1,result},{1,0,result},{0,1,result},{0,0,result}};
    }

    //명제변수가 3개일 경우
    else if(var_num ==3){
        int table3[8][4]={{1,1,1,result},{1,1,0,result},{1,0,1,result},{1,0,0,result},{0,1,1,result},{0,1,0,result},{0,0,1,result},{0,0,0,result}};
        for(int h =0 ; h<total; h++){
            
        }
    }




}