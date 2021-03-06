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


#ifndef IO_ANALOGS_H_
#define IO_ANALOGS_H_

#define IO_ANALOGS_CHANNEL_PUSHBUTTON_VCC9         1
#define IO_ANALOGS_CHANNEL_EYE                     2

void IO_Analogs_Initialize(void);
void IO_Analogs_Update(void);

uint16_t IO_Analogs_GetChannel(uint32_t channel);

#endif /* IO_ANALOGS_H_ */