#ifndef CAMERA_H
#define CAMERA_H

#include "ext/matrix_float4x4.hpp"
#include "ext/matrix_transform.hpp"

class Camera
{
	private:
		float yaw, pitch;
		glm::vec3 camera_front;

	public:
		glm::vec3 camera_pos;

		glm::mat4 camera_space()
		{
			glm::vec3 world_up = glm::vec3(0.f, 1.f, 0.f);

			return glm::lookAt(camera_pos, camera_front + camera_pos, world_up);
		}

		Camera(glm::vec3 pos)
		{
			this->yaw = 0.f;
			this->pitch = 0.f;
			this->camera_front = glm::vec3(0.f, 0.f, 1.f);
			this->camera_pos = pos;
		}

		void turn_pitch(float radians)
		{
			this->pitch += radians;
			
			const float less_than_tau = glm::pi<float>()/2.1;
			if(this->pitch < -less_than_tau) this->pitch = -less_than_tau;
			if(this->pitch > less_than_tau) this->pitch = less_than_tau;

			camera_front.x = cos(yaw)*cos(pitch);
			camera_front.y = sin(pitch);
			camera_front.z = sin(yaw)*cos(pitch);
		}

		void turn_yaw(float radians)
		{
			this->yaw += radians;

			camera_front.x = cos(yaw)*cos(pitch);
			camera_front.z = sin(yaw)*cos(pitch);
		}

		void move(glm::vec3 movement)
		{
			this->camera_pos += movement;
		}

		glm::vec3 get_position()
		{
			return this->camera_pos;
		}

		glm::vec3 get_front()
		{
			return this->camera_front;
		}

		float get_yaw()
		{
			return this->yaw;
		}

		float get_pitch()
		{
			return this->pitch;
		}
};

#endif
