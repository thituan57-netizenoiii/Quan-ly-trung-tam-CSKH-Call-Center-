#include <iostream>

using namespace std;

int main() {
	int n;
	cout <<"Nhap vao 1 so: ";
	cin>>n;
	if(n<=2){
		cout<<"Khong phai so nguyen to."<<endl;
		return 0;
	}
	else{
	for(int i=2; i<=n-1; i++)
	if(n%i==0){
		cout<<"Khong phai so nguyen to."<<endl;
			return 0;
	}
	else{
		cout<<"So nguyen to."<<endl;
			return 0;
	}
    }
}
