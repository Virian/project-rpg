#include "Gui.h"
#include <Windows.h>

Gui::Gui()
{
	if (!font.loadFromFile("game_over.ttf")) /*Reminder - do zmiany sciezka, mozna tez zmienic czcionke*/
	{
		MessageBox(NULL, "Font not found!", "ERROR", NULL);
		return;
	}
	currHp.setFont(font);
	currHp.setCharacterSize(90);
	maximHp.setFont(font);
	maximHp.setCharacterSize(45);
	experience.setFont(font);
	experience.setCharacterSize(100);
	texture.loadFromFile("placeholder.png");
	hpGauge.setTexture(texture);
	hpGauge.setTextureRect(IntRect(0, 1024, 128, 128));
	expGauge.setTexture(texture);
	expGauge.setTextureRect(IntRect(0, 896, 128, 128));
	skill1.setSize(Vector2f(64, 64));
	skill2.setSize(Vector2f(64, 64));
	skill3.setSize(Vector2f(64, 64));

	skill1.setFillColor(Color::Green);
	skill2.setFillColor(Color::Green);
	skill3.setFillColor(Color::Green);	

	flash.restart();

	pauseMenu.setSize(Vector2f(350, 450));
	resumeButton.setSize(Vector2f(320, 100));
	loadButton.setSize(Vector2f(320, 100));
	quitButton.setSize(Vector2f(320, 100));
	
	pauseMenu.setFillColor(Color::Black);
	pauseMenu.setOutlineThickness(-2);
	pauseMenu.setOutlineColor(Color::White);
	resumeButton.setFillColor(Color::Cyan);
	resumeButton.setOutlineColor(Color::Red);
	loadButton.setFillColor(Color::Magenta);
	loadButton.setOutlineColor(Color::Red);
	quitButton.setFillColor(Color::White);
	quitButton.setOutlineColor(Color::Red);

	backpackBackground.setSize(Vector2f(680, 296));
	activeEquipment.setSize(Vector2f(300, 440));
	characterInfo.setSize(Vector2f(680, 360));
	itemInfo.setSize(Vector2f(300, 216));

	backpackSlot.setTexture(texture);
	backpackSlot.setTextureRect(IntRect(0, 768, 128, 128));

	backpackBackground.setFillColor(Color::Black);
	backpackBackground.setOutlineThickness(-2);
	backpackBackground.setOutlineColor(Color::White);
	activeEquipment.setFillColor(Color::Black);
	activeEquipment.setOutlineThickness(-2);
	activeEquipment.setOutlineColor(Color::White);
	characterInfo.setFillColor(Color::Black);
	characterInfo.setOutlineThickness(-2);
	characterInfo.setOutlineColor(Color::White);
	itemInfo.setFillColor(Color::Black);
	itemInfo.setOutlineThickness(-2);
	itemInfo.setOutlineColor(Color::White);

	activeEquipmentHeader.setFont(font);
	activeEquipmentHeader.setCharacterSize(80);
	activeEquipmentHeader.setStyle(Text::Bold);
	activeEquipmentHeader.setString("Active equipment");
	characterInfoHeader.setFont(font);
	characterInfoHeader.setCharacterSize(80);
	characterInfoHeader.setStyle(Text::Bold);
	characterInfoHeader.setString("Character information");
	itemInfoHeader.setFont(font);
	itemInfoHeader.setCharacterSize(80);
	itemInfoHeader.setStyle(Text::Bold);
	itemInfoHeader.setString("Item information");

	playerStats.setFont(font);
	playerStats.setCharacterSize(55);
	itemStats.setFont(font);
	itemStats.setCharacterSize(55);
	activeEquipmentInfo.setFont(font);
	activeEquipmentInfo.setCharacterSize(65);
}

Gui::~Gui()
{

}

