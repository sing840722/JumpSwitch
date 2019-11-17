// Fill out your copyright notice in the Description page of Project Settings.

#include "Brainslol.h"
#include "Engine.h"
#include "BabyGM.h"

ABabyGM::ABabyGM()
{
	RankArray.Add("Rank0");
	RankArray.Add("Rank1");
	RankArray.Add("Rank2");
}


void ABabyGM::OnStartUpRetrieve()
{
	TSharedRef<IHttpRequest> GetScores = FHttpModule::Get().CreateRequest();
	GetScores->SetURL("https://amber-heat-4334.firebaseio.com/BrainsEden/Highscores/.json?print=pretty");
	GetScores->SetVerb("GET");
	GetScores->SetHeader("Content-Type", "Application/json");
	GetScores->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	GetScores->ProcessRequest();
	GetScores->OnProcessRequestComplete().BindUObject(this, &ABabyGM::OnRetrieveResponse);
}

void ABabyGM::OnRetrieveResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success)
{

	if (Success == true)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Black, TEXT("Hello"));
		TSharedPtr<FJsonObject> HUploadObject;

		TSharedRef<TJsonReader<>> Read = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		HighScoreNameArray.Empty();
		HighScoreScoreArray.Empty();
		if (FJsonSerializer::Deserialize(Read, HUploadObject))
		{
			for (FString Rank : RankArray)
			{
				HighScoreNameArray.Add(HUploadObject->GetObjectField(Rank)->GetStringField(TEXT("Hname")));
				HighScoreScoreArray.Add(HUploadObject->GetObjectField(Rank)->GetIntegerField(TEXT("Hscore")));
				
				GEngine->AddOnScreenDebugMessage(1, 5.0, FColor::Black, HUploadObject->GetObjectField(Rank)->GetStringField(TEXT("Hname")));
			}

		}
	}
}

void ABabyGM::UploadNewScore()
{
	FString HString;
	TSharedPtr<FJsonObject> HMainObject = MakeShareable(new FJsonObject);
	
	for (int32 i = 0; i < 3; i++)
	{
		TSharedPtr<FJsonObject> EmbeddedObject = MakeShareable(new FJsonObject);
		EmbeddedObject->SetStringField("Hname", HighScoreNameArray[i]);// 
		EmbeddedObject->SetNumberField("Hscore", HighScoreScoreArray[i]);// 
		HMainObject->SetObjectField("Rank" + FString::FromInt(i), EmbeddedObject);
	}

	TSharedRef<TJsonWriter<>>HScoreWriter = TJsonWriterFactory<>::Create(&HString);
	FJsonSerializer::Serialize(HMainObject.ToSharedRef(), HScoreWriter);
	TSharedRef<IHttpRequest> UploadScores = FHttpModule::Get().CreateRequest();
	UploadScores->SetVerb("PUT");
	UploadScores->SetURL("https://amber-heat-4334.firebaseio.com/BrainsEden/Highscores/.json");
	UploadScores->SetHeader("Content-Type", "application/json");
	UploadScores->SetContentAsString(HString);
	UploadScores->ProcessRequest();

}

int32 ABabyGM::ScoreToLevel(float Score)
{
	int32 ConverterScore = (int32)Score;
	int32 ReturnLevel = (ConverterScore / 10) * 1.3;
	return ReturnLevel;


}
bool ABabyGM::GetName(int32 score)
{
	if (score > HighScoreScoreArray[2])
	{
		return true;
	}
	else
		return false;
}
void ABabyGM::SortArray(int32 score, FString name)
{
	int32 TempRank1;
	int32 TempRank2;

	
	FString TempName1;
	FString TempName2;
	
	if ((score> HighScoreScoreArray[2]) && (score <HighScoreScoreArray[1]))
	{
		HighScoreScoreArray[2] = score;
		HighScoreNameArray[2] = name;
	}
	
	else if ((score> HighScoreScoreArray[1]) && (score <HighScoreScoreArray[0]))
	{

		HighScoreNameArray[2] = HighScoreNameArray[1];
		HighScoreScoreArray[2] = HighScoreScoreArray[1];
		HighScoreNameArray[1] = name;
		HighScoreScoreArray[1] = score;
				
	}

	else if (score> HighScoreScoreArray[0])
	{

		TempName1 = HighScoreNameArray[0];
		TempRank1 = HighScoreScoreArray[0];

		TempName2 = HighScoreNameArray[1];
		TempRank2 = HighScoreScoreArray[1];
		HighScoreNameArray[2] = HighScoreNameArray[1];
		HighScoreScoreArray[2] = HighScoreScoreArray[1];

		HighScoreNameArray[1] = HighScoreNameArray[0];
		HighScoreScoreArray[1] = HighScoreScoreArray[0];

		HighScoreScoreArray[0] = score;
		HighScoreNameArray[0] = name;

	}
	UploadNewScore();

}