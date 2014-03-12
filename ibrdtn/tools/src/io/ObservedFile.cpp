/*
 * ObservedFile.cpp
 *
 * Copyright (C) 2013 IBR, TU Braunschweig
 *
 * Written-by: David Goltzsche <goltzsch@ibr.cs.tu-bs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  Created on: Sep 30, 2013
 */

#include "ObservedFile.h"
#include <string.h>

ObservedFile::ObservedFile()
 : _last_sent(0), _size(0), _is_system(false), _is_directory(false)
{
}
ObservedFile::~ObservedFile()
{
}

bool ObservedFile::lastHashesEqual( size_t n )
{
	if (n > _hashes.size()) return false;

	for (size_t i = 1; i < n; i++)
	{
		const char* hash1 = _hashes.at(_hashes.size() - i).c_str();
		const char* hash2 = _hashes.at(_hashes.size() - i - 1).c_str();
		int ret = memcmp(hash1,hash2,sizeof(hash1));
		if(ret != 0)
			return false;
	}
	return true;
}

size_t ObservedFile::size() const
{
	return _size;
}

bool ObservedFile::isSystem() const
{
	return _is_system;
}

bool ObservedFile::isDirectory() const
{
	return _is_directory;
}

std::string ObservedFile::getHash() const
{
	return _hash;
}
void ObservedFile::tick()
{
	_hashes.push_back(getHash());
}

void ObservedFile::send()
{
	_hashes.clear();
}

bool ObservedFile::hashcompare( ObservedFile* a, ObservedFile* b )
{
	const char* hash1 = a->getHash().c_str();
	const char* hash2 = b->getHash().c_str();
	return (memcmp(hash1,hash2,sizeof(*hash1)) != 0);
}

bool ObservedFile::namecompare( ObservedFile* a, ObservedFile* b )
{
	std::string p1= a->getPath();
	std::string p2 = b->getPath();
	return (p1 != p2);
}
