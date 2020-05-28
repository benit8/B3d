/*
** B, 2018
** Utils / IEventListener.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	template <typename ArgsPack, typename ParamsPack>
	class IEventListener;
}

////////////////////////////////////////////////////////////////////////////////

#include "B/Utils/Signal.hpp"

#include <functional>
#include <forward_list>
#include <map>
#include <memory>
#include <optional>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

template <typename...>
struct ParameterPack {};

////////////////////////////////////////////////////////////////////////////////

template <typename... Args, typename... Params>
class IEventListener<ParameterPack<Args...>, ParameterPack<Params...>>
{
public:
	IEventListener() = delete;

public:
	virtual Signal<Args...> &operator()(Params... params) = 0;
	virtual void emit(Args&&... args) = 0;
};

////////////////////////////////////////////////////////////

template <typename... Args>
class EventListener : public IEventListener<ParameterPack<Args...>, ParameterPack<>>
{
public:
	EventListener();

public:
	Signal<Args...> &operator()() override {
		return m_signal;
	}

	void emit(Args&&... args) override {
		m_signal.emit(std::forward<Args>(args)...);
	}

private:
	Signal<Args...> m_signal;
};

////////////////////////////////////////////////////////////

// class MouseEventListener : public IEventListener<ParameterPack<const Event &>, ParameterPack<std::optional<Rect>>>
// {
// public:
// 	MouseEventListener();

// public:
// 	Signal<const Event &> &operator()(std::optional<Rect> area = std::nullopt) override {
// 		SignalArea sa;
// 		sa.area = area;

// 		m_signals.push_front(sa);
// 		return m_signals.front().signal;
// 	}

// 	void emit(const Event &event) override {
// 		for (auto s : m_signals) {
// 			if (s.area && s.area->contains(event.pos))
// 				s.signal.emit(event);
// 		}
// 	}

// private:
// 	struct SignalArea { Signal<const Event &> signal; std::optional<Rect> area; };
// 	std::forward_list<SignalArea> m_signals;
// };

////////////////////////////////////////////////////////////////////////////////

}