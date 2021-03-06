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

#include "object.h"

using namespace std;

namespace reone {

namespace game {

void Object::clearAllActions() {
    while (!_actions.empty()) {
        _actions.pop_front();
    }
}

void Object::addAction(unique_ptr<Action> action) {
    _actions.push_back(move(action));
}

void Object::addActionOnTop(unique_ptr<Action> action) {
    _actions.push_front(move(action));
}

void Object::delayAction(unique_ptr<Action> action, float seconds) {
    DelayedAction delayed;
    delayed.action = move(action);
    delayed.timer.reset(seconds);
    _delayed.push_back(move(delayed));
}

void Object::updateActions(float dt) {
    removeCompletedActions();
    updateDelayedActions(dt);
}

void Object::removeCompletedActions() {
    while (true) {
        shared_ptr<Action> action(getCurrentAction());
        if (!action || !action->isCompleted()) return;

        _actions.pop_front();
    }
}

void Object::updateDelayedActions(float dt) {
    for (auto &delayed : _delayed) {
        if (delayed.timer.advance(dt)) {
            _actions.push_back(move(delayed.action));
        }
    }
    auto delayedToRemove = remove_if(
        _delayed.begin(),
        _delayed.end(),
        [](const DelayedAction &delayed) { return delayed.timer.isTimedOut(); });

    _delayed.erase(delayedToRemove, _delayed.end());
}

bool Object::hasUserActionsPending() const {
    for (auto &action : _actions) {
        if (action->isUserAction()) return true;
    }
    return false;
}

shared_ptr<Action> Object::getCurrentAction() const {
    return _actions.empty() ? nullptr : _actions.front();
}

} // namespace game

} // namespace reone
