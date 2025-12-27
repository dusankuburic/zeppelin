#ifndef CARGO_HPP
#define CARGO_HPP

#include <string>
#include <iostream>

typedef int KG;
typedef double VALUE;

class Cargo {
private:
    std::string name_;
    KG weight_;
    VALUE price_;

public:
    Cargo(std::string name, KG weight, VALUE price);
    Cargo(const Cargo& c);
    
    void aboutCargo() const;
    std::string getName() const;
    KG getWeight() const;
    void setPrice(VALUE price);
    VALUE getPrice() const;
};

#endif 
