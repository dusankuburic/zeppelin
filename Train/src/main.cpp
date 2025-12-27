#include <iostream>
#include <string>
#include "Context.hpp"
#include "Systems.hpp"

// Factory functions for creating entities with strong typing
CargoID CreateCargo(Context& ctx, std::string name, float weight, float price) {
    CargoID id = static_cast<CargoID>(ctx.cargos.weights.size());
    ctx.cargos.weights.push_back(weight);
    ctx.cargos.prices.push_back(price);
    ctx.cargos.types.push_back(0);  // Default type
    ctx.cargos.names.push_back(std::move(name));
    return id;
}

WagonID CreateWagon(Context& ctx, float maxW, int maxS) {
    WagonID id = static_cast<WagonID>(ctx.wagons.max_weights.size());
    ctx.wagons.max_weights.push_back(maxW);
    ctx.wagons.current_weights.push_back(0.0f);
    ctx.wagons.max_space.push_back(maxS);
    ctx.wagons.cargo_ids.emplace_back();
    return id;
}

TrainID CreateTrain(Context& ctx, std::string name) {
    TrainID id = static_cast<TrainID>(ctx.trains.names.size());
    ctx.trains.names.push_back(std::move(name));
    ctx.trains.wagon_ids.emplace_back();
    ctx.trains.positions.push_back(0.0f);
    ctx.trains.velocities.push_back(0.0f);
    return id;
}

int main() {
    Context ctx;

    std::cout << "=== Data-Oriented Design Train Simulator ===\n\n";
    std::cout << "--- Initializing Entities ---\n";

    // Create cargo items
    CargoID c1 = CreateCargo(ctx, "Wood Planks", 530.0f, 222.0f);
    CargoID c2 = CreateCargo(ctx, "Gold Bars", 21.0f, 543.0f);
    CargoID c3 = CreateCargo(ctx, "Steel Beams", 1200.0f, 890.0f);
    std::cout << "Created " << ctx.cargos.size() << " cargo types\n";

    // Create wagons with different capacities
    WagonID w1 = CreateWagon(ctx, 5000.0f, 30);
    WagonID w2 = CreateWagon(ctx, 3000.0f, 40);
    WagonID w3 = CreateWagon(ctx, 24000.0f, 100);
    std::cout << "Created " << ctx.wagons.size() << " wagons\n";

    // Load cargo into wagons
    std::cout << "\n--- Loading Cargo ---\n";
    Systems::TryAddCargoToWagon(ctx, w1, c1);  // Wood to wagon 1
    Systems::TryAddCargoToWagon(ctx, w1, c2);  // Gold to wagon 1
    Systems::TryAddCargoToWagon(ctx, w1, c2);  // More gold

    Systems::TryAddCargoToWagon(ctx, w2, c2);  // Gold to wagon 2
    Systems::TryAddCargoToWagon(ctx, w2, c3);  // Steel to wagon 2

    Systems::TryAddCargoToWagon(ctx, w3, c2);  // Gold to wagon 3
    Systems::TryAddCargoToWagon(ctx, w3, c2);  // More gold
    Systems::TryAddCargoToWagon(ctx, w3, c3);  // Steel to wagon 3
    std::cout << "Cargo loading complete\n";

    // Create train and attach wagons
    std::cout << "\n--- Assembling Train ---\n";
    TrainID t1 = CreateTrain(ctx, "Express Freight 3000");
    ctx.trains.wagon_ids[t1].push_back(w3);  // Attach wagons
    ctx.trains.wagon_ids[t1].push_back(w1);
    ctx.trains.wagon_ids[t1].push_back(w2);
    ctx.trains.velocities[t1] = 15.0f;  // Set speed
    std::cout << "Train assembled with " << ctx.trains.wagon_ids[t1].size() << " wagons\n";

    // Display initial analytics
    std::cout << "\n--- Initial State ---\n";
    Systems::PrintSystemAnalytics(ctx);
    std::cout << "Train Value: $" << Systems::GetTrainValue(ctx, t1) << "\n";

    // Run simulation
    std::cout << "\n=== Simulation Running ===\n";
    for (int tick = 0; tick < 5; ++tick) {
        std::cout << "\n[Tick " << tick << "]\n";
        Systems::UpdateMovement(ctx, 1.0f);
        Systems::PrintTrainStatus(ctx, t1);
    }

    // Final analytics
    std::cout << "\n=== Final Analytics ===\n";
    Systems::PrintSystemAnalytics(ctx);

    // Demonstrate batch recalculation
    std::cout << "\n--- Testing Batch Weight Recalculation ---\n";
    Systems::RecalculateAllWagonWeights(ctx);
    std::cout << "All wagon weights recalculated successfully\n";

    std::cout << "\n=== Simulation Complete ===\n";
    return 0;
}
