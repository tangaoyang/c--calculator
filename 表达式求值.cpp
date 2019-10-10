#include <stdio.h>
struct Sqstack {
	int data[100];
	int top;
};
char opset[10] = {'+', '-', '*', '/', '(', ')', '#'};
//�������бȽ���������ȼ��ľ���,3����'=',2����'>',1����'<',0�����ɱ� 
int  cmp[7][7]  = {
        { 2, 2, 1, 1, 1, 2, 2 },
        { 2, 2, 1, 1, 1, 2, 2 },
        { 2, 2, 2, 2, 1, 2, 2 },
        { 2, 2, 2, 2, 1, 2, 2 },
        { 1, 1, 1, 1, 1, 3, 0 },
        { 2, 2, 2, 2, 0, 2, 2 },
        { 1, 1, 1, 1, 1, 0, 3 }  };
Sqstack Num;
Sqstack Oper;

void InitStack(Sqstack &s);//��ʼ��ջ
void Push(Sqstack &s, char ch);//��ջ
char GetTop(Sqstack &s);//��ȡջ��Ԫ�ص�ֵ 
int In(char ch, char operArr[10]);//�ж��Ƿ�Ϊ�����
int Cal();
int Pop (Sqstack &s, char &x);//��ջ 
char Compare(char oper1, char oper2); 
int Count(int x1, char op, int x2);

void InitStack(Sqstack &s) {
	s.top = -1;
}

void Push(Sqstack &s, char ch) {
	
	if(s.top == 99) {//ջ�� 
		return ;
	}
	s.top++;
	s.data[s.top] = ch;
	return ;
	
}

char GetTop(Sqstack &s) {
	
	if(s.top == -1) {
		return 0;
	}
	char ch;
	ch = s.data[s.top];
	return ch;
	
}

int Pop(Sqstack &s, char &x) {
	
     if(s.top == -1)
         return 0;
     x = s.data[s.top];
     --(s.top);
     return 1;
     
 }

int In(char ch, char operArr[10]) {
	
	for(int i = 0; i < 7; i++) {
		if(ch == operArr[i]) {
			return 1;
		}
	}
	return 0;
	
}

char Compare(char oper1, char oper2) {
	int m = 0, n = 0, i, ans;
	char ch;
	for(i = 0; i < 7; i++) {
		if(oper1 == opset[i]) {
			m = i;
		}
		if(oper2 == opset[i]) {
			n = i;
		}
	}
	ans = cmp[m][n];
	switch (ans) {
		case 2:
        	return (char)('<');
    	case 1:
       		return (char)('>');
    	case 3:
        	return (char)('=');
    	default:
     	    printf("���ʽ����!\n");
       		break;
    }
}

int Count(int x1, char op, int x2) {
	int val;
	switch(op) {
		case '+': val = x1 + x2; break;
		case '-': val = x1 - x2; break;
		case '*': val = x1 * x2; break;
		case '/': val = x1 / x2; break;
	}
	return val;
}

int Cal() {
	
	char ch, x, op, a1, a2, val;
	int data, ans;
	InitStack(Num);//��ʼ��������ջ 
	InitStack(Oper);//��ʼ�������ջ
	Push(Oper, '#');//�������ջ�м�����ֹ��Ϊ�˽��бȽϣ���������
	printf("������һ�����ʽ��\n");
	ch = getchar();
	while(ch != '#' || GetTop(Oper) != '#') {
		//opsetΪ��������� 
		if(!In(ch, opset)) {//���������ǲ����� 
			data = ch - '0';
			ch = getchar();
			while(!In(ch, opset)){//����Ĳ�����������ǲ�����
			 	data = data * 10 + ch - '0';//����������ĸ�λ���룬��ת��Ϊʮ������data 
			 	ch = getchar();
			}
			Push(Num, data);//��������ջ
		} else {
			switch(Compare(GetTop(Oper), ch)) {
				case '>': 
					Push(Oper, ch); 
					ch = getchar(); 
					break;
				case '=': 
					Pop(Oper, x); 
					ch = getchar(); 
					break;
				case '<': 
					Pop(Oper, op); 
					Pop(Num, a2); 
					Pop(Num, a1); 
					val = Count(a1, op, a2); 
					Push(Num, val); 
					break;
			}
		}
	}
	val = GetTop(Num);
	return val; 
	
} 

int main() {
	int answer;
	answer = Cal();
	printf("%d", answer);
}

