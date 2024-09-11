#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <cstdlib>

template <typename T, typename Alloc = std::allocator<T>>
struct Point {
    T x, y;
    Point(T _x, T _y) : x(_x), y(_y) {}
};

template <typename T, typename Alloc = CustomAllocator<T>>
struct AABB {
    Point<T, Alloc> center;
    T halfWidth, halfHeight;

    AABB(const Point<T, Alloc>& _center, T hw, T hh)
        : center(_center), halfWidth(hw), halfHeight(hh) {}

    bool contains(const Point<T, Alloc>& point) const {
        return (point.x >= center.x - halfWidth && point.x <= center.x + halfWidth &&
                point.y >= center.y - halfHeight && point.y <= center.y + halfHeight);
    }

    bool intersects(const AABB<T, Alloc>& other) const {
        return !(other.center.x - other.halfWidth > center.x + halfWidth ||
                 other.center.x + other.halfWidth < center.x - halfWidth ||
                 other.center.y - other.halfHeight > center.y + halfHeight ||
                 other.center.y + other.halfHeight < center.y - halfHeight);
    }
};

template <typename T, typename Alloc = CustomAllocator<T>>
class QuadTree {
private:
    const size_t capacity;
    AABB<T, Alloc> boundary;
    std::vector<Point<T, Alloc>, Alloc> points;
    bool divided;
    std::unique_ptr<QuadTree> northeast, northwest, southeast, southwest;

    void subdivide() {
        T x = boundary.center.x;
        T y = boundary.center.y;
        T hw = boundary.halfWidth / 2;
        T hh = boundary.halfHeight / 2;

        northeast = std::make_unique<QuadTree>(
            AABB<T, Alloc>(Point<T, Alloc>(x + hw, y - hh), hw, hh), capacity);
        northwest = std::make_unique<QuadTree>(
            AABB<T, Alloc>(Point<T, Alloc>(x - hw, y - hh), hw, hh), capacity);
        southeast = std::make_unique<QuadTree>(
            AABB<T, Alloc>(Point<T, Alloc>(x + hw, y + hh), hw, hh), capacity);
        southwest = std::make_unique<QuadTree>(
            AABB<T, Alloc>(Point<T, Alloc>(x - hw, y + hh), hw, hh), capacity);

        divided = true;
    }

public:
    QuadTree(const AABB<T, Alloc>& _boundary, size_t _capacity)
        : boundary(_boundary), capacity(_capacity), divided(false) {}

    bool insert(const Point<T, Alloc>& point) {
        if (!boundary.contains(point)) {
            return false;
        }

        if (points.size() < capacity) {
            points.push_back(point);
            return true;
        }

        if (!divided) {
            subdivide();
        }

        if (northeast->insert(point)) return true;
        if (northwest->insert(point)) return true;
        if (southeast->insert(point)) return true;
        if (southwest->insert(point)) return true;

        return false;
    }

    void query(const AABB<T, Alloc>& range, std::vector<Point<T, Alloc>, Alloc>& found) const {
        if (!boundary.intersects(range)) {
            return;
        }

        for (const Point<T, Alloc>& p : points) {
            if (range.contains(p)) {
                found.push_back(p);
            }
        }

        if (divided) {
            northeast->query(range, found);
            northwest->query(range, found);
            southeast->query(range, found);
            southwest->query(range, found);
        }
    }
};
