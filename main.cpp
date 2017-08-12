#include <iostream>
#include "Vec3.h"
#include "Ray.h"


int main() {
    Ray r(Vec3(0,0,0),Vec3(1,1,0));
    Vec3 res;
    if(r.intersect_sphere(Sphere(Vec3(2,2,0),1),res)){
      std::cout << res.to_string() << std::endl;
    } else {
      std::cout << "No intersections" << std::endl;
    }
    return 0;
}