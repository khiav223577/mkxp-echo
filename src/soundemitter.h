/*
** soundemitter.h
**
** This file is part of mkxp.
**
** Copyright (C) 2014 Jonas Kulla <Nyocurio@gmail.com>
**
** mkxp is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 2 of the License, or
** (at your option) any later version.
**
** mkxp is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with mkxp.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOUNDEMITTER_H
#define SOUNDEMITTER_H

#include "intrulist.h"
#include "al-util.h"
#include "boost-hash.h"

#include <string>

#define SE_SOURCES 6

struct SoundBuffer;

struct SoundEmitter
{
	typedef BoostHash<std::string, SoundBuffer*> BufferHash;

	IntruList<SoundBuffer> buffers;
	BufferHash bufferHash;

	/* Byte count sum of all cached / playing buffers */
	uint32_t bufferBytes;

	AL::Source::ID alSrcs[SE_SOURCES];
	SoundBuffer *atchBufs[SE_SOURCES];

	/* Indices of sources, sorted by priority (lowest first) */
	size_t srcPrio[SE_SOURCES];

	SoundEmitter();
	~SoundEmitter();

	void play(const std::string &filename,
	          int volume,
	          int pitch);

	void stop();

private:
	SoundBuffer *allocateBuffer(const std::string &filename);
};

#endif // SOUNDEMITTER_H