#include <iostream>
#include <string> 
#include <fstream> 
#include <vector>
#include <iterator>
#include <sstream>

using namespace std; 

int main(int const arg1, char** arg2) {
    //�������� �� �����������������

    //std::cout << arg1 << " " << arg2[2] << std::endl;
    //std::cout << "It worked!" << endl;


    //�������� ����� � ���������� ����������� ����������
    std::ifstream input;
    input.open(arg2[2]);

    if (!input) {
        std::cerr << "Errors with reading file " << arg2[2] << endl;
        return 1;
    }

    std::string readString;
    std::vector<std::string> current_string;
    int length = arg1;
    int spaces;

    //��������� ���������� �����
    while (std::getline(input, readString)) {
        //std::cout << readString << endl;
        //����� ������� ������ �� �����
        std::istringstream iss(readString);
        std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
        std::string result;


        for (const auto& word : words) {
            //������������� ������ ����, ��� ����� ������� ������� 
            if (word == "my") {
                std::cout << word.size() << " " << length << endl;
            }
            if (word.size() > length) std::cerr << "Word " << word << " is too long to be placed on a line" << endl;

            //������������� ������ ����, ��� ����� ��� �� ������ � ������� (1 ��������� ��� ������� ������)
            else if (result.size() + word.size() +1 > length) {
                spaces = (length - result.size()) / 2;
                for (int i = 0; i < spaces; i++) {
                    std::cout << " ";
                }
                std::cout << result << endl;
                result.clear();
                result+=word;
            }
            //���� ����� ���������, ��������� ������� ����� ��� � ���� ����� � ������� ������
            else {
                result += " ";
                result += word;
            }
        }

    }

    input.close();

    return 0;
}