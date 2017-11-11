#pragma once
class window
{
public:
	window();
	~window();

	void create();

	float getWidth();

	void widthEvent();

private:
	float _width;
};

