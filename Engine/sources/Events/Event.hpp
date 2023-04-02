#pragma once

class Event {
private:
	bool	m_Handled = false;
public:
	virtual ~Event() = default;

	[[nodiscard]] virtual const char* GetName() const = 0;

	void SetHandled(bool handled) { m_Handled = handled; }
	bool IsHandled() { return m_Handled; }
};

#define DECLARE_EVENT_NAME(name)\
	static const char* GetStaticName() { return #name; }\
	virtual const char* GetName() const override { return GetStaticName(); }