void Gui::drawScreen(RenderWindow &window, Player* player)
{
	short currentHp = player->getHp();
	short maxHp = player->getMaxHp();
	unsigned exp = player->getExp();
	unsigned expForNextLevel = player->getExpForNextLevel();
	
	for (size_t i = 0; i < damageInfo.size(); ++i)
	{
		if (damageInfo[i]->lifeTime.getElapsedTime() > seconds(0.6))
		{
			delete damageInfo[i];
			damageInfo.erase(damageInfo.begin() + i);
		}
		else
		{
			window.draw(damageInfo[i]->text);
			if (damageInfo[i]->tick.getElapsedTime() > milliseconds(10))
			{
				damageInfo[i]->text.move(0.0f, -1.0f);
				damageInfo[i]->tick.restart();
			}
		}
	}

	float hpPercent = (static_cast<float>(currentHp) / static_cast<float>(maxHp)) * 100.0f;
	if ((hpPercent <= 100) && (hpPercent > 500.0f/6.0f)) hpGauge.setTextureRect(IntRect(0, 1024, 128, 128));
	else if ((hpPercent <= 500.0f / 6.0f) && (hpPercent > 400.0f / 6.0f)) hpGauge.setTextureRect(IntRect(128, 1024, 128, 128));
	else if ((hpPercent <= 400.0f / 6.0f) && (hpPercent > 50)) hpGauge.setTextureRect(IntRect(256, 1024, 128, 128));
	else if ((hpPercent <= 50) && (hpPercent > 200.0f / 6.0f)) hpGauge.setTextureRect(IntRect(384, 1024, 128, 128));
	else if ((hpPercent <= 200.0f / 6.0f) && (hpPercent > 100.0f / 6.0f)) hpGauge.setTextureRect(IntRect(512, 1024, 128, 128));
	else if ((hpPercent <= 100.0f / 6.0f) && (hpPercent > 0))
	{
		if (flash.getElapsedTime().asSeconds() > 0.5 && flash.getElapsedTime().asSeconds() <= 1)
			hpGauge.setTextureRect(IntRect(768, 1024, 128, 128));
		else if (flash.getElapsedTime().asSeconds() > 1)
		{
			hpGauge.setTextureRect(IntRect(640, 1024, 128, 128));
			flash.restart();
		}
	}

	float expPercent = (static_cast<float>(exp) / static_cast<float>(expForNextLevel)) * 100.0f;
	if ((expPercent <= 100) && (expPercent > 500.0f / 6.0f)) expGauge.setTextureRect(IntRect(0, 896, 128, 128));
	else if ((expPercent <= 500.0f / 6.0f) && (expPercent > 400.0f / 6.0f)) expGauge.setTextureRect(IntRect(128, 896, 128, 128));
	else if ((expPercent <= 400.0f / 6.0f) && (expPercent > 50)) expGauge.setTextureRect(IntRect(256, 896, 128, 128));
	else if ((expPercent <= 50) && (expPercent > 200.0f / 6.0f)) expGauge.setTextureRect(IntRect(384, 896, 128, 128));
	else if ((expPercent <= 200.0f / 6.0f) && (expPercent > 100.0f / 6.0f)) expGauge.setTextureRect(IntRect(512, 896, 128, 128));
	else if ((expPercent <= 100.0f / 6.0f) && (expPercent >= 0)) expGauge.setTextureRect(IntRect(640, 896, 128, 128));

	hpGauge.setPosition(window.mapPixelToCoords(Vector2i(36, 570)));
	expGauge.setPosition(window.mapPixelToCoords(Vector2i(1116, 570)));
	skill1.setPosition(window.mapPixelToCoords(Vector2i(482, 636)));
	skill2.setPosition(window.mapPixelToCoords(Vector2i(608, 636)));
	skill3.setPosition(window.mapPixelToCoords(Vector2i(734, 636)));

	currHp.setString(std::to_string(currentHp));
	maximHp.setString(std::to_string(maxHp));
	experience.setString(std::to_string(static_cast<int>(expPercent)) + "%");
	
	if (currentHp > 99) currHp.setPosition(window.mapPixelToCoords(Vector2i(70, 550))); /*Reminder - fajnie by bylo dodac zeby pozycja zalezala od ilosci cyfr*/
	else if (currentHp <= 99 && currentHp > 9) currHp.setPosition(window.mapPixelToCoords(Vector2i(78, 550)));
	else currHp.setPosition(window.mapPixelToCoords(Vector2i(86, 550)));
	maximHp.setPosition(window.mapPixelToCoords(Vector2i(85, 610)));
	experience.setPosition(window.mapPixelToCoords(Vector2i(1142, 546)));

	window.draw(hpGauge);
	window.draw(expGauge);
	window.draw(skill1);
	window.draw(skill2);
	window.draw(skill3);
	currHp.move(Vector2f(2, 2));
	currHp.setColor(Color::Black);
	window.draw(currHp);
	currHp.move(Vector2f(-2, -2));
	currHp.setColor(Color::White);
	window.draw(currHp);
	maximHp.move(Vector2f(2, 2));
	maximHp.setColor(Color::Black);
	window.draw(maximHp);
	maximHp.move(Vector2f(-2, -2));
	maximHp.setColor(Color::White);
	window.draw(maximHp);
	experience.move(Vector2f(2, 2));
	experience.setColor(Color::Black);
	window.draw(experience);
	experience.move(Vector2f(-2, -2));
	experience.setColor(Color::White);
	window.draw(experience);
}

