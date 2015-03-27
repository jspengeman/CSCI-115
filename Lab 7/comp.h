class Max {
public:
    template <typename T>
    static bool prior (T a, T b) {
        return a > b;
    }
};

class Min {
public:
    template <typename T>
    static bool prior (T a, T b) {
        return a < b;
    }
};