/* Copyright 2021 hyperfnugg <eviddal@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define ___ KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
 
#define LAYOUT( \
	k00, k01, k02, k03,     k56, k57, k58, k59, \
	k10, k11, k12, k13,     k66, k67, k68, k69, \
	k20, k21, k22, k23,     k76, k77, k78, k79, \
	k30, k31, k32, k33,     k86, k87, k88, k89, \
	k40, k41, k42, k43,     k96, k97, k98, k99, \
	k04, k14,                         k55, k65, \
	k24, k34,                         k75, k85, \
	k44,                                   k95  \
) { \
{k00,k01,k02,k03,k04,___,___,___,___,___}, \
{k10,k11,k12,k13,k14,___,___,___,___,___}, \
{k20,k21,k22,k23,k24,___,___,___,___,___}, \
{k30,k31,k32,k33,k34,___,___,___,___,___}, \
{k40,k41,k42,k43,k44,___,___,___,___,___}, \
{___,___,___,___,___,k55,k56,k57,k58,k59}, \
{___,___,___,___,___,k65,k66,k67,k68,k69}, \
{___,___,___,___,___,k75,k76,k77,k78,k79}, \
{___,___,___,___,___,k85,k86,k87,k88,k89}, \
{___,___,___,___,___,k95,k96,k97,k98,k99} \
}
