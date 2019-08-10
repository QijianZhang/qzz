// qzz: simple compressor stuff
// Copyright (C) 2019  Qijian Zhang <qijian.zhang@qq.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef QZZ_RLE_H
#define QZZ_RLE_H
#include <stdlib.h>
#include <stdint.h>
#include <cutils/Vector/Str.h>

/// Use RLE to compress data
///
/// Compressed data is layout as:
///	[<count-of-byte - 1><byte>]...
/// <count-of-byte - 1> and <byte> both are one-byte unsigned integer.
/// For example, 16 bytes that have same value 255 will be compressed
/// to 2 bytes, the first one is 15 and another 255.
///
/// @args:
///	data: A sequence of bytes to be compressed
///	size: Number of bytes to be compressed
///	output: A Str to hold the encoded data, must not be NULL
void qzz_rle_encode(const uint8_t *data, size_t size, Str output);

/// decompressor of @function qzz_rle_encode
///
/// If @arg size is not an even number, the last one byte will be ignored.
void qzz_rle_decode(const uint8_t *data, size_t size, Str output);

#endif

