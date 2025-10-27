
#include <Features/Actions/Move.hpp>

#include <stdexcept>
#include <string>

namespace features
{
	bool Move::doAction(
		std::shared_ptr<core::IMap>& map,
		std::shared_ptr<core::UnitHandler> unitHandler,
		uint32_t unitId,
		uint64_t tick,
		std::shared_ptr<sw::EventLog> eventLog)
	{

		auto unit = unitHandler->getUnit(unitId);

		core::Point targetPoint = unit->getTargetCoordinates();


		core::Point currPoint = unit->getCoordinates();

		if (currPoint == targetPoint)
		{
			eventLog->log(
				tick,
				sw::io::MarchEnded{
					unit->getId(), unit->getCoordinates().getX(), unit->getCoordinates().getY()});

			return false;
		}
		uint32_t newX = currPoint.getX();
		uint32_t newY = currPoint.getY();

		if (currPoint.getX() < targetPoint.getX())
		{

			newX++;
		}
		else if (currPoint.getX() > targetPoint.getX())
		{

			newX--;
		}

		if (currPoint.getY() < targetPoint.getY())
		{
			newY++;
		}
		else if (currPoint.getY() > targetPoint.getY())
		{
			newY--;
		}

		core::Point newPoint(newX, newY);

		if ((newPoint != currPoint) && (!unit->geOccupyStatus() || map->isCellEmpty(newPoint)))
		{
			map->removeFromCell(currPoint, unitId, unit->geOccupyStatus());
			unit->setCoordinates(newPoint);
			map->setToCell(newPoint, unitId, unit->geOccupyStatus());
			eventLog->log(tick, sw::io::UnitMoved{unitId, newX, newY});
			return true;
		}

		return false;
	}
}
