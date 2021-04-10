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
 *  Item functions related to blueprint loading.
 */

#include "item.h"

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

#include "../../audio/files.h"
#include "../../render/model/models.h"
#include "../../render/textures.h"
#include "../../resource/resources.h"
#include "../../resource/strings.h"

using namespace std;

using namespace reone::audio;
using namespace reone::render;
using namespace reone::resource;

namespace reone {

namespace game {

void Item::loadUTI(const GffStruct &uti) {
    _baseItemType = uti.getInt("BaseItem");
    _blueprintResRef = boost::to_lower_copy(uti.getString("TemplateResRef"));
    _descIdentified = Strings::instance().get(uti.getInt("DescIdentified"));
    _localizedName = Strings::instance().get(uti.getInt("LocalizedName"));
    _tag = boost::to_lower_copy(uti.getString("Tag"));

    shared_ptr<TwoDA> baseItems(Resources::instance().get2DA("baseitems"));
    _attackRange = baseItems->getInt(_baseItemType, "maxattackrange");
    _criticalHitMultiplier = baseItems->getInt(_baseItemType, "crithitmult");
    _criticalThreat = baseItems->getInt(_baseItemType, "critthreat");
    _damageFlags = baseItems->getInt(_baseItemType, "damageflags");
    _dieToRoll = baseItems->getInt(_baseItemType, "dietoroll");
    _equipableSlots = baseItems->getUint(_baseItemType, "equipableslots", 0);
    _itemClass = boost::to_lower_copy(baseItems->getString(_baseItemType, "itemclass"));
    _numDice = baseItems->getInt(_baseItemType, "numdice");
    _weaponType = static_cast<WeaponType>(baseItems->getInt(_baseItemType, "weapontype"));
    _weaponWield = static_cast<WeaponWield>(baseItems->getInt(_baseItemType, "weaponwield"));

    string iconResRef;
    if (isEquippable(InventorySlot::body)) {
        _baseBodyVariation = boost::to_lower_copy(baseItems->getString(_baseItemType, "bodyvar"));
        _bodyVariation = uti.getInt("BodyVariation", 1);
        _textureVariation = uti.getInt("TextureVar", 1);
        iconResRef = str(boost::format("i%s_%03d") % _itemClass % _textureVariation);
    } else if (isEquippable(InventorySlot::rightWeapon)) {
        _modelVariation = uti.getInt("ModelVariation", 1);
        iconResRef = str(boost::format("i%s_%03d") % _itemClass % _modelVariation);
    } else {
        _modelVariation = uti.getInt("ModelVariation", 1);
        iconResRef = str(boost::format("i%s_%03d") % _itemClass % _modelVariation);
    }
    _icon = Textures::instance().get(iconResRef, TextureUsage::GUI);

    loadAmmunitionTypeFromUTI(uti);
}

void Item::loadAmmunitionTypeFromUTI(const GffStruct &uti) {
    int baseItemIdx = uti.getInt("BaseItem");
    shared_ptr<TwoDA> baseItems(Resources::instance().get2DA("baseitems"));

    int ammunitionIdx = baseItems->getInt(baseItemIdx, "ammunitiontype", -1);
    if (ammunitionIdx != -1) {
        shared_ptr<TwoDA> twoDa(Resources::instance().get2DA("ammunitiontypes"));
        _ammunitionType = make_shared<Item::AmmunitionType>();
        _ammunitionType->model = Models::instance().get(boost::to_lower_copy(twoDa->getString(ammunitionIdx, "model")));
        _ammunitionType->shotSound1 = AudioFiles::instance().get(boost::to_lower_copy(twoDa->getString(ammunitionIdx, "shotsound0")));
        _ammunitionType->shotSound2 = AudioFiles::instance().get(boost::to_lower_copy(twoDa->getString(ammunitionIdx, "shotsound1")));
        _ammunitionType->impactSound1 = AudioFiles::instance().get(boost::to_lower_copy(twoDa->getString(ammunitionIdx, "impactsound0")));
        _ammunitionType->impactSound2 = AudioFiles::instance().get(boost::to_lower_copy(twoDa->getString(ammunitionIdx, "impactsound1")));
    }
}

} // namespace game

} // namespace reone