#include <iostream>
#include <string> 
#include <fstream> 
#include <vector>
#include <iterator>
#include <sstream>
#include <cstdlib>

using namespace std; 
//Проблема в неправильном переводе из чара в инт длины строки + если длина больше всех слов, то ниче не выводится. Куда въебать галочку для проверки вывода?? где обнулять??
int main(int const argc, char* argv[]) {
    //Проверка на работоспособность

    if (argc < 3) {
        std::cerr << "Incorrect input data" << endl;
        return 1;
    }

    std::cout << argc << " " << argv[1] << " " << argv[2] << std::endl;
    std::cout << "it worked!" << endl;


    //открытие файла и подготовка необходимых переменных
    std::ifstream input;
    input.open(argv[2]);

    if (!input) {
        std::cerr << "Errors with reading file " << argv[2] << endl;
        return 1;
    }

    std::string readString;
    std::vector<std::string> current_string;
    int length = std::atoi(argv[1]);
    std::cout << length << endl;
    int spaces;

    //Начиныаем считывание строк
    while (std::getline(input, readString)) {
        //std::cout << readString << endl;
        //Делим текущую строку на слова
        std::istringstream iss(readString);
        std::vector<std::string> words((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
        std::string result;

        for (const auto& word : words) {
            //Прорабатываем случай того, что слово слишком большое 
            //if (word == "my") {
            //    std::cout << word.size() << " " << length << endl;
            //}
            if (word.size() > length) std::cerr << "Word " << word << " is too long to be placed on a line" << endl;

            //Прорабатываем случай того, что слово уже не влазит в строчку (1 вставляем для пробела нового)
            else if (result.size() + word.size() +1 > length) {
                spaces = (length - (int)result.size())/2;
                for (int i = 0; i < spaces; i++) {
                    std::cout << " ";
                }
                std::cout << result << endl;
                result.clear();
                result+=word;
            }
            //Если слово вмещается, добавляем проблем перед ним и само слово в текущую строку
            else {
                result += " ";
                result += word;
            }
        }

        //Вывод последней незаполненной строки
        //if (result.size() > 0) {

        //}

    }


    input.close();

    return 0;
}