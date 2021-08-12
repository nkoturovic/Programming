#include <string>
// Alternatively, you can inherit from boost::noncopyable or declare them as deleted (in C++11 and above):
// 
// Person(const Person& that) = delete;
// Person& operator=(const Person& that) = delete;
// 
// The rule of three
// 
// Sometimes you need to implement a class that manages a resource. (Never manage multiple resources in a single class, this will only lead to pain.) In that case, remember the rule of three:
// 
//     If you need to explicitly declare either the destructor, copy constructor or copy assignment operator yourself, you probably need to explicitly declare all three of them.
// 
// (Unfortunately, this "rule" is not enforced by the C++ standard or any compiler I am aware of.)
// The rule of five
// 
// From C++11 on, an object has 2 extra special member functions: the move constructor and move assignment. The rule of five states to implement these functions as well.
// 
// An example with the signatures:

class Person {
    std::string m_name;
    int m_age;
public:
    Person(const std::string& name, int age) : m_name(name), m_age(age) {}        // Ctor
    Person(const Person &) = default;                // 1/5: Copy Ctor
    Person(Person &&) noexcept = default;            // 4/5: Move Ctor
    Person& operator=(const Person &) = default;     // 2/5: Copy Assignment
    Person& operator=(Person &&) noexcept = default; // 5/5: Move Assignment
    ~Person() noexcept = default;                    // 3/5: Dtor
};

//The rule of zero
//
//The rule of 3/5 is also referred to as the rule of 0/3/5. The zero part of the rule states that you are allowed to not write any of the special member functions when creating your class.
//Advice
//
//Most of the time, you do not need to manage a resource yourself, because an existing class such as std::string already does it for you. Just compare the simple code using a std::string member to the convoluted and error-prone alternative using a char* and you should be convinced. As long as you stay away from raw pointer members, the rule of three is unlikely to concern your own code.
