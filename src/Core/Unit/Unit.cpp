
#include <Core/Unit/Unit.hpp>
#include <vector>

namespace core
{

	Unit::Unit(uint32_t id, uint32_t x, uint32_t y, bool occupyStatus, std::string name) :
			_id(id),
			_point(Point(x,y)), 
			_targetPoint(Point(x, y)), 
			_occupyStatus(occupyStatus),
			_name(name),
			_characteristicsHandler(std::make_unique<CharacteristicHandler>())
	{}

	bool Unit::doAction(
		std::shared_ptr<IMap>& map,
		std::shared_ptr<UnitHandler> unitHandler,
		uint64_t tick,
		std::shared_ptr<sw::EventLog> eventLog)
	{
		for (auto&& action : _actions)
		{
			if (action->doAction(map, unitHandler, _id, tick, eventLog))
			{
				return true;
			}
		}

		return false;
	}

	bool Unit::deathAction(
		std::shared_ptr<IMap>& map,
		std::shared_ptr<UnitHandler> unitHandler,
		uint64_t tick,
		std::shared_ptr<sw::EventLog> eventLog)
	{
		if (_death_action != nullptr)
		{
			if (_death_action->doAction(map, unitHandler, _id, tick, eventLog))
			{
				return true;
			}
		}

		return false;
	}

	uint32_t Unit::getId() const
	{
		return _id;
	}

	std::string Unit::getName() const
	{
		return _name;
	}

	Point Unit::getCoordinates() const
	{
		return _point;
	}

	void Unit::setCoordinates(const Point& point)
	{
		_point = point;
	}

	Point Unit::getTargetCoordinates() const
	{
		return _targetPoint;
	}

	void Unit::setTargetCoordinates(const Point& point)
	{
		_targetPoint = point;
	}

	bool Unit::geOccupyStatus() const
	{
		return _occupyStatus;
	}

	int32_t Unit::getCharacteristic(features::Characteristic type)
	{
		return _characteristicsHandler->getCharacteristic(type);
	}

	void Unit::setCharacteristic(
		std::unordered_map<features::Characteristic, std::pair<int32_t, int32_t>> characteristics)
	{
		_characteristicsHandler->setCharacteristic(characteristics);
	}

	int32_t Unit::incrCharacteristic(features::Characteristic type, int32_t val)
	{
		return _characteristicsHandler->incrCharacteristic(type, val);
	}

}
