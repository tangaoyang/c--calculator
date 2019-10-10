#include <stdio.h>
struct Sqstack {
	int data[100];
	int top;
};
char opset[10] = {'+', '-', '*', '/', '(', ')', '#'};
//用来进行比较运算符优先级的矩阵,3代表'=',2代表'>',1代表'<',0代表不可比 
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

void InitStack(Sqstack &s);//初始化栈
void Push(Sqstack &s, char ch);//入栈
char GetTop(Sqstack &s);//获取栈顶元素的值 
int In(char ch, char operArr[10]);//判断是否为运算符
int Cal();
int Pop (Sqstack &s, char &x);//出栈 
char Compare(char oper1, char oper2); 
int Count(int x1, char op, int x2);

void InitStack(Sqstack &s) {
	s.top = -1;
}

void Push(Sqstack &s, char ch) {
	
	if(s.top == 99) {//栈满 
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
     	    printf("表达式错误!\n");
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
	InitStack(Num);//初始化操作数栈 
	InitStack(Oper);//初始化运算符栈
	Push(Oper, '#');//在运算符栈中加入终止符为了进行比较，结束运算
	printf("请输入一个表达式：\n");
	ch = getchar();
	while(ch != '#' || GetTop(Oper) != '#') {
		//opset为运算符集合 
		if(!In(ch, opset)) {//如果读入的是操作数 
			data = ch - '0';
			ch = getchar();
			while(!In(ch, opset)){//读入的不是运算符，是操作数
			 	data = data * 10 + ch - '0';//读入操作数的各位数码，并转化为十进制数data 
			 	ch = getchar();
			}
			Push(Num, data);//操作数入栈
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

