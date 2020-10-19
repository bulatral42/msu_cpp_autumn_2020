#pragma once

#include <string>
#include <cstdint>
#include <cinttypes>
#include <cstdio>

using void_f = void (*)(); 
using str_procedure = void (*)(std::string);//, void *ptr=nullptr); /* takes token, makes processing */
using num_procedure = void (*)(uint64_t);//, void *ptr=nullptr); /* and writes result to some ptr */
//using str_retn = std::string (*)(std::string); /* returns  */
//using num_retn = uint64_t (*)(uint64_t);

void parser_start_default();
void parser_end_default();

class Parser
{
    str_procedure str_handler{nullptr};
    num_procedure num_handler{nullptr};
    //void_f start{nullptr}, end{nullptr};
    
    void_f start{parser_start_default}, end{parser_end_default};
    //num_retn num_handler_retn{nullptr};
    //str_retn str_handler_retn{nullptr};
        
    int tokens_cnt, str_cnt{}, num_cnt{};
    
    std::string get_token(std::string::const_iterator &, std::string::const_iterator &);
    void start_default();
    void end_default();
    bool is_number(const std::string &);
    
public:
    Parser();
    ~Parser();
    void set_start_callback(void_f);
    void set_end_callback(void_f);
    void set_number_callback(num_procedure);
    void set_string_callback(str_procedure);
    void operator()(const std::string &);
};

