#include <iostream>
/* Template wrappers */
template<class T>
std::string format(const std::string &&fmt_line, T &&arg)
{
    std::ostringstream out;
    out << arg;
    std::string result;
    set_at_zero(fmt_line, out.str(), result, true);
    return result;
}


template<class T, class... ArgsT>
std::string format(const std::string &&fmt_line, T &&arg, ArgsT&&... args)
{
    std::ostringstream out;
    out << arg;
    std::string mid_result;
    set_at_zero(fmt_line, out.str(), mid_result, false);
    std::cout << "before return format(std::fwd)" << std::endl;
    return format(std::move(mid_result), std::forward<ArgsT>(args)...);
}

