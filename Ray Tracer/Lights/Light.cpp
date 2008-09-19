/*
 *  Light.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/18/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Light.h"
#include "Constants.h"

Light::Light(void) {}

Light::Light(const Light& ls) {}

Light&
Light::operator= (const Light& rhs) {
	if (this == &rhs) 
		return (*this);
		
	return (*this);		// same I guess
}

Light::~Light(void) {}
	
MyRGBColor
Light::L(ShadeRec& sr) {
	return (black);			// return the radiance
}