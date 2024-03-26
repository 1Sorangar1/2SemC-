#include <iostream>
#include <string> 
#include <fstream> 

using namespace std; 

int main() {
    std::string s;
    std::ifstream file("input.txt"); 


    while (std::getline(file, s)) {
        cout << s << endl;
    }

    file.close();

    return 0;
}