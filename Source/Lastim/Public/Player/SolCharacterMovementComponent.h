// Copyright Kyle Taylor Lange

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "SolCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class LASTIM_API USolCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
	USolCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	virtual float GetMaxSpeed() const override;

	virtual bool DoJump(bool bReplayingMoves) override;

	virtual float CalculateJumpVelocity() const;

	/** Maximum speed when activating sprint. **/
	UPROPERTY(EditAnywhere)
	float MaxSprintSpeed;

	/** Maximum speed when aiming. Also used for slow walking. **/
	UPROPERTY(EditAnywhere)
	float MaxAimingSpeed;
	
};