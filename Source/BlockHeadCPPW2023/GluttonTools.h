#pragma once

#define GLUTTON_LOG(Message) \
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(Message)); \
	if (GEngine) GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, Message)
#define PRINTF(Message, Variable) FString::Printf(TEXT(Message), Variable)
