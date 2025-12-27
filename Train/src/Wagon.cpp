#include "Wagon.hpp"

int Wagon::ID = 0;

Wagon::Wagon(KG max_weight, SPACE max_space) :
    max_weight_(max_weight), max_space_(max_space), myID_(++ID)
{
    list.reserve(max_space_);
}

Wagon::Wagon(const Wagon& other) :
    max_weight_(other.max_weight_),
    max_space_(other.max_space_),
    myID_(++ID)
{
    list.reserve(max_space_);
    for (const auto& cargo : other.list) {
        list.push_back(std::make_unique<Cargo>(*cargo));
    }
}

Wagon& Wagon::operator=(const Wagon& other) {
    if (this != &other) {
        max_weight_ = other.max_weight_;
        max_space_ = other.max_space_;
        list.clear();
        list.reserve(other.max_space_);
        for (const auto& cargo : other.list) {
            list.push_back(std::make_unique<Cargo>(*cargo));
        }
    }
    return *this;
}

KG Wagon::getMaxWeight() const {
    return this->max_weight_;
}

KG Wagon::getCurrentWeight() const {
    KG total = 0;
    for (const auto& cargo : list) {
        total += cargo->getWeight();
    }
    return total;
}

VALUE Wagon::getWagonPrice() const {
    VALUE total = 0;
    for (const auto& cargo : list) {
        total += cargo->getPrice();
    }
    return total;
}

void Wagon::aboutWagon() const {
    std::cout << "----------------------" << "\n";
    std::cout << "Wagon ID: " << this->myID_ << "\n";
    std::cout << "Current weight: " << getCurrentWeight() << "\n";
    std::cout << "Wagon price: " << getWagonPrice() << "\n";
}

bool Wagon::freeWeight(const Cargo* c) const {
    KG cargo_weight = c->getWeight();
    KG current_weight = getCurrentWeight();

    if ((cargo_weight + current_weight) <= max_weight_) {
        return true;
    }
    return false;
}

bool Wagon::operator==(const Wagon& w) const {
    return (max_weight_ == w.max_weight_) && (max_space_ == w.max_space_);
}

void Wagon::addCargo(std::unique_ptr<Cargo> c) {
    if (list.size() < (size_t)max_space_ && freeWeight(c.get())) {
        list.push_back(std::move(c));
    }
    else {
        std::cout << "There is no more space or your cargo is too heavy." << "\n";
    }
}
