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
	if (mf_MasterVolume < 0) 
	{
		mf_MasterVolume = 0;
	}
	if (mf_MasterVolume > 1) 
	{
		mf_MasterVolume = 1.f; 
	}
}

void UVolume_ControlBPLibrary::SetEffectVolume(float sfx)
{
	mf_SoundEffectVolume = sfx; 
	if (mf_SoundEffectVolume < 0) 
	{
		mf_SoundEffectVolume = 0; 
	}
	if (mf_SoundEffectVolume > 1) 
	{
		mf_SoundEffectVolume = 1; 
	}
}

void UVolume_ControlBPLibrary::SetMusicVolume(float music)
{
	mf_MusicVolume = music; 
	if (mf_MusicVolume < 0) 
	{
		mf_MusicVolume = 0; 
	}
	if (mf_MusicVolume > 1) 
	{
		mf_MusicVolume = 1; 
	}
}
