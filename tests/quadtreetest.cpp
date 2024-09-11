#include "../headers/Trees/quadTree.cpp"
#include <cassert>

void test_insert() {
    AABB<float> boundary(Point<float>(0, 0), 200, 200);
    QuadTree<float> qt(boundary, 4);

    assert(qt.insert(Point<float>(50, 50)) == true);
    assert(qt.insert(Point<float>(-50, -50)) == true);
    assert(qt.insert(Point<float>(-100, 100)) == true);
    assert(qt.insert(Point<float>(150, -150)) == true);
    assert(qt.insert(Point<float>(-100, -100)) == true); // Should trigger subdivision
}

void test_query() {
    AABB<float> boundary(Point<float>(0, 0), 200, 200);
    QuadTree<float> qt(boundary, 4);

    qt.insert(Point<float>(50, 50));
    qt.insert(Point<float>(-50, -50));
    qt.insert(Point<float>(-100, 100));
    qt.insert(Point<float>(150, -150));
    qt.insert(Point<float>(-100, -100));

    AABB<float> range(Point<float>(0, 0), 100, 100);
    std::vector<Point<float>> found;

    qt.query(range, found);

    assert(found.size() == 2); // Only (50, 50) and (-50, -50) are inside range
}

void run_tests() {
    test_insert();
    test_query();
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    run_tests();
    return 0;
}
