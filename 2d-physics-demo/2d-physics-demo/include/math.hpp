#pragma once

#include "vector2.hpp"
#include "box_shape.hpp"
#include "mat2x2.h"

namespace fs
{
	bool biasGreaterThan(float a, float b) 
	{
		const float relative = 0.95f;
		const float absolute = 0.01f;
	
		return a >= b * relative + a * absolute;
	}


	void findAxisLeastPenetration(unsigned int* faceIndex, float* distance, fs::RigidBody* aBody, fs::RigidBody* bBody)
	{
		float bestDistance	   = -FLT_MAX;
		unsigned int bestIndex = 0u;

		fs::BoxShape* aShape = dynamic_cast<fs::BoxShape*>(aBody->shape);
		fs::BoxShape* bShape = dynamic_cast<fs::BoxShape*>(bBody->shape);

		for (unsigned int i = 0u; i < BoxShape::VertexCount; i++)
		{
			fs::Vector2 normal      = aShape->normals[i];
			fs::Vector2 worldNormal = aShape->modelToWorld * normal;

			fs::Mat2x2 transpose = Mat2x2(bShape->modelToWorld[0][0], bShape->modelToWorld[1][0], bShape->modelToWorld[0][1], bShape->modelToWorld[1][1]);
		
			normal = transpose * worldNormal;

			fs::Vector2 support = bShape->getSupport(normal * -1.0f);

			fs::Vector2 vertex = aShape->vertices[i];
			vertex			   = aShape->modelToWorld * vertex + aBody->position;
			vertex			   -= bBody->position;
			vertex			   = transpose * vertex;
		
			float distance = fs::Vector2::dot(normal, (support - vertex));

			if (distance > bestDistance)
			{
				bestDistance = distance;
				bestIndex    = i;
			}
		}

		*faceIndex = bestIndex;
		*distance  = bestDistance;
	}

	void findIncidentFace(fs::Vector2* incidentFace, fs::RigidBody* a, fs::RigidBody* b, unsigned int referenceIndex)
	{
		fs::BoxShape* referencedBox = dynamic_cast<fs::BoxShape*>(a->shape);
		fs::BoxShape* incidentBox   = dynamic_cast<fs::BoxShape*>(b->shape);

		fs::Vector2 referenceNormal = referencedBox->normals[referenceIndex];

		referenceNormal = referencedBox->modelToWorld * referenceNormal;

		fs::Mat2x2 transpose = Mat2x2(incidentBox->modelToWorld[0][0], incidentBox->modelToWorld[1][0], incidentBox->modelToWorld[0][1], incidentBox->modelToWorld[1][1]);
	
		referenceNormal = transpose * referenceNormal;

		unsigned int faceIndex = 0u;
		float minDot		   = FLT_MAX;

		for (unsigned int i = 0u; i < incidentBox->VertexCount; i++)
		{
			float dot = fs::Vector2::dot(referenceNormal, incidentBox->normals[i]);

			if (dot < minDot)
			{
				minDot    = dot;
				faceIndex = i;
			}
		}

		incidentFace[0] = incidentBox->modelToWorld * incidentBox->vertices[faceIndex] + b->position;

		faceIndex = faceIndex + 1 >= incidentBox->VertexCount ? 0u : faceIndex + 1u;

		incidentFace[1] = incidentBox->modelToWorld * incidentBox->vertices[faceIndex] + b->position;
	}

	int clip(fs::Vector2 normal, float distance, fs::Vector2* face)
	{
		int faceIndex = 0;

		fs::Vector2 out[2] 
		{
			face[0], 
			face[1]
		};

		float distance1 = fs::Vector2::dot(normal, face[0]) - distance;
		float distance2 = fs::Vector2::dot(normal, face[1]) - distance;

		if (distance1 <= 0.0f) out[faceIndex++] = face[0];
		if (distance2 <= 0.0f) out[faceIndex++] = face[1];
	
		if (distance1 * distance2 < 0.0f)
		{
			float alpha = distance1 / (distance1 - distance2);

			out[faceIndex] = face[0] + alpha * (face[1] - face[0]);

			faceIndex++;
		}

		face[0] = out[0];
		face[1] = out[1];
	
		return faceIndex;
	}
}