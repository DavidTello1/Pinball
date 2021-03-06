#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "string.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void CreateAllBouncers();
	void CreateAllSensors();
	void CreateAllFlippers();
	void ResetGame();

public:

	bool gameover;
	int score;
	int highscore;
	p2SString title;

	PhysBody* ball;
	PhysBody* over;

	//bouncers
	PhysBody* bouncer1 = nullptr;
	PhysBody* bouncer2 = nullptr;
	PhysBody* bouncer3 = nullptr;
	PhysBody* bouncer4 = nullptr;
	PhysBody* bouncer5 = nullptr;

	int bouncer4_coords[22] = {
		414, 691,
		375, 758,
		376, 770,
		387, 773,
		452, 721,
		460, 711,
		461, 693,
		463, 634,
		457, 629,
		449, 628,
		421, 679
	};

	int bouncer5_coords[22] = {
		101, 627,
		108, 629,
		179, 760,
		180, 769,
		173, 773,
		163, 769,
		100, 719,
		94, 708,
		94, 696,
		94, 639,
		94, 630 
	};

	//sensors
	PhysBody* layer2_sensor_left;
	PhysBody* layer2_sensor_right;
	PhysBody* layer1_sensor_left;
	PhysBody* layer1_sensor_right;
	PhysBody* end_sensor_left;
	PhysBody* end_sensor_right;
	PhysBody* cat1;
	PhysBody* cat2;
	PhysBody* cat3;
	PhysBody* cat4;
	PhysBody* hole;

	//flippers
	b2RevoluteJoint* flipper_right;
	b2RevoluteJoint* flipper_left;

	//spring
	PhysBody* spring;

	PhysBody* coll_1 = nullptr;
	PhysBody* coll_2 = nullptr;
	PhysBody* coll_4 = nullptr;
	PhysBody* coll_7 = nullptr;
	PhysBody* coll_8 = nullptr;
	PhysBody* coll_9 = nullptr;
	PhysBody* coll_l2 = nullptr;
	PhysBody* coll_l2b = nullptr;

	SDL_Texture* background;
	SDL_Texture* circle;
	SDL_Texture* muelle;
	uint bonus_fx;

	SDL_Rect background_rect;
	bool layer2;
	bool shown;
	bool destroyed;
	bool cat_1, cat_2, cat_3, cat_4;
	bool Hole;

	// colliders
	int background1[178] = {
		587, 938,
		587, 259,
		580, 215,
		562, 164,
		540, 127,
		502, 88,
		468, 61,
		406, 34,
		361, 20,
		299, 17,
		244, 25,
		201, 43,
		149, 78,
		120, 115,
		101, 162,
		95, 198,
		100, 241,
		113, 289,
		127, 326,
		143, 365,
		160, 404,
		152, 411,
		126, 360,
		105, 309,
		89, 262,
		49, 277,
		64, 320,
		78, 357,
		93, 392,
		114, 439,
		85, 457,
		74, 407,
		71, 370,
		69, 349,
		57, 339,
		42, 336,
		26, 343,
		18, 363,
		17, 388,
		22, 428,
		34, 477,
		47, 509,
		64, 541,
		12, 614,
		12, 756,
		14, 771,
		27, 782,
		161, 888,
		189, 907,
		224, 918,
		264, 923,
		294, 924,
		341, 916,
		374, 902,
		395, 891,
		533, 778,
		542, 766,
		545, 752,
		545, 612,
		491, 539,
		522, 453,
		516, 450,
		529, 405,
		533, 375,
		535, 337,
		535, 310,
		493, 307,
		491, 342,
		491, 363,
		486, 399,
		477, 424,
		367, 361,
		391, 348,
		424, 323,
		444, 293,
		463, 265,
		474, 226,
		481, 188,
		481, 148,
		475, 122,
		479, 114,
		492, 124,
		512, 147,
		529, 174,
		540, 197,
		549, 219,
		555, 248,
		557, 265,
		557, 938
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

};
