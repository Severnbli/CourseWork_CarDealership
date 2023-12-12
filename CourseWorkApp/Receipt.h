#pragma once

#include <memory>
#include <utility>
#include "Client.h"
#include "Car.h"
#include <string>
#include "Date.h"

class Receipt
{
public:
	Receipt() = delete;

	Receipt(const std::vector<std::string>&);

	Receipt(std::pair<std::shared_ptr<Client>, std::shared_ptr<Car>>);

	Receipt(const Receipt&);

	bool operator<(const Receipt&) const;

	void setInfoInVectorStringForm(const std::vector<std::string>&);

	std::vector<std::string> getInfoInVectorStringForm();

	static size_t getDimensionality();

	void printInfoTableForm() const;

private:
	static size_t dimensionality_;

	Date date_;

	Client client_;

	Car car_;
};