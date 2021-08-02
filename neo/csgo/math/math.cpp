#include "math.h"
#include <d3d9.h>
#include "../globals.h"
#include <DirectXMath.h>

namespace math {
    void vector_transform(const vec3_t& in1, const matrix3x4_t& in2, vec3_t& out)
    {
        out[0] = in1.dot(in2[0]) + in2[0][3];
        out[1] = in1.dot(in2[1]) + in2[1][3];
        out[2] = in1.dot(in2[2]) + in2[2][3];
    }
	bool screen_transform(const vec3_t& in, vec3_t& out)
	{
		auto exception_filter = [](int code, PEXCEPTION_POINTERS ex)
		{
			return EXCEPTION_EXECUTE_HANDLER;
		};

		__try
		{
			auto result = *(PDWORD)(g::v_matrix::offset) + 988;
			if (!result)
			{
				out.x *= 100000;
				out.y *= 100000;
				return false;
			}

			const auto& world_matrix = *(_D3DMATRIX*)result;

			const auto w = world_matrix.m[3][0] * in.x + world_matrix.m[3][1] * in.y + world_matrix.m[3][2] * in.z + world_matrix.m[3][3];
			if (w < 0.001f)
			{
				out.x *= 100000;
				out.y *= 100000;
				return false;
			}

			out.x = world_matrix.m[0][0] * in.x + world_matrix.m[0][1] * in.y + world_matrix.m[0][2] * in.z + world_matrix.m[0][3];
			out.y = world_matrix.m[1][0] * in.x + world_matrix.m[1][1] * in.y + world_matrix.m[1][2] * in.z + world_matrix.m[1][3];
			out.z = 0.0f;

			out.x /= w;
			out.y /= w;

			return true;
		}
		__except (exception_filter(GetExceptionCode(), GetExceptionInformation()))
		{
			out.x *= 100000;
			out.y *= 100000;
			return false;
		}
	}

	bool w2s(const vec3_t& in, vec3_t& out)
	{
		if (!g::v_matrix::has_offset)
			return false;

		if (!screen_transform(in, out))
			return false;

		int w, h;
		csgo::engine->screen_size(w, h);

		out.x = (w / 2.0f) + (out.x * w) / 2.0f;
		out.y = (h / 2.0f) - (out.y * h) / 2.0f;

		return true;
	}
	void vector_angles(const vec3_t& forward, vec3_t& angles)
	{
		float	tmp, yaw, pitch;

		if (forward[1] == 0 && forward[0] == 0) {
			yaw = 0;
			if (forward[2] > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else {
			yaw = (atan2(forward[1], forward[0]) * 180 / DirectX::XM_PI);
			if (yaw < 0)
				yaw += 360;

			tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
			pitch = (atan2(-forward[2], tmp) * 180 / DirectX::XM_PI);
			if (pitch < 0)
				pitch += 360;
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}
	void fix_angles(vec3_t* angles) {
		angles->clamp();
		//angles->normalized();
	}
}
