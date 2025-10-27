#pragma once

#include <Core/Interfaces/IAction.hpp>

namespace features
{
	class Death final : public core::IAction
	{
	public:
		bool doAction(
			std::shared_ptr<core::IMap>& map,
			std::shared_ptr<core::UnitHandler> unitHandler,
			uint32_t unitId,
			uint64_t tick,
			std::shared_ptr<sw::EventLog> eventLog);

	private:
		bool _isLastTurn = false;
	};
}