#include "Data.h"

Data::Data(const int var_) : var{ var_ }
{}

Data::~Data()
{}

Data::Data(const Data& data) : var(data.var)
{
	if (&data == this)
	{
		throw std::invalid_argument("Invalid_argument: this object and the argument object are the same");
	}
}

Data& Data::operator=(const Data& other_data)
{
	if (&other_data == this)
	{
		throw std::invalid_argument("Invalid_argument: this object and the argument object are the same");
	}

	return *this = Data(other_data);
}


Data& Data::operator=(Data&& other_data) noexcept
{
	if (&other_data == this)
	{
		throw std::invalid_argument("Invalid_argument: this object and the argument object are the same");
	}

	std::swap(var, other_data.var);
	return *this;
}

Data::Data(Data&& other_data) : var(std::exchange(other_data.var, NULL/*nullptr*/))//if other_data.var was int* i would put nullptr
{}

