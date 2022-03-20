#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{

}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();

	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	collisionCheck();

	deleteDeadEnemies();
}


void PlayScene::clean()
{
	CleanObjects();
	removeAllChildren();
	SoundManager::Instance().stopMusic(0);
	SoundManager::Instance().unload("Level-Music", SOUND_MUSIC);
	SoundManager::Instance().unload("Boss-Music", SOUND_MUSIC);
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_MINUS))
	{
		TheGame::Instance().changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_EQUALS))
	{
		TheGame::Instance().changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	std::string m_guiTitle = "Play Scene";

	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer, OBJECTS);
	m_pPlayer->setCanMove(true);


	//Ui
	m_scoreCounter = 0;

	// Music
	SoundManager::Instance().load("../Assets/audio/Aftermath.mp3", "Level-Music", SOUND_MUSIC);
	SoundManager::Instance().load("../Assets/audio/Boss.mp3", "Boss-Music", SOUND_MUSIC);
	SoundManager::Instance().playMusic("Level-Music", -1, 0);
	SoundManager::Instance().setMusicVolume(3);

	// Enemy death sound
	SoundManager::Instance().load("../Assets/audio/SkullDeath.wav", "Skull-Death", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/ZombieDeath.mp3", "Zombie-Death", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/SpellCaster.mp3", "SpellCaster-Death", SOUND_SFX);
	SoundManager::Instance().setSoundVolume(6);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}


int PlayScene::getScore()
{
	return m_scoreCounter;
}


void PlayScene::collisionCheck()
{
	for(auto enemy: m_pEnemies)
	{
		if (CollisionManager::AABBCheck(enemy, m_pPlayer))
		{
			if (enemy->hasCollisionDamage())
			{
				m_pPlayer->takeDamage(enemy->getDamage());
				
			}
			// Can be added stuff if player has collision damage
			if (m_pPlayer->getTransform()->position.x < enemy->getTransform()->position.x)
			{
				m_pPlayer->getTransform()->position.x = m_pPlayer->getTransform()->position.x - 20;
			}
			if (m_pPlayer->getTransform()->position.x > enemy->getTransform()->position.x)
			{
				m_pPlayer->getTransform()->position.x = m_pPlayer->getTransform()->position.x + 20;
			}
			if (m_pPlayer->getTransform()->position.y < enemy->getTransform()->position.y)
			{
				m_pPlayer->getTransform()->position.y = m_pPlayer->getTransform()->position.y - 20;
			}
			if (m_pPlayer->getTransform()->position.y > enemy->getTransform()->position.y)
			{
				m_pPlayer->getTransform()->position.y = m_pPlayer->getTransform()->position.y + 20;
			}
		}
		if (m_pPlayer->getWeapon() != nullptr)
		{
			if (m_pPlayer->getWeapon()->getType() == MELEE_WEAPON)
			{
				if (m_pPlayer->getWeapon()->hasCollisionDamage())
				{
					if (CollisionManager::AABBCheck(enemy, m_pPlayer->getWeapon()))
					{
						
						if (enemy->getLastHitFrame() < m_pPlayer->getWeapon()->getAttackStart())
						{
							enemy->takeDamage(m_pPlayer->getDamage());
						}
					}
				}
			}
			else if (m_pPlayer->getWeapon()->getType() == RANGED_WEAPON)
			{
				for (unsigned i = 0; i < m_pEnemies.size(); i++)
				{
					for (unsigned j = 0; j < m_pPlayersBullets.size(); j++)
					{
						if (CollisionManager::AABBCheck(m_pPlayersBullets[j], m_pEnemies[i]))
						{
							m_pEnemies[i]->takeDamage(m_pPlayer->getWeapon()->getDamage());

							//delete bullet
							removeBullet(m_pPlayersBullets[j]);
						}
					}
				}
			}
		}
	}
	
}


void PlayScene::deleteDeadEnemies()
{
	for (int i = 0; i < m_pEnemies.size(); i++)
	{
		if (!m_pEnemies[i]->isAlive())
		{
			if (dynamic_cast<Skull*>(m_pEnemies[i]))//check if enemy is a skull
			{
				m_scoreCounter++;
				removeChild(m_pEnemies[i]);
				m_pEnemies[i] = nullptr;
				m_pEnemies.erase(m_pEnemies.begin() + i);
				i--;

				SoundManager::Instance().playSound("Skull-Death", 0, -1);
			}
			else if (dynamic_cast<Zombie*>(m_pEnemies[i]))//check if enemy is a zombie
			{
				m_scoreCounter = m_scoreCounter + 2;
				removeChild(m_pEnemies[i]);
				m_pEnemies[i] = nullptr;
				m_pEnemies.erase(m_pEnemies.begin() + i);
				i--;
				//play zombie death sound
				SoundManager::Instance().playSound("Zombie-Death", 0, -1);
			}
			else if (dynamic_cast<SpellCaster*>(m_pEnemies[i]))//check if enemy is a Spell caster
			{
				//play Spellcaster death sound
				SoundManager::Instance().playSound("SpellCaster-Death", 0, -1);
			}
		}
	}
}


void PlayScene::CleanObjects()
{
	for (auto& count : m_pEnemies)
	{
		count = nullptr;
	}

	m_pEnemies.clear();
}

Player* PlayScene::getPlayer()
{
	return m_pPlayer;
}

std::vector<AliveObject*>* PlayScene::getEnemies()
{
	return &m_pEnemies;
}

void PlayScene::addBullet(Bullet* b)
{
	if (b->getOwner() == PLAYER_BULLET)
	{
		m_pPlayersBullets.push_back(b);
	}
	else if (b->getOwner() ==  ENEMY_BULLET)
	{
		m_pEnemiesBullets.push_back(b);
	}
	addChildAfterUpdate(b, BULLETS);
}

void PlayScene::removeBullet(Bullet* b)
{
	if (b->getOwner() == PLAYER_BULLET)
	{
		m_pPlayersBullets.erase(std::remove(m_pPlayersBullets.begin(), m_pPlayersBullets.end(), b), m_pPlayersBullets.end());
	}
	else if(b->getOwner() == ENEMY_BULLET)
	{
		m_pEnemiesBullets.erase(std::remove(m_pEnemiesBullets.begin(), m_pEnemiesBullets.end(), b), m_pEnemiesBullets.end());
	}
	removeChildAfterUpdate(b);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	if(ImGui::Button("My Button"))
	{
		
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if(ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
	}
	
	ImGui::End();
}

void PlayScene::moveAllObjects(glm::vec2 d_pos)
{
	for (auto DisplayObject : getDisplayList())
	{
		if (!dynamic_cast<Player*>(DisplayObject))
		{
			DisplayObject->getTransform()->position += d_pos;
		}
	}
}
