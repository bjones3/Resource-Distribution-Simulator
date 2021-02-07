#include "ID.hpp"

ID::ID(){
    id = 0;
}

long long int ID::generateID(){
    id++;
    return id;
}
