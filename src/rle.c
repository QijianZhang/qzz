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

#include "rle.h"

static inline size_t count_same_bytes(const uint8_t *bytes, size_t size)
{
	for (size_t i = 1; i < size; i++) {
		if (bytes[i] != bytes[0])
			return i;
	}
	return size;
}

static inline void encode_push(Str edata, uint8_t byte, size_t count)
{
	size_t r = count / 256;
	for (size_t i = 0; i < r; i++) {
		Str_push(edata, 255);
		Str_push(edata, byte);
	}
	size_t m = count % 256;
	if (m != 0) {
		Str_push(edata, m - 1);
		Str_push(edata, byte);
	}
}

static inline void decode_push(Str ddata, uint8_t byte, size_t count)
{
	for (size_t i = 0; i < count; i++) {
		Str_push(ddata, byte);
	}
}

void qzz_rle_encode(const uint8_t *data, size_t size, Str output)
{
	Str_clear(output);

	size_t count = 0;

	while (count < size) {
		size_t c = count_same_bytes(data, size - count);
		encode_push(output, data[0], c);
		count += c;
		data += count;
	}
	Str_shrink(output);
}

void qzz_rle_decode(const uint8_t *data, size_t size, Str output)
{
	Str_clear(output);
	size -= 1;

	for (size_t i = 0; i < size; i += 2) {
		decode_push(output, data[i + 1], data[i] + 1);
	}
	Str_shrink(output);
}

