#include <stdexcept>
#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"

using namespace std;

int main(int ac, char** av)
{
    try {
        return CommandLineTestRunner::RunAllTests(ac, av);
    }
    catch (logic_error &e) {
        cerr << "An error occurred: " << e.what() << endl;
    }
}
