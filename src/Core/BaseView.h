#pragma once

#include <string>

class BaseView
{
protected:
	std::string Name;
	
public:
	BaseView(const std::string& InName);
	virtual ~BaseView();
	BaseView(const BaseView&) = delete;
	BaseView(BaseView&&) = delete;

	virtual bool Init() = 0;
	virtual void Draw() = 0;
	std::string GetName() { return Name; }
};
