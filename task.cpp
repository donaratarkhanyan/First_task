#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>

struct typeInfo {
    std::string type;
    std::string value;
    std::string name;
    size_t pos;
    size_t line;
    
};

std::map<std::string, typeInfo> ti;

std::string change_word(std::string str) {
    std::string tmp = "";
    std::string t {};
    int i = 0;
    std::stringstream s(str);

    while (s >> t) {
        tmp += t[0];
    }
    return tmp;
}

void tokenizing(std::string& part, std::ofstream& out_file, size_t& pos, size_t& line)
{
    std::stringstream iss(part);
    std::vector<std::string> vec;
    std::string word;
    while (iss >> word) {
        vec.push_back(word);
    }
    std::string Name = "";
    std::string Type = "";
    std::string Value = "";
    if (vec.size() > 1) {
        if (vec[vec.size() - 2] == "=") {
            Name = vec[vec.size() - 3];
            Value = vec[vec.size() - 1];
            for (size_t i = 0; i < vec.size() - 3; ++i) {
                Type += vec[i][0];
            }
        } else {
            Name = vec[vec.size() - 1];
            Value = "GARBAGE";
            for (size_t i = 0; i < vec.size() - 1; ++i) {
                Type += vec[i][0];
            }
        }
        ti[Name].name = Name;
        ti[Name].value = Value;
        ti[Name].type = Type;
        ti[Name].pos = pos;
        ti[Name].line = line;

    } else {
        auto it = ti.find(vec[0]);
            if (it != ti.end()) {
                typeInfo& obj = it -> second;
                out_file << std::left
                         << std::setw(25) << obj.type
                         << std::setw(25) << obj.value
                         << std::setw(25) << obj.name
                         << std::setw(25) << obj.line
                         << std::setw(25) << obj.pos
                         << std::endl;
            } else {
        out_file << std::left
                 << std::setw(25) << "-"
                 << std::setw(25) << "-"
                 << std::setw(25) << vec[0]
                 << std::setw(25) << "-"
                 << std::setw(25) << "-"
                 << std::endl;
        }
        ++pos;
    
    }
    ++line;
}

void cut_Line(const std::string& line, std::ofstream& out_file,  size_t& line_number, size_t& pos) {
    std::string line_Copy = line;
    size_t pos_token = 0;
    std::string part = "";
    while ((pos_token = line_Copy.find(';')) != std::string::npos) {
        part = line_Copy.substr(0, pos_token);
        tokenizing(part, out_file, pos, line_number);
        line_Copy.erase(0, pos_token + 1);
    }
}
void print_info(std::ofstream& out_file){

    std::vector<std::string> allTypes {"int", "short", "long", "long long", "float", "double", "long double", 
    "char", "wchar_t", "bool", "long int", "long long int", "short int", "const int", "const char","const float", 
    "const double", "const bool", "const long","const long long", "const short", "const long double", 
    "const wchar_t", "unsigned int", "unsigned char", "unsigned float", "unsigned double","unsigned long long", 
    "unsigned wchar_t", "unsigned short", "unsigned long double", "unsigned long", "unsigned bool", "signed int", 
    "signed char", "signed float", "signed double", "signed long long", "signed wchar_t", "signed short", 
    "signed long double", "signed long", "const unsigned int", "const unsigned char", "const unsigned float", 
    "const unsigned double", "const unsigned long long", "const unsigned wchar_t", "const unsigned short", 
    "const unsigned long double", "const unsigned long", "const unsigned bool", "const signed int", 
    "const signed char", "const signed float", "const signed double", "const signed long long", 
    "const signed wchar_t", "const signed short", "const signed long double", "const signed long int", 
    "const signed long long int", "const unsigned long int", "const unsigned long long int", "size_t", 
    "const size_t" };
    
    for (auto el : allTypes){
        out_file << el << "  val" << std::endl; 
    }
}
int main() {
    std::ifstream input_file("text.txt");
    std::ofstream out_file("result.txt");
    std::ofstream out_f2("typeInfo.txt");
    

    const int col_size = 25;
    out_file << std::left
             << std::setw(col_size) << "Type"
             << std::setw(col_size) << "Value"
             << std::setw(col_size) << "Name"
             << std::setw(col_size) << "Line"
             << std::setw(col_size) << "Position"
             << std::endl;

    std::string line;
    size_t line_number = 1;
    size_t pos = 1;

    if (input_file.is_open() && out_file.is_open()) {
        while (std::getline(input_file, line)) {
            cut_Line(line, out_file,line_number, pos);
            ++line_number;
        }
        input_file.close();
        out_file.close();
        out_file.close();
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
    print_info(out_f2);
    return 0;
}
