#pragma once
#include <Icetrix\Events.h>
#include <Icetrix\Application.h>
#include <appdata/pch-il2cpp.h>

class UnlockCursor
{
public:
	UnlockCursor()
	{
        g_sApp.dispatcher.sink<Icetrix::Layer::MenuDrawEvent>().connect<&UnlockCursor::OnMenu>(*this);
	}

	void OnMenu(Icetrix::Layer::MenuDrawEvent event)
	{
        if (event.show && app::Cursor_get_lockState(NULL) == app::CursorLockMode__Enum_Locked)
        {
			app::Cursor_set_lockState(app::CursorLockMode__Enum_Confined, NULL);
        }
	}
};
