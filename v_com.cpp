#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include "v_com.h"



typeInfo::typeInfo()
        : m_type {}
        , m_name {}
        , m_value {}
        , m_line {0}
        , m_pos {0}
{}

void typeInfo::init(const std::string& typeName, const std::string& value, const std::string& name, const size_t& position, const size_t& line)
{
    m_type = typeName;
    m_value = value;
    m_name = name;
    m_pos = position;
    m_line = line;
}

All_Types::All_Types(const std::string& file_Name)
        : input_file(file_Name)
        , out_file("result.txt")
{
    if (out_file.is_open()) {
        out_file << std::left
                   << std::setw(25) << "Type"
                   << std::setw(25) << "Value"
                   << std::setw(25) << "Name"
                   << std::setw(25) << "Line"
                   << std::setw(25) << "Position"
                   << std::endl << std::endl;
    }
}

All_Types::~All_Types()
{
    if (input_file.is_open()) {
        input_file.close();
    }
    if (out_file.is_open()) {
        out_file.close();
    }
}

void All_Types::begin ()
{    
    if(!input_file.is_open())
    {
        throw std::invalid_argument("Don't open this file!!!");
    }
    size_t line = 0;
    std::string str_line = "";
    while (std::getline(input_file, str_line), !input_file.eof())
    {
        int s = str_line.size() - 1;
        bool flag = false;
        if (str_line[s] != ';')
        {
            flag = true;
        }
        if (flag) 
        {   
            std::string temp = "";
            std::getline(input_file, temp, ';');
            str_line += temp;
        }
       helperCut_Line (str_line, line);
        ++line;
    }
}

void All_Types::helperCut_Line (std::string& str, size_t& line)
{
    std::istringstream iss (str);
    size_t position = 0;
    std::string part = "";
    while (std::getline(iss, part, ';'))
    {
        tokenizing(part, line, position);
        ++position;
    }
}

void All_Types::tokenizing(std::string& part, size_t& line, size_t& pos)
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
    } else {
        Name = vec[0];
        print_to_result(Name, line, pos);
        return; 
    }
    typeInfo ob;
    ob.init(Type, Value, Name, pos, line);
    ti[Name] = ob;
}



void All_Types::print_to_result(std::string& Name, size_t& line, size_t& pos)
{
    auto it = ti.find(Name);
    if (it != ti.end()) {
                typeInfo& obj = it -> second;
                out_file << std::left
                         << std::setw(25) << obj.m_type
                         << std::setw(25) << obj.m_value
                         << std::setw(25) << obj.m_name
                         << std::setw(25) << obj.m_line
                         << std::setw(25) << obj.m_pos
                         << std::endl;
        } else {
        out_file << std::left
                 << std::setw(25) << "-"
                 << std::setw(25) << "-"
                 << std::setw(25) << Name
                 << std::setw(25) << line
                 << std::setw(25) << pos
                 << std::endl;
        }
}

