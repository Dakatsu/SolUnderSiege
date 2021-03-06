// Copyright Kyle Taylor Lange

#include "Lastim.h"
#include "Weap_FragGrenade.h"

AWeap_FragGrenade::AWeap_FragGrenade(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DisplayName = NSLOCTEXT("Weap_FragGrenade", "WeaponName", "Frag Grenade");

	WeaponOffset = FVector(10.f, 10.f, -10.f);
	BaseAIRating = 0.25f;
}


