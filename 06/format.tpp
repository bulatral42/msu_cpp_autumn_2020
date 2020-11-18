/* Template wrappers */
/*template<class T>
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
}*/

template<class T>
void vectorize_args(std::vector<std::string> &s_args, T &&arg)
{
    std::stringstream tmp;
    tmp << arg;
    s_args.push_back(tmp.str());
}

    
template<class T, class... ArgsT>
void vectorize_args(std::vector<std::string> &s_args, T &&arg, ArgsT&&... args)
{
    std::stringstream tmp;
    tmp << arg;
    s_args.push_back(tmp.str());
    vectorize_args(s_args, std::move(args)...);
}


template<class... ArgsT>
std::string format(const std::string &fmt_line, ArgsT&&... args)
{
    std::vector<std::string> s_args;
    vectorize_args(s_args, std::forward<ArgsT>(args)...);
    
    std::string res;
    return substitute(fmt_line, s_args, res);
}


