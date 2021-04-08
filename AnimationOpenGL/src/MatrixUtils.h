#pragma once
#include "vendor/glm/glm/glm.hpp"
#include <iostream>

class MatrixUtils
{
public:
	static float determinant(const glm::mat4& m) 
	{
		float f =
			m[0][0]
			* ((m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1] + m[1][3] * m[2][1] * m[3][2])
				- m[1][3] * m[2][2] * m[3][1]
				- m[1][1] * m[2][3] * m[3][2]
				- m[1][2] * m[2][1] * m[3][3]);
		f -= m[0][1]
			* ((m[1][0] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][0] + m[1][3] * m[2][0] * m[3][2])
				- m[1][3] * m[2][2] * m[3][0]
				- m[1][0] * m[2][3] * m[3][2]
				- m[1][2] * m[2][0] * m[3][3]);
		f += m[0][2]
			* ((m[1][0] * m[2][1] * m[3][3] + m[1][1] * m[2][3] * m[3][0] + m[1][3] * m[2][0] * m[3][1])
				- m[1][3] * m[2][1] * m[3][0]
				- m[1][0] * m[2][3] * m[3][1]
				- m[1][1] * m[2][0] * m[3][3]);
		f -= m[0][3]
			* ((m[1][0] * m[2][1] * m[3][2] + m[1][1] * m[2][2] * m[3][0] + m[1][2] * m[2][0] * m[3][1])
				- m[1][2] * m[2][1] * m[3][0]
				- m[1][0] * m[2][2] * m[3][1]
				- m[1][1] * m[2][0] * m[3][2]);
		return f;
	}

	static float determinant3x3
	(float t00, float t01, float t02,
	 float t10, float t11, float t12,
	 float t20, float t21, float t22)
	{
		return   t00 * (t11 * t22 - t12 * t21)
			+ t01 * (t12 * t20 - t10 * t22)
			+ t02 * (t10 * t21 - t11 * t20);
	}

	static glm::mat4 invert(const glm::mat4& src, glm::mat4& dest) 
	{
		float determinant = MatrixUtils::determinant(src);

		if (determinant != 0) {
			/*
			 * m00 m01 m02 m03
			 * m10 m11 m12 m13
			 * m20 m21 m22 m23
			 * m30 m31 m32 m33
			 */
			float determinant_inv = 1.0f / determinant;

			// first row
			float t00 =  determinant3x3(src[1][1], src[1][2], src[1][3], src[2][1], src[2][2], src[2][3], src[3][1], src[3][2], src[3][3]);
			float t01 = -determinant3x3(src[1][0], src[1][2], src[1][3], src[2][0], src[2][2], src[2][3], src[3][0], src[3][2], src[3][3]);
			float t02 =  determinant3x3(src[1][0], src[1][1], src[1][3], src[2][0], src[2][1], src[2][3], src[3][0], src[3][1], src[3][3]);
			float t03 = -determinant3x3(src[1][0], src[1][1], src[1][2], src[2][0], src[2][1], src[2][2], src[3][0], src[3][1], src[3][2]);
			// second row
			float t10 = -determinant3x3(src[0][1], src[0][2], src[0][3], src[2][1], src[2][2], src[2][3], src[3][1], src[3][2], src[3][3]);
			float t11 =  determinant3x3(src[0][0], src[0][2], src[0][3], src[2][0], src[2][2], src[2][3], src[3][0], src[3][2], src[3][3]);
			float t12 = -determinant3x3(src[0][0], src[0][1], src[0][3], src[2][0], src[2][1], src[2][3], src[3][0], src[3][1], src[3][3]);
			float t13 =  determinant3x3(src[0][0], src[0][1], src[0][2], src[2][0], src[2][1], src[2][2], src[3][0], src[3][1], src[3][2]);
			// third row
			float t20 =  determinant3x3(src[0][1], src[0][2], src[0][3], src[1][1], src[1][2], src[1][3], src[3][1], src[3][2], src[3][3]);
			float t21 = -determinant3x3(src[0][0], src[0][2], src[0][3], src[1][0], src[1][2], src[1][3], src[3][0], src[3][2], src[3][3]);
			float t22 =  determinant3x3(src[0][0], src[0][1], src[0][3], src[1][0], src[1][1], src[1][3], src[3][0], src[3][1], src[3][3]);
			float t23 = -determinant3x3(src[0][0], src[0][1], src[0][2], src[1][0], src[1][1], src[1][2], src[3][0], src[3][1], src[3][2]);
			// fourth row
			float t30 = -determinant3x3(src[0][1], src[0][2], src[0][3], src[1][1], src[1][2], src[1][3], src[2][1], src[2][2], src[2][3]);
			float t31 =  determinant3x3(src[0][0], src[0][2], src[0][3], src[1][0], src[1][2], src[1][3], src[2][0], src[2][2], src[2][3]);
			float t32 = -determinant3x3(src[0][0], src[0][1], src[0][3], src[1][0], src[1][1], src[1][3], src[2][0], src[2][1], src[2][3]);
			float t33 =  determinant3x3(src[0][0], src[0][1], src[0][2], src[1][0], src[1][1], src[1][2], src[2][0], src[2][1], src[2][2]);

			// transpose and divide by the determinant
			dest[0][0] = t00 * determinant_inv;
			dest[1][1] = t11 * determinant_inv;
			dest[2][2] = t22 * determinant_inv;
			dest[3][3] = t33 * determinant_inv;
			dest[0][1] = t10 * determinant_inv;
			dest[1][0] = t01 * determinant_inv;
			dest[2][0] = t02 * determinant_inv;
			dest[0][2] = t20 * determinant_inv;
			dest[1][2] = t21 * determinant_inv;
			dest[2][1] = t12 * determinant_inv;
			dest[0][3] = t30 * determinant_inv;
			dest[3][0] = t03 * determinant_inv;
			dest[1][3] = t31 * determinant_inv;
			dest[3][1] = t13 * determinant_inv;
			dest[3][2] = t23 * determinant_inv;
			dest[2][3] = t32 * determinant_inv;
			return dest;
		}
		else
			return glm::mat4(1.0f);
	}

	static void debugPrintMatrix(const glm::mat4& matrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				std::cout << matrix[i][j] << ' ';
			}
			std::cout << std::endl;
		}
	}
};

