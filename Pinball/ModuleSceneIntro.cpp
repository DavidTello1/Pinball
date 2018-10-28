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
	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	background_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	int background[148] = {
		585, 778,
		585, 303,
		585, 265,
		580, 220,
		572, 195,
		561, 167,
		548, 142,
		534, 123,
		514, 101,
		489, 80,
		456, 57,
		433, 44,
		408, 36,
		370, 24,
		338, 20,
		315, 20,
		291, 20,
		270, 21,
		249, 27,
		223, 35,
		201, 43,
		181, 26,
		148, 18,
		99, 18,
		69, 27,
		27, 68,
		20, 109,
		15, 162,
		49, 301,
		65, 344,
		55, 338,
		41, 335,
		27, 342,
		17, 355,
		16, 383,
		18, 407,
		24, 443,
		31, 468,
		42, 496,
		53, 520,
		66, 543,
		11, 614,
		11, 762,
		14, 771,
		23, 782,
		150, 881,
		182, 902,
		212, 913,
		212, 935,
		348, 935,
		344, 915,
		381, 900,
		534, 778,
		545, 761,
		545, 613,
		490, 541,
		521, 459,
		532, 428,
		538, 383,
		540, 268,
		528, 204,
		508, 153,
		474, 124,
		486, 118,
		501, 135,
		527, 170,
		544, 207,
		556, 249,
		557, 262,
		558, 775,
		557, 794,
		557, 934,
		586, 935,
		586, 788
	};

	int background2[32] = {
		154, 411,
		161, 409,
		111, 282,
		102, 247,
		97, 223,
		96, 181,
		101, 161,
		110, 138,
		121, 114,
		138, 92,
		153, 74,
		101, 74,
		72, 132,
		89, 240,
		127, 353,
		150, 407
	};

	int background3[18] = {
		66, 332,
		108, 442,
		85, 457,
		78, 434,
		73, 401,
		71, 380,
		71, 357,
		65, 344,
		53, 334
	};

	int background4[46] = {
		405, 88,
		412, 101,
		415, 116,
		418, 146,
		418, 181,
		414, 206,
		406, 227,
		391, 256,
		378, 285,
		365, 308,
		347, 329,
		367, 318,
		384, 305,
		403, 286,
		419, 265,
		430, 243,
		438, 223,
		444, 199,
		446, 178,
		448, 152,
		441, 123,
		433, 106,
		421, 93
	};

	int background6[26] = {
		369, 362,
		474, 422,
		486, 347,
		538, 362,
		527, 193,
		478, 123,
		476, 220,
		469, 250,
		459, 272,
		441, 299,
		425, 320,
		400, 342,
		386, 351
	};

	int background7[30] = {
		54, 691,
		52, 741,
		54, 749,
		58, 756,
		64, 761,
		153, 831,
		160, 835,
		168, 835,
		174, 830,
		173, 822,
		168, 815,
		73, 738,
		66, 729,
		62, 721,
		56, 696
	};

	int background8[28] = {
		504, 688,
		504, 744,
		503, 751,
		497, 757,
		490, 765,
		403, 833,
		396, 834,
		386, 830,
		385, 820,
		391, 813,
		484, 740,
		491, 728,
		497, 716,
		501, 697
	};

	int background9[40] = {
		173, 107,
		161, 123,
		150, 141,
		140, 169,
		135, 190,
		134, 210,
		137, 233,
		142, 256,
		148, 276,
		160, 310,
		188, 379,
		238, 327,
		219, 290,
		200, 243,
		190, 204,
		188, 174,
		191, 142,
		203, 101,
		220, 70,
		178, 101
	};
	
	int background_layer2[168] = {
		517, 445,
		525, 428,
		527, 405,
		533, 368,
		535, 329,
		535, 295,
		534, 257,
		529, 229,
		521, 194,
		508, 165,
		491, 142,
		477, 131,
		454, 122,
		437, 120,
		414, 124,
		396, 134,
		379, 150,
		368, 168,
		361, 192,
		360, 208,
		360, 253,
		357, 381,
		360, 409,
		367, 437,
		379, 463,
		391, 486,
		407, 510,
		426, 533,
		441, 553,
		452, 575,
		460, 603,
		465, 624,
		465, 648,
		464, 662,
		465, 672,
		458, 674,
		445, 585,
		411, 546,
		367, 476,
		347, 417,
		340, 339,
		340, 170,
		390, 109,
		469, 93,
		510, 113,
		547, 187,
		567, 428,
		560, 544,
		531, 620,
		502, 682,
		502, 644,
		500, 610,
		491, 576,
		477, 541,
		459, 516,
		440, 491,
		419, 461,
		408, 440,
		400, 419,
		395, 393,
		394, 365,
		396, 337,
		395, 311,
		397, 285,
		398, 254,
		403, 211,
		406, 194,
		412, 178,
		422, 168,
		436, 163,
		448, 165,
		460, 171,
		468, 185,
		478, 210,
		483, 225,
		487, 250,
		490, 275,
		490, 304,
		491, 324,
		490, 363,
		487, 387,
		478, 425,
		469, 434,
		515, 459
	};

	int background_layer2b[170] = {
		114, 441,
		100, 406,
		70, 334,
		53, 286,
		36, 233,
		28, 194,
		23, 163,
		22, 126,
		26, 91,
		39, 63,
		60, 40,
		85, 26,
		116, 22,
		150, 23,
		166, 29,
		185, 37,
		206, 53,
		218, 74,
		226, 106,
		225, 130,
		222, 143,
		218, 166,
		213, 202,
		207, 223,
		203, 248,
		204, 276,
		214, 298,
		220, 318,
		226, 344,
		229, 364,
		230, 391,
		230, 414,
		224, 439,
		214, 458,
		203, 476,
		182, 500,
		158, 522,
		140, 536,
		119, 558,
		100, 583,
		91, 599,
		89, 615,
		90, 633,
		91, 663,
		91, 678,
		92, 690,
		292, 381,
		219, 16,
		8, 5,
		26, 696,
		56, 690,
		53, 660,
		53, 607,
		63, 571,
		87, 534,
		120, 507,
		155, 475,
		189, 432,
		193, 397,
		193, 359,
		184, 322,
		166, 272,
		167, 237,
		176, 192,
		182, 156,
		179, 140,
		180, 107,
		172, 84,
		154, 68,
		135, 66,
		109, 66,
		88, 72,
		75, 87,
		68, 106,
		65, 133,
		67, 162,
		75, 212,
		84, 245,
		99, 288,
		112, 325,
		124, 353,
		133, 380,
		144, 405,
		153, 419,
		117, 450
	};
	
	App->physics->CreateChain(0, 0, background, 148);
	App->physics->CreateChain(0, 0, background2, 32);
	App->physics->CreateChain(0, 0, background3, 18);
	App->physics->CreateChain(0, 0, background4, 46);
	App->physics->CreateChain(0, 0, background6, 26);
	App->physics->CreateChain(0, 0, background7, 30);
	App->physics->CreateChain(0, 0, background8, 28);
	App->physics->CreateChain(0, 0, background9, 40);
	

	App->physics->CreateChain(0, 0, background_layer2, 168);
	App->physics->CreateChain(0, 0, background_layer2b, 170);



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(background);
	App->textures->Unload(circle);
	App->textures->Unload(box);
	App->textures->Unload(rick);
	bonus_fx = NULL;

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 40, b2_dynamicBody, 0.0f, 1.0f));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50, b2_dynamicBody, 0.0f));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	App->renderer->Blit(background, background_rect.x, background_rect.y, &background_rect, 1.0f);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	App->audio->PlayFx(bonus_fx);
}
