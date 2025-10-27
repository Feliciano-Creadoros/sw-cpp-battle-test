
#include <Core/Game.hpp>

#include <stdexcept>
#include <string>
#include <random>

namespace core
{
	Game::Game(std::shared_ptr<sw::EventLog> eventLog) :
		_tick(1),
		_unitHandler(std::make_shared<UnitHandler>()),
		_eventLog(eventLog)
	{}

	void Game::createMap(uint32_t width, uint32_t height) {
		_map = std::make_shared<Map>(width, height);
		_eventLog->log(_tick, sw::io::MapCreated{width, height});
	}

	void Game::spawnUnit(std::shared_ptr<Unit> unit)
	{
		if (_map == nullptr)
		{
			throw std::logic_error(
				"ERR: The map has not been initialised!");
		}

		if (unit->geOccupyStatus() && !_map->isCellEmpty(unit->getCoordinates()))
		{
			throw std::logic_error(
				"ERR: Cell " + std::to_string(unit->getCoordinates().getX()) + ", "
				+ std::to_string(unit->getCoordinates().getY()) 
				+ " is already occupied by another unit capable of occupying cells..");
		}

		_map->setToCell(unit->getCoordinates(), unit->getId(), unit->geOccupyStatus());
		_unitHandler->setUnit(unit);

		_eventLog->log(
			_tick,
			sw::io::UnitSpawned{
				unit->getId(), unit->getName(), unit->getCoordinates().getX(), unit->getCoordinates().getY()});
	}

	void Game::march(uint32_t unitId, uint32_t x, uint32_t y) {

		auto unit = _unitHandler->getUnit(unitId);
		unit->setTargetCoordinates(Point(x, y));
		
		_eventLog->log(
			_tick,
			sw::io::MarchStarted{
				unit->getId(), unit->getCoordinates().getX(), unit->getCoordinates().getY(), x, y});
	}

	bool Game::update() {
		_tick++;

		auto units = _unitHandler->getUnits();

		if (units.size() <= 1)
		{
			return false;
		}
		bool endGameFlag = false;
		for (auto& [unitId, unit] : units)
		{			
			if (unit->doAction(_map, _unitHandler, _tick, _eventLog))
			{
				endGameFlag = true;
			}
		}

		// Here we see which units died during the turn
		for (auto& [unitId, unit] : units)
		{
			if (unit->deathAction(_map, _unitHandler, _tick, _eventLog))
			{
				endGameFlag = true;
			}
		}
		return endGameFlag;
	}

	uint32_t Game::randomRange(uint32_t from, uint32_t to) {
		static std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<uint32_t> dist(from, to);

		return dist(rng);
	}

}
