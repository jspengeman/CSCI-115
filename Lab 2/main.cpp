#include <iostream>
#include "hanoi.cpp"

using namespace std;

int main(){
	int n;
	cout << "Enter an integer: ";
	cin >> n;
	HanoiTower hanoi_tower(n);
	hanoi_tower.display();
	hanoi_tower.solve(n);
	hanoi_tower.display();
}