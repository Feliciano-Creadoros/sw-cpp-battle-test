
#include <Core/Game.hpp>
#include <Features/Actions/Melee.hpp>

namespace features
{
	bool Melee::doAction(
		std::shared_ptr<core::IMap>& map,
		std::shared_ptr<core::UnitHandler> unitHandler,
		uint32_t unitId,
		uint64_t tick,
		std::shared_ptr<sw::EventLog> eventLog)
	{
		auto unit = unitHandler->getUnit(unitId);

		std::vector<uint32_t> enemiesId = map->getUnitsInZone(unit->getCoordinates(), 0, 1);
		
		if (enemiesId.size() == 0)
		{
			return false;
		}

		uint32_t enemyId = enemiesId.at(core::Game::randomRange(0, enemiesId.size() - 1));
		auto enemyUnit = unitHandler->getUnit(enemyId);

		int32_t strength = unit->getCharacteristic(Characteristic::Strength);
		enemyUnit->incrCharacteristic(Characteristic::HP, -strength);
		eventLog->log(
			tick,
			sw::io::UnitAttacked{
				unitId, enemyId, (uint32_t)strength, (uint32_t)enemyUnit->getCharacteristic(Characteristic::HP)});

		return true;

	}
}
