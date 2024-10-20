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
 * @file all_samples.h
 * @author Marcel Licence
 * @date 20.10.2024
 *
 * @brief This file links some samples into the project
 */

#include "ClintEastwoodInstrumental.h" /* can be created using bin2c from 16bit mono wav file */
#include "scratch01.h" /* can be created using bin2c from 16bit mono wav file */
#include "scratch08.h" /* can be created using bin2c from 16bit mono wav file */
#include "scratch10.h" /* can be created using bin2c from 16bit mono wav file */


struct sample_list_s
{
    const unsigned char *data;
    int len;
} ;


struct sample_list_s sample_list[] =
{
    {_acClintEastwoodInstrumental, sizeof(_acClintEastwoodInstrumental)},
    {_acscratch01, sizeof(_acscratch01)},
    {_acscratch08, sizeof(_acscratch08)},
    {_acscratch10, sizeof(_acscratch10)},
};
