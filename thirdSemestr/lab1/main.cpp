#include <iostream>
#include "src/All.hpp"
#include "src/catch/include/catch.hpp"





int main() {

//    auto mStorage = IPv4::fromString("122.222.121.111");
//    std::cout << mStorage.address();
//
//    auto b = IPv6::fromString("1111:A22:3F3:4444::FF66:A777:88E8");
//    std::cout << '\n' << b.address();
//
//    std::cout << "\n\n " << utils::to_hex(34454) << " " << utils::to_int("1A8");
//
//    auto c = MAC::fromString("52:74:f2:b1:a8:7f");
//    std::cout << '\n' << c.address();
//    std::cout << "\n\n" << IPv6::fromIPv4(mStorage).address();
//    std::cout << "\n\n" << IPv6::fromMAC(c).address();

//    Stack::Listbased <std::string> a;
//    Stack::Arraybased <std::string, 100> b;
//    Stack::STLImpl <std::string> f;
//    Queue::Listbased <std::string> c;
//    Queue::Arraybased <std::string, 100> d;
//    Queue::STLImpl <std::string> e;
//
//    a.push("1");
//    b.push("1");
//    f.push("1");
//    c.push("1");
//    d.push("1");
//    e.push("1");
//
//    a.push("2");
//    b.push("2");
//    f.push("2");
//    c.push("2");
//    d.push("2");
//    e.push("2");
//
//    a.push("3");
//    b.push("3");
//    f.push("3");
//    c.push("3");
//    d.push("3");
//    e.push("3");
//
//    std::cout << a.top() << ' ' << b.top() << ' ' << f.top() << ' '
//              << c.front() << ' ' << d.front() << ' ' << e.front() << '\n';
//
//    a.pop();
//    b.pop();
//    f.pop();
//    c.pop();
//    d.pop();
//    e.pop();
//
//    a.pop();
//    b.pop();
//    f.pop();
//    c.pop();
//    d.pop();
//    e.pop();
//
//    std::cout << a.top() << ' ' << b.top() << ' ' << f.top() << ' '
//              << c.front() << ' ' << d.front() << ' ' << e.front() << '\n';
//
//    std::cout << a.size() <<' ';

    Deque::Arraybased <int, 100> a;
    Deque::LibImpl <int> b;
    Deque::Listbased <int> c;

    a.pushBack(4);
    b.pushBack(4);
    c.pushBack(4);
    a.pushBack(12);
    b.pushBack(12);
    c.pushBack(12);
    a.pushFront(2);
    b.pushFront(2);
    c.pushFront(2);

//    std::cout << a.top() << "  " << b.top() << "  " << c.top() << '\n';
//
//    int var;
//
//    std::cout << *c.begin() << "  " << *(c.begin()+1) << "  " << *(c.begin()+2);
//    if (c.begin() + 3 == c.end())
//        std::cout << 'f';
//
//    for (auto i = c.begin(); i != c.end(); ++i)
//        std::cout << *i;
//    std::cout << '\n';
//
//
//    std::cout << a.size() << "  " << b.size() << " " << c.size() << '\n';
//
//    std::cout << c[1];

    return 0;
}
