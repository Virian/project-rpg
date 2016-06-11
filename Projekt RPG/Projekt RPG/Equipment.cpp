#include "Equipment.h"

Equipment::Equipment()
{
	potionCount = 0;
	activeArmor = NULL;
	activeWeapon = NULL;
	Item* temp1 = new Weapon(true);
	Item* temp2 = new Armor();
	Item* temp3 = new Armor();
	Item* temp4 = new Armor();
	Item* temp5 = new Armor();
	Item* temp6 = new Armor();
	Item* temp7 = new Weapon(true);
	Item* temp8 = new Weapon(false);
	Item* temp9 = new Weapon(false);

	backpack.push_back(temp1);
	backpack.push_back(temp2);
	backpack.push_back(temp3);
	backpack.push_back(temp4);
	backpack.push_back(temp5);
	backpack.push_back(temp6);
	backpack.push_back(temp7);
	backpack.push_back(temp8);
	backpack.push_back(temp9);

	activeArmor = new Armor();
	activeWeapon = new Weapon(true);
}

Equipment::~Equipment()
{
	
}

vector<Item*> Equipment::getBackpack()
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
	for (size_t i = 0; i < backpack.size(); ++i)
	{
		delete backpack[i];
	}
	backpack.clear();
}

void Equipment::deleteItem(short position)
{
	if (position == -1)
	{
		delete activeWeapon;
		activeWeapon = NULL;
	}
	else if (position == -2)
	{
		delete activeArmor;
		activeArmor = NULL;
	}
	else if(position < backpack.size())
	{
		delete backpack[position];
		backpack.erase(backpack.begin() + position);
	}
}

void Equipment::swapActiveItem(short position)
{
	if (position == -1)
	{
		if ((backpack.size() + 1 <= backpackSize) && (activeWeapon != NULL))
		{
			backpack.push_back(activeWeapon);
			activeWeapon = NULL;
		}
	}
	else if (position == -2)
	{
		if ((backpack.size() + 1 <= backpackSize) && (activeArmor != NULL))
		{
			backpack.push_back(activeArmor);
			activeArmor = NULL;
		}
	}
	else if (position < backpack.size())
	{
		Weapon* temp1;
		Armor* temp2;
		if (temp1 = dynamic_cast<Weapon*>(backpack[position]))
		{
			if (activeWeapon == NULL) backpack.erase(backpack.begin() + position);
			else backpack[position] = activeWeapon;
			activeWeapon = temp1;
		}
		if (temp2 = dynamic_cast<Armor*>(backpack[position]))
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