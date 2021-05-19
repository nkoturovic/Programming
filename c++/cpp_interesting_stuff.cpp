// mem_fn: Lightweight low-cost replacement for raw function pointer/reference wrapper to member function
std::mem_fn<void(std::string&&)>(&std::vector<std::string>::push_back);
std::mem_fn(static_cast<std::string&(std::vector<std::string>::*)(std::string&&)>(&std::vector<std::string>::emplace_back));
// mem_fn can be used as pointer to member variable instead of member function!
