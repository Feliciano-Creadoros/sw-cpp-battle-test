
#include <Core/Game.hpp>
#include <Features/Actions/Ranged.hpp>

namespace features
{
	bool Ranged::doAction(
		std::shared_ptr<core::IMap>& map,
		std::shared_ptr<core::UnitHandler> unitHandler,
		uint32_t unitId,
		uint64_t tick,
		std::shared_ptr<sw::EventLog> eventLog)
	{
		auto unit = unitHandler->getUnit(unitId);

		int32_t range = unit->getCharacteristic(Characteristic::Range);
		std::vector<uint32_t> enemiesId = map->getUnitsInZone(unit->getCoordinates(), 1, range);
		
		if (enemiesId.size() == 0)
		{
			return false;
		}

		uint32_t enemyId = enemiesId.at(core::Game::randomRange(0, enemiesId.size() - 1));
		auto enemyUnit = unitHandler->getUnit(enemyId);

		int32_t agility = unit->getCharacteristic(Characteristic::Agility);
		enemyUnit->incrCharacteristic(Characteristic::HP, -agility);
		eventLog->log(
			tick,
			sw::io::UnitAttacked{
				unitId, enemyId, (uint32_t)agility, (uint32_t)enemyUnit->getCharacteristic(Characteristic::HP)});

		return true;

	}
}
