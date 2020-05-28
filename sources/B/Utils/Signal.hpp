/*
** B, 2018
** Utils / Signal.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace B {
	template <typename... Args>
	class Signal;
}

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <list>
#include <memory>

////////////////////////////////////////////////////////////////////////////////

namespace B
{

////////////////////////////////////////////////////////////////////////////////

template <typename... Args>
class Signal
{
	class Slot
	{
	public:
		virtual void invoke(Args...) = 0;

		void trigger(Args... args) {
			if (!m_filter || (m_filter && m_filter(std::forward<Args>(args)...)))
				invoke(std::forward<Args>(args)...);
		}

		void filter(std::function<bool(Args...)> f) {
			m_filter = f;
		}

	protected:
		std::function<bool(Args...)> m_filter;
	};

	////////////////////////////////////////

	class Slot_STLFunction : public Slot
	{
	public:
		Slot_STLFunction(std::function<void(Args...)> function)
		: m_function(function)
		{}

		void invoke(Args... args) override {
			m_function(std::forward<Args>(args)...);
		}

	private:
		std::function<void(Args...)> m_function;
	};

	////////////////////////////////////////

	template <typename T>
	class Slot_ClassMember : public Slot
	{
	public:
		Slot_ClassMember(T *classPtr, void (T::*classMember)(Args...))
		: m_classPtr(classPtr)
		, m_classMember(classMember)
		{}

		void invoke(Args... args) override {
			(m_classPtr->*m_classMember)(std::forward<Args>(args)...);
		}

	private:
		T *m_classPtr;
		void (T::*m_classMember)(Args...);
	};

	////////////////////////////////////////

	class Slot_Function : public Slot
	{
	public:
		Slot_Function(void (*function)(Args...))
		: m_function(function)
		{}

		void invoke(Args... args) override {
			(*m_function)(std::forward<Args>(args)...);
		}

	private:
		void (*m_function)(Args...);
	};

	////////////////////////////////////////

public:
	typedef std::shared_ptr<Slot> SlotPtr;

public:
	Signal() = default;

public:
	SlotPtr add(std::function<void(Args...)> function) {
		return add(std::make_shared<Slot_STLFunction>(function));
	}

	template <typename T>
	SlotPtr add(T *classPtr, void (T::*classMember)(Args...)) {
		return add(std::make_shared<Slot_ClassMember<T>>(classPtr, classMember));
	}

	SlotPtr add(void (*function)(Args...)) {
		return add(std::make_shared<Slot_Function>(function));
	}

	SlotPtr add(SlotPtr slot) {
		m_slots.push_back(slot);
		return slot;
	}

	void clear() {
		m_slots.clear();
	}

	void emit(Args... args) {
		for (auto &slot : m_slots)
			slot->trigger(std::forward<Args>(args)...);
	}

	/// Alias for emit()
	void operator ()(Args... args) { emit(std::forward<Args>(args)...); }

private:
	std::list<SlotPtr> m_slots;
};

////////////////////////////////////////////////////////////////////////////////

}