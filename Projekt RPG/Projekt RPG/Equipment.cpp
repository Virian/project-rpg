#include "Equipment.h"

Equipment::Equipment()
{
	potionCount = 0;
	activeArmor = NULL;
	activeWeapon = NULL;
	/*stworzenie losowych przedmiotow*/
	activeArmor = new Armor(1);
	short randomWeapon = rand() % 2;
	if (randomWeapon == 0) activeWeapon = new Weapon(false, 1); /*bron melee*/
	else activeWeapon = new Weapon(true, 1); /*bron dystansowa*/
}

Equipment::~Equipment()
{
	/*wyczyszczenie z pamieci*/
	if (activeWeapon) delete activeWeapon;
	if (activeArmor) delete activeArmor;
	for (size_t i = 0; i < backpack.size(); ++i) delete backpack[i];
	backpack.clear();
}

std::vector<Item*> Equipment::getBackpack()
{
	return backpack;
}

Weapon* Equipment::getActiveWeapon()
{
	return activeWeapon;
}

Armor* Equipment::getActiveArmor()
{
	return activeArmor;
}

void Equipment::addItem(Item* newItem)
{
	backpack.push_back(newItem);
}

void Equipment::clearBackpack()
{
	if (activeWeapon) delete activeWeapon;
	if (activeArmor) delete activeArmor;
	for (size_t i = 0; i < backpack.size(); ++i)
	{
		delete backpack[i];
	}
	backpack.clear();
}

void Equipment::deleteItem(short position)
{
	if (position == -1) /*usuwa aktywna bron*/
	{
		delete activeWeapon;
		activeWeapon = NULL;
	}
	else if (position == -2) /*usuwa aktywna zbroje*/
	{
		delete activeArmor;
		activeArmor = NULL;
	}
	else if(position < backpack.size()) /*usuwa przedmiot z plecaka*/
	{
		delete backpack[position];
		backpack.erase(backpack.begin() + position);
	}
}

void Equipment::swapActiveItem(short position)
{
	if (position == -1) /*zdjecie aktywnej broni*/
	{
		if ((backpack.size() + 1 <= backpackSize) && (activeWeapon != NULL))
		{
			backpack.push_back(activeWeapon);
			activeWeapon = NULL;
		}
	}
	else if (position == -2) /*zdjecie aktywnej zbroi*/
	{
		if ((backpack.size() + 1 <= backpackSize) && (activeArmor != NULL))
		{
			backpack.push_back(activeArmor);
			activeArmor = NULL;
		}
	}
	else if (position < backpack.size()) /*zamiana przedmiotu z plecaka z aktywnym przedmiotem*/
	{
		Weapon* temp1;
		Armor* temp2;
		if (temp1 = dynamic_cast<Weapon*>(backpack[position])) /*sprawdzenie czy zadany przedmiot jest bronia czy zbroja*/
		{
			if (activeWeapon == NULL) backpack.erase(backpack.begin() + position);
			else backpack[position] = activeWeapon;
			activeWeapon = temp1;
		}
		else if (temp2 = dynamic_cast<Armor*>(backpack[position]))
		{
			if (activeArmor == NULL) backpack.erase(backpack.begin() + position);
			else backpack[position] = activeArmor;
			activeArmor = temp2;
		}
	}
}

unsigned short Equipment::usePotion()
{
	if (potionCount > 0)
	{
		--potionCount;
		return 0;
	}
	else return 1;
}

short Equipment::getPotionCount()
{
	return potionCount;
}

void Equipment::setPotionCount(short _count)
{
	potionCount = _count;
}

void Equipment::addPotion()
{
	++potionCount;
}