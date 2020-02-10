std::string toString(stack<int>& value);

std::ostream& operator << (std::ostream& os, stack<int> const& value);

std::string toString(queue<int>& value);

std::ostream& operator << (std::ostream& os, queue<int> const& value);

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

std::string toString(stack<int>& value){
    std::string retval("{");
    stack<int> temp;
    while(!value.empty()){
        temp.push(value.top());
        retval += std::to_string(value.top());
        value.pop();
        if(!value.empty())
            retval += std::string(", ");
        else
            retval += std::string("}");
    }
    for(; !temp.empty(); value.push(temp.top()), temp.pop());
    return retval;
}

std::ostream& operator << (std::ostream& os, stack<int> const& value){
    stack<int> val = value;
    os << toString(val);
    return os;
}

std::string toString(queue<int>& value){
    std::string retval("{");
    stack<int> temp;
    for(unsigned long i = 0; i < value.size(); i++){
        temp.push(value.front());
        value.push(value.front());
        value.pop();
    }
    while(!temp.empty()){
        retval += std::to_string(temp.top());
        temp.pop();
        if(!temp.empty())
            retval += std::string(", ");
        else
            retval += std::string("}");
    }
    return retval;
}

std::ostream& operator << (std::ostream& os, queue<int> const& value){
    queue<int> val = value;
    os << toString(val);
    return os;
}