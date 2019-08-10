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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/rle.h"

void check_rle()
{
	// 17 q 24 z
	uint8_t data[] = "qqqqqqqqqqqqqqqqqqzzzzzzzzzzzzzzzzzzzzzzzzz";
	size_t data_size = sizeof(data) - 1;

	Str encoded = Str_newWithCapacity(0);
	Str decoded = Str_newWithCapacity(0);

	qzz_rle_encode(data, data_size, encoded);
	qzz_rle_decode(Str_data(encoded), Str_getLength(encoded), decoded);

	assert(4 == Str_getLength(encoded));
	assert(17 == Str_get(encoded, 0));
	assert('q' == Str_get(encoded, 1));
	assert(24 == Str_get(encoded, 2));
	assert('z' == Str_get(encoded, 3));

	assert(data_size == Str_getLength(decoded));
	assert(0 == strncmp(data, Str_data(decoded), data_size));

	Str_free(encoded);
	Str_free(decoded);
}

int main(int argc, char *argv[])
{
	check_rle();
	return 0;
}

