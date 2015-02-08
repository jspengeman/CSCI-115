#include <iostream>
#include "hanoi.cpp"

using namespace std;

int main(){
	HanoiTower hanoi_tower(5);
	hanoi_tower.display();
	hanoi_tower.solve(5, 0, 2, 1);
	hanoi_tower.display();
}