#include <lib/adapters.cpp>
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <map>

#include <ranges>

bool is_devided_by_twoo(std::pair<int, int> x) {
    return (x.first % 2 == 0);
}

bool is_devided_by_twoo_int(int x) {
    return (x % 2 == 0);
}

std::pair<int,int> mult_2(std::pair<int, int> x) {
    return std::make_pair(x.first * 2, x.second) ;
}

int mult_2_int(int x) {
    return x * 2;
}

bool mod_2(int x) {
    return x % 2;
}

TEST(adaptersTestSuite, UltraMapTest) {
    std::map<int, int> g {
        {0, 1},
        {2, 3},
        {3, 0},
        {4, 4},
        {5, 2},
        {6, 5},
        {8, 6},
        {10, 7},
        {12, 8},
        {14, 9},
    };

    auto y = drop(g, 2); // 3, 4, 5, 6, 8, 10, 12, 14
    auto q = take(y, 7); // 3, 4, 5, 6, 8, 10, 12
    auto t = filter(q, is_devided_by_twoo); // 4, 6, 8, 10, 12
    auto r = reverse(t); // 12, 10, 8, 6, 4
    auto rr = reverse(r); // 4, 6, 8, 10, 12
    auto rrr = reverse(rr); // 12, 10, 8, 6, 4
    auto m = transform(rrr, mult_2); // 24, 20, 16, 12, 8
    auto keys_ = keys(m); // 24, 20, 16, 12, 8
    auto values_ = values(m); //

    std::vector<int> right_answer_keys {24, 20, 16, 12, 8};
    int c_keys = 0;
    for (auto element: keys_) {
        ASSERT_EQ(element, right_answer_keys[c_keys]);
        ++c_keys;
    }

    std::vector<int> right_answer_values {8, 7, 6, 5, 4};
    int c_values = 0;
    for (auto element: values_) {
        ASSERT_EQ(element, right_answer_values[c_values]);
        ++c_values;
    }
}

TEST(adaptersTestSuite, UltraVectorTest) {
    std::vector<int> g {0, 2, 3, 4, 5, 6, 8, 10, 12, 14};

    auto y = drop(g, 2); // 3, 4, 5, 6, 8, 10, 12, 14
    auto q = take(y, 7); // 3, 4, 5, 6, 8, 10, 12
    auto t = filter(q, is_devided_by_twoo_int); // 4, 6, 8, 10, 12
    auto r = reverse(t); // 12, 10, 8, 6, 4
    auto rr = reverse(r); // 4, 6, 8, 10, 12
    auto rrr = reverse(rr); // 12, 10, 8, 6, 4
    auto m = transform(rrr, mult_2_int); // 24, 20, 16, 12, 8

    std::vector<int> right_answer_keys {24, 20, 16, 12, 8};
    int c_keys = 0;
    for (auto element: m) {
        ASSERT_EQ(element, right_answer_keys[c_keys]);
        ++c_keys;
    }
}

TEST(adaptersTestSuite, UltraMapTestStick) {
    std::map<int, int> g {
            {0, 1},
            {2, 3},
            {3, 0},
            {4, 4},
            {5, 2},
            {6, 5},
            {8, 6},
            {10, 7},
            {12, 8},
            {14, 9},
    };


    auto keys_ = g | drop(2) | take(7) | filter(is_devided_by_twoo)
                                    | reverse() | reverse() | reverse() | transform(mult_2) | keys();
    auto values_ = g | drop(2) | take(7) | filter(is_devided_by_twoo)
                 | reverse() | reverse() | reverse() | transform(mult_2) | values();


    std::vector<int> right_answer_keys {24, 20, 16, 12, 8};
    int c_keys = 0;
    for (auto element: keys_) {
        ASSERT_EQ(element, right_answer_keys[c_keys]);
        ++c_keys;
    }

    std::vector<int> right_answer_values {8, 7, 6, 5, 4};
    int c_values = 0;
    for (auto element: values_) {
        ASSERT_EQ(element, right_answer_values[c_values]);
        ++c_values;
    }
}

