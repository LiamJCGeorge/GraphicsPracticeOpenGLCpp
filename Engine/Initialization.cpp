#include "Initialization.h"


template <typename TFunction, typename... TArgs>
void Initialization::schedulePreInit(TFunction&& a_func, TArgs&&... a_args){
	_preInit.emplace_back(std::bind(std::forward<TFunction>(a_func), std::forward<TArgs>(a_args)...));
}

template <typename TFunction, typename... TArgs>
void Initialization::scheduleInit(TFunction&& a_func, TArgs&&... a_args) {
	_init.emplace_back(std::bind(std::forward<TFunction>(a_func), std::forward<TArgs>(a_args)...));
}

template <typename TFunction, typename... TArgs>
void Initialization::schedulePostInit(TFunction&& a_func, TArgs&&... a_args) {
	_postInit.emplace_back(std::bind(std::forward<TFunction>(a_func), std::forward<TArgs>(a_args)...));
}

void Initialization::initialize() {
	for (auto it = _preInit.begin(); it != _preInit.end(); ++it) {
		(*it)();
	}
	for (auto it = _init.begin(); it != _init.end(); ++it) {
		(*it)();
	}
	for (auto it = _postInit.begin(); it != _postInit.end(); ++it) {
		(*it)();
	}
}
