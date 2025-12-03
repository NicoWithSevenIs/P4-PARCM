#pragma once
#include <type_traits>
#include <string>
#include <any>
template<typename M>
concept Class = std::is_class_v<M>;

template<Class C>
class IMediator {
	public:
		virtual void Notify(C* notifier, std::string notification) = 0;
		virtual C* Get(std::string name) = 0;
};