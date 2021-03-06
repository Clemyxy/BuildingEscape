// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	
	//Port�e du Line Trace du Grabber
	UPROPERTY(EditAnywhere)
		float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	//Raycast grab
	void Grab();

	//Called when grab is released
	void Release();
	
	//Find attached physics handle
	void FindPhysicsHandleComponent();

	//Setup Attached input component
	void SetupInputComponent();

	//Return hit for first physics body in reach
	FHitResult GetFirstPhysicsBodyInReach() const;
	
	//Return the raycast start and end
	FTwoVectors GetLineTracePoints() const;
};
