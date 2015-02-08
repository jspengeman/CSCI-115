#include <vector>
#include <array>

class HanoiTower {
	public:
		HanoiTower(int n);
		void display();
		void move(int start, int goal);
		void solve(int n, int start, int goal, int temp);
		void solve_prime(int n, int start, int goal, int temp);
	private:
		std::array<std::vector<int>, 3> rings;
};