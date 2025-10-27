#pragma once

#include <Core/Map/Point.hpp>
#include <Core/Interfaces/IMap.hpp>
#include <Core/Unit/UnitHandler.hpp>

#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/System/EventLog.hpp>

#include <memory>

namespace core
{
	class UnitHandler;

	/**
	* Basic Action Interface
	*/
	class IAction
	{
	public:
		virtual ~IAction() {}

		/**
		* Implement basic actions for units through this method. Such as dying, movement, melee attack, shooting, hooking other units, etc.
		* @param map - the battle map interface, through which we can access the locations of units on the map.
		* @param unitHandler - Unit Handler.
		* @param tick - Current simulation tick.
		* @param eventLog - Logger.
		* @return Success of completed action. false - the conditions for performing the action were not met. 
		* true - the action was performed.
		*/
		virtual bool doAction(
			std::shared_ptr<IMap>& map,
			std::shared_ptr<UnitHandler> unitHandler, uint32_t unitId,
			uint64_t tick,
			std::shared_ptr<sw::EventLog> eventLog)
			= 0;
	};
}
