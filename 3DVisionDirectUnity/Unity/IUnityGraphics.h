#pragma once
#include "IUnityInterface.h"

typedef enum UnityGfxRenderer
{
	kUnityGfxRendererD3D11             =  2, // Direct3D 11
	kUnityGfxRendererNull = 4, // "null" device (used in batch mode)
} UnityGfxRenderer;

typedef enum UnityGfxDeviceEventType
{
	kUnityGfxDeviceEventInitialize     = 0,
	kUnityGfxDeviceEventShutdown       = 1,
	kUnityGfxDeviceEventBeforeReset    = 2,
	kUnityGfxDeviceEventAfterReset     = 3,

} UnityGfxDeviceEventType;

typedef void (UNITY_INTERFACE_API * IUnityGraphicsDeviceEventCallback)(UnityGfxDeviceEventType eventType);

// Should only be used on the rendering thread unless noted otherwise.
UNITY_DECLARE_INTERFACE(IUnityGraphics)
{
	UnityGfxRenderer (UNITY_INTERFACE_API * GetRenderer)(); // Thread safe

	// This callback will be called when graphics device is created, destroyed, reset, etc.
	// It is possible to miss the kUnityGfxDeviceEventInitialize event in case plugin is loaded at a later time,
	// when the graphics device is already created.
	void (UNITY_INTERFACE_API * RegisterDeviceEventCallback)(IUnityGraphicsDeviceEventCallback callback);
	void (UNITY_INTERFACE_API * UnregisterDeviceEventCallback)(IUnityGraphicsDeviceEventCallback callback);
};
UNITY_REGISTER_INTERFACE_GUID(0x7CBA0A9CA4DDB544ULL,0x8C5AD4926EB17B11ULL,IUnityGraphics)



// Certain Unity APIs (GL.IssuePluginEvent, CommandBuffer.IssuePluginEvent) can callback into native plugins.
// Provide them with an address to a function of this signature.
typedef void (UNITY_INTERFACE_API * UnityRenderingEvent)(int eventId);