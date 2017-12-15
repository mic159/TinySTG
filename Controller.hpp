#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Controller
{
public:
	enum
	{
		// Pin
//		DIR_X_PIN = 42,
//		DIR_Y_PIN = 1,
		DIR_UP_PIN = 5,
		DIR_DOWN_PIN = 2,
		DIR_LEFT_PIN = 3,
		DIR_RIGHT_PIN = 11,
		BUTTON_LEFT_PIN = 0,
		BUTTON_RIGHT_PIN = 1,
		// Button
		BUTTON_UP = 0x01,
		BUTTON_DOWN = 0x02,
		BUTTON_LEFT = 0x04,
		BUTTON_RIGHT = 0x08,
		BUTTON_1 = 0x10,
		BUTTON_2 = 0x20,
		// Threshold
		DIR_THRESHOLD = 250,
	};
	Controller(void);
	~Controller(void);
	static Controller* controller;
	static Controller& GetInstance();
	static void Initialize(void);
	static void Finalize(void);
	void Update(void);
	unsigned int GetButton(void);
private:
	Controller(Controller&);
	Controller& operator = (Controller&);
	int version;
	unsigned int button;
};

#endif
