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

#pragma once

#include "action.h"

namespace reone {

namespace game {

class MoveToPointAction : public Action {
public:
    MoveToPointAction(glm::vec3 point) :
        Action(ActionType::MoveToPoint),
        _point(std::move(point)) {
    }

    const glm::vec3 &point() const { return _point; }

private:
    glm::vec3 _point;
};

} // namespace game

} // namespace reone
