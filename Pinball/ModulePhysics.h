#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -10.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)
enum Side { right, left };
// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	void GetPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius, b2BodyType type, float restitution, float density);
	PhysBody* CreateCircleSensor(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height, b2BodyType type, float density, float angle);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, int angle = 0);
	PhysBody* CreateChain(int x, int y, int* points, int size, float restitution, float density);

	PhysBody* CreateCircleBouncers(int x, int y);

	void CreateRevJointDef(b2RevoluteJointDef* def, PhysBody* A, PhysBody* B);
	b2RevoluteJoint* CreateFlipper(int x, int y, Side side);

	void CreateDistJointDef(b2DistanceJointDef* def, PhysBody* A, PhysBody* B);
	b2DistanceJoint* CreateSpring(int x, int y, int length); //need to be reviewed


	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	b2World* world;

private:

	bool debug;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
	b2Body* is_selected = nullptr;
};