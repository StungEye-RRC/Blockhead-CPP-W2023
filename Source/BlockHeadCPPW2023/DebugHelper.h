#define GLUTTON_LOG(Message) \
    UE_LOG(LogTemp, Log, TEXT("%s"), *FString{Message}); \
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Message)

#define PREP(Message, Variable) FString::Printf(TEXT(Message), Variable)
