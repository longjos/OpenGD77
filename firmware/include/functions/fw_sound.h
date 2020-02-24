/*
 * Copyright (C)2019 Kai Ludwig, DG4KLU
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef _FW_SOUND_H_
#define _FW_SOUND_H_

#include "FreeRTOS.h"
#include "task.h"

#include "fw_common.h"
#include "fw_spi.h"
#include "fw_trx.h"
#include "fsl_sai.h"
#include "fsl_sai_edma.h"
#include "fw_i2s.h"
#include "fw_pit.h"
#include "fw_wdog.h"

//extern const uint8_t sine_beep[];
//extern volatile int sine_beep_freq;
// volatile int sine_beep_duration;

extern int melody_generic[512];
extern const int melody_poweron[];
extern const int melody_key_beep[];
extern const int melody_key_long_beep[];
extern const int melody_sk1_beep[];
extern const int melody_sk2_beep[];
extern const int melody_orange_beep[];
extern const int melody_ACK_beep[];
extern const int melody_NACK_beep[];
extern const int melody_ERROR_beep[];
extern const int melody_tx_timeout_beep[];
extern const int melody_private_call[];
extern const int melody_TXtone_beep[];
extern const int melody_RXtone_beep[];
extern volatile int *melody_play;
extern volatile int melody_idx;
extern volatile int micAudioSamplesTotal;
extern int soundBeepVolumeDivider;

#define WAV_BUFFER_SIZE 0xa0
#define WAV_BUFFER_COUNT 18
#define HOTSPOT_BUFFER_SIZE 50
#define HOTSPOT_BUFFER_COUNT 48

extern union sharedDataBuffer
{
	volatile uint8_t wavbuffer[WAV_BUFFER_COUNT][WAV_BUFFER_SIZE];
	volatile uint8_t hotspotBuffer[HOTSPOT_BUFFER_COUNT][HOTSPOT_BUFFER_SIZE];
} audioAndHotspotDataBuffer;

extern volatile int wavbuffer_read_idx;
extern volatile int wavbuffer_write_idx;
extern volatile int wavbuffer_count;
extern uint8_t *currentWaveBuffer;

extern uint8_t spi_sound1[WAV_BUFFER_SIZE*2];
extern uint8_t spi_sound2[WAV_BUFFER_SIZE*2];
extern uint8_t spi_sound3[WAV_BUFFER_SIZE*2];
extern uint8_t spi_sound4[WAV_BUFFER_SIZE*2];

extern volatile bool g_TX_SAI_in_use;

extern uint8_t *spi_soundBuf;
extern sai_transfer_t xfer;

void init_sound(void);
void terminate_sound(void);
void set_melody(const int *melody);
int get_freq(int tone);
void create_song(const uint8_t *melody);
void fw_init_beep_task(void);
void send_sound_data(void);
void receive_sound_data(void);
void store_soundbuffer(void);
void retrieve_soundbuffer(void);
void tick_RXsoundbuffer(void);
void setup_soundBuffer(void);
void tick_melody(void);
void fw_beep_task(void *data);

#endif /* _FW_SOUND_H_ */
