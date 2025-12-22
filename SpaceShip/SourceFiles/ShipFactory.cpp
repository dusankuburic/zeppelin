#include "../HeaderFiles/Ships/ShipFactory.h"
#include <iostream>
#include <iomanip>

std::unique_ptr<Ship> ShipFactory::CreateByID(const std::string& ship_id,
                                              const std::string& faction) {
    const ShipSpec& spec = ShipCatalog::GetInstance().GetSpecByID(ship_id);
    return CreateFromSpec(spec, faction);
}

std::unique_ptr<Ship> ShipFactory::CreateByName(const std::string& ship_name,
                                                const std::string& faction) {
    const ShipSpec& spec = ShipCatalog::GetInstance().GetSpecByName(ship_name);
    return CreateFromSpec(spec, faction);
}

std::unique_ptr<Ship> ShipFactory::CreateFromSpec(const ShipSpec& spec,
                                                  const std::string& faction) {
    try {
        return std::make_unique<Ship>(spec, faction);
    } catch (const std::exception& e) {
        throw std::runtime_error(
            std::string("Failed to create ship from spec: ") + e.what()
        );
    }
}

std::vector<std::unique_ptr<Ship>> ShipFactory::CreateFleet(
    const std::vector<std::string>& ship_ids,
    const std::string& faction) {
    std::vector<std::unique_ptr<Ship>> fleet;

    for (const auto& ship_id : ship_ids) {
        try {
            fleet.push_back(CreateByID(ship_id, faction));
        } catch (const std::exception& e) {
            throw std::runtime_error(
                std::string("Failed to create fleet - error with ship '") +
                ship_id + "': " + e.what()
            );
        }
    }

    return fleet;
}

std::vector<std::unique_ptr<Ship>> ShipFactory::CreateCategorySet(
    const std::string& category,
    const std::string& faction) {
    std::vector<std::unique_ptr<Ship>> ships;
    const auto& specs = ShipCatalog::GetInstance().GetShipsByCategory(category);

    if (specs.empty()) {
        throw std::runtime_error("No ships found in category: " + category);
    }

    for (const auto& spec : specs) {
        ships.push_back(CreateFromSpec(spec, faction));
    }

    return ships;
}

std::vector<std::unique_ptr<Ship>> ShipFactory::CreateAllShips(
    const std::string& faction) {
    std::vector<std::unique_ptr<Ship>> ships;
    const auto& ids = ShipCatalog::GetInstance().GetAllShipIDs();

    for (const auto& id : ids) {
        ships.push_back(CreateByID(id, faction));
    }

    return ships;
}

void ShipFactory::PrintShipCatalog(bool detailed) {
    const ShipCatalog& catalog = ShipCatalog::GetInstance();

    if (catalog.GetShipCount() == 0) {
        std::cout << "No ships in catalog. Please load from JSON first.\n";
        return;
    }

    std::cout << "\n";
    std::cout << "================================================================================\n";
    std::cout << "SHIP CATALOG (" << catalog.GetShipCount() << " ships)\n";
    std::cout << "================================================================================\n";

    std::vector<std::string> categories = {"gunboat", "fighter", "capital"};

    for (const auto& category : categories) {
        const auto& specs = catalog.GetShipsByCategory(category);

        if (specs.empty()) continue;

        std::cout << "\n" << std::string(category.length(), '-') << "\n";
        std::cout << "    " << std::string(1, std::toupper(category[0]))
                  << category.substr(1) << " Ships (" << specs.size() << ")\n";
        std::cout << std::string(category.length(), '-') << "\n\n";

        for (const auto& spec : specs) {
            if (detailed) {
                std::cout << "  ID: " << spec.id << "\n";
                std::cout << "  Name: " << spec.name << "\n";
                std::cout << "  Faction: " << spec.faction << "\n";
                std::cout << "  Hull: " << spec.hull << "\n";
                std::cout << "  Max Shield: " << spec.max_shield << "\n";
                std::cout << "  Cargo: " << spec.cargo << "\n";
                std::cout << "  Speed: " << spec.speed << "\n";
                std::cout << "  Price: " << spec.price << "\n";

                if (!spec.description.empty()) {
                    std::cout << "  Description: " << spec.description << "\n";
                }

                std::cout << "\n";
            } else {
                std::cout << "  [" << spec.id << "]\n";
                std::cout << "    " << spec.name << " (Price: " << spec.price << ")\n";
            }
        }
    }

    std::cout << "================================================================================\n";
    std::cout << "\n";
}
