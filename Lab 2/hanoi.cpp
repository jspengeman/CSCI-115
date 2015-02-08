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
	for (int s = n + 1; s <= 2 * n; s++){
		rings[1].push_back(s);
	}
}

void HanoiTower::display(){
	for (int i = 0; i <= 2; i++){
		int size = rings[i].size();
		cout << "Tower " << i << ": ";
		
		for (int j = 0; j < size; j++){
			cout << rings[i][j] << " ";
		}
		cout << endl;
	}
}

void HanoiTower::move(int start, int goal){
	// Takes the top ring from tower start and moves it to tower goal
	cout << "(" << start << ", " << goal << ")" << endl;
	int temp_ring = rings[start][0];
	rings[start].erase(rings[start].begin());
	rings[goal].insert(rings[goal].begin(), temp_ring);
}

void HanoiTower::solve_prime(int n, int start, int goal, int temp){
	// Adapted the solution from the textbook to fit my needs
	if (n == 0) return; 
	solve_prime(n - 1, start, temp, goal);
	move(start, goal);
	solve_prime(n - 1, temp, goal, start);
}

void HanoiTower::solve(int n){
	/* Step 1: Tower 0 contains rings 1 to N and tower 1 contains rings N + 1 to N.
	 * Move rings 1 to N to tower 1 using tower 2 as a spare. This collects all rings
	 * to tower 1.
	 *
	 * Step 2: Tower 1 now contains rings 1 to 2N, now solve prime can be called to 
	 * move all rings on tower 1 to tower 2 using tower 0 as a spare. Solve prime
	 * is called using 2 * n as the size because tower 1 contains all of the rings.
	 */
	solve_prime(n, 0, 1, 2);
	solve_prime(2 * n, 1, 2, 0);
}