#ifndef _Input_H_
#define _Input_H_

class Input {
public:
	Input();
	Input(const Input&);
	~Input();

	void initialize();

	void keyDown(unsigned int);
	void keyUp(unsigned int);


	bool isKeyDown(unsigned int);

private:
	bool m_keys[256];
};

#endif

