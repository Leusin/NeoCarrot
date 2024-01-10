///
/// 2024-01-09

#pragma once

#include "IComponent.h"
#include "Matrix.h"

namespace game
{

class Transform : public core::IComponent
{
public:
    Transform();
    ~Transform();

    /*
    	math::Matrix GetPosition() const;
		math::Matrix GetRotation() const;
		math::Matrix GetScale() const;
		
		void SetPostiton(math::Matrix& pos);
        void SetRotation(math::Matrix& rot);
        void SetScale(math::Matrix& scl);
    */

private:
    math::Matrix _position;
    math::Matrix _rotation;
    math::Matrix _scale;
};

} // namespace game