#ifndef WAGON_HPP
#define WAGON_HPP

#include "Cargo.hpp"
#include <vector>
#include <memory>

typedef int SPACE;

class Wagon {
private:
    KG max_weight_;
    SPACE max_space_;
    std::vector<std::unique_ptr<Cargo>> list;
    static int ID;
    int myID_;

public:
    Wagon(KG max_weight, SPACE max_space);
    Wagon(const Wagon& other);
    Wagon(Wagon&& other) noexcept = default;
    ~Wagon() = default;

    Wagon& operator=(const Wagon& other);
    Wagon& operator=(Wagon&& other) noexcept = default;

    KG getMaxWeight() const;
    KG getCurrentWeight() const;
    VALUE getWagonPrice() const;
    void aboutWagon() const;
    void addCargo(std::unique_ptr<Cargo> c);
    bool operator==(const Wagon& w) const;
    bool freeWeight(const Cargo* c) const;
};

#endif 