TEST(adaptersTestSuite, UltraVectorTestStick) {
    std::vector<int> g {0, 2, 3, 4, 5, 6, 8, 10, 12, 14};

    auto m = g | drop(2) | take(7) | filter(is_devided_by_twoo_int)
             | reverse() | reverse() | reverse() | transform(mult_2_int);

    std::vector<int> right_answer_keys {24, 20, 16, 12, 8};
    int c_keys = 0;
    for (auto element: m) {
        ASSERT_EQ(element, right_answer_keys[c_keys]);
        ++c_keys;
    }
}

TEST(adaptersTestSuite, UltraConstMapTest) {
    const std::map<int, int> g {
            {0, 1},
            {2, 3},
            {3, 0},
            {4, 4},
            {5, 2},
            {6, 5},
            {8, 6},
            {10, 7},
            {12, 8},
            {14, 9},
    };

    auto y = drop(g, 2); // 3, 4, 5, 6, 8, 10, 12, 14
    auto q = take(y, 7); // 3, 4, 5, 6, 8, 10, 12
    auto t = filter(q, is_devided_by_twoo); // 4, 6, 8, 10, 12
    auto r = reverse(t); // 12, 10, 8, 6, 4
    auto rr = reverse(r); // 4, 6, 8, 10, 12
    auto rrr = reverse(rr); // 12, 10, 8, 6, 4
    auto m = transform(rrr, mult_2); // 24, 20, 16, 12, 8
    auto keys_ = keys(m); // 24, 20, 16, 12, 8
    auto values_ = values(m); //

    std::vector<int> right_answer_keys {24, 20, 16, 12, 8};
    int c_keys = 0;
    for (auto element: keys_) {
        ASSERT_EQ(element, right_answer_keys[c_keys]);
        ++c_keys;
    }

    std::vector<int> right_answer_values {8, 7, 6, 5, 4};
    int c_values = 0;
    for (auto element: values_) {
        ASSERT_EQ(element, right_answer_values[c_values]);
        ++c_values;
    }
}

TEST(adaptersTestSuite, UltraConstVectorTest) {
    const std::vector<int> g {0, 2, 3, 4, 5, 6, 8, 10, 12, 14};

    auto y = drop(g, 2); // 3, 4, 5, 6, 8, 10, 12, 14
    auto q = take(y, 7); // 3, 4, 5, 6, 8, 10, 12
    auto t = filter(q, is_devided_by_twoo_int); // 4, 6, 8, 10, 12
    auto r = reverse(t); // 12, 10, 8, 6, 4
    auto rr = reverse(r); // 4, 6, 8, 10, 12
    auto rrr = reverse(rr); // 12, 10, 8, 6, 4
    auto m = transform(rrr, mult_2_int); // 24, 20, 16, 12, 8

    std::vector<int> right_answer_keys {24, 20, 16, 12, 8};
    int c_keys = 0;
    for (auto element: m) {
        ASSERT_EQ(element, right_answer_keys[c_keys]);
        ++c_keys;
    }
}

TEST(adaptersTestSuite, UltraConstMapTestStick) {
    const std::map<int, int> g {
            {0, 1},
            {2, 3},
            {3, 0},
            {4, 4},
            {5, 2},
            {6, 5},
            {8, 6},
            {10, 7},
            {12, 8},
            {14, 9},
    };


    auto keys_ = g | drop(2) | take(7) | filter(is_devided_by_twoo)
                 | reverse() | reverse() | reverse() | transform(mult_2) | keys();
    auto values_ = g | drop(2) | take(7) | filter(is_devided_by_twoo)
                   | reverse() | reverse() | reverse() | transform(mult_2) | values();


    std::vector<int> right_answer_keys {24, 20, 16, 12, 8};
    int c_keys = 0;
    for (auto element: keys_) {
        ASSERT_EQ(element, right_answer_keys[c_keys]);
        ++c_keys;
    }

    std::vector<int> right_answer_values {8, 7, 6, 5, 4};
    int c_values = 0;
    for (auto element: values_) {
        ASSERT_EQ(element, right_answer_values[c_values]);
        ++c_values;
    }
}

TEST(adaptersTestSuite, UltraConstVectorTestStick) {
    const std::vector<int> g {0, 2, 3, 4, 5, 6, 8, 10, 12, 14};

    auto m = g | drop(2) | take(7) | filter(is_devided_by_twoo_int)
             | reverse() | reverse() | reverse() | transform(mult_2_int);

    std::vector<int> right_answer_keys {24, 20, 16, 12, 8};
    int c_keys = 0;
    for (auto element: m) {
        ASSERT_EQ(element, right_answer_keys[c_keys]);
        ++c_keys;
    }
}

