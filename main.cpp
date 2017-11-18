#include "utility.h"							
#include "calculator.h"						

int main(void)
{
		bool bYes;								//是否继续
/*运行计算器*/
		do
		{
			Calculator<double> objExpression;	
			cout << "输入表达式:" << endl;
			objExpression.Run();				
			cout << "是否继续";
			bYes = UserSaysYes();				
		} while (bYes);							
	return 0;									
}
