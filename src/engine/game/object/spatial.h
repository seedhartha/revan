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

#include "../../graphics/walkmesh/walkmesh.h"
#include "../../scene/animproperties.h"
#include "../../scene/node/scenenode.h"
#include "../../scene/scenegraph.h"

#include "../action/playanimation.h"
#include "../enginetype/effect.h"
#include "../types.h"

#include "object.h"

namespace reone {

namespace game {

class Item;
class ObjectFactory;
class Room;

class SpatialObject : public Object {
public:
    void update(float dt) override;

    virtual void die();

    void face(const SpatialObject &other);
    void face(const glm::vec3 &point);
    void faceAwayFrom(const SpatialObject &other);

    float getDistanceTo(const glm::vec2 &point) const;
    float getDistanceTo2(const glm::vec2 &point) const;
    float getDistanceTo(const glm::vec3 &point) const;
    float getDistanceTo2(const glm::vec3 &point) const;
    float getDistanceTo(const SpatialObject &other) const;
    float getDistanceTo2(const SpatialObject &other) const;

    bool contains(const glm::vec3 &point) const;

    virtual bool isSelectable() const;
    bool isOpen() const { return _open; }

    virtual glm::vec3 getSelectablePosition() const;
    float getFacing() const { return glm::eulerAngles(_orientation).z; }

    virtual std::shared_ptr<graphics::Walkmesh> getWalkmesh() const;

    Room *room() const { return _room; }
    const glm::vec3 &position() const { return _position; }
    const glm::mat4 &transform() const { return _transform; }
    bool visible() const { return _visible; }
    std::shared_ptr<scene::SceneNode> sceneNode() const { return _sceneNode; }

    void setRoom(Room *room);
    void setPosition(const glm::vec3 &position);
    void setFacing(float facing);
    void setVisible(bool visible);

    // Animation

    virtual void playAnimation(AnimationType type, scene::AnimationProperties properties = scene::AnimationProperties(), std::shared_ptr<PlayAnimationAction> actionToComplete = nullptr);

    // END Animation

    // Inventory

    std::shared_ptr<Item> addItem(const std::string &resRef, int stackSize = 1, bool dropable = true);
    void addItem(const std::shared_ptr<Item> &item);
    bool removeItem(const std::shared_ptr<Item> &item, bool &last);
    void moveDropableItemsTo(SpatialObject &other);

    std::shared_ptr<Item> getFirstItem();
    std::shared_ptr<Item> getNextItem();
    std::shared_ptr<Item> getItemByTag(const std::string &tag);

    const std::vector<std::shared_ptr<Item>> &items() const { return _items; }

    // END Inventory

    // Effects

    void clearAllEffects();
    void applyEffect(const std::shared_ptr<Effect> &effect, DurationType durationType, float duration = 0.0f);

    // END Effects

    // Stunt mode

    bool isStuntMode() const { return _stunt; }

    /**
     * Places this object into the stunt mode. Objects in this mode have their
     * position and orientation fixed to the world origin. Subsequent changes to
     * position and orientation will be buffered and applied when
     * stopStuntMode is called.
     */
    void startStuntMode();

    void stopStuntMode();

    // END Stunt mode

protected:
    struct AppliedEffect {
        std::shared_ptr<Effect> effect;
        DurationType durationType { DurationType::Instant };
        float duration { 0.0f };
    };

    ObjectFactory *_objectFactory;
    scene::SceneGraph *_sceneGraph;

    glm::vec3 _position { 0.0f };
    glm::quat _orientation { 1.0f, 0.0f, 0.0f, 0.0f };
    glm::mat4 _transform { 1.0f };
    bool _visible { true };
    std::shared_ptr<scene::SceneNode> _sceneNode;
    Room *_room { nullptr };
    std::vector<std::shared_ptr<Item>> _items;
    std::deque<AppliedEffect> _effects;
    bool _open { false };
    bool _stunt { false };

    SpatialObject(
        uint32_t id,
        ObjectType type,
        Game *game,
        ObjectFactory *objectFactory,
        scene::SceneGraph *sceneGraph);

    virtual void updateTransform();

private:
    int _itemIndex { 0 };

    void updateEffects(float dt);
    void applyInstantEffect(Effect &effect);
};

} // namespace game

} // namespace reone