TEST(adaptersTestSuite, VectorCharTakeDropTest) {
    std::vector<char> symbols {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    std::vector<char> answer {'3', '4', '5', '6', '7'};

    auto res = symbols | take(8) | drop(1) | take(8) | drop(1) | take(0) | drop(0);

    int c = 0;
    for (auto element: res) {
        ASSERT_EQ(element, answer[c]);
        ++c;
    }
}

TEST(adaptersTestSuite, VectorIntReverseTest) {
    std::vector<int> number {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> reversed_numbers {8, 7, 6, 5, 4, 3, 2, 1};

    auto res = number | reverse() | reverse() | reverse() | reverse() | reverse();

    int c = 0;
    for (auto element: res) {
        ASSERT_EQ(element, reversed_numbers[c]);
        ++c;
    }
}

int square(int x) { return x * x; }

TEST(adaptersTestSuite, VectorTransformTest) {
    std::vector<int> numbers {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    auto res = numbers | transform(square) | transform(square) | transform(square);

    int c = 0;
    for (auto element: res) {
        ASSERT_EQ(element, square(square(square(numbers[c]))));
        ++c;
    }
}

TEST(adaptersTestSuite, UltraVectorDetailedTest) {
    std::vector<int> g {0, 2, 3, 4, 5, 6, 8, 10, 12, 14};


    std::vector<int> y_ans {3, 4, 5, 6, 8, 10, 12, 14};
    std::vector<int> q_ans {3, 4, 5, 6, 8, 10, 12};
    std::vector<int> t_ans {4, 6, 8, 10, 12};
    std::vector<int> r_ans {12, 10, 8, 6, 4};
    std::vector<int> rr_ans {4, 6, 8, 10, 12};
    std::vector<int> rrr_ans {12, 10, 8, 6, 4};
    std::vector<int> m_ans {24, 20, 16, 12, 8};

    auto y = drop(g, 2); // 3, 4, 5, 6, 8, 10, 12, 14
    auto q = take(y, 7); // 3, 4, 5, 6, 8, 10, 12
    auto t = filter(q, is_devided_by_twoo_int); // 4, 6, 8, 10, 12
    auto r = reverse(t); // 12, 10, 8, 6, 4
    auto rr = reverse(r); // 4, 6, 8, 10, 12
    auto rrr = reverse(rr); // 12, 10, 8, 6, 4
    auto m = transform(rrr, mult_2_int); // 24, 20, 16, 12, 8

    int c;
    c = 0;
    for (auto element: y) {
        ASSERT_EQ(element, y_ans[c]);
        ++c;
    }

    c = 0;
    for (auto element: q) {
        ASSERT_EQ(element, q_ans[c]);
        ++c;
    }

    c = 0;
    for (auto element: t) {
        ASSERT_EQ(element, t_ans[c]);
        ++c;
    }

    c = 0;
    for (auto element: r) {
        ASSERT_EQ(element, r_ans[c]);
        ++c;
    }

    c = 0;
    for (auto element: rr) {
        ASSERT_EQ(element, rr_ans[c]);
        ++c;
    }

    c = 0;
    for (auto element: rrr) {
        ASSERT_EQ(element, rrr_ans[c]);
        ++c;
    }

    c = 0;
    for (auto element: m) {
        ASSERT_EQ(element, m_ans[c]);
        ++c;
    }

    std::vector<int> right_answer_keys {24, 20, 16, 12, 8};
    int c_keys = 0;
    for (auto element: m) {
        ASSERT_EQ(element, right_answer_keys[c_keys]);
        ++c_keys;
    }
}

bool filter1(int x) { return x % 2 == 0; }

bool filter2(int x) { return x % 5 == 0; }

TEST(adaptersTestSuite, VectorFilterTest) {
    std::vector<int> numbers {3, 4, 5, 6, 8, 10, 12, 20, 30};
    std::vector<int> ans {10, 20, 30};

    auto res = numbers | filter(filter1) | filter(filter2);

    int c = 0;
    for (auto element: res) {
        ASSERT_EQ(element, ans[c]);
        ++c;
    }
}






