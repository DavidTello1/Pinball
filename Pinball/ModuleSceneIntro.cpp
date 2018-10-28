#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	background = App->textures->Load("pinball/background.png");
	circle = App->textures->Load("pinball/ball.png"); 
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	background_rect = { 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT };

	CreateAllBouncers();
	CreateAllSensors();
	App->physics->CreateAllFlippers();

	destroyed = true;
	shown = false;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(background);
	App->textures->Unload(circle);
	bonus_fx = NULL;

	//p2List_item<SDL_Texture*>* item = App->textures->textures.getFirst();
	//
	//while (item != NULL)
	//{
	//	LOG("deleting %s", item->data);
	//	App->textures->Unload(item->data);
	//	item = item->next;
	//}
	//
	//for (item = App->textures->textures.getFirst(); item != NULL; item = item->next)
	//{
	//	LOG("deleting %s", item->data);
	//	App->textures->Unload(item->data);
	//}
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// hole
	if (Hole == true)
	{
		App->audio->PlayFx(bonus_fx);
		//velocity = 0;
		//delay
		//release

		//score += ...
		circles.getLast()->data->listener = this;
	}

	// cats
	if (cat_1 == true)
	{
		//change animation
	}
	if (cat_2 == true)
	{
		//change animation
	}
	if (cat_3 == true)
	{
		//change animation
	}
	if (cat_4 == true)
	{
		//change animation
	}
	if (cat_1 == true && cat_2 == true && cat_3 == true && cat_4 == true)
	{
		App->audio->PlayFx(bonus_fx);
		//score += ...
		cat_1 = cat_2 = cat_3 = cat_4 = false;
	}

	// layers and colliders
	if (shown == false)
	{
		if (layer2 == true)
		{
			// destroy layer1 colliders
			if (destroyed == false)
			{
				App->physics->world->DestroyBody(coll_1->body);
				App->physics->world->DestroyBody(coll_2->body);
				App->physics->world->DestroyBody(coll_3->body);
				App->physics->world->DestroyBody(coll_4->body);
				App->physics->world->DestroyBody(coll_6->body);
				App->physics->world->DestroyBody(coll_7->body);
				App->physics->world->DestroyBody(coll_8->body);
				App->physics->world->DestroyBody(coll_9->body);
				destroyed = true;
			}

			// create layer2 colliders
			coll_l2 = App->physics->CreateChain(0, 0, background_layer2, 168);
			coll_l2b = App->physics->CreateChain(0, 0, background_layer2b, 170);
		}
		else
		{
			// destroy layer2 colliders
			if (destroyed == false)
			{
				App->physics->world->DestroyBody(coll_l2->body);
				App->physics->world->DestroyBody(coll_l2b->body);
				destroyed = true;
			}

			// create layer1 colliders
			coll_1 = App->physics->CreateChain(0, 0, background1, 148);
			coll_2 = App->physics->CreateChain(0, 0, background2, 32);
			coll_3 = App->physics->CreateChain(0, 0, background3, 18);
			coll_4 = App->physics->CreateChain(0, 0, background4, 46);
			coll_6 = App->physics->CreateChain(0, 0, background6, 26);
			coll_7 = App->physics->CreateChain(0, 0, background7, 30);
			coll_8 = App->physics->CreateChain(0, 0, background8, 28);
			coll_9 = App->physics->CreateChain(0, 0, background9, 40);

		}
		shown = true;
	}

	// ball
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 13));
		circles.getLast()->data->listener = this;
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------

	App->renderer->Blit(background, background_rect.x, background_rect.y, &background_rect, 1.0f);

	p2List_item<PhysBody*>* c = circles.getFirst();
	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}


	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == layer2_sensor_left || bodyB == layer2_sensor_right)
	{ 
		if (layer2 == false)
		{
			layer2 = true;
			shown = false;
			destroyed = false;
		}
	}
	if (bodyB == layer1_sensor_left || bodyB == layer1_sensor_right)
	{
		if (layer2 == true)
		{
			layer2 = false;
			shown = false;
			destroyed = false;
		}
	}
	if (bodyB == end_sensor_left || bodyB == end_sensor_right)
	{
		if (layer2 == true)
		{
			layer2 = false;
			shown = false;
			destroyed = false;
			//score += ...
			App->audio->PlayFx(bonus_fx);
		}
	}

	if (bodyB == cat1) { cat_1 = true; 	App->audio->PlayFx(bonus_fx);}
	if (bodyB == cat2) { cat_2 = true; 	App->audio->PlayFx(bonus_fx);}
	if (bodyB == cat3) { cat_3 = true;	App->audio->PlayFx(bonus_fx);}
	if (bodyB == cat4) { cat_4 = true; 	App->audio->PlayFx(bonus_fx);}

	if (bodyB == hole) { Hole = true; 	App->audio->PlayFx(bonus_fx);}
	
}

void ModuleSceneIntro::CreateAllBouncers()
{
	bouncer1 = App->physics->CreateBouncers(290, 87);
	bouncer2 = App->physics->CreateBouncers(288, 222);
	bouncer3 = App->physics->CreateBouncers(226, 364);

	bouncers.add(bouncer1);
	bouncers.add(bouncer2);
	bouncers.add(bouncer3);
}

void ModuleSceneIntro::CreateAllSensors()
{
	layer2_sensor_left = App->physics->CreateRectangleSensor(120, 400, 52, 2, -30);
	layer1_sensor_left = App->physics->CreateRectangleSensor(130, 430, 52, 2, -30);

	layer2_sensor_right = App->physics->CreateRectangleSensor(510, 400, 52, 2, 30);
	layer1_sensor_right = App->physics->CreateRectangleSensor(500, 430, 52, 2, 30);

	end_sensor_left = App->physics->CreateRectangleSensor(80, 695, 35, 2, -10);
	end_sensor_right = App->physics->CreateRectangleSensor(485, 690, 35, 2, 10);

	sensors.add(layer2_sensor_left);
	sensors.add(layer1_sensor_left);
	sensors.add(layer2_sensor_right);
	sensors.add(layer1_sensor_right);
	sensors.add(end_sensor_left);
	sensors.add(end_sensor_right);

}

void ModuleSceneIntro::CreateAllFlippers()
{
	flipper_right = App->physics->CreateFlipper();
	flipper_left = App->physics->CreateFlipper();
}
