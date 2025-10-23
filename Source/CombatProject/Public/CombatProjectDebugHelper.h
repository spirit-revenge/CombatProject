#pragma once

namespace Debug
{
	//InKey,消息的唯一键值，用于更新或替换已有消息。如果设为 -1，表示添加新的消息。
	static void Print(const FString& Message, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 8.f, Color, Message);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}
}
