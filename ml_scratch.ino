/*
 * Copyright (c) 2024 Marcel Licence
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
 * der GNU General Public License, wie von der Free Software Foundation,
 * Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
 * veröffentlichten Version, weiter verteilen und/oder modifizieren.
 *
 * Dieses Programm wird in der Hoffnung bereitgestellt, dass es nützlich sein wird, jedoch
 * OHNE JEDE GEWÄHR,; sogar ohne die implizite
 * Gewähr der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
 * Siehe die GNU General Public License für weitere Einzelheiten.
 *
 * Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
 * Programm erhalten haben. Wenn nicht, siehe <https://www.gnu.org/licenses/>.
 */

/**
 * @file ml_scratch.ino
 * @author Marcel Licence
 * @date 20.10.2024
 *
 * @brief This file contains the main project appplication
 *
 * @see YouTube demo of the origin: https://www.youtube.com/watch?v=Ml6VrlV3hvk
 */

#include "config.h"

#include <Wire.h>

#include <ml_utils.h> /*!< required library: ML SynthTools from https://github.com/marcel-licence/ML_SynthTools */
#include <ml_scratch.h> /*!< required library: ML SynthTools from https://github.com/marcel-licence/ML_SynthTools */

#include "samples/all_samples.h"

#define ML_SYNTH_INLINE_DECLARATION
#include <ml_inline.h> /*!< required library: ML SynthTools from https://github.com/marcel-licence/ML_SynthTools */
#undef ML_SYNTH_INLINE_DECLARATION


#define ML_SYNTH_INLINE_DEFINITION
#include <ml_inline.h> /*!< required library: ML SynthTools from https://github.com/marcel-licence/ML_SynthTools */
#undef ML_SYNTH_INLINE_DEFINITION


struct app_s
{
    float inputGain;
};


static struct app_s app =
{
    0.0f
};


void setup(void)
{
    /*
     * this code runs once
     */
    delay(1000);
    Serial.begin(SERIAL_BAUDRATE);
    delay(3000);
    Serial.printf("ml_scratch\n");

#if (defined I2C_SDA_PIN) && (defined I2C_SCL_PIN)
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
#else
    Wire.begin();
#endif
#ifdef I2C_SPEED
    Wire.setClock(I2C_SPEED);
#endif
    AS5600_Setup();

#ifdef ML_BOARD_SETUP
    Board_Setup();
#else
    Audio_Setup();
    Midi_Setup();
#ifdef BLINK_LED_PIN
    Blink_Setup();
#endif
#endif

    Scratch_Init(SAMPLE_RATE);

    /*
     * load static samples from flash assigned to note C (36) ++
     */
    for (uint32_t i = 0; i < sizeof(sample_list) / sizeof(sample_list[0]); i++)
    {
        if (Scratch_AddSampleStatic((const uint8_t *)sample_list[i].data, sample_list[i].len, 36 + i))
        {
            printf("sample len: %d\n", sample_list[i].len);
        }
        else
        {
            printf("error couldn't add sample!\n");
        }
        Scratch_SetPitchAbs(0, i);
    }

    Scratch_SetPitchAbs(1, 0); /* start playback of sample0 */
}

#ifdef AS5600_ENABLED
void loop_4th(void)
{
    uint8_t sample_to_scratch = 1;
    AS5600_Loop();
    float pitch = AS5600_GetPitch(4);
#if 1
    if ((pitch > 0.05) || (pitch < - 0.05))
    {
        Serial.printf("%0.3f\n", pitch);
    }
#endif
    Scratch_SetPitchAbs(pitch, sample_to_scratch);
}
#endif

/**
    @brief This function will be called every second.
        In case of an overload the function will not called so often
  */
void loop_1Hz(void)
{
#ifdef BLINK_LED_PIN
    Blink_Process();
#endif
}

void loop(void)
{
    static int loop_cnt_1hz = 0; /*!< counter to allow 1Hz loop cycle */

    loop_cnt_1hz += SAMPLE_BUFFER_SIZE;

    if (loop_cnt_1hz >= SAMPLE_RATE)
    {
        loop_cnt_1hz -= SAMPLE_RATE;
        loop_1Hz();
    }

#ifdef AS5600_ENABLED
    static uint32_t prec4 = 0;
    prec4++;
    if ((prec4 % 4) == 0)
    {
        loop_4th();
    }
#endif

    /*
     * MIDI processing
     */
    Midi_Process();

    /*
      * And finally the audio stuff
      */
    Q1_14 left[SAMPLE_BUFFER_SIZE], right[SAMPLE_BUFFER_SIZE];

    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));

#ifdef ESP32
    Audio_Input(left, right);
#endif

    mul(left, app.inputGain, left, SAMPLE_BUFFER_SIZE);
    mul(right, app.inputGain, right, SAMPLE_BUFFER_SIZE);
    Scratch_Process(left, right, SAMPLE_BUFFER_SIZE);

    Audio_Output(left, right);
}

