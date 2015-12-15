/* 1fe=12in
///	1yd=3fe
///	1mi=1760yd
///
///	This program convert degrees.
/// For example, "10 f i" -> "120.000000"
///"20 i y" -> "0.555556"
*/

#include <stdio.h>
int main(void){
	double amount;
	char fromUnit,toUnit;
	int from=0,to=0;
	scanf("%lf %c %c",&amount,&fromUnit,&toUnit);
	if(fromUnit=='i')
		from=1;
	else if(fromUnit=='f')
		from=2;
	else if(fromUnit=='y')
		from=3;
	else if(fromUnit=='m')
		from = 4;
	else
		from = 0;
			
	if(toUnit=='i')
		to=1;
	else if(toUnit=='f')
		to=2;
	else if(toUnit=='y')
		to=3;
	else if(toUnit=='m')
		to = 4;
	else
		to=0;
	
	while(1)
	{
		if(from == to)
		{
			printf("%.6lf\n",amount);return 0;
		}
		if(to>from)
		{
			switch(from)
			{
				case 1:
					amount/=12;
					from++;
					break;
				case 2:
					amount/=3;
					from++;
					break;
				case 3:
					amount/=1760;
					from++;
					break;
				default:
					from=to;
					break;
			}
		}
		else
		{
			switch(from)
			{
				case 4:
					amount*=1760;
					from--;
					break;
				case 3:
					amount*=3;
					from--;
					break;
				case 2:
					amount*=12;
					from--;
					break;
				default:
					from=to;
					break;
			}
		}
	}

}
