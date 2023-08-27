# libaudioplugin

![licence badge](https://img.shields.io/badge/licence-MIT-blue?style=for-the-badge)
![cpp badge](https://img.shields.io/badge/C%2B%2B-17-blue?style=for-the-badge)
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/adriensalon/libplugin/windows.yaml?label=windows%20(AAX,%20VST2,%20VST3)&style=for-the-badge)
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/adriensalon/libplugin/macos.yaml?label=macos%20(AUv2,%20AUv3,%20AAX,%20VST2,%20VST3)&style=for-the-badge)
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/adriensalon/libplugin/linux.yaml?label=linux%20(VST3)&style=for-the-badge)

## Motivation

## Features
- Builds to all the plugin formats supported by the VST3 SDK for desktop platforms
- Provides a single CMake command 'add_plugin'
- Validates plugins after wrapping with the 'VALIDATE' keyword for the 'add_plugin' function
	- AUv2/AUv3 using the 'auval -v' MacOS command that provides deep insight
	- VST2 using a lightweight validator that mimics the VST3 default validator
	- VST3 using the default validator that comes with the SDK
	- No validator for AAX as we won't have access to the host SDK


og core audio sdk https://developer.apple.com/library/archive/samplecode/CoreAudioUtilityClasses/Introduction/Intro.html

but would be nice to support this instead https://github.com/apple/AudioUnitSDK