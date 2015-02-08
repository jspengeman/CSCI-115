#include "hanoi.h"
using namespace std;

HanoiTower::HanoiTower(int n){
	// Sequantially stacks all rings postion 0 being
	// the top and postion n being the bottom of the tower

	// Intializes first ring from 1 to n
	for (int s = 1; s <= n; s++){
		rings[0].push_back(s);
	}

	// Intializes second ring from n+1 to 2n
	// for (int s = n + 1; s <= 2 * n; s++){
	// 	rings[1].push_back(s);
	// }
}

void HanoiTower::display(){
	for (int i = 0; i <= 2; i++){
		int size = rings[i].size();
		cout << "Tower " << i << ": ";
		if (rings[i].empty() != true){
			for (int j = 0; j < size; j++){
				cout << rings[i][j] << " ";
			}
		}
		cout << endl;
	}
}

void HanoiTower::move(int start, int goal){
	// Takes the top ring from pole start and moves it to pole goal
	int temp_ring = rings[start][0];
	rings[start].erase(rings[start].begin());
	rings[goal].insert(rings[goal].begin(), temp_ring);
}

void HanoiTower::solve(int n, int start, int goal, int temp){
	if (n == 0) return; 
	solve(n - 1, start, temp, goal);
	move(start, goal);
	solve(n - 1, temp, goal, start);

	// solve(n - 1, start + 1, goal, temp - 1);
	// move(start, goal);
	// solve(n - 1, temp - 1, goal, start + 1);
}