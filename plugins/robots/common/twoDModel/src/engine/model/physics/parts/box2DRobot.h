/* Copyright 2017 Dmitry Mordvinov, Gleb Zakharov
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
 * limitations under the License. */

#pragma once

#include <QList>

#include "src/engine/model/physics/box2DPhysicsEngine.h"

class b2World;
class b2Joint;
class b2Body;

namespace twoDModel {
namespace model {
	class RobotModel;
namespace physics {
namespace parts {

class box2DWheel;

class box2DRobot{
public:
	b2Body *body; // Take ownership
	QList<box2DWheel *> wheels; // Take ownership
	QList<b2Joint *> joints; // Take ownership
	twoDModel::model::RobotModel * const model; // Doesn't take ownership
	twoDModel::model::physics::box2DPhysicsEngine *engine; // Doesn't take ownership
	b2World &world; // Doesn't take ownership

	box2DRobot(twoDModel::model::physics::box2DPhysicsEngine *engine
			, twoDModel::model::RobotModel * const robotModel
			, b2Vec2 pos
			, float angle);
	~box2DRobot();

	void Stop();
	void StartStopping();
	void FinishStopping();
	bool IsStopping();

private:
	void connectWheels();
	void connectWheel(box2DWheel &wheel);

	bool isStopping = false;
};

}
}
}
}
