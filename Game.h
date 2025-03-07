#pragma once

#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <assert.h>
#include "Math.h"
#include "InputSystem.h"
#include "AudioEngine.h"
#include "PlayerCombatSystem.h"
#include "EnemyCombatSystem.h"
#include "LevelUpSystem.h"
#include "Font.h"
#include "Texture.h"
#include <thread>
#include "AStar.h"
#include <utility>

class Game
{
public:
	enum GameState {
		gameplay,
		paused,
		quit
	};

	enum GameScene {
		MAZE_SCENE = 0,
		ENEMY_FIGHT_SCENE,
		BOSS_FIGHT_SCENE,
		END_GAME_SCENE
	};

	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	typedef pair<int, int> Pair;


	class Renderer* GetRenderer() { 
		return renderer; 
	}

	class Skeleton* GetSkeleton(const std::string& fileName);

	class Animation* GetAnimation(const std::string& fileName);

	class CameraTargetActor* GetPlayer() {
		return cameraTargetActor;
	}

	GameState GetState() const {
		return gameState;
	}

	void SetState(GameState state) {
		gameState = state;
	}

	void SetEnemyCollision(bool isCollision) {
		enemyCollision = isCollision;
	}

	void SetStairCollision(bool isCollision) {
		stairCollision = isCollision;
	}

	bool GetEnemyCollision() {
		return enemyCollision;
	}

	int** GetMap2D() {
		return map2D;
	}

	int IsWalkable(int row, int col);
	void Game::SetWalkable(int row, int col);
	void Game::SetEnemyMapPos(int row, int col);
	void Game::SetPlayerMapPos(int row, int col);
	void Game::SetStairMapPos(int row, int col);
	void CombatRound(int atkType);
	Pair Game::EnemySpotted(int row, int col);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void CreatePointLights(Actor*& a, Vector3& pos, int z);
	void UnloadData();
	void UnloadSkelAnim();
	void InitHUD();
	void UnloadHud();
	
	
	std::vector<class Actor*> actors;
	std::vector<class Actor*> pendingActors;

	// Map of loaded skeletons
	std::unordered_map<std::string, class Skeleton*> skeletons;
	// Map of loaded animations
	std::unordered_map<std::string, class Animation*> anims;

	class InputSystem* inputSystem;
	class AudioEngine* AE;
	Studio::EventInstance* currentAudioInstance;
	class Renderer* renderer;
	class Generator* randGen;
	Uint32 ticksCount;
	int scene;
	int level;
	GameState gameState;
	bool isRunning;
	bool isLoading;
	bool updatingActors;
	std::vector<class EnemyActor*> enemies;
	std::vector<class Room*> rooms;

	int exit_posX;
	int exit_posY;
	int start_posX;
	int start_posY;

	int** map2D;
	AStar* astar;

	//Game Specific
	class CameraTargetActor* cameraTargetActor;
	class CubeActor* cubeActor;
	class PlayerCombatSystem* playerCombat;
	class LevelUpSystem* playerLevels;
	class EnemyCombatSystem* enemyCombat;
	class EnemyActor* enemyActor;
	class BossSprite* bossSprite;
	class SkeletonSprite* skeletonSprite;
	class KnightSprite* knightSprite;
	class VictorySprite* victorySprite;

	class HUD* hud;
	
	class TextBox* playerHealth_text;
	class TextBox* enemyHealth_text;
	class TextBox* gameMessage_text;
	class TextBox* endMessage_text;
	class TextBox* replayMessage_text;
	class TextBox* playerLevel_text;
	class TextBox* playerAttack_text;
	class TextBox* enemnyAttack_text;

	class TextBox* playerHealthLabel_text;
	class TextBox* playerXPLabel_text;
	class HealthBar* playerHealthBar;
	class HealthBar* playerXPBar;
	
	bool isReturning;
	bool enemyCollision;
	bool stairCollision;
	bool isAttacking;
	bool waitForEnemyAttack;
	bool waitForEnemyDeath;
	bool waitForPlayerDeath;
	bool doesWin;
	
	Vector3 savedPlayerPosition;
	vector<Vector3> saved_enemies;
	vector<Actor*> enems;

	vector<int> numEnemies;

};
