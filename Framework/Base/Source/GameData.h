#include "SingletonTemplate.h"

class GameData : public Singleton<GameData> {

	friend class Singleton<GameData>;

public:
	const float worldSizeX, worldSizeY;
	bool mute;
	int level;

private:
	//Constructor(s) & Destructor
	GameData() : worldSizeX(8), worldSizeY(12), mute(false), level(1) {}
	virtual ~GameData() {}

};