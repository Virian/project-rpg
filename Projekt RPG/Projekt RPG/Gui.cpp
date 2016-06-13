#include "Gui.h"
#include <Windows.h>

Gui::Gui()
{
	if (!font.loadFromFile("fonts/game_over.ttf")) /*Reminder - do zmiany sciezka, mozna tez zmienic czcionke*/
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
	potions.setFont(font);
	potions.setCharacterSize(70);
	texture.loadFromFile("images/tilesheet.png");
	hpGauge.setTexture(texture);
	hpGauge.setTextureRect(IntRect(0, 1024, 128, 128));
	expGauge.setTexture(texture);
	expGauge.setTextureRect(IntRect(0, 896, 128, 128));
	skill1.setSize(Vector2f(64, 64));
	skill2.setSize(Vector2f(64, 64));
	skill3.setSize(Vector2f(64, 64));

	skill1.setTexture(&texture);
	skill2.setTexture(&texture);
	skill3.setTexture(&texture);
	fadedSkill1.setTexture(&texture);
	fadedSkill2.setTexture(&texture);
	fadedSkill3.setTexture(&texture);

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

	plus.setSize(Vector2f(20, 20));
	plus.setFillColor(Color::Green);

	levelMenu.setSize(Vector2f(350, 550));
	levelMenu.setFillColor(Color::Black);
	levelMenu.setOutlineThickness(-2.f);
	levelMenu.setOutlineColor(Color::White);
	Text header;
	Text information;
	Text option1, option2, option3, option4, option5;
	header.setString("Choose level:");
	information.setString("Press ESC to go back.");
	option1.setString("1 - Level1");
	option2.setString("2 - Level2");
	option3.setString("3 - Level3");
	option4.setString("4 - Level4");
	option5.setString("5 - Level5");
	levelOptions.push_back(header);
	levelOptions.push_back(option1);
	levelOptions.push_back(option2);
	levelOptions.push_back(option3);
	levelOptions.push_back(option4);
	levelOptions.push_back(option5);
	levelOptions.push_back(information);
	for (size_t i = 0; i < levelOptions.size(); ++i)
	{
		levelOptions[i].setFont(font);
		levelOptions[i].setCharacterSize(70);
	}
}

Gui::~Gui()
{
	for (size_t i = 0; i < damageInfo.size(); ++i)
	{
		delete damageInfo[i];
	}
	for (size_t i = 0; i < hpInfo.size(); ++i)
	{
		delete hpInfo[i];
	}
}

Gui::HpBar::HpBar()
{
	currentHp.setFillColor(Color::Red);
	missingHp.setFillColor(Color(120, 0, 0));
}

void Gui::setSkillPictures(string className)
{
	if (className == "Soldier")
	{
		skill1.setTextureRect(IntRect(0, 1152, 64, 64));
		fadedSkill1.setTextureRect(IntRect(64, 1152, 64, 64));
		skill2.setTextureRect(IntRect(128, 1152, 64, 64));
		fadedSkill2.setTextureRect(IntRect(192, 1152, 64, 64));
		skill3.setTextureRect(IntRect(256, 1152, 64, 64));
		fadedSkill3.setTextureRect(IntRect(320, 1152, 64, 64));
	}
	else if (className == "Sentinel")
	{
		skill1.setTextureRect(IntRect(0, 1216, 64, 64));
		fadedSkill1.setTextureRect(IntRect(64, 1216, 64, 64));
		skill2.setTextureRect(IntRect(128, 1216, 64, 64));
		fadedSkill2.setTextureRect(IntRect(192, 1216, 64, 64));
		skill3.setTextureRect(IntRect(256, 1216, 64, 64));
		fadedSkill3.setTextureRect(IntRect(320, 1216, 64, 64));
	}
	else
	{
		skill1.setTextureRect(IntRect(0, 1280, 64, 64));
		fadedSkill1.setTextureRect(IntRect(64, 1280, 64, 64));
		skill2.setTextureRect(IntRect(128, 1280, 64, 64));
		fadedSkill2.setTextureRect(IntRect(192, 1280, 64, 64));
		skill3.setTextureRect(IntRect(256, 1280, 64, 64));
		fadedSkill3.setTextureRect(IntRect(320, 1280, 64, 64));
	}
}

