#include "EnemySpawnerScript.h"
#include "MyMath.h"
#include "GameObjectFactory.h"

void EnemySpawnerScript::Update(double deltaTime) {
	if (spawner == nullptr) {
		return;
	}

	for (unsigned int i = 0; i < NUM_ENEMY_TYPES; ++i) {
		if (spawnTimes[i].empty() == true) {
			continue;
		}
		spawnTimer[i] += deltaTime;
		vector<double>::iterator fuckYouIter = spawnTimes[i].begin();
		if (spawnTimer[i] >= (*fuckYouIter)) {
			switch (i) {
				case ENEMY_OCTOMAN: {
					GameObjectFactory::CreateOctoman(spawner->GetSpace());
					break;
				}
				case ENEMY_BOWSIR: {
					GameObjectFactory::CreateBowsir(spawner->GetSpace(), player);
					break;
				}
			}
			spawnTimer[i] = 0.0f;
			spawnTimes[i].erase(spawnTimes[i].begin());
		}
		
	}
		
}