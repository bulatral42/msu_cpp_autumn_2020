#pragma once
#include <functional>

constexpr int MAX_MSG_LEN = 255;  /* Exception message buffer size */

struct Parser_exception : std::exception {
    Parser_exception(const char *);
    Parser_exception(int);
    const char* what() const throw();
    int code() const throw();
    ~Parser_exception();
private:
    char msg[MAX_MSG_LEN + 1] = { 0 };
    int ex_code{}; 
};

struct Parser_stats { /* Parser statistics */
    int tokens{}, strings{}, numbers{};
};

void parser_start_default();
void parser_end_default(const Parser_stats &);
void parser_str_default(const std::string &);
void parser_num_default(uint64_t);

using void_f = std::function<void()>; 
using str_procedure = std::function<void(const std::string &)>;
using num_procedure = std::function<void(uint64_t)>;
using end_procedure = std::function<void(const Parser_stats &stats)>;

class Parser
{
    str_procedure str_handler{parser_str_default};
    num_procedure num_handler{parser_num_default};
    void_f start{parser_start_default};
    end_procedure end{parser_end_default};
    
    Parser_stats stats;
    
    std::string get_token(std::string::const_iterator &, 
                          const std::string::const_iterator &);
    bool is_number(const std::string &) const;
    
public:
    Parser();
    ~Parser();
    void set_start_callback(void_f);
    void set_end_callback(end_procedure);
    void set_number_callback(num_procedure);
    void set_string_callback(str_procedure);
    void operator()(const std::string &);  /* Parsing operator */
};

