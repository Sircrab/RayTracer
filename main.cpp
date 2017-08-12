#include <iostream>
#include "Vec3.h"


int main() {
    Vec3 v = Vec3(0.5,3.8,7.6);
    Vec3 v2 = Vec3(1,4,7);
    std::cout << (v + v2).to_string() << std::endl;
    return 0;
}