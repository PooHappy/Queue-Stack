#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 30

typedef struct {
	int id;
	int arrival_time;
	int service_time;
	bool pandan;	//����ִ��� �ƴ��� �Ǵ��ϱ� ���� boolean ����
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
	init_stack(&s);				//stack �ʱ�ȭ
	element a;
	a.id = 0; a.arrival_time = 0; a.pandan = false; a.service_time = 0;
	element b;
	b.id = 0; b.arrival_time = 0; b.pandan = false; b.service_time = 0;
	element c;
	c.id = 0; c.arrival_time = 0; c.pandan = false; c.service_time = 0;
	//a,b,c �ʱ�ȭ �� pandan false �� ��������� ǥ��
	element Arr[3] = { a,b,c };	//a,b,c�����ϴ� element�� �迭 Arr����
	int count = 0;				//�� ������ ��ǻ�� ���� ���� ����
	int days = 30;				//30�� ����
	int computer_count = 1;		//ù��° �մԺ��� ���ö����� ����������
	int service_time = 0;		//����ó���ð�
	int pay = 0;				//���� ��
	int n = 0;					//n��° �մ�
	int tot_pay = 0;			//�� ���� ��

	srand(time(NULL));

	for (int clock = 1; clock <= days; clock++) {

		printf("\n%d����\n", clock);
		for (int i = 0; i < 3; i++) {
			Arr[i].service_time--;
		}
		for (int i = 0; i < 3; i++) {				//���� �������� �� ���� ���
			if (Arr[i].pandan == true) {
				printf("%d��° �� ���� ��, ���� �ð� : %d\n", Arr[i].id, Arr[i].service_time);
			}
		}
		if (rand() % 10 < 7) {						//���ο� �� ���� �Ҵ�
			element plus;							//element��ü plus ����
			printf("%d��° ���� ���ɴϴ�\n ", computer_count);
			computer_count++;						//���ο� �� ���� -> 1 ����
			n++;									//n�� ����������
			plus.id = n;
			plus.arrival_time = clock;				//���� ������ �ð� ����
			plus.service_time = rand() % 7 + 1;		//����Ÿ�� 1~7�� ���� 
			push(plus, &s);							//���� ���� ��ǻ�Ͱ� ���������� push

			if ((Arr[0].pandan == true) & (Arr[1].pandan == true) & (Arr[2].pandan == true)) {
				printf("��� �ڸ��� �� á���ϴ�. â�� �ֽ��ϴ�.\n");
			}										//��� �۾� �������Ͻ� ���
		}

		for (int i = 0; i < 3; i++) {
			if (Arr[i].pandan == false) {			//������ ���� �ڸ��� ������
				if (!is_empty(&s)) {				//stack�� ������� ������
					element P = pop(&s);			//element��ü P ���� , stack �� ������ pop�ؿ�
					Arr[i] = P;						//����ִ� �ڸ��� P���� ����
					printf("����ó���ð� = %d\n", Arr[i].service_time);
					printf("%d��° �� ���� �����մϴ�. ���ð��� %d���̾����ϴ�\n", n, clock - (Arr[i].arrival_time));
					Arr[i].pandan = true;			//���� ���� �ڸ� ǥ��
					break;							//�ϳ� ���� ������ break�� ��������
				}
			}
		}
		for (int i = 0; i < 3; i++) {
			if (Arr[i].service_time == 0) {			//���� �Ϸ� ��
				Arr[i].pandan = false;				//���� ���� ǥ��
				count++;							//������ ��ǻ�� ���� ����
				pay = rand() % 16 + 5;				//������ 5~20���� ����
				tot_pay += pay;						//tot_pay�� pay�� ���ؼ� ������Ŵ
				printf("%d��° �մ� ���� ��, �ݾ��� : %d\n", Arr[i].id, pay);
			}
		}
	}
	printf("30�� ���� ������ ��ǻ�� : %d, ���� �ݾ� : %d", count, tot_pay);
}