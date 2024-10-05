// Fill out your copyright notice in the Description page of Project Settings.


#include "Fountain.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BODY"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATER"));
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("LIGHT"));
	Splash = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SPLASH"));

	//StaticMeshComponent인 Body와 Water를 생성
	//AFountain의 루트컴포넌트는 바디(스테틱메시 컴포넌트)
	RootComponent = Body;

	Water->SetupAttachment(Body); //Water MeshComponent를 Body에다가 붙여줌
	Light->SetupAttachment(Body);
	Splash->SetupAttachment(Body);

	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f)); //높이를 1.35m 높여준다(물)
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f)); //빛을 1.95m
	Splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f)); //튀기는 모션을 1.95m
}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

