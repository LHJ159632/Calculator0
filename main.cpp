#include "utility.h"							
#include "calculator.h"						

int main(void)
{
		bool bYes;								//�Ƿ����
/*���м�����*/
		do
		{
			Calculator<double> objExpression;	
			cout << "������ʽ:" << endl;
			objExpression.Run();				
			cout << "�Ƿ����";
			bYes = UserSaysYes();				
		} while (bYes);							
	return 0;									
}
