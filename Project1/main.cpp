#include <iostream>
#include <string> 
#include <fstream> 

using namespace std; 

int main(int const arg1, char** arg2) {
    std::string s;

    std::cout << arg1 << " " << arg2[2] << std::endl;
    std::cout << "It worked!" << endl;

    std::ifstream input;
    input.open(arg2[2]);

    while (std::getline(input, s)) {
        cout << s << endl;
    }

    
    input.close();
    return 0;
}