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

void HanoiTower::solve(int n, int start, int goal, int temp){
	/* Since tower 2 would contain N + 1 to 2N rings we also 
	 * need to move those as well. Those should all be moved
	 * first since they are going to be larger. Since they are
	 * larger it is really like two sub problems. First solve 
	 * N + 1 to 2N then you will be able to solve 1 to N.
	 */
	solve_prime(n, start + 1, goal, temp - 1);
	solve_prime(n, start, goal, temp);
}