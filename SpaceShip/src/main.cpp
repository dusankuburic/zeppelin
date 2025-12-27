#include "ShipFactory.h"
#include "ComponentFactory.h"
#include "ComponentSpec.h"
#include "InputValidator.h"
#include <memory>
#include <iostream>

const int NUM_OF_WEAPONS = 4;
const int NUM_OF_CARGO = 3;
const int NUM_OF_ENGINES = 2;
const int NUM_OF_SHIELDS = 1;

int main() {
	std::cout << "Loading ship and component catalogs...\n";
	ShipCatalog::GetInstance().LoadFromJSON("ships.json");
	ComponentCatalog::GetInstance().LoadFromJSON("components.json");
	std::cout << "\n";

	bool quit = false;
	int choiceShip = 0;
	int choiceEngine = 0;
	int choiceShield = 0;
	int choiceWeapon = 0;
	int choiceCargo = 0;

	std::unique_ptr<Ship> ship_ptr = nullptr;

	while (1) {
		std::cout << "Choose space ship:" << "\n";
		std::cout << "(1) Gunboat CTE12400 Condor   (4) Fighter MJ1 Gecko Council        (7) Capital Liberty Archer Siege Cruiser"  << "\n";
		std::cout << "(2) Gunboat Kusari Ashikaga   (5) Fighter R1SERIES P Skeleton      (8) Capital Triumph Galic Royal Navy Destroyer" << "\n";
		std::cout << "(3) Gunboat T883GB Ahoudari   (6) Fighter RHGM17 Loki Red Hessian  (9) Capital RHGM482 Red Hessian Cruiser " << "\n";
		std::cout << "\n";

		if (!InputValidator::readInt("Enter your choice (1-9): ", choiceShip, 1, 9)) {
			std::cout << "Exiting due to invalid input.\n";
			break;
		}

		std::string ship_id;
		switch (choiceShip) {
			case 1: ship_id = "gunboat_cte12400_condor"; break;
			case 2: ship_id = "gunboat_kusari_ashikaga"; break;
			case 3: ship_id = "gunboat_t883gb_ahoudari"; break;
			case 4: ship_id = "fighter_mj1_gecko_council"; break;
			case 5: ship_id = "fighter_r1series_p_skeleton"; break;
			case 6: ship_id = "fighter_rhgm17_loki_red_hessian"; break;
			case 7: ship_id = "capital_liberty_archer_siege_cruiser"; break;
			case 8: ship_id = "capital_triumph_galic_royal_navy_destroyer"; break;
			case 9: ship_id = "capital_rhgm482_red_hessian_cruiser"; break;
			default: quit = true; break;
		}

		if (quit) {
			break;
		}

		ship_ptr = ShipFactory::CreateByID(ship_id, "");
		if (!ship_ptr) {
			std::cout << "Error creating ship!\n";
			continue;
		}

		for (int min = 1; min <= NUM_OF_ENGINES; ++min) {
			std::cout << "\n\n\n";
			std::cout << "On: " << min << "\n";
			std::cout << "Add Engine on your ship: " << "\n";
			std::cout << "(1) Nomad F1G Elipsion Engine" << "\n";
			std::cout << "(2) AI Auxiliary Engine" << "\n";
			std::cout << "(3) Cheetah ZZ8J Engine" << "\n";

			if (!InputValidator::readInt("Enter your choice (1-3): ", choiceEngine, 1, 3)) {
				std::cout << "Skipping engine selection.\n";
				continue;
			}

			std::string engine_id;
			switch (choiceEngine) {
				case 1: engine_id = "nomad_f1g_elipsion"; break;
				case 2: engine_id = "ai_auxiliary"; break;
				case 3: engine_id = "cheetah_zz8j"; break;
				default: std::cout << "ERROR\n"; continue;
			}

			Engine engine = ComponentFactory::CreateEngineByID(engine_id);
			ship_ptr->AddEngine(engine);
		}

		for (int min = 1; min <= NUM_OF_SHIELDS; ++min) {
			std::cout << "\n\n\n";
			std::cout << "On: " << min << "\n";
			std::cout << "Add Shield on your ship: " << "\n";
			std::cout << "(1) CG6S Pavise Transport Shield" << "\n";
			std::cout << "(2) Gunboat Graviton Shield" << "\n";
			std::cout << "(3) SGD2 Advance Protector Fighter Shield" << "\n";

			if (!InputValidator::readInt("Enter your choice (1-3): ", choiceShield, 1, 3)) {
				std::cout << "Skipping shield selection.\n";
				continue;
			}

			std::string shield_id;
			switch (choiceShield) {
				case 1: shield_id = "cg6s_pavise_transport"; break;
				case 2: shield_id = "gunboat_graviton"; break;
				case 3: shield_id = "sgd2_advance_protector_fighter"; break;
				default: std::cout << "ERROR\n"; continue;
			}

			Shield shield = ComponentFactory::CreateShieldByID(shield_id);
			ship_ptr->AddShield(shield);
		}

		for (int min = 1; min <= NUM_OF_WEAPONS; ++min) {
			std::cout << "\n\n\n";
			std::cout << "On: " << min << "\n";
			std::cout << "Add Weapon on your ship: " << "\n";
			std::cout << "(1) EMP 7 Pulse Cannon" << "\n";
			std::cout << "(2) H4Z Brimstone Helfire Turret" << "\n";
			std::cout << "(3) Musket Gallic Tachyon Cannon" << "\n";

			if (!InputValidator::readInt("Enter your choice (1-3): ", choiceWeapon, 1, 3)) {
				std::cout << "Skipping weapon selection.\n";
				continue;
			}

			std::string weapon_id;
			switch (choiceWeapon) {
				case 1: weapon_id = "emp_7_pulse_cannon"; break;
				case 2: weapon_id = "h4z_brimstone_helfire_turret"; break;
				case 3: weapon_id = "musket_gallic_tachyon_cannon"; break;
				default: std::cout << "ERROR\n"; continue;
			}

			Weapon weapon = ComponentFactory::CreateWeaponByID(weapon_id);
			ship_ptr->AddWeapon(weapon);
		}

		for (int min = 1; min <= NUM_OF_CARGO; ++min) {
			std::cout << "\n\n\n";
			std::cout << "On: " << min << "\n";
			std::cout << "Add Cargo on your ship: " << "\n";
			std::cout << "(1) Oxygen" << "\n";
			std::cout << "(2) Radon" << "\n";
			std::cout << "(3) Xeon" << "\n";

			if (!InputValidator::readInt("Enter your choice (1-3): ", choiceCargo, 1, 3)) {
				std::cout << "Skipping cargo selection.\n";
				continue;
			}

			std::string cargo_id;
			switch (choiceCargo) {
				case 1: cargo_id = "oxygen"; break;
				case 2: cargo_id = "radon"; break;
				case 3: cargo_id = "xeon"; break;
				default: std::cout << "ERROR\n"; continue;
			}

			Cargo cargo = ComponentFactory::CreateCargoByID(cargo_id);
			ship_ptr->AddCargo(cargo);
		}

		std::cout << "\n\n==========================================\n";
		std::cout << "SHIP CONFIGURATION COMPLETE\n";
		std::cout << "==========================================\n";
		std::cout << ship_ptr->GetInfo() << std::endl;

		std::cout << "\n";
		ship_ptr->ListEngine();
		ship_ptr->ListShield();
		ship_ptr->ListWeapon();
		ship_ptr->ListCargo();

		std::cout << "\n";
		std::cout << "Total Ship Price: " << ship_ptr->GetShipPrice() << "\n";
		std::cout << "==========================================\n\n";

		if (!InputValidator::confirm("Configure another ship? (y/n): ")) {
			break;
		}
	}

	std::cout << "Thank you for using the Ship Configuration System!\n";
	return 0;
}
