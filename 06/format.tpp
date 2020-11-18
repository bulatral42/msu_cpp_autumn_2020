/* Template wrappers */
template<class T>
std::string format(const std::string &fmt_line, const T &arg)
{
    std::ostringstream out;
    out << arg;
    std::string result;
    set_at_zero(fmt_line, out.str(), result, true);
    return result;
}


template<class T, class... ArgsT>
std::string format(const std::string &fmt_line, const T &arg, 
                   const ArgsT &... args)
{
    std::ostringstream out;
    out << arg;
    std::string mid_result;
    set_at_zero(fmt_line, out.str(), mid_result, false);

    return format(mid_result, args...);
}