void Gui::drawPauseMenu(RenderWindow &window)
{
	pauseMenu.setPosition(window.mapPixelToCoords(Vector2i(465, 135)));
	resumeButton.setPosition(window.mapPixelToCoords(Vector2i(480, 172)));
	loadButton.setPosition(window.mapPixelToCoords(Vector2i(480, 310)));
	quitButton.setPosition(window.mapPixelToCoords(Vector2i(480, 447)));
	
	window.draw(pauseMenu);
	window.draw(resumeButton);
	window.draw(loadButton);
	window.draw(quitButton);
}

void Gui::drawEquipment(RenderWindow &window, Player* player, short position)
{
	vector<Item*> backpack;
	Weapon* activeWeapon;
	Armor* activeArmor;
	
	backpackBackground.setPosition(window.mapPixelToCoords(Vector2i(120, 398)));
	activeEquipment.setPosition(window.mapPixelToCoords(Vector2i(860, 254)));
	characterInfo.setPosition(window.mapPixelToCoords(Vector2i(120, 26)));
	itemInfo.setPosition(window.mapPixelToCoords(Vector2i(860, 26)));

	activeEquipmentHeader.setPosition(window.mapPixelToCoords(Vector2i(870, 214)));
	characterInfoHeader.setPosition(window.mapPixelToCoords(Vector2i(130, -14)));
	itemInfoHeader.setPosition(window.mapPixelToCoords(Vector2i(870, -14)));

	playerStats.setString("Name: " + player->getName() + "\nClass: " + player->getClassName() + "\nLevel: " + to_string(player->getLvl())
		+ "\nExperience: " + to_string(player->getExp()) + "\nExperience to level up: " + to_string(player->getExpForNextLevel())
		+ "\nStrength: " + to_string(player->getStr()) + "\nIntelligence: " + to_string(player->getInt()) + "\nAgility: "
		+ to_string(player->getAgi()));
	playerStats.setPosition(window.mapPixelToCoords(Vector2i(130, 40)));

	backpack = player->getEquipment().getBackpack();
	activeArmor = player->getEquipment().getActiveArmor();
	activeWeapon = player->getEquipment().getActiveWeapon();

	if (position == -1) itemStats.setString("");
	else if ((position == -2) && (activeWeapon != NULL))
	{
		if (activeWeapon->isRanged()) itemStats.setString(activeWeapon->getName() + "\nAttack: " + to_string(activeWeapon->getAttackValue()) + "\nRange: Ranged");
		else itemStats.setString(activeWeapon->getName() + "\nAttack: " + to_string(activeWeapon->getAttackValue()) + "\nRange: Melee");
	}
	else if ((position == -3) && (activeArmor != NULL)) itemStats.setString(activeArmor->getName() + "\nArmor: " + to_string(activeArmor->getArmorValue()));
	else
	{
		if (position < backpack.size())
		{
			Weapon* temp1;
			Armor* temp2;
			if (temp1 = dynamic_cast<Weapon*>(backpack[position]))
			{				
				if (temp1->isRanged()) itemStats.setString(backpack[position]->getName() + "\nAttack: " + to_string(temp1->getAttackValue()) + "\nRange: Ranged");
				else itemStats.setString(backpack[position]->getName() + "\nAttack: " + to_string(temp1->getAttackValue()) + "\nRange: Melee");
			}
			else if (temp2 = dynamic_cast<Armor*>(backpack[position]))
				itemStats.setString(backpack[position]->getName() + "\nArmor: " + to_string(temp2->getArmorValue()));
		}
	}
	itemStats.setPosition(window.mapPixelToCoords(Vector2i(870, 40)));

	window.draw(backpackBackground);
	window.draw(activeEquipment);
	window.draw(characterInfo);
	window.draw(itemInfo);
	window.draw(activeEquipmentHeader);
	window.draw(characterInfoHeader);
	window.draw(itemInfoHeader);
	window.draw(playerStats);
	window.draw(itemStats);

	for (short i = 0; i < 2; ++i)
	{
		for (short j = 0; j < 5; ++j)
		{
			backpackSlot.setPosition(window.mapPixelToCoords(Vector2i(140 + j * 128, 418 + i * 128)));
			window.draw(backpackSlot);
		}
	}
	activeEquipmentInfo.setString("Weapon");
	activeEquipmentInfo.setPosition(window.mapPixelToCoords(Vector2i(960, 264)));
	backpackSlot.setPosition(window.mapPixelToCoords(Vector2i(946, 340)));
	window.draw(backpackSlot);
	window.draw(activeEquipmentInfo);
	activeEquipmentInfo.setString("Armor");
	activeEquipmentInfo.setPosition(window.mapPixelToCoords(Vector2i(970, 446)));
	backpackSlot.setPosition(window.mapPixelToCoords(Vector2i(946, 520)));
	window.draw(backpackSlot);
	window.draw(activeEquipmentInfo);
	
	for (size_t i = 0, j = 0; i < backpack.size(); ++i)
	{
		if (i == 5) ++j;
		backpack[i]->setPosition(window.mapPixelToCoords(Vector2i(140 + i * 128 - 5 * j * 128, 418 + j * 128)));
		window.draw(*backpack[i]);
	}

	if (activeWeapon != NULL)
	{
		activeWeapon->setPosition(window.mapPixelToCoords(Vector2i(946, 340)));
		window.draw(*activeWeapon);
	}
	if (activeArmor != NULL)
	{
		activeArmor->setPosition(window.mapPixelToCoords(Vector2i(946, 520)));
		window.draw(*activeArmor);
	}	
}

