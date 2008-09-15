#ifndef __WORLD__
#define __WORLD__


// This file contains the declaration of the class World
// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 


#include <vector>

#include "ViewPlane.h"
#include "MyRGBColor.h"
#include "Tracer.h"
#include "GeometricObject.h"
#include "Sphere.h"
#include "Ray.h"

#include "Camera.h"

using namespace std;

class RenderThread; 	//part of skeleton - wxRaytracer.h


class World {	
	public:
	
		ViewPlane					vp;
		MyRGBColor					background_color;
		Tracer*						tracer_ptr;
		Sphere 						sphere;		// for Chapter 3 only
		vector<GeometricObject*>	objects;		
		RenderThread* 				paintArea; 	//connection to skeleton - wxRaytracer.h
		Camera*						camera_ptr;	// the camera to use
			

	public:
	
		World(void);												
		
		~World();
								
		void 
		add_object(GeometricObject* object_ptr);
		
		void 					
		build(void);

		void 												
		render_scene(void) const;
	
		void
		set_camera(Camera* camera);
						
		MyRGBColor
		max_to_one(const MyRGBColor& c) const;
		
		MyRGBColor
		clamp_to_color(const MyRGBColor& c) const;
		
		void
		display_pixel(const int row, const int column, const MyRGBColor& pixel_color) const;

		ShadeRec									
		hit_bare_bones_objects(const Ray& ray);
						
	private:
		
		void 
		delete_objects(void);

};


// ------------------------------------------------------------------ add_object

inline void 
World::add_object(GeometricObject* object_ptr) {  
	objects.push_back(object_ptr);	
}

inline void
World::set_camera(Camera* camera) {
	camera_ptr = camera;
}

#endif
