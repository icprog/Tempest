/*

	Copyright (C) 2015 Matthias Friedrich

	This file is part of Tempest Firmware.

	Tempest Firmware is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Tempest Firmware is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Tempest Firmware.  If not, see <http://www.gnu.org/licenses/>.
	
 */ 


#ifndef IO_EEPROM_H_
#define IO_EEPROM_H_


void IO_Eeprom_Initialize(void);

void IO_Eeprom_ReadPage(const uint8_t logicalPage, uint8_t *const data);

void IO_Eeprom_WritePage(const uint8_t logicalPage, uint8_t *const data);

void IO_Eeprom_Commit(void);

#endif /* IO_EEPROM_H_ */