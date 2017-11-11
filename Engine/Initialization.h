#pragma once
#include <vector>
#include <functional>

class Initialization
{
	
	typedef std::vector<std::function<void(void)>> f_list;

public:
	template <typename TFunction, typename... TArgs>
	static void schedulePreInit(TFunction&& a_func, TArgs&&... a_args);

	template <typename TFunction, typename... TArgs>
	static void scheduleInit(TFunction&& a_func, TArgs&&... a_args);

	template <typename TFunction, typename... TArgs>
	static void schedulePostInit(TFunction&& a_func, TArgs&&... a_args);

	static void initialize();
	
private:
	
	static f_list _preInit;
	static f_list _init;
	static f_list _postInit;

};

/*



class DelayedCaller : public std::function< void(void) > {
public:
DelayedCaller(std::function< void(void) > fn)
: std::function< void(void) >(fn) {}
};


DelayedCaller caller1([]() { myFunc1(123, 45.6); });
DelayedCaller caller2([]() { myFunc2("A string"); }); */

