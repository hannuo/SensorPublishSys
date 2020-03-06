#pragma once

class subscriber_base
{
public:
	virtual ~subscriber_base() {}
	virtual std::string name() = 0;
};
