#include <iostream>

class CAlg_base
{
public:
	CAlg_base() {}
	virtual ~CAlg_base() {}

	virtual bool init() = 0;

	virtual bool start() = 0;

	virtual std::string GetName() = 0;
};
