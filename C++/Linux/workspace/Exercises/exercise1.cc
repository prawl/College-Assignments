
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

main ()
{

	int numToPurchase;
	int totCost;

	cout<<"Please enter the amount of x you are purchasing."<<endl;
	cin>>numToPurchase;

	if(numToPurchase<=1000)
	{
		totCost = (numToPurchase * 1);
		cout<<"Your total cost is " <<totCost<<" dollars."<<endl;
	}

	else if (numToPurchase <=20000)
	{
		totCost = 10000 + .90 * (numToPurchase - 10000);
		cout<<"Your total cost is " <<totCost<<" dollars."<<endl;
	}

	else if (numToPurchase <= 30000)
	{
		totCost = 19000 + .80 * (numToPurchase - 20000);
		cout<<"Your total cost is " <<totCost<<" dollars."<<endl;
	}

	else 
	{
		totCost = 27000 + .70 * (numToPurchase - 30000);
		cout<<"Your total cost is " <<totCost<<" dollars."<<endl;
	}

return 0;
}
