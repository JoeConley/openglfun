#ifndef __BRDF__
#define __BRDF__

/*
 *  BRDF.h
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/17/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "MyRGBColor.h"
#include "Vector3D.h"
#include "ShadeRec.h"
#include "Sampler.h"

class BRDF {
public:
	
	BRDF(void);
	
	BRDF(const BRDF& brdf);
	
	virtual BRDF*
	clone(void)const = 0;
	
	BRDF&
	operator= (const BRDF& rhs);
	
	virtual
	~BRDF(void);
	
	void
	set_sampler(Sampler* sPtr);
	
	virtual MyRGBColor
	f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) const = 0;
	
	virtual MyRGBColor
	sample_f(const ShadeRec& sr, const Vector3D& wi, Vector3D& wo) const = 0;
	
	virtual MyRGBColor
	rho(const ShadeRec& sr, const Vector3D& wo) const = 0;
	
protected:
	
	Sampler* sampler_ptr;
};



#endif