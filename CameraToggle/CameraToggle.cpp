#include "pch.h"
#include "CameraToggle.h"


BAKKESMOD_PLUGIN(CameraToggle, "a bakkesplugin which allows you to toggle between two camera settings", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void CameraToggle::onLoad()
{
	this->registerCvars();
	gameWrapper->HookEvent("Function ProjectX.Camera_X.EventCameraStateChanged", std::bind(&CameraToggle::onBallcam, this, std::placeholders::_1));
}

void CameraToggle::registerCvars() {
	cvarManager->registerCvar("cameraToggle_toggle", "0", "toggles between both camera settings set in the plugin menue", true, true, 0.0f, true, 1.0f, false).addOnValueChanged(std::bind(&CameraToggle::toggleCamera, this, std::placeholders::_1, std::placeholders::_2));

	cvarManager->registerCvar("cameraToggle_distancePrimary", "300", "distance of primary cam", false, true, 100.0f, true, 400.0f, true);
	cvarManager->registerCvar("cameraToggle_fovPrimary", "110", "fov of primary cam", false, true, 60.0f, true, 110.0f, true);
	cvarManager->registerCvar("cameraToggle_hightPrimary", "100", "hight of primary cam", false, true, 40.0f, true, 200.0f, true);
	cvarManager->registerCvar("cameraToggle_pitchPrimary", "-3.0", "pitch of primary cam", false, true, -15.0f, true, 0.0f, true);
	cvarManager->registerCvar("cameraToggle_stiffnessPrimary", "0.5", "stiffnes of primary cam", false, true, 0.0f, true, 1.0f, true);
	cvarManager->registerCvar("cameraToggle_swivelSpeedPrimary", "5.0", "swivelSpeed of primary cam", false, true, 1.0f, true, 10.0f, true);
	cvarManager->registerCvar("cameraToggle_transitionSpeedPrimary", "1.5", "transitionSpeed of primary cam", false, true, 1.0f, true, 2.0f, true);

	cvarManager->registerCvar("cameraToggle_distanceSecondary", "300", "distance of secondary cam", false, true, 100.0f, true, 400.0f, true);
	cvarManager->registerCvar("cameraToggle_fovSecondary", "110", "fov of secondary cam", false, true, 60.0f, true, 110.0f, true);
	cvarManager->registerCvar("cameraToggle_hightSecondary", "100", "hight of secondary cam", false, true, 40.0f, true, 200.0f, true);
	cvarManager->registerCvar("cameraToggle_pitchSecondary", "-3.0", "pitch of secondary cam", false, true, -15.0f, true, 0.0f, true);
	cvarManager->registerCvar("cameraToggle_stiffnessSecondary", "0.5", "stiffnes of secondary cam", false, true, 0.0f, true, 1.0f, true);
	cvarManager->registerCvar("cameraToggle_swivelSpeedSecondary", "5.0", "swivelSpeed of secondary cam", false, true, 1.0f, true, 10.0f, true);
	cvarManager->registerCvar("cameraToggle_transitionSpeedSecondary", "1.5", "transitionSpeed of secondary cam", false, true, 1.0f, true, 2.0f, true);
}

void CameraToggle::toggleCamera(std::string oldValue, CVarWrapper cvar) {
	if (cvar.getBoolValue() == true) {
		if (gameWrapper->IsInFreeplay() == true || gameWrapper->IsInGame() == true) {
			ProfileCameraSettings Cam = gameWrapper->GetSettings().GetCameraSettings();
			if (currentCam == 1) {
				Cam.Distance = cvarManager->getCvar("cameraToggle_distancePrimary").getFloatValue();
				Cam.FOV = cvarManager->getCvar("cameraToggle_fovPrimary").getFloatValue();
				Cam.Height = cvarManager->getCvar("cameraToggle_hightPrimary").getFloatValue();
				Cam.Pitch = cvarManager->getCvar("cameraToggle_pitchPrimary").getFloatValue();
				Cam.Stiffness = cvarManager->getCvar("cameraToggle_stiffnessPrimary").getFloatValue();
				Cam.SwivelSpeed = cvarManager->getCvar("cameraToggle_swivelSpeedPrimary").getFloatValue();
				Cam.TransitionSpeed = cvarManager->getCvar("cameraToggle_transitionSpeedPrimary").getFloatValue();
				currentCam = 0;
			}
			else {
				Cam.Distance = cvarManager->getCvar("cameraToggle_distanceSecondary").getFloatValue();
				Cam.FOV = cvarManager->getCvar("cameraToggle_fovSecondary").getFloatValue();
				Cam.Height = cvarManager->getCvar("cameraToggle_hightSecondary").getFloatValue();
				Cam.Pitch = cvarManager->getCvar("cameraToggle_pitchSecondary").getFloatValue();
				Cam.Stiffness = cvarManager->getCvar("cameraToggle_stiffnessSecondary").getFloatValue();
				Cam.SwivelSpeed = cvarManager->getCvar("cameraToggle_swivelSpeedSecondary").getFloatValue();
				Cam.TransitionSpeed = cvarManager->getCvar("cameraToggle_transitionSpeedSecondary").getFloatValue();
				currentCam = 1;
			}
			gameWrapper->GetCamera().SetCameraSettings(Cam);
		}
		cvar.setValue(false);
	}
}

void CameraToggle::onBallcam(std::string eventName) {
	if (gameWrapper->IsInFreeplay() == true || gameWrapper->IsInGame() == true) {
		ProfileCameraSettings Cam = gameWrapper->GetSettings().GetCameraSettings();
		if (currentCam == 0) {
			Cam.Distance = cvarManager->getCvar("cameraToggle_distancePrimary").getFloatValue();
			Cam.FOV = cvarManager->getCvar("cameraToggle_fovPrimary").getFloatValue();
			Cam.Height = cvarManager->getCvar("cameraToggle_hightPrimary").getFloatValue();
			Cam.Pitch = cvarManager->getCvar("cameraToggle_pitchPrimary").getFloatValue();
			Cam.Stiffness = cvarManager->getCvar("cameraToggle_stiffnessPrimary").getFloatValue();
			Cam.SwivelSpeed = cvarManager->getCvar("cameraToggle_swivelSpeedPrimary").getFloatValue();
			Cam.TransitionSpeed = cvarManager->getCvar("cameraToggle_transitionSpeedPrimary").getFloatValue();
		}
		else {
			Cam.Distance = cvarManager->getCvar("cameraToggle_distanceSecondary").getFloatValue();
			Cam.FOV = cvarManager->getCvar("cameraToggle_fovSecondary").getFloatValue();
			Cam.Height = cvarManager->getCvar("cameraToggle_hightSecondary").getFloatValue();
			Cam.Pitch = cvarManager->getCvar("cameraToggle_pitchSecondary").getFloatValue();
			Cam.Stiffness = cvarManager->getCvar("cameraToggle_stiffnessSecondary").getFloatValue();
			Cam.SwivelSpeed = cvarManager->getCvar("cameraToggle_swivelSpeedSecondary").getFloatValue();
			Cam.TransitionSpeed = cvarManager->getCvar("cameraToggle_transitionSpeedSecondary").getFloatValue();
		}
		gameWrapper->GetCamera().SetCameraSettings(Cam);
	}
}

void CameraToggle::onUnload()
{
	gameWrapper->UnhookEvent("Function ProjectX.Camera_X.EventCameraStateChanged");
}