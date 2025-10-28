#pragma once

#include <Core/Interfaces/IAction.hpp>
#include <Features/Actions/Death.hpp>
#include <Features/Actions/Melee.hpp>
#include <Features/Actions/Move.hpp>

namespace features
{
	class Swordsman final : public core::Unit
	{
	public:
		Swordsman(uint32_t id, uint32_t x, uint32_t y, uint32_t hp, uint32_t strength) :
				core::Unit(id, x, y, true, "Swordsman")
		{

			std::unordered_map<Characteristic, std::pair<int32_t, int32_t>> characteristics
				= {{Characteristic::HP, {hp, hp}},
				   {Characteristic::Strength, {strength, strength}}};
			setCharacteristics(characteristics);

			_death_action = std::make_unique<Death>();
			_actions.push_back(std::make_unique<Melee>());
			_actions.push_back(std::make_unique<Move>());
		}
	};
}
