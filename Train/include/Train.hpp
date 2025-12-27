#ifndef TRAIN_HPP
#define TRAIN_HPP

#include "Wagon.hpp"
#include <vector>
#include <string>
#include <memory>

class Train {
private:
    std::string name_;
    std::vector<std::unique_ptr<Wagon>> wagons_;

public:
    explicit Train(std::string name);
    Train(const Train& t);
    Train(Train&& t) noexcept = default;
    ~Train() = default;

    Train& operator=(const Train& t);
    Train& operator=(Train&& t) noexcept = default;

    void addWagon(std::unique_ptr<Wagon> w);
    void removeAllWagons();
    void aboutTrain() const;
};


bool more_valuable(const Wagon& w1, const Wagon& w2);

#endif 
