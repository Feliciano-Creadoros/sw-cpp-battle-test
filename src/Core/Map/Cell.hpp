#pragma once

#include <vector>
#include <cstdint> 

namespace core
{
	/*
	* Cell class. Stores data about the units located on it and whether it is occupied or not.
	*/
	class Cell
	{
	public:
		Cell();

		[[nodiscard]]
		bool getEmptyStatus() const;
		void setEmptyStatus(bool emptyStatus);

		[[nodiscard]]
		std::vector<uint32_t> getUnitIds() const;

		[[nodiscard]]
		bool checkUnitId(uint32_t unitId) const;
		void appendUnitId(uint32_t unitId);
		void deleteUnitId(uint32_t unitId);

	private:
		bool _emptyStatus;
		std::vector<uint32_t> _unitIds;
	};
}
