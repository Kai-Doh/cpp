#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include <iostream>

int main() {
	// Subject's tests
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;

	std::cout << std::endl << "--- Additional tests ---" << std::endl << std::endl;

	// Test deep copy
	Character original("original");
	original.equip(new Ice());
	original.equip(new Cure());

	Character copy(original);
	std::cout << "Original uses materias:" << std::endl;
	Character target("target");
	original.use(0, target);
	original.use(1, target);

	std::cout << "Copy uses materias:" << std::endl;
	copy.use(0, target);
	copy.use(1, target);

	// Test unequip
	std::cout << std::endl << "Testing unequip:" << std::endl;
	Character charlie("charlie");
	AMateria* ice = new Ice();
	charlie.equip(ice);
	charlie.use(0, target);
	charlie.unequip(0);
	charlie.use(0, target); // Should do nothing

	// Test assignment operator
	std::cout << std::endl << "Testing assignment:" << std::endl;
	Character assigned("assigned");
	assigned = original;
	assigned.use(0, target);
	assigned.use(1, target);

	// Test full inventory
	std::cout << std::endl << "Testing full inventory:" << std::endl;
	Character full("full");
	full.equip(new Ice());
	full.equip(new Cure());
	full.equip(new Ice());
	full.equip(new Cure());
	AMateria* extra = new Ice();
	full.equip(extra); // Should not equip, inventory full
	delete extra; // Need to manually delete since it wasn't equipped

	std::cout << "Full inventory uses:" << std::endl;
	full.use(0, target);
	full.use(1, target);
	full.use(2, target);
	full.use(3, target);

	return 0;
}
