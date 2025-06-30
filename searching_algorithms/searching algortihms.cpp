#include <bits/stdc++.h>
using namespace std;

// ================================ BINARY SEARCH VARIATIONS ================================
class BinarySearch {
public:
    // Standard binary search - find exact value
    template<typename T>
    static int binary_search(vector<T>& arr, T target) {
        int left = 0, right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) return mid;
            if (arr[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1; // Not found
    }

    // Lower bound - first element >= target
    template<typename T>
    static int lower_bound(vector<T>& arr, T target) {
        int left = 0, right = arr.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < target) left = mid + 1;
            else right = mid;
        }
        return left;
    }

    // Upper bound - first element > target
    template<typename T>
    static int upper_bound(vector<T>& arr, T target) {
        int left = 0, right = arr.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] <= target) left = mid + 1;
            else right = mid;
        }
        return left;
    }

    // Binary search on answer - find minimum value that satisfies condition
    template<typename Predicate>
    static long long binary_search_answer(long long left, long long right, Predicate check) {
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (check(mid)) right = mid;
            else left = mid + 1;
        }
        return left;
    }

    // Binary search on floating point
    static double binary_search_real(double left, double right, function<bool(double)> check, double eps = 1e-9) {
        while (right - left > eps) {
            double mid = left + (right - left) / 2;
            if (check(mid)) right = mid;
            else left = mid;
        }
        return left;
    }

    // Binary search on rotated sorted array
    template<typename T>
    static int search_rotated(vector<T>& arr, T target) {
        int left = 0, right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) return mid;

            if (arr[left] <= arr[mid]) { // Left half is sorted
                if (target >= arr[left] && target < arr[mid])
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            else { // Right half is sorted
                if (target > arr[mid] && target <= arr[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return -1;
    }

    // Find peak element (element greater than neighbors)
    template<typename T>
    static int find_peak(vector<T>& arr) {
        int left = 0, right = arr.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] < arr[mid + 1])
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }
};

// ================================ TERNARY SEARCH ================================
class TernarySearch {
public:
    // Ternary search for maximum of unimodal function
    template<typename Function>
    static double find_maximum(double left, double right, Function f, double eps = 1e-9) {
        while (right - left > eps) {
            double m1 = left + (right - left) / 3;
            double m2 = right - (right - left) / 3;

            if (f(m1) < f(m2))
                left = m1;
            else
                right = m2;
        }
        return (left + right) / 2;
    }

    // Ternary search for minimum of unimodal function
    template<typename Function>
    static double find_minimum(double left, double right, Function f, double eps = 1e-9) {
        while (right - left > eps) {
            double m1 = left + (right - left) / 3;
            double m2 = right - (right - left) / 3;

            if (f(m1) > f(m2))
                left = m1;
            else
                right = m2;
        }
        return (left + right) / 2;
    }

    // Integer ternary search
    template<typename Function>
    static long long find_minimum_int(long long left, long long right, Function f) {
        while (right - left > 2) {
            long long m1 = left + (right - left) / 3;
            long long m2 = right - (right - left) / 3;

            if (f(m1) > f(m2))
                left = m1;
            else
                right = m2;
        }

        long long best = left;
        for (long long i = left; i <= right; i++) {
            if (f(i) < f(best))
                best = i;
        }
        return best;
    }

    // 2D Ternary search for finding minimum of bivariate unimodal function
    template<typename Function>
    static pair<double, double> find_minimum_2d(double x1, double x2, double y1, double y2,
        Function f, double eps = 1e-9) {
        double best_x = x1, best_y = y1;

        for (int iter = 0; iter < 100; iter++) {
            if (x2 - x1 < eps && y2 - y1 < eps) break;

            // Ternary search on x
            double mx1 = x1 + (x2 - x1) / 3;
            double mx2 = x2 - (x2 - x1) / 3;

            if (f(mx1, best_y) > f(mx2, best_y))
                x1 = mx1;
            else
                x2 = mx2;

            best_x = (x1 + x2) / 2;

            // Ternary search on y
            double my1 = y1 + (y2 - y1) / 3;
            double my2 = y2 - (y2 - y1) / 3;

            if (f(best_x, my1) > f(best_x, my2))
                y1 = my1;
            else
                y2 = my2;

            best_y = (y1 + y2) / 2;
        }

        return { best_x, best_y };
    }
};

// ================================ COORDINATE COMPRESSION ================================
class CoordinateCompression {
    vector<int> values;
    map<int, int> compress_map;

public:
    CoordinateCompression() {}

    CoordinateCompression(vector<int>& coords) {
        build(coords);
    }

    void add(int val) {
        values.push_back(val);
    }

    void build(vector<int>& coords) {
        values = coords;
        build();
    }

    void build() {
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());

        compress_map.clear();
        for (int i = 0; i < values.size(); i++) {
            compress_map[values[i]] = i;
        }
    }

    int compress(int val) {
        return compress_map[val];
    }

    int decompress(int idx) {
        return values[idx];
    }

    int size() {
        return values.size();
    }

    // Get compressed coordinates for a range
    pair<int, int> compress_range(int l, int r) {
        auto it_l = lower_bound(values.begin(), values.end(), l);
        auto it_r = upper_bound(values.begin(), values.end(), r);

        int left_idx = it_l - values.begin();
        int right_idx = (it_r - values.begin()) - 1;

        return { left_idx, right_idx };
    }

    // For 2D coordinate compression
    static pair<CoordinateCompression, CoordinateCompression> compress_2d(
        vector<pair<int, int>>& points) {

        vector<int> x_coords, y_coords;
        for (auto& p : points) {
            x_coords.push_back(p.first);
            y_coords.push_back(p.second);
        }

        CoordinateCompression x_comp(x_coords);
        CoordinateCompression y_comp(y_coords);

        return { x_comp, y_comp };
    }
};