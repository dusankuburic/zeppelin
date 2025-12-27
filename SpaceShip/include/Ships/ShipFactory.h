#pragma once

#include "Ship.h"
#include "ShipSpec.h"
#include <memory>
#include <string>
#include <vector>

class ShipFactory {
public:
    static std::unique_ptr<Ship> CreateByID(const std::string& ship_id,
                                            const std::string& faction);

    static std::unique_ptr<Ship> CreateByName(const std::string& ship_name,
                                              const std::string& faction);

    static std::unique_ptr<Ship> CreateFromSpec(const ShipSpec& spec,
                                                const std::string& faction = "");

    static std::vector<std::unique_ptr<Ship>> CreateFleet(
        const std::vector<std::string>& ship_ids,
        const std::string& faction);

    static std::vector<std::unique_ptr<Ship>> CreateCategorySet(
        const std::string& category,
        const std::string& faction);

    static std::vector<std::unique_ptr<Ship>> CreateAllShips(
        const std::string& faction);

    static void PrintShipCatalog(bool detailed = false);
};
