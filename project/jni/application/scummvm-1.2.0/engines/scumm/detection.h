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
 * $URL: https://scummvm.svn.sourceforge.net/svnroot/scummvm/scummvm/tags/release-1-2-0/engines/scumm/detection.h $
 * $Id: detection.h 41278 2009-06-06 17:59:54Z sev $
 *
 */

#ifndef SCUMM_DETECTION_H
#define SCUMM_DETECTION_H

#include "common/util.h"

namespace Scumm {

/**
 * Descriptor of a specific SCUMM game. Used internally to store
 * information about the tons of game variants that exist.
 */
struct GameSettings {
	/**
	 * The gameid of this game.
	 */
	const char *gameid;

	/**
	 * An identifier which can be used to distinguish game variants.
	 * This string is also used to augment the description string
	 * generated by the detector, and to search the gameFilenamesTable.
	 * It is also used to search the MD5 table (it matches the "extra"
	 * data in scumm-md5.txt).
	 *
	 * Equal to 0 (zero) *if and only if* the game has precisely one
	 * variant. Failing to obey this rule can lead to odd bugs.
	 */
	const char *variant;

	/**
	 * An optional string that will be added to the 'preferredtarget'
	 * computed by the detector.
	 */
	const char *preferredTag;

	/**
	 * The numerical gameid of this game.
	 * This is not in one-to-one correspondence with the gameid above.
	 * But if two games settings have the same id (except for GID_HEGAME),
	 * then they also have the same gameid ; the converse does not hold
	 * in general.
	 */
	byte id;

	/** The SCUMM version. */
	byte version;

	/** The HE subversion. */
	byte heversion;

	/** MidiDriverFlags values */
	int midi;

	/**
	 * Bitmask obtained by ORing various GameFeatures enums, and used
	 * to en-/disable certain features of this game variant.
	 */
	uint32 features;

	/**
	 * Platform indicator, this is set to a value different from
	 * kPlatformUnknown if this game variant only existed for this
	 * specific platform.
	 */
	Common::Platform platform;

	/**
	 * Game GUI options. Used to enable/disable certain GUI widgets
	 */
	uint32 guioptions;
};

enum FilenameGenMethod {
	kGenDiskNum,
	kGenRoomNum,
	kGenHEMac,
	kGenHEMacNoParens,
	kGenHEPC,
	kGenUnchanged
};

struct FilenamePattern {
	const char *pattern;
	FilenameGenMethod genMethod;
};

struct GameFilenamePattern {
	const char *gameid;
	const char *pattern;
	FilenameGenMethod genMethod;
	Common::Language language;
	Common::Platform platform;
	const char *variant;
};

struct DetectorResult {
	FilenamePattern fp;
	GameSettings game;
	Common::Language language;
	Common::String md5;
	const char *extra;
};

} // End of namespace Scumm


#endif
