#include"Speed.h"

Speed::Speed(float framerate, float timeDelta) {
	gameSpeedValue = speed * framerate * timeDelta;
}