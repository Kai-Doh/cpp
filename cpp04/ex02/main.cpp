#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main() {
	// This line would cause a compile error because Animal is abstract:
	// Animal animal;  // Error: cannot instantiate abstract class

	std::cout << "=== Creating concrete animals ===" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	j->makeSound();
	i->makeSound();

	delete j;
	delete i;

	std::cout << "\n=== Array of Animals ===" << std::endl;
	const int size = 4;
	Animal* animals[size];

	for (int k = 0; k < size / 2; k++) {
		animals[k] = new Dog();
	}
	for (int k = size / 2; k < size; k++) {
		animals[k] = new Cat();
	}

	std::cout << "\n=== Making sounds ===" << std::endl;
	for (int k = 0; k < size; k++) {
		std::cout << animals[k]->getType() << ": ";
		animals[k]->makeSound();
	}

	std::cout << "\n=== Deleting Animals ===" << std::endl;
	for (int k = 0; k < size; k++) {
		delete animals[k];
	}

	std::cout << "\n=== Deep copy test ===" << std::endl;
	Dog dog;
	dog.getBrain()->ideas[0] = "Chase the cat!";

	Dog dogCopy(dog);
	std::cout << "Original: " << dog.getBrain()->ideas[0] << std::endl;
	std::cout << "Copy: " << dogCopy.getBrain()->ideas[0] << std::endl;

	dogCopy.getBrain()->ideas[0] = "Sleep all day";
	std::cout << "\nAfter modifying copy:" << std::endl;
	std::cout << "Original: " << dog.getBrain()->ideas[0] << std::endl;
	std::cout << "Copy: " << dogCopy.getBrain()->ideas[0] << std::endl;

	std::cout << "\n=== End of main ===" << std::endl;
	return 0;
}
