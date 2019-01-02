
#include "RayTracer.h"
#include <iostream>

// Returns the maximum of two values
double max(double a, double b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

void RayTracer::setDepth(int newDepth) {
	if (newDepth > 0) {
		depth = newDepth;
	}
}

// Generic constructor that does nothing
RayTracer::RayTracer() {
	depth = 3;
}

RGBApixel RayTracer::shade(Ray &ray, Objects** obj, Light** light, int size, int numLights, bool toon) {

	RGBApercentage color = shadeHelper(ray, obj, light, size, numLights, 1, toon);
	// Set the correct color based off of the percentages

	RGBApixel returnCol;
	returnCol.r = color.r * 255.0;
	returnCol.g = color.g * 255.0;
	returnCol.b = color.b * 255.0;

	return returnCol;
}

// Determines the pixel color that a ray should be intersecting with the list of object. Will be grey if no
// intersection found.
RGBApercentage RayTracer::shadeHelper(Ray &ray, Objects** obj, Light** light, int size, int numLights, int recursionLevel, bool toon) {
	hitI = getFirstHit(ray, obj, size);

	RGBApercentage color = { 0.0, 0.0, 0.0, 1 };
	RGBApercentage newColor = { 0.0, 0.0, 0.0, 1 };

	Point hitPoint = ray.start + ray.dir * hitI.hit;
	Vector s, H, normal, dir;
	double lambert, phong, angle, attenuation, dist, intensity;

	// If no hit, then set it to grey
	if (hitI.numHits == 0) {
		newColor = { .2, .2, .2, 1 };

		for (int i = 0; i < numLights; ++i) {
			// Only need to check global ambient light if no hit found
			if (light[i]->type == GLOBAL) {
				newColor.r *= light[i]->ambient.r;
				newColor.g *= light[i]->ambient.g;
				newColor.b *= light[i]->ambient.b;
			}
		}
	}
	else {
		// Iterate through every light and calculate the light information for each pixel
		for (int i = 0; i < numLights; ++i) {
			color = { 0.0, 0.0, 0.0, 1 };

			normal = hitPoint - Point(obj[hitI.index]->x, obj[hitI.index]->y, obj[hitI.index]->z);
			normal.normalize();

			// Find the direction
			if (light[i]->type == DIRECTIONAL) {
				s = light[i]->direction;
			}
			else {
				s = light[i]->position - hitPoint;
			}
			s.normalize();

			intensity = s.dot(normal);

			dir = ray.dir * -1;
			dir.normalize();

			H = s + dir;
			H.normalize();

			// Used in attenuation to find the distance
			Vector distance = hitPoint - Point(obj[hitI.index]->x, obj[hitI.index]->y, obj[hitI.index]->z);
			dist = distance.magnitude();

			// If it is a spotlight, we need to check the angle to see if it is outside the cutoff
			if (light[i]->type == SPOTLIGHT) {
				dir = light[i]->direction;
				dir.normalize();

				// Find the angle between the direction of light and the vector from the hitpoint to light position
				// Subtract 180 because acos gives an angle larger than 90;
				angle = 180 - acos(dir.dot(s))* 180.0 / pi;
				if (angle < 0) {
					angle *-1;
				}
				if (angle > light[i]->angle) {
					angle = 0;
				}
				else {
					angle = angle * pi / 180;
				}
			}

			lambert = max(s.dot(normal), 0);
			phong = max(pow(H.dot(normal), obj[hitI.index]->shinyness), 0);

			// Spotlight
			if (light[i]->type == SPOTLIGHT) {
				if (angle > 0.0) {
					attenuation = 1;
					// Abmient Light
					color.r += obj[hitI.index]->ambient.r * light[i]->ambient.r * pow(cos(angle), light[i]->exponent);
					color.g += obj[hitI.index]->ambient.g * light[i]->ambient.g * pow(cos(angle), light[i]->exponent);
					color.b += obj[hitI.index]->ambient.b * light[i]->ambient.b * pow(cos(angle), light[i]->exponent);

					// Diffuse Light
					color.r += obj[hitI.index]->diffuse.r * light[i]->diffuse.r * lambert * pow(cos(angle), light[i]->exponent);
					color.g += obj[hitI.index]->diffuse.g * light[i]->diffuse.g * lambert * pow(cos(angle), light[i]->exponent);
					color.b += obj[hitI.index]->diffuse.b * light[i]->diffuse.b * lambert * pow(cos(angle), light[i]->exponent);

					// Specular Light
					if (!toon) {
						color.r += obj[hitI.index]->specular.r * light[i]->specular.r * phong * pow(cos(angle), light[i]->exponent) * attenuation;
						color.g += obj[hitI.index]->specular.g * light[i]->specular.g * phong * pow(cos(angle), light[i]->exponent) * attenuation;
						color.b += obj[hitI.index]->specular.b * light[i]->specular.b * phong * pow(cos(angle), light[i]->exponent) * attenuation;
					}
					else if (phong > .9 && light[i]->specular.r > 0 && light[i]->specular.g > 0 && light[i]->specular.b > 0 && obj[hitI.index]->specular.r > 0 && obj[hitI.index]->specular.g > 0 && obj[hitI.index]->specular.b > 0) {
						color.r = 1;
						color.g = 1;
						color.b = 1;
					}
				}
			}
			else {
				// Ambient Light
				color.r += obj[hitI.index]->ambient.r * light[i]->ambient.r;
				color.g += obj[hitI.index]->ambient.g * light[i]->ambient.g;
				color.b += obj[hitI.index]->ambient.b * light[i]->ambient.b;

				// Diffuse Light
				color.r += obj[hitI.index]->diffuse.r * light[i]->diffuse.r * lambert;
				color.g += obj[hitI.index]->diffuse.g * light[i]->diffuse.g * lambert;
				color.b += obj[hitI.index]->diffuse.b * light[i]->diffuse.b * lambert;

				// Specular Light
				if (!toon) {
					color.r += obj[hitI.index]->specular.r * light[i]->specular.r * phong;
					color.g += obj[hitI.index]->specular.g * light[i]->specular.g * phong;
					color.b += obj[hitI.index]->specular.b * light[i]->specular.b * phong;
				}
				else if (phong > .9 && light[i]->specular.r > 0 && light[i]->specular.g > 0 && light[i]->specular.b > 0 && obj[hitI.index]->specular.r > 0 && obj[hitI.index]->specular.g > 0 && obj[hitI.index]->specular.b > 0) {
					color.r = 1;
					color.g = 1;
					color.b = 1;
				}
			}

			// Discretize the color if we are using the toon shading model
			if (toon) {
				// Only discretize the light that isn't global
				if (light[i]->type != GLOBAL) {
					if (intensity > .95) {
						color.r = color.r * .95;
						color.g = color.g * .95;
						color.b = color.b * .95;
					}
					else if (intensity > .7) {
						color.r = color.r * .75;
						color.g = color.g * .75;
						color.b = color.b * .75;
					}
					else if (intensity > .4) {
						color.r = color.r * .4;
						color.g = color.g * .4;
						color.b = color.b * .4;
					}
					else if (intensity > .2) {
						color.r = color.r * .25;
						color.g = color.g * .25;
						color.b = color.b * .25;
					}
					else {
						color.r = color.r * .1;
						color.g = color.g * .1;
						color.b = color.b * .1;
					}
				}
			}

			newColor.r += color.r;
			newColor.g += color.g;
			newColor.b += color.b;
		}

		// Use recursion and see if we need to call the function again
		if (recursionLevel < depth) {
			recursionLevel++;
			RGBApercentage tempColor;

			// Computer the new start point, which is just the hit
			Ray newRay;
			newRay.setStart(hitPoint);

			// Compute the new direction vector
			Vector temp = normal * (2 * ((ray.dir).dot(normal)));
			Vector temp2 = ray.dir - temp;
			temp2.normalize();
			newRay.setDirection(temp2);

			// Get the color from the shade function and then add it to our color
			// Multiply by the shinyness of the object (I set to .7).
			tempColor = shadeHelper(newRay, obj, light, size, numLights, recursionLevel, toon);

			newColor.r += tempColor.r * .7;
			newColor.g += tempColor.g * .7;
			newColor.b += tempColor.b * .7;
		}

		// Check if any colors are greater than one, and if they are just set them to 1
		// Since they cannot be greater than 1
		if (newColor.r > 1) {
			newColor.r = 1;
		}
		if (newColor.g > 1) {
			newColor.g = 1;
		}
		if (newColor.b > 1) {
			newColor.b = 1;
		}
	}

	return newColor;
}

// Helper function that retrns the time of the first hit with a list of objects
hitInfo RayTracer::getFirstHit(Ray &ray, Objects** obj, int size) {
	hitI = { 0, DBL_MAX, 0 };
	
	// Iterate through all of the objects to find intersections with the ray
	for (int i = 0; i < size; ++i) {
		hit = obj[i]->hit(ray);
		if (hit > 0) {
			if (hit < hitI.hit) {
				hitI.hit = hit;
				hitI.index = i;
			}
			hitI.numHits++;
		}
	}

	return hitI;
}