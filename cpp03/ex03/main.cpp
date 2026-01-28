#include "DiamondTrap.hpp"

int main() {
	std::cout << "=== Creating DiamondTrap ===" << std::endl;
	DiamondTrap diamond("Diamond");

	std::cout << "\n=== DiamondTrap stats ===" << std::endl;
	std::cout << "Name: " << diamond.getName() << std::endl;
	std::cout << "HP: " << diamond.getHitPoints() << " (FragTrap: 100)" << std::endl;
	std::cout << "Energy: " << diamond.getEnergyPoints() << " (ScavTrap: 50)" << std::endl;
	std::cout << "Attack Damage: " << diamond.getAttackDamage() << " (FragTrap: 30)" << std::endl;

	std::cout << "\n=== Testing whoAmI ===" << std::endl;
	diamond.whoAmI();

	std::cout << "\n=== Testing attack (ScavTrap's) ===" << std::endl;
	diamond.attack("Enemy");

	std::cout << "\n=== Testing inherited special abilities ===" << std::endl;
	diamond.guardGate();
	diamond.highFivesGuys();

	std::cout << "\n=== Testing inherited functions ===" << std::endl;
	diamond.takeDamage(30);
	diamond.beRepaired(10);

	std::cout << "\n=== Testing copy ===" << std::endl;
	DiamondTrap diamond2(diamond);
	diamond2.whoAmI();

	std::cout << "\n=== Destruction (reverse order) ===" << std::endl;
	return 0;
}
