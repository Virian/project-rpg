#pragma once
#include "Item.h"
#include <vector>

class Equipment
{
private:
	Weapon* activeWeapon;
	Armor* activeArmor;
	std::vector<Item*> backpack;
	short potionCount;
public:
	static const int backpackSize = 10;
	Equipment();
	~Equipment();
	std::vector<Item*> getBackpack();
	Weapon* getActiveWeapon();
	Armor* getActiveArmor();
	void addItem(Item*);
	void clearBackpack();
	void deleteItem(short);
	void swapActiveItem(short);
	unsigned short usePotion();
	short getPotionCount();
	void setPotionCount(short);
	void addPotion();
};
