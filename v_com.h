#ifndef VISUAL_COMPILER
#define VISUAL_COMPILER

#include <map>
#include <fstream>

struct typeInfo {
    std::string m_type;
    std::string m_value;
    std::string m_name;
    size_t m_pos;
    size_t m_line;
    typeInfo();
    void init(const std::string&, const std::string&, const std::string&, const size_t&, const size_t&);
};


class All_Types
{   
public:
    explicit All_Types (const std::string&);
    ~All_Types ();
    void begin();
private:
    void helperCut_Line(std::string&, size_t&);
    void tokenizing(std::string&, size_t&, size_t&);
    void print_to_result(std::string&, size_t&, size_t&);
    std::map <std::string, typeInfo> ti;
    std::ifstream input_file;
    std::ofstream out_file;
};

#endif // VISUAL_COMPILER                                   

