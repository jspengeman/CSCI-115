#include <vector>
#include <array>

class HanoiTower {
	public:
		HanoiTower();
		void move();
		void TOH();
	private:
		std::array<std::vector<int>, 3> rings;
};