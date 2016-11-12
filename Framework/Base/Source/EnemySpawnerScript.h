#ifndef ENEMY_SPAWNNER_SCRIPT_H
#define ENEMY_SPAWNNER_SCRIPT_H

#include "Script.h"
#include <vector>

using std::vector;

class GameObject;

class EnemySpawnerScript : public Script {

public:
	GameObject* spawner;
	GameObject* player;

	enum ENEMY_TYPES {
		ENEMY_OCTOMAN,
		ENEMY_COOKIE_MASTER,
		ENEMY_BOWSIR,
		ENEMY_DONKEY_KING,
		NUM_ENEMY_TYPES,
	};

	float spawnTimer[NUM_ENEMY_TYPES];
	vector<double> spawnTimes[NUM_ENEMY_TYPES];

	EnemySpawnerScript() {
		spawner = nullptr;
		player = nullptr;
		for (unsigned int i = 0; i < NUM_ENEMY_TYPES; ++i) {
			spawnTimer[i] = 0.0f;
		}
	}
	virtual ~EnemySpawnerScript() {}

	virtual void Update(double deltaTime);

};

#endif