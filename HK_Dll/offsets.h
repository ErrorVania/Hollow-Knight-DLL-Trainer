#pragma once


#pragma once
//contains pointer to version value
#define HK_VERSION_POINTER 0x8

#define HEALTH_OFFSET 0xE4
#define MAX_HEALTH_OFFSET 0xE8
#define SOUL_OFFSET 0x120
#define GEO_OFFSET 0x118
#define USED_NOTCHES 0x420
#define MAX_NOTCHES 0x41c



#define NAILDAMAGE_OFFSET_UNUSED 0x1a0
/*
I gotta explain this one.
This address contains the "default" value for the nail damage,
but is never affected by other things except when upgrading your nail.
Changing the Value and THEN equipping and unequipping a strength increasing charm will set the actual nail damage to this offsets value.
Made sense? No? I agree.*/


#define ESSENCE_OFFSET 0x1c8

#define RANDIC_EGGS_OFFSET 0x230

#define IS_RESTING 0x144
#define COMPLETION 0xc58 //there are 2 completion offsets. this is the real one
#define OVERCHARMED 0x42D
#define OWNED_CHARMS 0x428

//debug cheats?
#define invinciTest 0xb49
#define infiniteAirJump 0xb48

#define SALUBRAS_BLESSING 0x363
#define BEAM_DAMAGE 0x1a8 //Grubberfly's Charm damage

#pragma region map
#define mapDirtmouth 0xB67
#define mapCrossroads mapDirtmouth+1
#define mapGreenpath mapCrossroads+1
#define mapFogCanyon mapGreenpath+1
#define mapRoyalGardens mapFogCanyon+1
#define mapFungalWastes mapRoyalGardens+1
#define mapCity mapFungalWastes+1
#define mapWaterways mapCity+1
#define mapMines mapWaterways+1
#define mapDeepnest mapMines+1
#define mapCliffs mapDeepnest+1
#define mapOutskirts mapCliffs+1
#define mapRestingGrounds mapOutskirts+1
#define mapAbyss mapRestingGrounds+1
#pragma endregion