void Gui::drawScreen(RenderWindow &window, Player* player)
{
	short currentHp = player->getHp();
	short maxHp = player->getMaxHp();
	unsigned exp = player->getExp();
	unsigned expForNextLevel = player->getExpForNextLevel();
	
	for (size_t i = 0; i < damageInfo.size(); ++i)
	{
		if (damageInfo[i]->lifeTime.getElapsedTime() > seconds(0.6f))
		{
			delete damageInfo[i];
			damageInfo.erase(damageInfo.begin() + i);
		}
		else
		{
			window.draw(damageInfo[i]->text);
			if (damageInfo[i]->tick.getElapsedTime() > milliseconds(10))
			{
				Color tempColor;

				damageInfo[i]->text.move(0.0f, -1.0f);
				tempColor = damageInfo[i]->text.getColor();
				tempColor.a -= 4;
				damageInfo[i]->text.setColor(tempColor);
				damageInfo[i]->tick.restart();
			}
		}
	}

	for (size_t i = 0; i < hpInfo.size(); ++i)
	{
		hpInfo[i]->currentHp.setPosition(Vector2f(hpInfo[i]->characterPosition.x - 32, hpInfo[i]->characterPosition.y - 24));
		hpInfo[i]->missingHp.setPosition(Vector2f(hpInfo[i]->characterPosition.x - 32 + hpInfo[i]->currentHp.getGlobalBounds().width, hpInfo[i]->characterPosition.y - 24));
		window.draw(hpInfo[i]->currentHp);
		window.draw(hpInfo[i]->missingHp);
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

	currHp.setString(std::to_string(currentHp));
	maximHp.setString(std::to_string(maxHp));
	experience.setString(std::to_string(static_cast<int>(expPercent)) + "%");
	potions.setString("Potions: " + std::to_string(player->getEquipment().getPotionCount()));
	
	if (currentHp > 99) currHp.setPosition(window.mapPixelToCoords(Vector2i(70, 550))); /*Reminder - fajnie by bylo dodac zeby pozycja zalezala od ilosci cyfr*/
	else if (currentHp <= 99 && currentHp > 9) currHp.setPosition(window.mapPixelToCoords(Vector2i(78, 550)));
	else currHp.setPosition(window.mapPixelToCoords(Vector2i(86, 550)));
	maximHp.setPosition(window.mapPixelToCoords(Vector2i(85, 610)));
	experience.setPosition(window.mapPixelToCoords(Vector2i(1142, 546)));
	potions.setPosition(window.mapPixelToCoords(Vector2i(170, 625)));

	window.draw(hpGauge);
	window.draw(expGauge);
	window.draw(skill1);
	window.draw(skill2);
	window.draw(skill3);
	window.draw(fadedSkill1);
	window.draw(fadedSkill2);
	window.draw(fadedSkill3);
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
	potions.move(Vector2f(2, 2));
	potions.setColor(Color::Black);
	window.draw(potions);
	potions.move(Vector2f(-2, -2));
	potions.setColor(Color::White);
	window.draw(potions);
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
		+ to_string(player->getAgi()) + "\nAvailable points to spend: " + to_string(player->getPointsToSpend()));
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
	if (player->getPointsToSpend() > 0)
	{
		plus.setPosition(window.mapPixelToCoords(Vector2i(340, 235)));
		window.draw(plus);
		plus.setPosition(window.mapPixelToCoords(Vector2i(340, 265)));
		window.draw(plus);
		plus.setPosition(window.mapPixelToCoords(Vector2i(340, 295)));
		window.draw(plus);
	}

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
		backpack[i]->setPosition(window.mapPixelToCoords(Vector2i(static_cast<int>(140 + i * 128 - 5 * j * 128), static_cast<int>(418 + j * 128))));
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

void Gui::drawDeathScreen(RenderWindow& window)
{
	Text info1("You are dead!", font, 200);
	Text info2("Press ENTER to return to the menu", font, 90);

	info1.setPosition(window.mapPixelToCoords(Vector2i(static_cast<int>(window.getSize().x / 2 - info1.getGlobalBounds().width / 2), 120)));
	info2.setPosition(window.mapPixelToCoords(Vector2i(static_cast<int>(window.getSize().x / 2 - info2.getGlobalBounds().width / 2), 400)));

	info1.setColor(Color::Black);
	info1.move(Vector2f(4, 4));
	window.draw(info1);
	info1.setColor(Color::White);
	info1.move(Vector2f(-4, -4));
	window.draw(info1);

	info2.setColor(Color::Black);
	info2.move(Vector2f(4, 4));
	window.draw(info2);
	info2.setColor(Color::White);
	info2.move(Vector2f(-4, -4));
	window.draw(info2);
}

void Gui::drawLevelMenu(RenderWindow &window)
{
	pauseMenu.setPosition(window.mapPixelToCoords(Vector2i(465, 85)));
	window.draw(pauseMenu);
	for (size_t i = 0; i < levelOptions.size(); ++i)
	{
		levelOptions[i].setPosition(window.mapPixelToCoords(Vector2i(480, 60 + i * 45)));
		window.draw(levelOptions[i]);
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

void Gui::pushDamageInfo(TextDamage* newText)
{
	newText->text.setFont(font);
	newText->text.setCharacterSize(40);
	newText->text.move(-newText->text.getGlobalBounds().width / 2, 0.0);
	newText->tick.restart();
	newText->lifeTime.restart();
	damageInfo.push_back(newText);
}

void Gui::pushHpInfo(HpBar* newHpInfo)
{
	hpInfo.push_back(newHpInfo);
}

void Gui::updateHpInfo(size_t i, Vector2f position, short currentHp, short maximumHp)
{
	hpInfo[i]->characterPosition = position;
	hpInfo[i]->currentHp.setSize(Vector2f((static_cast<float>(currentHp) / static_cast<float>(maximumHp)) * 64.f, 6));
	hpInfo[i]->missingHp.setSize(Vector2f(64.f - (static_cast<float>(currentHp) / static_cast<float>(maximumHp)) * 64.f, 6));
}

void Gui::eraseHpInfo(size_t i)
{
	delete hpInfo[i];
	hpInfo.erase(hpInfo.begin() + i);
}

size_t Gui::getHpInfoSize()
{
	return hpInfo.size();
}

void Gui::clearHpInfo()
{
	hpInfo.clear();
}

void Gui::updateSkillCooldowns(RenderWindow &window, float ratioSkill1, float ratioSkill2, float ratioSkill3)
{
	IntRect temp;
	
	fadedSkill1.setSize(Vector2f(64.f, truncf(ratioSkill1 * 64.f)));
	fadedSkill2.setSize(Vector2f(64.f, truncf(ratioSkill2 * 64.f)));
	fadedSkill3.setSize(Vector2f(64.f, truncf(ratioSkill3 * 64.f)));
	/*skill1.setSize(Vector2f(64.f, truncf((1.f - ratioSkill1) * 64.f)));
	skill2.setSize(Vector2f(64.f, truncf((1.f - ratioSkill2) * 64.f)));
	skill3.setSize(Vector2f(64.f, truncf((1.f - ratioSkill3) * 64.f)));*/
	temp = fadedSkill1.getTextureRect();
	temp.height = fadedSkill1.getSize().y;
	fadedSkill1.setTextureRect(temp);
	temp = fadedSkill2.getTextureRect();
	temp.height = fadedSkill2.getSize().y;
	fadedSkill2.setTextureRect(temp);
	temp = fadedSkill3.getTextureRect();
	temp.height = fadedSkill3.getSize().y;
	fadedSkill3.setTextureRect(temp);
	//skill1.setTextureRect(skill1.getTextureRect());
	/*temp = skill1.getTextureRect();
	temp.height = skill1.getSize().y;
	skill1.setTextureRect(temp);
	temp = skill2.getTextureRect();
	temp.height = skill2.getSize().y;
	skill2.setTextureRect(temp);
	temp = skill2.getTextureRect();
	temp.height = skill2.getSize().y;
	skill2.setTextureRect(temp);*/
	fadedSkill1.setPosition(window.mapPixelToCoords(Vector2i(482, 636)));
	fadedSkill2.setPosition(window.mapPixelToCoords(Vector2i(608, 636)));
	fadedSkill3.setPosition(window.mapPixelToCoords(Vector2i(734, 636)));
	/*skill1.setPosition(window.mapPixelToCoords(Vector2i(482, 636 + static_cast<int>(fadedSkill1.getSize().y))));
	skill2.setPosition(window.mapPixelToCoords(Vector2i(608, 636 + static_cast<int>(fadedSkill2.getSize().y))));
	skill3.setPosition(window.mapPixelToCoords(Vector2i(734, 636 + static_cast<int>(fadedSkill3.getSize().y))));*/
	skill1.setPosition(window.mapPixelToCoords(Vector2i(482, 636)));
	skill2.setPosition(window.mapPixelToCoords(Vector2i(608, 636)));
	skill3.setPosition(window.mapPixelToCoords(Vector2i(734, 636)));
}