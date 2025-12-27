#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include "Context.hpp"
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <cassert>

namespace Systems {

    // ==================== Validation Systems ====================

    inline bool ValidateCargoID(const Context& ctx, CargoID id) {
        return ctx.cargos.isValid(id);
    }

    inline bool ValidateWagonID(const Context& ctx, WagonID id) {
        return ctx.wagons.isValid(id);
    }

    inline bool ValidateTrainID(const Context& ctx, TrainID id) {
        return ctx.trains.isValid(id);
    }

    // ==================== Query Systems ====================

    // Fixed: Only counts cargo actually loaded in wagons (not all cargo in registry)
    double CalculateTotalLoadedCargoValue(const Context& ctx) {
        double total = 0.0;
        std::unordered_set<CargoID> counted;  // Track counted cargo to avoid duplicates

        // Iterate through all wagons and sum unique cargo values
        for (size_t w = 0; w < ctx.wagons.size(); ++w) {
            const auto& cargo_list = ctx.wagons.cargo_ids[w];
            for (CargoID cargoID : cargo_list) {
                if (counted.insert(cargoID).second) {  // Only count if not already counted
                    total += ctx.cargos.prices[cargoID];
                }
            }
        }
        return total;
    }

    // Get value of all cargo in a specific wagon
    double GetWagonValue(const Context& ctx, WagonID wagonID) {
        assert(ValidateWagonID(ctx, wagonID) && "Invalid wagon ID");

        double val = 0.0;
        const auto& cargo_list = ctx.wagons.cargo_ids[wagonID];
        for (CargoID cargoID : cargo_list) {
            assert(ValidateCargoID(ctx, cargoID) && "Invalid cargo ID in wagon");
            val += ctx.cargos.prices[cargoID];
        }
        return val;
    }

    // Get total value of a train (all wagons combined)
    double GetTrainValue(const Context& ctx, TrainID trainID) {
        assert(ValidateTrainID(ctx, trainID) && "Invalid train ID");

        double total = 0.0;
        const auto& wagon_list = ctx.trains.wagon_ids[trainID];
        for (WagonID wagonID : wagon_list) {
            total += GetWagonValue(ctx, wagonID);
        }
        return total;
    }

    // ==================== Mutation Systems ====================

    // Try to add cargo to a wagon (with bounds checking)
    bool TryAddCargoToWagon(Context& ctx, WagonID wagonID, CargoID cargoID) {
        // Validate IDs
        if (!ValidateWagonID(ctx, wagonID)) {
            std::cerr << "Error: Invalid wagon ID " << wagonID << "\n";
            return false;
        }
        if (!ValidateCargoID(ctx, cargoID)) {
            std::cerr << "Error: Invalid cargo ID " << cargoID << "\n";
            return false;
        }

        float cargoWeight = ctx.cargos.weights[cargoID];
        float wagonMax = ctx.wagons.max_weights[wagonID];
        float currentW = ctx.wagons.current_weights[wagonID];

        // Check weight constraint
        if (currentW + cargoWeight > wagonMax) {
            return false;
        }

        // Check space constraint
        if (ctx.wagons.cargo_ids[wagonID].size() >= (size_t)ctx.wagons.max_space[wagonID]) {
            return false;
        }

        // Add cargo
        ctx.wagons.cargo_ids[wagonID].push_back(cargoID);
        ctx.wagons.current_weights[wagonID] += cargoWeight;
        return true;
    }

    // ==================== Batch Processing Systems (Cache-Friendly) ====================

    // Update all train positions in one pass (better cache utilization)
    void UpdateMovement(Context& ctx, float dt) {
        size_t count = ctx.trains.positions.size();

        // This loop is cache-friendly: iterates linearly through contiguous arrays
        for (size_t i = 0; i < count; ++i) {
            ctx.trains.positions[i] += ctx.trains.velocities[i] * dt;
        }
    }

    // Batch calculate all wagon weights (useful for validation/analytics)
    void RecalculateAllWagonWeights(Context& ctx) {
        for (size_t w = 0; w < ctx.wagons.size(); ++w) {
            float total_weight = 0.0f;
            const auto& cargo_list = ctx.wagons.cargo_ids[w];

            for (CargoID cargoID : cargo_list) {
                total_weight += ctx.cargos.weights[cargoID];
            }

            ctx.wagons.current_weights[w] = total_weight;
        }
    }

    // ==================== Output/Debug Systems ====================

    void PrintTrainStatus(const Context& ctx, TrainID trainID) {
        assert(ValidateTrainID(ctx, trainID) && "Invalid train ID");

        std::cout << "Train: " << ctx.trains.names[trainID] << "\n";
        std::cout << "Position: " << ctx.trains.positions[trainID] << "\n";

        const auto& wagon_list = ctx.trains.wagon_ids[trainID];
        for (WagonID wagonID : wagon_list) {
            std::cout << "  Wagon ID: " << wagonID
                      << " | Weight: " << ctx.wagons.current_weights[wagonID]
                      << "/" << ctx.wagons.max_weights[wagonID]
                      << " | Value: " << GetWagonValue(ctx, wagonID)
                      << "\n";
        }
    }

    // Print analytics about the entire system
    void PrintSystemAnalytics(const Context& ctx) {
        std::cout << "=== System Analytics ===\n";
        std::cout << "Total Cargo Types: " << ctx.cargos.size() << "\n";
        std::cout << "Total Wagons: " << ctx.wagons.size() << "\n";
        std::cout << "Total Trains: " << ctx.trains.size() << "\n";
        std::cout << "Total Loaded Cargo Value: " << CalculateTotalLoadedCargoValue(ctx) << "\n";
        std::cout << "========================\n";
    }
}

#endif 
