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

	//StaticMeshComponent�� Body�� Water�� ����
	//AFountain�� ��Ʈ������Ʈ�� �ٵ�(����ƽ�޽� ������Ʈ)
	RootComponent = Body;

	Water->SetupAttachment(Body); //Water MeshComponent�� Body���ٰ� �ٿ���
	Light->SetupAttachment(Body);
	Splash->SetupAttachment(Body);

	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 135.0f)); //���̸� 1.35m �����ش�(��)
	Light->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f)); //���� 1.95m
	Splash->SetRelativeLocation(FVector(0.0f, 0.0f, 195.0f)); //Ƣ��� ����� 1.95m

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BODY(TEXT("/Game/InfinityBladeGrassLands/Environments/Plains/Env_Plains_Ruins/StaticMesh/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	if (SM_BODY.Succeeded()) 
	{
		Body->SetStaticMesh(SM_BODY.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_WATER(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Meshes/Env/SM_Plains_Fountain_02.SM_Plains_Fountain_02"));
	if (SM_WATER.Succeeded())
	{
		Water->SetStaticMesh(SM_WATER.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_SPLASH(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Ambient/Water/P_Water_Fountain_Splash_01.P_Water_Fountain_Splash_01"));
	if (PS_SPLASH.Succeeded()) 
	{
		Splash->SetTemplate(PS_SPLASH.Object);
	}
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