void Gui::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(hpGauge);
	target.draw(expGauge);
	target.draw(skill1);
	target.draw(skill2);
	target.draw(skill3);
}

RectangleShape Gui::getResumeButton()
{
	return resumeButton;
}

RectangleShape Gui::getLoadButton()
{
	return loadButton;
}

RectangleShape Gui::getQuitButton()
{
	return quitButton;
}

void Gui::setResumeHighlight(short swtch)
{
	if (swtch == 0) resumeButton.setOutlineThickness(0);
	else resumeButton.setOutlineThickness(-4);
}

void Gui::setLoadHighlight(short swtch)
{
	if (swtch == 0) loadButton.setOutlineThickness(0);
	else loadButton.setOutlineThickness(-4);
}

void Gui::setQuitHighlight(short swtch)
{
	if (swtch == 0) quitButton.setOutlineThickness(0);
	else quitButton.setOutlineThickness(-4);
}

void Gui::pushDamageInfo(TextDamage* newText, std::string damageValue)
{
	newText->text.setFont(font);
	newText->text.setColor(Color::Red);
	newText->text.setCharacterSize(40);
	newText->text.setString(damageValue);
	/*setstring*/
	/*setposition*/
	newText->tick.restart();
	newText->lifeTime.restart();
	damageInfo.push_back(newText);
}