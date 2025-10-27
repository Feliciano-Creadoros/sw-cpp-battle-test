#pragma once

#include <Core/Map/Cell.hpp>
#include <Core/Map/Point.hpp>

#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

namespace core
{	
	/**
	* Game Map Interface
	*/
	class IMap
	{
	public:
		virtual ~IMap() {}

		/**
		* Get the ids of units standing in the zone centred at point
        * with inner radius and outer radius
		* @param point - centre of the area
        * @param innerRadius - inner radius
        * @param outerRadius - outer radius
        * @return set of unit ids
		*/
		virtual std::vector<uint32_t> getUnitsInZone(
			const Point& point, int32_t innerRadius, int32_t outerRadius) const
			= 0;

		/**
		* Checking for an empty cell with point
		* @param point - the location being looked for
		* @return empty status; true - empty;  false - cell occupied
		*/
		virtual bool isCellEmpty(const Point& point) const = 0;

		/**
		* Checking for an empty cell with point
		* @param point - the location being looked for
		* @param unitId - id of the unit to be removed
		* @param isOccupiable - is this unit capable of occupying a cell
		*/
		virtual void removeFromCell(const Point& point, uint32_t unitId, bool isOccupiable) = 0;

		/**
		* Places the unit id in the cell using the point
		* @param point - the location being looked for
		* @param unitId - id of the unit to be set
		* @param isOccupiable - is this unit capable of occupying a cell
		*/
		virtual void setToCell(const Point& point, uint32_t unitId, bool isOccupiable) = 0;

		/**
		* Getter for width
		* @return width
		*/
		virtual uint32_t getWidth() const = 0;

		/**
		* Getter for height
		* @return height
		*/
		virtual uint32_t getHeight() const = 0;

	};

}
