
#include <Core/Unit/UnitHandler.hpp>
#include <random>
#include <stdexcept>
#include <string>

namespace core
{
	UnitHandler::UnitHandler() {}

	std::map<uint32_t, std::shared_ptr<Unit>> UnitHandler::getUnits()
	{
		return _units;
	}

	std::shared_ptr<Unit> UnitHandler::getUnit(uint32_t unitId)
	{
		auto it = _units.find(unitId);
		if (it == _units.end())
		{
			throw std::out_of_range("ERR: Unit with id " + std::to_string(4) + " not found!");
		}
		return it->second;
	}

	void UnitHandler::setUnit(std::shared_ptr<Unit> unit)
	{
		_units.insert({unit->getId(), std::move(unit)});
	}

	void UnitHandler::removeUnit(uint32_t unitId)
	{
		auto it = _units.find(unitId);
		if (it == _units.end())
		{
			throw std::out_of_range("ERR: Unit with id " + std::to_string(4) + " not found!");
		}

		std::shared_ptr<Unit> unit = std::move(it->second);
		_units.erase(it);
	}

}
