#pragma once
#include <pch.h>
#include <iostream>
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include "Icetrix/Renderer.h"
#include <appdata/pch-il2cpp.h>
#include "Utility.h"
#include "Game.h"
#include <algorithm>
#include "Utility.h"

using namespace app;

class Fly
{
private:
	bool fly = false;
	Phasmo::Player_1* localPlayer = nullptr;

	float cameraSensitivity = 90;
	float climbSpeed = 4;
	float normalMoveSpeed = 10;
	float slowMoveFactor = 0.25f;
	float fastMoveFactor = 3;

	float rotationX = 0.0f;
	float rotationY = 0.0f;

public:
	Fly()
	{
		g_sApp.dispatcher.sink<Icetrix::Layer::MenuDefaultWindowEvent>().connect<&Fly::Menu>(*this);
		g_sApp.dispatcher.sink<Icetrix::Hook::InputEvent::hwndProc>().connect<&Fly::Input>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::PlayerUpdate>().connect<&Fly::PlayerUpdate>(*this);
	}

	void Menu()
	{
		ImGui::Checkbox("Teleport", &fly);
	}

	void PlayerUpdate(Phasmo::Event::PlayerUpdate e) { this->localPlayer = e.localPlayer; }

	void Input(const Icetrix::Hook::InputEvent::hwndProc& input)
	{
		if (fly && this->localPlayer)
			HandleFly();
	}

	void HandleFly()
	{
		auto transform = app::Component_1_get_transform((app::Component_1*)this->localPlayer, NULL);

		/*
		rotationX += app::Input_GetAxis(CreateNETStringFromANSI("Mouse X"), NULL) * cameraSensitivity * app::Time_get_deltaTime(NULL);
		rotationY += app::Input_GetAxis(CreateNETStringFromANSI("Mouse Y"), NULL) * cameraSensitivity * app::Time_get_deltaTime(NULL);
		rotationY = std::clamp<float>(rotationY, -90, 90);

		Transform_set_localRotation(
			transform,
			Quaternion_op_Multiply(
				Quaternion_AngleAxis(rotationX, Vector3_get_up(NULL), NULL),
				Quaternion_AngleAxis(rotationY, Vector3_get_left(NULL), NULL),
				NULL),
			NULL
		);
		*/

		app::Vector3 position = app::Transform_get_position(transform, NULL);

		// position.z = app::Transform_get_forward(transform, NULL).z * normalMoveSpeed * app::Input_GetAxis(CreateNETStringFromANSI("Vertical"), NULL) * app::Time_get_deltaTime(NULL);
		// position.x = app::Transform_get_right(transform, NULL).x * normalMoveSpeed * app::Input_GetAxis(CreateNETStringFromANSI("Horizontal"), NULL) * app::Time_get_deltaTime(NULL);

		if (GetAsyncKeyState(VK_UP) & 1)
		{
			app::Transform_set_position(transform, position, NULL);
			position.x += 1;
		}

		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			app::Transform_set_position(transform, position, NULL);
			position.x -= 1;
		}

		if (GetAsyncKeyState(VK_LEFT) & 1)
		{
			position.y += 1;
			app::Transform_set_position(transform, position, NULL);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 1)
		{
			position.y -= 1;
			app::Transform_set_position(transform, position, NULL);
		}

		/*
		if (Input.GetKey(KeyCode.Q)) { transform.position += transform.up * climbSpeed * Time.deltaTime; }
		if (Input.GetKey(KeyCode.E)) { transform.position -= transform.up * climbSpeed * Time.deltaTime; }
		*/
	}
};
