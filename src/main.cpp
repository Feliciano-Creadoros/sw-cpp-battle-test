#include "IO/System/TypeRegistry.hpp"


#include <Features/Actions/Move.hpp>
#include <Core/Game.hpp>

#include <Features/Units/Swordsman.hpp>
#include <Features/Units/Hunter.hpp>

#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/SpawnHunter.hpp>
#include <IO/Commands/SpawnSwordsman.hpp>
#include <IO/Events/MapCreated.hpp>
#include <IO/Events/MarchEnded.hpp>
#include <IO/Events/MarchStarted.hpp>
#include <IO/Events/UnitAttacked.hpp>
#include <IO/Events/UnitDied.hpp>
#include <IO/Events/UnitMoved.hpp>
#include <IO/Events/UnitSpawned.hpp>
#include <IO/System/CommandParser.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/System/PrintDebug.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <cstdint> 


int main(int argc, char** argv)
{
	using namespace sw;
	
	if (argc != 2)
	{
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);

	if (!file)
	{
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	std::shared_ptr<core::Game> game = std::make_shared<core::Game>(std::make_shared<EventLog>());
	
	std::cout << "Commands:\n";
	io::CommandParser parser;
	parser.add<io::CreateMap>(
			[&game](auto command) 
			{ 
				game->createMap(command.width, command.height); 
			})
		.add<io::SpawnSwordsman>(
			[&game](auto command)
			{
				game->spawnUnit(std::make_shared<features::Swordsman>(
					command.unitId,
					command.x,
					command.y,
					command.hp,
					command.strength));
			})
		.add<io::SpawnHunter>(
			[&game](auto command)
			{
				game->spawnUnit(std::make_shared<features::Hunter>(
					command.unitId,
					command.x,
					command.y,
					command.hp,
					command.agility,
					command.range,
					command.strength));
			})
		.add<io::March>(
			[&game](auto command) 
			{ 
				game->march(command.unitId, command.targetX, command.targetY);
			});

	parser.parse(file);

	std::cout << "\n\nEvents:\n";
	while (game->update()){}

	return 0;
}
