// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_system.h"

#ifdef TB_CLIPBOARD_GLFW

#include "GLFW/glfw3.h"

namespace tb {

// == TBClipboard =====================================

void TBClipboard::Empty()
{
	SetText("");
}

bool TBClipboard::HasText()
{
	if (GLFWwindow *window = glfwGetCurrentContext())
	{
		const char *str = glfwGetClipboardString(window);
		if (str && *str)
			return true;
	}
	return false;
}

bool TBClipboard::SetText(const char *text)
{
	if (GLFWwindow *window = glfwGetCurrentContext())
	{
		glfwSetClipboardString(window, text);
		return true;
	}
	return false;
}

bool TBClipboard::GetText(TBStr &text)
{
	if (GLFWwindow *window = glfwGetCurrentContext())
	{
		if (const char *str = glfwGetClipboardString(window))
			return text.Set(str);
	}
	return false;
}

}; // namespace tb

#endif // TB_CLIPBOARD_GLFW
