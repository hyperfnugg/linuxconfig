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

#define LAYOUT( \
	L00, L01, L02, L03,           R03, R02, R01, R00, \
	     L10, L11, L12,           R12, R11, R10, \
	L20, L21, L22, L23,           R23, R22, R21, R20, \
	L30, L31, L32, L33,           R33, R32, R31, R30, \
            L42, L43,           R43, R42 \
	) \
	{ \
		{ L00, L01, L02, L03, }, \
		{ KC_NO, L10, L11, L12, }, \
		{ L20, L21, L22, L23, }, \
		{ L30, L31, L32, L33, }, \
		{ KC_NO, KC_NO, L42, L43, }, \
		{ R00, R01, R02, R03, }, \
		{ KC_NO, R10, R11, R12, }, \
		{ R20, R21, R22, R23, }, \
		{ R30, R31, R32, R33, }, \
		{ KC_NO, KC_NO, R42, R43, }, \
	}
