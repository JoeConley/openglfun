/*
 *  Matte.cpp
 *  Ray Tracer
 *
 *  Created by NoEvilPeople on 9/19/08.
 *  Copyright 2008 jmc2385@rit.edu. All rights reserved.
 *
 */

#include "Matte.h"
#include "World.h"

Matte::Matte(void)
:	Material(),
	ambient_ptr(new Lambertian),
	diffuse_ptr(new Lambertian)
{}
 
Matte::Matte(const Matte& m) 
:	Material(m) {
	if (m.ambient_ptr)
		ambient_ptr = (Lambertian*)m.ambient_ptr->clone();
	else
		ambient_ptr = NULL;
	
	if (m.diffuse_ptr)
		diffuse_ptr = (Lambertian*)m.diffuse_ptr->clone();
	else
		ambient_ptr = NULL;
}

Matte::~Matte(void) {
	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
	if (diffuse_ptr) {
		delete diffuse_ptr;
		diffuse_ptr = NULL;
	}
}

Matte& 
Matte::operator= (const Matte& m) {
	if (this == &m)
		return (*this);
	
	Material::operator= (m);
	
	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
	if (diffuse_ptr) {
		delete diffuse_ptr;
		diffuse_ptr = NULL;
	}
	
	if (m.ambient_ptr)
		ambient_ptr = (Lambertian*)m.ambient_ptr->clone();
	
	
	if (m.diffuse_ptr)
		diffuse_ptr = (Lambertian*)m.diffuse_ptr->clone();
	
	return (*this);
}

Material*
Matte::clone(void) const {
	return (new Matte(*this));
}

void
Matte::set_sampler(Sampler* sampl_ptr) {
	
	ambient_ptr->set_sampler(sampl_ptr);
	diffuse_ptr->set_sampler(sampl_ptr->clone());
}

void
Matte::set_ka(const float ka) {
	ambient_ptr->set_kd(ka);
}

void
Matte::set_kd(const float kd) {
	diffuse_ptr->set_kd(kd);
}

void
Matte::set_cd(const MyRGBColor& c) {
	ambient_ptr->set_cd(c);
	diffuse_ptr->set_cd(c);
}

void
Matte::set_cd(const float r, const float g, const float b) {
	ambient_ptr->set_cd(MyRGBColor(r,g,b));
	diffuse_ptr->set_cd(MyRGBColor(r,g,b));
}

MyRGBColor
Matte::shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	MyRGBColor L = ambient_ptr->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int numLights = sr.w.lights.size();
	
	for(int j = 0; j < numLights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;
		
		if (ndotwi > 0.0)	{
			bool in_shadow = false;
			if (sr.w.lights[j]->casts_shadows()) {
				Ray shadow_ray(sr.hit_point, wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
			}
			
			if (!in_shadow)
				L+=diffuse_ptr->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
		}
	}
	
	return (L);
}

MyRGBColor
Matte::area_light_shade(ShadeRec& sr) {
	Vector3D wo = -sr.ray.d;
	MyRGBColor L = ambient_ptr->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int num_lights = sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi;
		
		if (ndotwi > 0.0) {
			bool in_shadow = false;
			
			if (!shadows)
				;
			else {		
				in_shadow = false;
				if (sr.w.lights[j]->casts_shadows()) {
					Ray shadow_ray(sr.hit_point, wi);
					in_shadow = sr.w.lights[j]->in_shadow(shadow_ray, sr);
				}
			}
			
			if (!in_shadow)
				L += diffuse_ptr->f(sr, wo, wi) * sr.w.lights[j]->L(sr) *
					sr.w.lights[j]->G(sr) * ndotwi /
				sr.w.lights[j]->pdf(sr);
		}
	}
	return (L);
}

MyRGBColor
Matte::path_shade(ShadeRec& sr) {
	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	MyRGBColor f = diffuse_ptr->sample_f(sr, wi, wo, pdf);
	float ndotwi = sr.normal * wi;
	Ray reflected_ray(sr.hit_point, wi);
	
	return (f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf);
}

MyRGBColor
Matte::global_shade(ShadeRec& sr) {
	MyRGBColor L;
	
	if (sr.depth == 0)
		L = area_light_shade(sr);
	
	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	MyRGBColor f = diffuse_ptr->sample_f(sr, wi, wo, pdf);
	float ndotwi = sr.normal * wi;
	Ray reflected_ray(sr.hit_point, wi);
	L += f * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi / pdf;
	
	return (L);
}
