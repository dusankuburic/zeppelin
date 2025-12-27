#include "Train.hpp"
#include <iostream>

Train::Train(std::string name) :
    name_(std::move(name))
{}

Train::Train(const Train& t) :
    name_(t.name_)
{
    for (const auto& wagon : t.wagons_) {
        wagons_.push_back(std::make_unique<Wagon>(*wagon));
    }
}

Train& Train::operator=(const Train& t) {
    if (this != &t) {
        name_ = t.name_;
        wagons_.clear();
        for (const auto& wagon : t.wagons_) {
            wagons_.push_back(std::make_unique<Wagon>(*wagon));
        }
    }
    return *this;
}

void Train::addWagon(std::unique_ptr<Wagon> w) {
    wagons_.push_back(std::move(w));
}

void Train::removeAllWagons() {
    wagons_.clear();
}

void Train::aboutTrain() const {
    std::cout << "Train name: " << name_ << "\n";
    std::cout << "Train wagons: " << "\n";
    
    for (const auto& w : wagons_) {
        w->aboutWagon();
    }
}

bool more_valuable(const Wagon& w1, const Wagon& w2) {
    return w1.getWagonPrice() > w2.getWagonPrice();
}