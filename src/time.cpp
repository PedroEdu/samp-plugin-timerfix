/**
* Copyright (c) 2013-2014, Dan
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "time.h"

#ifdef WIN32
LARGE_INTEGER startTime;
unsigned long long freq;
#else
struct timespec startTime;
#endif

void InitTime()
{
#ifdef WIN32
	LARGE_INTEGER t;
	QueryPerformanceFrequency(&t);
	freq = t.QuadPart / 1000;
	QueryPerformanceCounter(&startTime);
#else
	clock_gettime(CLOCK_MONOTONIC, &startTime);
#endif
}

unsigned long long GetMsTime()
{
#ifdef WIN32
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return (t.QuadPart - startTime.QuadPart) / freq;
#else
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	t.tv_sec -= startTime.tv_sec;
	t.tv_nsec -= startTime.tv_nsec;
	if (t.tv_nsec < 0) {
		t.tv_sec -= 1;
		t.tv_nsec += 1000000000;
	}
	return t.tv_sec * 1000 + t.tv_nsec / 1000000;
#endif
}
