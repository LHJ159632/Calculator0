#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include "lk_stack.h"										// 链栈类

template<class ElemType>
class Calculator
{
private:
	LinkStack<ElemType> opnd;								// 操作数栈
	LinkStack<char> optr;									// 操作符栈

	int OperPrior(char op);									// 操作符优先级
	void Get2Operands(ElemType &left, ElemType &right);		// 从栈opnd中退出两个操作数
	ElemType Operate(ElemType left, char op, ElemType right);// 执行运算left op right
	bool IsOperator(char ch);								// 判断ch是否为操作符 

public:
	Calculator(){};											
	virtual ~Calculator(){};								
	void Run();												
};

template<class ElemType>
int Calculator<ElemType>::OperPrior(char op)
{	
	switch(op)
	{
		case'=':
			return 1;
			break;
		case'(':
			return 2;
			break;
		case')':
		    return 2;
		    break;
		case'+':
			return 3;
			break;
		case'-':
			return 3;
			break;
		case'*':
		   	return 4;
		   	break;
		case'/':
		   	return 4;
		   	break;
		case'%':
		   	return 4;
			   break;	  
		case'^':
			return 5;  
			break;     		    	
	}							
}

template<class ElemType>
void Calculator<ElemType>::Get2Operands(ElemType &left, ElemType &right)
// 操作结果：从栈opnd中退出两个操作数
{
	opnd.Pop(right); 
	opnd.Pop(left);
};

template<class ElemType>
ElemType Calculator<ElemType>::Operate(ElemType left, char op, ElemType right)
// 操作结果：执行运算left op right
{
	ElemType result;
	if (op == '+') 
	result = left + right;			// 加法
	else if (op == '-') 
	result = left - right;		// 减法
	else if (op == '*') 
	result = left * right;		// 乘法
	else if (op == '/' && right == 0) 
	throw Error("除数为零!");	
		// 除数不为0 
	else if (op == '/' && right != 0) 
	result = left / right;	// 除法
	else if (op == '%' && (long)right == 0) 
	throw Error("除数为零!");	
		// 除数不为0
	else if (op == '%' && (long)right != 0) 
	result = (long)left % (long)right;
		// 整除运算
	else if (op == '^') 
	result = pow(left, right);	// 乘方
	return result;					 				
}

template<class ElemType>
bool Calculator<ElemType>::IsOperator(char ch)
// 操作结果：判断ch是否为操作符 
{
	if (ch == '=' || ch == '(' || ch == '^' || ch == '*' ||
		ch == '/' || ch =='%' || ch == '+' || ch== '-' || ch == ')') 
		return true;
	else 
	return false;
};

template<class ElemType>
void Calculator<ElemType>::Run()
// 操作结果：运算表达式
{
	optr.Clear();	opnd.Clear();		// 清空optr栈与opnd栈
	optr.Push('=');						// 在optr栈中加入一个'='
	char ch;							// 临时字符
	char priorChar;						// 当前输入的前一个字符，如不为操作符，则令其值为'0'
	char optrTop;						// 临optr栈的栈顶字符
	double operand;						// 操作数
	char op;							// 操作符

	priorChar = '=';					// 前一字符
	ch = GetChar();						// 读入一个字符
	
	while (optrTop != '=' || ch != '=')
	{	
		if (isdigit(ch) || ch == '.')
		{	
			cin.putback(ch);			// 将字符ch放回输入流
			cin >> operand;				// 读入操作数
			opnd.Push(operand);			// 操作数入opnd栈 
			priorChar = '0';			// 前一字符不是操作符, 规定前一字符为'0'
			ch = GetChar();				// 读入下一个字符
		}
		else if(!IsOperator(ch))
		{	// 既不是操作符,也不属于操作数
			throw ("表达式有错!");// 抛出异常
		}
		else
		{	// ch为操作符
			if ((priorChar == '=' || priorChar == '(') && (ch == '+' || ch == '-'))
			{
				opnd.Push(0);			// ch为单目运算符+-, 在其前面加上操作数0
				priorChar = '0';		// 前一字符不是操作符, 规定前一字符为'0'
			}
			if (optrTop == ')' && ch == '(' || optrTop == '(' && ch == '=' || optrTop == '=' && ch == ')')
				 throw Error("表达式有错!");	
			else if	(optrTop == '(' && ch == ')')
			{	// 去括号
				if (optr.Pop(optrTop) == UNDER_FLOW) throw Error("表达式有错!");	
					// 抛出异常
			    ch = GetChar();			// 读入新字符
			    priorChar = ')';		// 新的前一字符为)
			}
			else if (ch == '(' || OperPrior(optrTop) < OperPrior(ch))
			{	// optrTop为(,或optrTop比ch的优先级低
				optr.Push(ch);			// ch入optr栈
			    priorChar = ch;			// 新的前一字符为ch
				ch = GetChar();			// 读入新字符
			}
			else
			{	// optrTop的大于或等于ch的优先级
				if (optr.Pop(op) == UNDER_FLOW) throw Error("表达式有错!");	
					// 抛出异常
				ElemType left, right;	// 操作数
				Get2Operands(left, right);				// 从opnd栈中取操作数
				opnd.Push(Operate(left, op, right));	// 运算结果入opnd栈
			}
		}
		if (optr.Top(optrTop) == UNDER_FLOW) throw Error("表达式有错!");// 抛出异常
			// 取出optr栈的栈顶
	}
	if (opnd.Top(operand) == UNDER_FLOW) throw Error("表达式有错!");	// 抛出异常
	cout << operand << endl;			// 显示表达式的值
};

#endif
