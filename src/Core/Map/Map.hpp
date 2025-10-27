#pragma once

#include <Core/Interfaces/IMap.hpp>

#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

namespace core
{
	/**
	* Game Map
	*/
	class Map : public IMap
	{
	public:
		Map(uint32_t width, uint32_t height);

		/**
		* Get the ids of units standing in the zone centred at point
        * with inner radius and outer radius
		* @param point - centre of the area
        * @param innerRadius - inner radius
        * @param outerRadius - outer radius
        * @return vector of unit ids
		*/
		[[nodiscard]]
		std::vector<uint32_t> getUnitsInZone(const Point& point, int32_t innerRadius, int32_t outerRadius) const;

		/**
		* Checking for an empty cell with point
		* @param point - the location being looked for
		* @return empty status; true - empty;  false - cell occupied
		*/
		[[nodiscard]]
		bool isCellEmpty(const Point& point) const;

		/**
		* Checking for an empty cell with point
		* @param point - the location being looked for
		* @param unitId - id of the unit to be removed
		* @param isOccupiable - is this unit capable of occupying a cell
		*/
		void removeFromCell(const Point& point, uint32_t unitId, bool isOccupiable);

		/**
		* Places the unit id in the cell using the point
		* @param point - the location being looked for
		* @param unitId - id of the unit to be set
		* @param isOccupiable - is this unit capable of occupying a cell
		*/
		void setToCell(const Point& point, uint32_t unitId, bool isOccupiable);

		/**
		* Getter for width
		* @return width
		*/
		[[nodiscard]]
		uint32_t getWidth() const;

		/**
		* Getter for height
		* @return height
		*/
		[[nodiscard]]
		uint32_t getHeight() const;

	private:
		/**
		* Checks whether the coordinate @param point lies within the map
        * @param point coordinate to check
		*/
		void checkPosition(const Point& point) const;

		uint32_t _width;

		uint32_t _height;

		// 2D matrix of field cells
		std::vector<std::vector<Cell>> _cells;
	};

}
