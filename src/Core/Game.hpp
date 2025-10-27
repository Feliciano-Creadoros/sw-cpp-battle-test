#pragma once

#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/System/EventLog.hpp>

#include <Core/Unit/Unit.hpp>
#include <Core/Map/Map.hpp>
#include <cstdint> 

 namespace core
{
	class Game final
	{
	public:
		Game(std::shared_ptr<sw::EventLog> eventLog);

		void createMap(uint32_t width, uint32_t height);

		void spawnUnit(std::shared_ptr<Unit> unit);

		void march(uint32_t unitId, uint32_t x, uint32_t y);

		/**
		* The main method of the game. Here, each turn, units on the map perform their actions.
		* @return True - simulation continued. False - simulation ended. 
		*/
		bool update();

		/**
		* Static method for randomisation
		*/
		static uint32_t randomRange(uint32_t from, uint32_t to);

	private:
		
		// Unit handler
		std::shared_ptr<UnitHandler> _unitHandler;
		// Battle map
		std::shared_ptr<IMap> _map;
		// �urrent tick of the game
		uint64_t _tick;

		// Event logger
		std::shared_ptr<sw::EventLog> _eventLog;
	};
}
