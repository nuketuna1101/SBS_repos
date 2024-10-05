// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS() //언리얼에서는 효율적인 객체관리를 위해 생 C++과 다른 
class ARENABATTLE_API AFountain : public AActor //상속 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//포인터를 직접적으로 사용할 경우 에러나 버그소지가 많아
	//언리얼 시스템 자체에서 포인터를 관리 할 수있게
    //만든 매크로
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;  //분수의 몸통

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Water; //분수의 물이 흐르는 

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* Light;  //분수의 빛

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* Splash; //분수의 물튀기는 파티클

	UPROPERTY(EditAnywhere, Category = ID)
	int32 ID;
};
