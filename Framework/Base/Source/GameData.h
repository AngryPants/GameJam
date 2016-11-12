#include "SingletonTemplate.h"

class GameData : public Singleton<GameData> {

	friend class Singleton<GameData>;

public:
	const float worldSizeX, worldSizeY;
	
private:
	//Constructor(s) & Destructor
	GameData() : worldSizeX(8), worldSizeY(12) {}
	virtual ~GameData() {}

};