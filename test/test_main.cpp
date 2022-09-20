#include <gtest.h>
//my changes
#include"tbitfield.h"
//eto ochen' vazhnii komentarii


// bf1 = 0011
// bf2 = 01010
int main(int argc, char **argv) {
    
    //TBitField a(10);
    //a.SetBit(3);
    //std::cout << "c)" << (a);
    //return 0;


    //TBitField a(32),b(17),c(0);
    //std::cin >> a;
    //std::cout << "a)" << a<<std::endl;
    //std::cin >> b;
    //std::cout<< "\n" << "b)" << b << std::endl;    
    //std::cout <<"c)" << (a|b);
    //return 0;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
