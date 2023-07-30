// Copyright Epic Games, Inc. All Rights Reserved.

#include "Volume_ControlBPLibrary.h"
#include "Volume_Control.h"

float mf_MasterVolume = 0.5f;
float mf_SoundEffectVolume = 0.5f;
float mf_MusicVolume = 0.5f;


UVolume_ControlBPLibrary::UVolume_ControlBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UVolume_ControlBPLibrary::GetMasterVolume()
{
	return mf_MasterVolume;
}

float UVolume_ControlBPLibrary::GetEffectVolume()
{
	return mf_SoundEffectVolume;
}

float UVolume_ControlBPLibrary::GetMusicVolume()
{
	return mf_MusicVolume;
}

void UVolume_ControlBPLibrary::SetMasterVolume(float master)
{
	mf_MasterVolume = master;
}

void UVolume_ControlBPLibrary::SetEffectVolume(float sfx)
{
	mf_SoundEffectVolume = sfx; 
}

void UVolume_ControlBPLibrary::SetMusicVolume(float music)
{
	mf_MusicVolume = music; 
}
