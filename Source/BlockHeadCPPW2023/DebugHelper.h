#define GLUTTON_LOG(Message) \
    UE_LOG(LogTemp, Warning, TEXT("%s"), *FString{Message}); \
    if (GEngine) GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Yellow, Message)

#define PREP(Message, Variable) FString::Printf(TEXT(Message), Variable)
