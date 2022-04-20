#pragma once
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include "Events.h"
#include <appdata/pch-il2cpp.h>
#include <imgui_internal.h>

class NoClip
{
private:
	Phasmo::Player_1* localPlayer;
public:
	NoClip()
	{

	}

	void Update()
	{
		if (!localPlayer)
			return;

		//localPlayer->fields.firstPersonController
	}

	/*
	photonObjectInteract.GetComponent<Collider>().enabled = false;
	photonObjectInteract.GetComponent<Rigidbody>().useGravity = false;
	photonObjectInteract.GetComponent<Rigidbody>().isKinematic = true;
	*/
};
