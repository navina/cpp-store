class Tuple {
public:
    Tuple(int one, int two) {
        a = one;
        b = two;
    }
    int sum() {
        return a+b;
    }

private:
    int a;
    int b;
};