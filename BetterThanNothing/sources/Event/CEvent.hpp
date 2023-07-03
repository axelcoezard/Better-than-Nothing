#pragma once

class CEvent {
private:
	bool	m_bHandled = false;
public:
	virtual ~CEvent() = default;

	[[nodiscard]] virtual const char* GetName() const = 0;

	void SetHandled(bool handled) { m_bHandled = handled; }
	bool IsHandled() { return m_bHandled; }
};

#define DECLARE_EVENT_NAME(name)\
	static const char* GetStaticName() { return #name; }\
	virtual const char* GetName() const override { return GetStaticName(); }
