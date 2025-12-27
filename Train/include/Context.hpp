#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <vector>
#include <string>
#include <cstdint>

// Strong type aliases for entity IDs (prevents mixing up IDs)
using CargoID = int32_t;
using WagonID = int32_t;
using TrainID = int32_t;

constexpr CargoID INVALID_CARGO_ID = -1;
constexpr WagonID INVALID_WAGON_ID = -1;
constexpr TrainID INVALID_TRAIN_ID = -1;

// Cargo data: separate hot (frequently accessed) from cold (rarely accessed) data
struct CargoRegistry {
    // Hot data: accessed in tight loops for physics/game logic
    std::vector<float> weights;
    std::vector<float> prices;

    // Cold data: accessed mainly for UI/debugging
    std::vector<int> types;
    std::vector<std::string> names;

    inline size_t size() const { return weights.size(); }
    inline bool isValid(CargoID id) const {
        return id >= 0 && id < static_cast<CargoID>(weights.size());
    }
};

// Wagon data: optimized for cache-friendly iteration
struct WagonRegistry {
    // Hot data: accessed frequently for cargo calculations
    std::vector<float> max_weights;
    std::vector<float> current_weights;
    std::vector<int> max_space;
    std::vector<std::vector<CargoID>> cargo_ids;  // Renamed for clarity

    inline size_t size() const { return max_weights.size(); }
    inline bool isValid(WagonID id) const {
        return id >= 0 && id < static_cast<WagonID>(max_weights.size());
    }
};

// Train data: position/velocity hot data, rest is cold
struct TrainRegistry {
    // Cold data: rarely changes
    std::vector<std::string> names;
    std::vector<std::vector<WagonID>> wagon_ids;  // Renamed for clarity

    // Hot data: updated every frame in physics loop
    std::vector<float> positions;
    std::vector<float> velocities;

    inline size_t size() const { return names.size(); }
    inline bool isValid(TrainID id) const {
        return id >= 0 && id < static_cast<TrainID>(names.size());
    }
};

// Main context holding all game data
struct Context {
    CargoRegistry cargos;
    WagonRegistry wagons;
    TrainRegistry trains;
};

#endif 
