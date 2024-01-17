#include <iostream>
#include <iomanip>
using namespace std;
int main() {
	cout<<"Please enter the number:";
	double num, temp = 0;
	cin>>num;
	if (num % 2 == 0) {
		temp = num / 2;
	} else if ((num + 1) % 2 == 0)) {
		temp = ((num + 1))) / 2;
	}
	cout<<"The number is: " << temp << endl;

return 0;
