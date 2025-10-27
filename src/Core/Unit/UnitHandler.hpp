#pragma once

#include <Core/Unit/Unit.hpp>

#include <memory>

namespace core
{
	class Unit;
	/**
	* Unit Handler 
	*/
	class UnitHandler
	{
	public:

		UnitHandler();

		/**
		* Get units
		* @return std::map of units
		*/
		std::map<uint32_t, std::shared_ptr<Unit>> getUnits();

		/**
		* Get unit by id
		* @param unitId - unit id
		* @return unit
		*/
		std::shared_ptr<Unit> getUnit(uint32_t unitId);

		/**
		* Set unit
		* @param unit - pointer to unit
		*/
		void setUnit(std::shared_ptr<Unit> unit);

		/**
		* Remove unit by id
		* @param unitId - unit id
		*/
		void removeUnit(uint32_t unitId);


	private:
		// Tree of all units.
		// std::map is used to keep the order of actions in the order of their creation
		// (Provided that the IDs are created sequentially)
		std::map<uint32_t, std::shared_ptr<Unit>> _units;

	};
}