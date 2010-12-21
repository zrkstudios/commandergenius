/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL: https://scummvm.svn.sourceforge.net/svnroot/scummvm/scummvm/tags/release-1-2-0/backends/platform/ds/arm9/source/cdaudio.h $
 * $Id: cdaudio.h 50689 2010-07-05 16:11:11Z fingolfin $
 *
 */

#ifndef _CDAUDIO_H_
#define _CDAUDIO_H_

namespace DS {
namespace CD {

void setActive(bool active);
void playTrack(int track, int numLoops, int startFrame, int duration);
void stopTrack();
bool checkCD();
bool getActive();
bool isPlaying();
void update();

}
}	// End of namespace DS

#endif
