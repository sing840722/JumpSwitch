// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "FileManager.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonSerializer.h"
#include "JsonWriter.h"
#include "JsonUtilities.h"
#include "BabyGM.generated.h"

/**
 * 
 */
UCLASS()
class BRAINSLOL_API ABabyGM : public AGameMode
{
	GENERATED_BODY()



public:
	ABabyGM();

	//Retrieve the high scores and then saves them
	UFUNCTION(BlueprintCallable, Category = "Get That Souljaboy")
	void OnStartUpRetrieve();

	void OnRetrieveResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);

	UFUNCTION(BlueprintCallable, Category = "Level = Difficulty")
		int32 ScoreToLevel(float Score);

	UFUNCTION(BlueprintCallable, Category = "Now watch me yooooouuuu")
	void UploadNewScore();
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> RankArray;
	UPROPERTY(BlueprintReadWrite)
	TArray<FString> HighScoreNameArray;
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> HighScoreScoreArray;

	UFUNCTION(BlueprintCallable, Category = "Did you Do it?")
		bool GetName(int32 score);
	UFUNCTION(BlueprintCallable, Category = "SortScore")
	void SortArray(int32 score, FString name);
	



	
	
};
