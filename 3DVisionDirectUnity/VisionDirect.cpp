#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "nvapi.h"
#include "nvapi_lite_stereo.h"
#include "Unity/IUnityGraphics.h"
#include "Unity/IUnityGraphicsD3D11.h"

static StereoHandle				g_StereoHandle;
static ID3D11Device*			g_pd3dDevice;
static IUnityInterfaces*		s_UnityInterfaces = NULL;

// Manually create stereo handle.  Needs to be called before any other NvAPI calls.
extern "C" INT UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API InitializeStereo()
{
	if (!s_UnityInterfaces)return -1;
	IUnityGraphicsD3D11* d3d = s_UnityInterfaces->Get<IUnityGraphicsD3D11>();
	if (!d3d)return -1;
	g_pd3dDevice = d3d->GetDevice();
	if (!g_pd3dDevice)return -1;
	NvAPI_Status status = NvAPI_Stereo_CreateHandleFromIUnknown(g_pd3dDevice, &g_StereoHandle);
	return status;
}

extern "C" INT UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API  ActivateLeftEye()
{
	if (g_StereoHandle)
	{
		NvAPI_Status status = NvAPI_Stereo_SetActiveEye(g_StereoHandle, NVAPI_STEREO_EYE_LEFT);
		return status;
	}
	return -1;
}

extern "C" INT UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API  ActivateRightEye()
{
	if (g_StereoHandle)
	{
		NvAPI_Status status = NvAPI_Stereo_SetActiveEye(g_StereoHandle, NVAPI_STEREO_EYE_RIGHT);
		return status;
	}
	return -1;
}


//Automatically called by Unity while after plugin is loaded
extern "C" void	UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
	s_UnityInterfaces = unityInterfaces; // get reference to Unity interface
}

// TODO: Resource cleanup
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
	
}



