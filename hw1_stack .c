#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 30

typedef struct {
	int id;
	int arrival_time;
	int service_time;
	bool pandan;	//비어있는지 아닌지 판단하기 위한 boolean 선언
}element;

typedef struct {
	int top;
	element data[MAX_STACK_SIZE];
}StackType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_stack(StackType* s) {
	s->top = -1;
}	 // stack clear;

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}
void push(element e, StackType* s) {
	if (!is_full(s)) {
		s->data[++(s->top)] = e;
	}
}
element pop(StackType* s) {
	if (!is_empty(s)) {
		return s->data[(s->top)--];
	}
}

int main(void) {
	StackType s;
	init_stack(&s);				//stack 초기화
	element a;
	a.id = 0; a.arrival_time = 0; a.pandan = false; a.service_time = 0;
	element b;
	b.id = 0; b.arrival_time = 0; b.pandan = false; b.service_time = 0;
	element c;
	c.id = 0; c.arrival_time = 0; c.pandan = false; c.service_time = 0;
	//a,b,c 초기화 및 pandan false 로 비어있음을 표현
	element Arr[3] = { a,b,c };	//a,b,c포함하는 element형 배열 Arr선언
	int count = 0;				//총 수리한 컴퓨터 개수 저장 변수
	int days = 30;				//30일 동안
	int computer_count = 1;		//첫번째 손님부터 들어올때마다 증가시켜줌
	int service_time = 0;		//업무처리시간
	int pay = 0;				//받은 돈
	int n = 0;					//n번째 손님
	int tot_pay = 0;			//총 받은 돈

	srand(time(NULL));

	for (int clock = 1; clock <= days; clock++) {

		printf("\n%d일차\n", clock);
		for (int i = 0; i < 3; i++) {
			Arr[i].service_time--;
		}
		for (int i = 0; i < 3; i++) {				//현재 수리중인 고객 정보 출력
			if (Arr[i].pandan == true) {
				printf("%d번째 고객 업무 중, 남은 시간 : %d\n", Arr[i].id, Arr[i].service_time);
			}
		}
		if (rand() % 10 < 7) {						//새로운 고객 업무 할당
			element plus;							//element객체 plus 선언
			printf("%d번째 고객이 들어옵니다\n ", computer_count);
			computer_count++;						//새로운 고객 들어옴 -> 1 증가
			n++;									//n를 증가시켜줌
			plus.id = n;
			plus.arrival_time = clock;				//현재 도착한 시간 저장
			plus.service_time = rand() % 7 + 1;		//서비스타임 1~7일 사이 
			push(plus, &s);							//수리 맡은 컴퓨터가 생겼음으로 push

			if ((Arr[0].pandan == true) & (Arr[1].pandan == true) & (Arr[2].pandan == true)) {
				printf("모든 자리가 꽉 찼습니다. 창고에 넣습니다.\n");
			}										//모든 작업 수행중일시 출력
		}

		for (int i = 0; i < 3; i++) {
			if (Arr[i].pandan == false) {			//업무를 맡을 자리가 있으면
				if (!is_empty(&s)) {				//stack이 비어있지 않으면
					element P = pop(&s);			//element객체 P 선언 , stack 맨 위에서 pop해옴
					Arr[i] = P;						//비어있는 자리에 P업무 시작
					printf("업무처리시간 = %d\n", Arr[i].service_time);
					printf("%d번째 고객 업무 시작합니다. 대기시간은 %d일이었습니다\n", n, clock - (Arr[i].arrival_time));
					Arr[i].pandan = true;			//업무 맡은 자리 표시
					break;							//하나 수리 맡을시 break로 빠져나옴
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			if (Arr[i].service_time == 0) {			//수행 완료 시
				Arr[i].pandan = false;				//업무 종료 표시
				count++;							//수리한 컴퓨터 갯수 증가
				pay = rand() % 16 + 5;				//보수는 5~20만원 사이
				tot_pay += pay;						//tot_pay에 pay를 더해서 누적시킴
				printf("%d번째 손님 업무 끝, 금액은 : %d\n", Arr[i].id, pay);
			}
		}
	}
	printf("30일 동안 수리한 컴퓨터 : %d, 받은 금액 : %d", count, tot_pay);
}