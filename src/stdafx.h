/* DST  -  Dune 2 Script Tools
 *  
 * Copyright (C) 2009 segra
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  
 * 
 * $Id$
 * 
 */

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;


typedef	unsigned char	byte;
typedef unsigned short	word;
typedef unsigned long	dword;

//		Endian functions
word	readWord(  const void *buffer );
dword	readDWord( const void *buffer );
word	swapWord(  word buffer );
dword	swapDWord( dword buffer );

enum _scriptTypes {
	_scriptBUILD = 0,
	_scriptUNIT,
	_scriptHOUSE
};

static const char *nameHouses[0x06] = {
	"Harkonnen",
	"Atreides",
	"Ordos",
	"Fremen",
	"Sardaukar",
	"Mercenary"
};

static const char *nameStructures[0x13] = {
	"Concrete",
	"Concrete4",
	"Palace",
	"LightFactory",
	"HeavyFactory",
	"Hi-Tech",
	"IX",
	"WOR",
	"ConstructionYard",
	"Windtrap",
	"Barracks",
	"Starport",
	"Refinery",
	"Repair",
	"Wall",
	"Turret",
	"R-Turret",
	"SpiceSilo",
	"Outpost"
};

static const char *nameUnits[0x1B] = {
	"Carryall",
	"Ornithopter",
	"Infantry",
	"Troopers",
	"Soldier",
	"Trooper",
	"Saboteur",
	"Launcher",
	"Deviator",
	"Tank",
	"SiegeTank",
	"Devastator",
	"SonicTank",
	"Trike",
	"RaiderTrike",	
	"Quad",
	"Harvester",
	"MCV",
	"DeathHand",
	"Rocket",
	"ARocket",
	"GRocket",
	"MiniRocket",
	"Bullet",
	"SonicBlast",
	"Sandworm",
	"Frigate"
};

static const char *nameUnitDetails[0x14] = {
	"HitPointRepairCalc?",   
	"BuildingTypeIndex",     
	"WeaponRange",           
	"IndexGet",              
	"Field64Get",            
	"AttackObjectIndexTypeGet",                   
	"Return",                  
	"TypeIndex",             
	"IndexGetAsObject",      
	"Field6BGet",                 
	"loc_27562",          
	"Field49AndField4BGet",                 
	"WeaponCoolDown?",                 
	"Field36And4h",               
	"HouseIDGet",            
	"loc_275C1",                 
	"TurretGet?",     
	"loc_2752F",                 
	"DoesTurretRotate",          
	"CheckIfHuman",                 
};
