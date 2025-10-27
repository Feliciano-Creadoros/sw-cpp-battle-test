
#include <Core/Game.hpp>
#include <Features/Actions/Death.hpp>

namespace features
{

	bool Death::doAction(
		std::shared_ptr<core::IMap>& map,
		std::shared_ptr<core::UnitHandler> unitHandler,
		uint32_t unitId,
		uint64_t tick,
		std::shared_ptr<sw::EventLog> eventLog)
	{
		auto unit = unitHandler->getUnit(unitId);

		if (unit->getCharacteristic(Characteristic::HP) > 0)
		{
			return false;
		}

		map->removeFromCell(unit->getCoordinates(), unitId, unit->geOccupyStatus());
		unitHandler->removeUnit(unitId);
		eventLog->log(tick, sw::io::UnitDied{unitId});
		return true;	
	}
}
