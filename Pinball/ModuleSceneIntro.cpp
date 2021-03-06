#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleWindow.h"
#include "string.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = background = muelle = NULL;
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
	muelle = App->textures->Load("pinball/muelle.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	background_rect = { 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT };

	CreateAllBouncers();
	CreateAllSensors();
	CreateAllFlippers();
	ball = App->physics->CreateCircle(572, 730, 13, b2_dynamicBody, 0.0f, 1.0f);
	spring = App->physics->CreateRectangle(575, 854, 28, 166, b2_dynamicBody, 1.0f, 0.0f);
	over = App->physics->CreateRectangleSensor(270, 920, 200, 20);
	
	destroyed = true;
	shown = false;
	Hole = false;
	cat_1 = cat_2 = cat_3 = cat_4 = false;
	highscore = 0;
	gameover = false;
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(background);
	App->textures->Unload(circle);
	App->textures->Unload(muelle);
	bonus_fx = NULL;

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{

	p2SString title(" -- The Rambling Wheels -- SCORE: %d -- HIGHSCORE: %d --", score, highscore);
	App->window->SetTitle(title.GetString());

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flipper_left->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipper_right->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		flipper_left->EnableMotor(false);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		flipper_right->EnableMotor(false);
	}

	// hole
	if (Hole == true)
	{
		App->audio->PlayFx(bonus_fx);
		//velocity = 0;
		//delay
		//release

		score += 10000;
	}

	if (cat_1 == true && cat_2 == true && cat_3 == true && cat_4 == true)
	{
		App->audio->PlayFx(bonus_fx);
		score += 5000;
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
				App->physics->world->DestroyBody(coll_4->body);
				App->physics->world->DestroyBody(coll_7->body);
				App->physics->world->DestroyBody(coll_8->body);
				App->physics->world->DestroyBody(coll_9->body);

				App->physics->world->DestroyBody(bouncer3->body);

				destroyed = true;
			}

			// create layer2 colliders
			coll_l2 = App->physics->CreateChain(0, 0, background_layer2, 168, 0.0, 1.0);
			coll_l2b = App->physics->CreateChain(0, 0, background_layer2b, 170, 0.0, 1.0);
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
			coll_1 = App->physics->CreateChain(0, 0, background1, 178, 0.0, 1.0);
			coll_4 = App->physics->CreateChain(0, 0, background4, 46, 0.0, 1.0);
			coll_7 = App->physics->CreateChain(0, 0, background7, 30, 0.0, 1.0);
			coll_8 = App->physics->CreateChain(0, 0, background8, 28, 0.0, 1.0);
			coll_9 = App->physics->CreateChain(0, 0, background9, 40, 0.0, 1.0);

			bouncer3 = App->physics->CreateCircleBouncers(227, 365);

		}
		shown = true;
	}

	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------

	App->renderer->Blit(background, background_rect.x, background_rect.y, &background_rect, 1.0f);

	// ball
	int x, y;
	ball->GetPosition(x, y);
	App->renderer->Blit(circle, x, y, NULL, 1.0f, ball->GetRotation());

	// spring
	b2Vec2 vec = { 0,1.0 };
	b2Vec2 point = { 589,937 };
	bool wake = true;

	spring->GetPosition(x, y);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		y -= 20;
		spring->body->ApplyLinearImpulse(vec, point, wake);
	}
	App->renderer->Blit(muelle, x, y, NULL, 1.0f);

	if (gameover == true)
	{
		ResetGame();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == over)
	{
		gameover = true;
	}
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

			App->audio->PlayFx(bonus_fx);
		}
	}

	if (bodyB == cat1) { cat_1 = true; 	App->audio->PlayFx(bonus_fx); }
	if (bodyB == cat2) { cat_2 = true; 	App->audio->PlayFx(bonus_fx); }
	if (bodyB == cat3) { cat_3 = true;	App->audio->PlayFx(bonus_fx); }
	if (bodyB == cat4) { cat_4 = true; 	App->audio->PlayFx(bonus_fx); }

	if (bodyB == hole)
	{
		Hole = true;
		App->audio->PlayFx(bonus_fx);
	}

	if (bodyB == bouncer1)
	{
		score += 3000;
		App->audio->PlayFx(bonus_fx);
	}
	if (bodyB == bouncer2)
	{
		score += 2000;
		App->audio->PlayFx(bonus_fx);
	}
	if (bodyB == bouncer3)
	{
		if (layer2 == false)
		{
			score += 1000;
			App->audio->PlayFx(bonus_fx);
		}
	}
}

void ModuleSceneIntro::CreateAllBouncers()
{
	bouncer1 = App->physics->CreateCircleBouncers(291, 88);
	bouncer2 = App->physics->CreateCircleBouncers(289, 223);
	bouncer3 = App->physics->CreateCircleBouncers(227, 365);

	bouncer4 = App->physics->CreateChain(0, 0, bouncer4_coords, 22, 0.8f, 1.0f);
	bouncer5 = App->physics->CreateChain(0, 0, bouncer5_coords, 22, 0.8f, 1.0f);
}

void ModuleSceneIntro::CreateAllSensors()
{
	layer2_sensor_left = App->physics->CreateRectangleSensor(120, 400, 52, 2, -30);
	layer1_sensor_left = App->physics->CreateRectangleSensor(130, 430, 52, 2, -30);

	layer2_sensor_right = App->physics->CreateRectangleSensor(510, 400, 52, 2, 30);
	layer1_sensor_right = App->physics->CreateRectangleSensor(500, 430, 52, 2, 30);

	end_sensor_left = App->physics->CreateRectangleSensor(80, 695, 35, 2, -10);
	end_sensor_right = App->physics->CreateRectangleSensor(485, 690, 35, 2, 10);

	cat_1 = App->physics->CreateRectangleSensor(376, 377, 23, 5, 30);
	cat_2 = App->physics->CreateRectangleSensor(401, 390, 23, 5, 30);
	cat_3 = App->physics->CreateRectangleSensor(428, 405, 23, 5, 30);
	cat_4 = App->physics->CreateRectangleSensor(454, 419, 23, 5, 30);

	Hole = App->physics->CreateCircleSensor(45, 364, 24);
}

void ModuleSceneIntro::CreateAllFlippers()
{
	flipper_right = App->physics->CreateFlipper(374, 832, right);
	flipper_left = App->physics->CreateFlipper(180, 832, left);
}

void ModuleSceneIntro::ResetGame()
{
	if (score > highscore || highscore == 0)
	{
		highscore = score;
	}

	score = 0;
	ball = App->physics->CreateCircle(572, 730, 13, b2_dynamicBody, 0.0f, 1.0f);
}
