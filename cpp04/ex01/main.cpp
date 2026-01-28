#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main() {
	std::cout << "=== Subject tests ===" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	delete j;
	delete i;

	std::cout << "\n=== Array of Animals ===" << std::endl;
	const int size = 10;
	Animal* animals[size];

	for (int k = 0; k < size / 2; k++) {
		animals[k] = new Dog();
	}
	for (int k = size / 2; k < size; k++) {
		animals[k] = new Cat();
	}

	std::cout << "\n=== Making sounds ===" << std::endl;
	for (int k = 0; k < size; k++) {
		animals[k]->makeSound();
	}

	std::cout << "\n=== Deleting Animals ===" << std::endl;
	for (int k = 0; k < size; k++) {
		delete animals[k];
	}

	std::cout << "\n=== Deep copy test ===" << std::endl;
	Dog originalDog;
	originalDog.getBrain()->ideas[0] = "I want to chase cats";
	originalDog.getBrain()->ideas[1] = "I love bones";

	Dog copyDog(originalDog);
	std::cout << "Original Dog idea[0]: " << originalDog.getBrain()->ideas[0] << std::endl;
	std::cout << "Copy Dog idea[0]: " << copyDog.getBrain()->ideas[0] << std::endl;

	copyDog.getBrain()->ideas[0] = "I want to sleep";
	std::cout << "\nAfter modifying copy:" << std::endl;
	std::cout << "Original Dog idea[0]: " << originalDog.getBrain()->ideas[0] << std::endl;
	std::cout << "Copy Dog idea[0]: " << copyDog.getBrain()->ideas[0] << std::endl;

	std::cout << "\n=== Assignment operator test ===" << std::endl;
	Dog assignDog;
	assignDog = originalDog;
	std::cout << "Assigned Dog idea[0]: " << assignDog.getBrain()->ideas[0] << std::endl;

	std::cout << "\n=== End of main ===" << std::endl;
	return 0;
}
