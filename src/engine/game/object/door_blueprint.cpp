/*
 * Copyright (c) 2020-2021 The reone project contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/** @file
 *  Door functions related to blueprint loading.
 */

#include "door.h"

#include "../../resource/strings.h"

#include "../game.h"

using namespace std;

using namespace reone::resource;

namespace reone {

namespace game {

void Door::loadUTD(const GffStruct &utd) {
    _tag = boost::to_lower_copy(utd.getString("Tag"));
    _name = _game->services().resource().strings().get(utd.getInt("LocName"));
    _blueprintResRef = boost::to_lower_copy(utd.getString("TemplateResRef"));
    _autoRemoveKey = utd.getBool("AutoRemoveKey");
    _conversation = boost::to_lower_copy(utd.getString("Conversation"));
    _interruptable = utd.getBool("Interruptable");
    _faction = utd.getEnum("Faction", Faction::Invalid);
    _plot = utd.getBool("Plot");
    _minOneHP = utd.getBool("Min1HP");
    _keyRequired = utd.getBool("KeyRequired");
    _lockable = utd.getBool("Lockable");
    _locked = utd.getBool("Locked");
    _openLockDC = utd.getInt("OpenLockDC");
    _keyName = utd.getString("KeyName");
    _hitPoints = utd.getInt("HP");
    _currentHitPoints = utd.getInt("CurrentHP");
    _hardness = utd.getInt("Hardness");
    _fortitude = utd.getInt("Fort");
    _genericType = utd.getInt("GenericType");
    _static = utd.getBool("Static");

    _onClosed = utd.getString("OnClosed"); // always empty, but could be useful
    _onDamaged = utd.getString("OnDamaged"); // always empty, but could be useful
    _onDeath = utd.getString("OnDeath");
    _onHeartbeat = utd.getString("OnHeartbeat");
    _onLock = utd.getString("OnLock"); // always empty, but could be useful
    _onMeleeAttacked = utd.getString("OnMeleeAttacked"); // always empty, but could be useful
    _onOpen = utd.getString("OnOpen");
    _onSpellCastAt = utd.getString("OnSpellCastAt"); // always empty, but could be useful
    _onUnlock = utd.getString("OnUnlock"); // always empty, but could be useful
    _onUserDefined = utd.getString("OnUserDefined");
    _onClick = utd.getString("OnClick");
    _onFailToOpen = utd.getString("OnFailToOpen");

    // Unused fields:
    //
    // - Description (always -1)
    // - CloseLockDC (always 0)
    // - PortraitId (not applicable, mostly 0)
    // - TrapDetectable (not applicable, always 1)
    // - TrapDetectDC (not applicable, always 0)
    // - TrapDisarmable (not applicable, always 1)
    // - DisarmDC (not applicable, mostly 28)
    // - TrapFlag (not applicable, always 0)
    // - TrapOneShot (not applicable, always 1)
    // - TrapType (not applicable)
    // - AnimationState (always 0)
    // - Appearance (always 0)
    // - Ref (always 0)
    // - Will (always 0)
    // - OnDisarm (not applicable, always empty)
    // - OnTrapTriggered (not applicable, always empty)
    // - LoadScreenID (always 0)
    // - PaletteID (toolset only)
    // - Comment (toolset only)
}

} // namespace game

} // namespace reone
