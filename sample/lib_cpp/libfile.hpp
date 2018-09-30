#include <string>


class Class_2 {
    public:
        Class_2(const std::string &nicName);
     
        void printName();
    
    private:
        std::string _nicName;
};
