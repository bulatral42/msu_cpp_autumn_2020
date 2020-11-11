/* Serializer */
Serializer::Serializer(std::ostream& out) : out_{out} {}

template<class T>
Error Serializer::save(T &&object) {
    return object.serialize(*this);
}

template<class... ArgsT>
Error Serializer::operator()(ArgsT&&... args) {
    return process_(std::forward<ArgsT>(args)...);
}
    
Error Serializer::write_(bool val) {
    try {
        if (val) {
            out_ << "true" << SEP;
        } else {
            out_ << "false" << SEP;
        }
        return Error::NoError;
    } catch(std::exception &exc) {
        return Error::SaveProblem;
    }
}
    
Error Serializer::write_(uint64_t val) {
    try {
        out_ << val << SEP;
        return Error::NoError;
    } catch(std::exception &exc) {
        return Error::SaveProblem;
    }
}
    
template<class T>
Error Serializer::process_(T &&val) {
    return write_(val);
}

template<class T, class... ArgsT>
Error Serializer::process_(T &&val, ArgsT&&... args) {
    if (write_(val) == Error::NoError) {
        return process_(std::forward<ArgsT>(args)...);
    } else {
        return Error::SaveProblem;
    }
}


/* Deserializer */
Deserializer::Deserializer(std::istream& in) : in_{in} {}

template<class T>
Error Deserializer::load(T &object) {
    return object.deserialize(*this);
}

template<class... ArgsT>
Error Deserializer::operator()(ArgsT&&... args) {
    return process_(std::forward<ArgsT>(args)...);
}

template<class T>
Error Deserializer::process_(T &&val) {
    return read_(val);
}
    
template<class T, class... ArgsT>
Error Deserializer::process_(T &&val, ArgsT&&... args) {
    if (read_(val) == Error::NoError) {
        return process_(std::forward<ArgsT>(args)...);
    } else {
        return Error::CorruptedArchive;
    }
}
    
Error Deserializer::read_(bool &val) {
    try{
        std::string tmp;
        in_ >> tmp;
        if (tmp == "true") {
            val = true;
            return Error::NoError;
        } else if (tmp == "false") {
            val = false;
            return Error::NoError;
        } else {
            return Error::CorruptedArchive;
        }
    } catch(std::exception &exc) {
        return Error::CorruptedArchive;
    }
}
    
Error Deserializer::read_(uint64_t &val) {
    try {
        std::string tmp;
        in_ >> tmp;
        val = std::stoull(tmp);
        return Error::NoError;
    } catch(std::exception &exc) {
        return Error::CorruptedArchive;
    }
}

