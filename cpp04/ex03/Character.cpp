#include "Character.hpp"

Character::Character() : _name("unnamed"), _floor(NULL), _floorCount(0), _floorCapacity(0) {
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
}

Character::Character(std::string const & name) : _name(name), _floor(NULL), _floorCount(0), _floorCapacity(0) {
	for (int i = 0; i < 4; i++)
		_inventory[i] = NULL;
}

Character::Character(const Character& other) : _name(other._name), _floor(NULL), _floorCount(0), _floorCapacity(0) {
	for (int i = 0; i < 4; i++) {
		if (other._inventory[i])
			_inventory[i] = other._inventory[i]->clone();
		else
			_inventory[i] = NULL;
	}
}

Character& Character::operator=(const Character& other) {
	if (this != &other) {
		_name = other._name;
		for (int i = 0; i < 4; i++) {
			delete _inventory[i];
			if (other._inventory[i])
				_inventory[i] = other._inventory[i]->clone();
			else
				_inventory[i] = NULL;
		}
	}
	return *this;
}

Character::~Character() {
	for (int i = 0; i < 4; i++)
		delete _inventory[i];
	for (int i = 0; i < _floorCount; i++)
		delete _floor[i];
	delete[] _floor;
}

void Character::addToFloor(AMateria* m) {
	if (_floorCount >= _floorCapacity) {
		int newCapacity = _floorCapacity == 0 ? 4 : _floorCapacity * 2;
		AMateria** newFloor = new AMateria*[newCapacity];
		for (int i = 0; i < _floorCount; i++)
			newFloor[i] = _floor[i];
		delete[] _floor;
		_floor = newFloor;
		_floorCapacity = newCapacity;
	}
	_floor[_floorCount++] = m;
}

std::string const & Character::getName() const {
	return _name;
}

void Character::equip(AMateria* m) {
	if (!m)
		return;
	for (int i = 0; i < 4; i++) {
		if (_inventory[i] == NULL) {
			_inventory[i] = m;
			return;
		}
	}
}

void Character::unequip(int idx) {
	if (idx < 0 || idx >= 4 || _inventory[idx] == NULL)
		return;
	addToFloor(_inventory[idx]);
	_inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx >= 4 || _inventory[idx] == NULL)
		return;
	_inventory[idx]->use(target);
}
