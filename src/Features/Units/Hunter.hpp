#pragma once

#include <Core/Interfaces/IAction.hpp>
#include <Features/Actions/Death.hpp>
#include <Features/Actions/Melee.hpp>
#include <Features/Actions/Move.hpp>
#include <Features/Actions/Ranged.hpp>

namespace features
{
	class Hunter final : public core::Unit
	{
	public:
		Hunter(uint32_t id, uint32_t x, uint32_t y, uint32_t hp, uint32_t agility, uint32_t range, uint32_t strength) : 
			core::Unit(id, x, y, true, "Hunter")
		{
			std::unordered_map<Characteristic, std::pair<int32_t, int32_t>> characteristics
				= {{Characteristic::HP, {hp, hp}},
				   {Characteristic::Agility, {agility, agility}},
				   {Characteristic::Range, {range, range}},
				   {Characteristic::Strength, {strength, strength}}};
			setCharacteristic(characteristics);

			_death_action = std::make_unique<Death>();
			_actions.push_back(std::make_unique<Ranged>());
			_actions.push_back(std::make_unique<Melee>());
			_actions.push_back(std::make_unique<Move>());
			

		}

	};
}