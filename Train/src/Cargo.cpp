#include "Cargo.hpp"

Cargo::Cargo(std::string name, KG weight, VALUE price) :
    name_(std::move(name)), weight_(weight), price_(price)
{}

Cargo::Cargo(const Cargo& c) {
    name_ = c.name_;
    weight_ = c.weight_;
    price_ = c.price_;
}

void Cargo::aboutCargo() const {
    std::cout << "Name: " << this->name_ << "\n";
    std::cout << "Weight: " << this->weight_ << "\n";
    std::cout << "Price: " << this->price_ << "\n";
}

std::string Cargo::getName() const {
    return this->name_;
}

KG Cargo::getWeight() const {
    return this->weight_;
}

void Cargo::setPrice(VALUE price) {
    price_ = price;
}

VALUE Cargo::getPrice() const {
    return this->price_;
}
