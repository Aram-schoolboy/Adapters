#include <lib/adapters.cpp>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

bool foo(std::pair<int, int> x) {
    return (x.first % 2 == 0);
}

std::pair<int,int> trans(std::pair<int, int> x) {
    return std::make_pair(x.first * 2, x.second) ;
}
bool filter1(int x) { return x % 2 == 0; }

bool filter2(int x) { return x % 5 == 0; }
bool boo(int x) {
    return x % 2 == 0;
}
int main() {
    std::vector<int> numbers {3, 4, 5, 6, 8, 10, 12};
    std::vector<int> ans {5};

    std::cout << "dffdsfs";
    auto res = numbers | filter(filter1);

    auto st1 = res.begin();
    auto st2 = res.end();

//
//    std::cout << (*f.begin()) << ' ' << (*f.end()) << '\n';
//    //std::cout << (*d.begin()) << ' ' << (*d.end()) << '\n';
//
//    auto r = reverse(f);
//
//    std::cout << (*--r.begin()) << ' ' << (*(--r.end())) << '\n';
//
//    auto rr = reverse(r);
//
//    std::cout << (*--rr.begin()) << ' ' << (*--rr.end()) << '\n';
//
//    auto rrr = reverse(rr);
//
//    std::cout << (*--rrr.begin()) << ' ' << (*--rrr.end()) << '\n';
//
//    auto rrrr = reverse(rrr);
//
//    std::cout << (*--rrrr.begin()) << ' ' << (*--rrrr.end()) << '\n';
//

//    return 0;
//    std::map<int, int> g {
//        {0, 1},
//        {2, 3},
//        {3, 0},
//        {4, 4}, // 4
//        {5, 2},
//        {6, 5}, // 5
//        {8, 6}, // 6
//        {10, 7}, // 7
//        {12, 8}, // 8
//        {14, 9}
//    };
//
//    auto y = drop(g, 2); // 3, 4, 5, 6, 8, 10, 12, 14
//    auto q = take(y, 7); // 3, 4, 5, 6, 8, 10, 12
//    auto t = filter(q, foo); // 4, 6, 8, 10, 12
//
//
//    auto r = reverse(t); // 12, 10, 8, 6, 4
//    auto rr = reverse(r); // 12, 10, 8, 6, 4
//    auto rrr = reverse(rr); // 12, 10, 8, 6, 4
//    auto rrrr = reverse(rrr); // 12, 10, 8, 6, 4
//    auto m = transform(rrrr, trans); // 24, 20, 16, 12, 8
//
//    auto keys_ = keys(m);
//
//    for (auto el: keys_) {
//        std::cout << el << ' ';
//    } std::cout << '\n';

//    for (auto el: keys_) {
//        std::cout << el << ' ';
//    } std::cout << '\n';
//
//    std::vector<int> start {1, 2, 3, 4, 5, 6};
//
//    auto w = reverse(start);
//    auto ww = reverse(w);
//    auto www = reverse(ww);
//    auto wwww = reverse(www);
//    auto wwwww = reverse(wwww);
//
//    for (auto el: wwwww) {
//        std::cout << el << ' ';
//    } std::cout << '\n';

//    auto st = r.end();
//    auto fn = r.begin();

//    std::cout << (*st)<< ' ' << (*fn);
//    return 0;

//    while (st != fn) {
//        std::cout << *st << ' ';
//        --st;
//    } std::cout << '\n';

//    for (auto el: t) {
//        std::cout << el << ' ';
//    } std::cout << '\n';

//    auto rev2 = reverse(g);
//    auto st = rev2.begin();
//    auto fn = rev2.end();
//
//    while (st != fn) {
//        std::cout << *st << ' ';
//        ++st;
//    } std::cout << '\n';
//    for (auto el:  rev2) {
//        std::cout << el << ' ';
//    }; std::cout << '\n';
//
//
//
//    auto view = take(g, 4);
//
//    for (auto el:  take(g, 2)) {
//        std::cout << el << ' ';
//    }; std::cout << '\n';
//
//    for (auto el: view) {
//        std::cout << el << ' ';
//    }; std::cout << '\n';
//
//    auto filt = filter(view, foo);
//
//    for (auto el: filt) {
//        std::cout << el << ' ';
//    }; std::cout << '\n';
//
//    auto rev = reverse(view);
//
//    for (auto el: rev) {
//        std::cout << el << ' ';
//    }; std::cout << '\n';

//    for (auto el: rev) {
//        std::cout << el << ' ';
//    } std::cout << '\n';

//    auto st1 = rev.begin();
//    auto fn1 = rev.end();
//
//    std::cout << (st1 == fn1);
//
//    while (st1 != fn1) {
//        std::cout << *st << ' ';
//        ++st;
//        std::cout << "bruh ";
//    }

    return 0;

    return 0;
}