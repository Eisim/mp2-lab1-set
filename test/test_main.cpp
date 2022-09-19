#include <gtest.h>
//my changes
#include"tbitfield.h"
//eto ochen' vazhnii komentarii

int main(int argc, char **argv) {
    TBitField a(32),b(17),c(0);
    std::cin >> a;
    std::cout << "a)" << a<<std::endl;
    std::cin >> b;
    std::cout<< "\n" << "b)" << b << std::endl;


    c = a | b;
    std::cout <<"c)" << c;
    return 0;

    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
}
