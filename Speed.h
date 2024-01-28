#ifndef SPEED_CLASS_H
#define SPEED_CLASS_H

class Speed {
	public:
		float speed = 0.5f;
		float gameSpeedValue;

		Speed(float framerate, float timeDelta);
};

#endif