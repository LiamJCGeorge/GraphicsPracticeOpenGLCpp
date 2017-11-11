#pragma once

class Singleton{
public:
	static Singleton& getInstance();

protected:
	
private:
	Singleton() {};

public:
	Singleton(Singleton const&) = delete;
	void operator=(Singleton const&) = delete;
};

