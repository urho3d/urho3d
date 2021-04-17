// DO NOT EDIT. This file is generated

// We need register all enums before registration of any functions because functions can use any enums

#include "../Precompiled.h"
#include "../AngelScript/APITemplates.h"

#include "../AngelScript/Generated_Includes.h"

namespace Urho3D
{

// enum AnimationChannel : unsigned char | File: ../Graphics/Animation.h
static const unsigned char AnimationChannel_CHANNEL_NONE = CHANNEL_NONE;
static const unsigned char AnimationChannel_CHANNEL_POSITION = CHANNEL_POSITION;
static const unsigned char AnimationChannel_CHANNEL_ROTATION = CHANNEL_ROTATION;
static const unsigned char AnimationChannel_CHANNEL_SCALE = CHANNEL_SCALE;

// enum BoneCollisionShape : unsigned char | File: ../Graphics/Skeleton.h
static const unsigned char BoneCollisionShape_BONECOLLISION_NONE = BONECOLLISION_NONE;
static const unsigned char BoneCollisionShape_BONECOLLISION_SPHERE = BONECOLLISION_SPHERE;
static const unsigned char BoneCollisionShape_BONECOLLISION_BOX = BONECOLLISION_BOX;

// enum ClearTarget : unsigned | File: ../Graphics/GraphicsDefs.h
static const unsigned ClearTarget_CLEAR_COLOR = CLEAR_COLOR;
static const unsigned ClearTarget_CLEAR_DEPTH = CLEAR_DEPTH;
static const unsigned ClearTarget_CLEAR_STENCIL = CLEAR_STENCIL;

// enum ControllerAxis : unsigned | File: ../Input/InputConstants.h
static const unsigned ControllerAxis_CONTROLLER_AXIS_LEFTX = CONTROLLER_AXIS_LEFTX;
static const unsigned ControllerAxis_CONTROLLER_AXIS_LEFTY = CONTROLLER_AXIS_LEFTY;
static const unsigned ControllerAxis_CONTROLLER_AXIS_RIGHTX = CONTROLLER_AXIS_RIGHTX;
static const unsigned ControllerAxis_CONTROLLER_AXIS_RIGHTY = CONTROLLER_AXIS_RIGHTY;
static const unsigned ControllerAxis_CONTROLLER_AXIS_TRIGGERLEFT = CONTROLLER_AXIS_TRIGGERLEFT;
static const unsigned ControllerAxis_CONTROLLER_AXIS_TRIGGERRIGHT = CONTROLLER_AXIS_TRIGGERRIGHT;

// enum ControllerButton : unsigned | File: ../Input/InputConstants.h
static const unsigned ControllerButton_CONTROLLER_BUTTON_A = CONTROLLER_BUTTON_A;
static const unsigned ControllerButton_CONTROLLER_BUTTON_B = CONTROLLER_BUTTON_B;
static const unsigned ControllerButton_CONTROLLER_BUTTON_X = CONTROLLER_BUTTON_X;
static const unsigned ControllerButton_CONTROLLER_BUTTON_Y = CONTROLLER_BUTTON_Y;
static const unsigned ControllerButton_CONTROLLER_BUTTON_BACK = CONTROLLER_BUTTON_BACK;
static const unsigned ControllerButton_CONTROLLER_BUTTON_GUIDE = CONTROLLER_BUTTON_GUIDE;
static const unsigned ControllerButton_CONTROLLER_BUTTON_START = CONTROLLER_BUTTON_START;
static const unsigned ControllerButton_CONTROLLER_BUTTON_LEFTSTICK = CONTROLLER_BUTTON_LEFTSTICK;
static const unsigned ControllerButton_CONTROLLER_BUTTON_RIGHTSTICK = CONTROLLER_BUTTON_RIGHTSTICK;
static const unsigned ControllerButton_CONTROLLER_BUTTON_LEFTSHOULDER = CONTROLLER_BUTTON_LEFTSHOULDER;
static const unsigned ControllerButton_CONTROLLER_BUTTON_RIGHTSHOULDER = CONTROLLER_BUTTON_RIGHTSHOULDER;
static const unsigned ControllerButton_CONTROLLER_BUTTON_DPAD_UP = CONTROLLER_BUTTON_DPAD_UP;
static const unsigned ControllerButton_CONTROLLER_BUTTON_DPAD_DOWN = CONTROLLER_BUTTON_DPAD_DOWN;
static const unsigned ControllerButton_CONTROLLER_BUTTON_DPAD_LEFT = CONTROLLER_BUTTON_DPAD_LEFT;
static const unsigned ControllerButton_CONTROLLER_BUTTON_DPAD_RIGHT = CONTROLLER_BUTTON_DPAD_RIGHT;

// enum DragAndDropMode : unsigned | File: ../UI/UIElement.h
static const unsigned DragAndDropMode_DD_DISABLED = DD_DISABLED;
static const unsigned DragAndDropMode_DD_SOURCE = DD_SOURCE;
static const unsigned DragAndDropMode_DD_TARGET = DD_TARGET;
static const unsigned DragAndDropMode_DD_SOURCE_AND_TARGET = DD_SOURCE_AND_TARGET;

// enum HatPosition : unsigned | File: ../Input/InputConstants.h
static const unsigned HatPosition_HAT_CENTER = HAT_CENTER;
static const unsigned HatPosition_HAT_UP = HAT_UP;
static const unsigned HatPosition_HAT_RIGHT = HAT_RIGHT;
static const unsigned HatPosition_HAT_DOWN = HAT_DOWN;
static const unsigned HatPosition_HAT_LEFT = HAT_LEFT;

// enum Key : unsigned | File: ../Input/InputConstants.h
static const unsigned Key_KEY_UNKNOWN = KEY_UNKNOWN;
static const unsigned Key_KEY_A = KEY_A;
static const unsigned Key_KEY_B = KEY_B;
static const unsigned Key_KEY_C = KEY_C;
static const unsigned Key_KEY_D = KEY_D;
static const unsigned Key_KEY_E = KEY_E;
static const unsigned Key_KEY_F = KEY_F;
static const unsigned Key_KEY_G = KEY_G;
static const unsigned Key_KEY_H = KEY_H;
static const unsigned Key_KEY_I = KEY_I;
static const unsigned Key_KEY_J = KEY_J;
static const unsigned Key_KEY_K = KEY_K;
static const unsigned Key_KEY_L = KEY_L;
static const unsigned Key_KEY_M = KEY_M;
static const unsigned Key_KEY_N = KEY_N;
static const unsigned Key_KEY_O = KEY_O;
static const unsigned Key_KEY_P = KEY_P;
static const unsigned Key_KEY_Q = KEY_Q;
static const unsigned Key_KEY_R = KEY_R;
static const unsigned Key_KEY_S = KEY_S;
static const unsigned Key_KEY_T = KEY_T;
static const unsigned Key_KEY_U = KEY_U;
static const unsigned Key_KEY_V = KEY_V;
static const unsigned Key_KEY_W = KEY_W;
static const unsigned Key_KEY_X = KEY_X;
static const unsigned Key_KEY_Y = KEY_Y;
static const unsigned Key_KEY_Z = KEY_Z;
static const unsigned Key_KEY_0 = KEY_0;
static const unsigned Key_KEY_1 = KEY_1;
static const unsigned Key_KEY_2 = KEY_2;
static const unsigned Key_KEY_3 = KEY_3;
static const unsigned Key_KEY_4 = KEY_4;
static const unsigned Key_KEY_5 = KEY_5;
static const unsigned Key_KEY_6 = KEY_6;
static const unsigned Key_KEY_7 = KEY_7;
static const unsigned Key_KEY_8 = KEY_8;
static const unsigned Key_KEY_9 = KEY_9;
static const unsigned Key_KEY_BACKSPACE = KEY_BACKSPACE;
static const unsigned Key_KEY_TAB = KEY_TAB;
static const unsigned Key_KEY_RETURN = KEY_RETURN;
static const unsigned Key_KEY_RETURN2 = KEY_RETURN2;
static const unsigned Key_KEY_KP_ENTER = KEY_KP_ENTER;
static const unsigned Key_KEY_SHIFT = KEY_SHIFT;
static const unsigned Key_KEY_CTRL = KEY_CTRL;
static const unsigned Key_KEY_ALT = KEY_ALT;
static const unsigned Key_KEY_GUI = KEY_GUI;
static const unsigned Key_KEY_PAUSE = KEY_PAUSE;
static const unsigned Key_KEY_CAPSLOCK = KEY_CAPSLOCK;
static const unsigned Key_KEY_ESCAPE = KEY_ESCAPE;
static const unsigned Key_KEY_SPACE = KEY_SPACE;
static const unsigned Key_KEY_PAGEUP = KEY_PAGEUP;
static const unsigned Key_KEY_PAGEDOWN = KEY_PAGEDOWN;
static const unsigned Key_KEY_END = KEY_END;
static const unsigned Key_KEY_HOME = KEY_HOME;
static const unsigned Key_KEY_LEFT = KEY_LEFT;
static const unsigned Key_KEY_UP = KEY_UP;
static const unsigned Key_KEY_RIGHT = KEY_RIGHT;
static const unsigned Key_KEY_DOWN = KEY_DOWN;
static const unsigned Key_KEY_SELECT = KEY_SELECT;
static const unsigned Key_KEY_PRINTSCREEN = KEY_PRINTSCREEN;
static const unsigned Key_KEY_INSERT = KEY_INSERT;
static const unsigned Key_KEY_DELETE = KEY_DELETE;
static const unsigned Key_KEY_LGUI = KEY_LGUI;
static const unsigned Key_KEY_RGUI = KEY_RGUI;
static const unsigned Key_KEY_APPLICATION = KEY_APPLICATION;
static const unsigned Key_KEY_KP_0 = KEY_KP_0;
static const unsigned Key_KEY_KP_1 = KEY_KP_1;
static const unsigned Key_KEY_KP_2 = KEY_KP_2;
static const unsigned Key_KEY_KP_3 = KEY_KP_3;
static const unsigned Key_KEY_KP_4 = KEY_KP_4;
static const unsigned Key_KEY_KP_5 = KEY_KP_5;
static const unsigned Key_KEY_KP_6 = KEY_KP_6;
static const unsigned Key_KEY_KP_7 = KEY_KP_7;
static const unsigned Key_KEY_KP_8 = KEY_KP_8;
static const unsigned Key_KEY_KP_9 = KEY_KP_9;
static const unsigned Key_KEY_KP_MULTIPLY = KEY_KP_MULTIPLY;
static const unsigned Key_KEY_KP_PLUS = KEY_KP_PLUS;
static const unsigned Key_KEY_KP_MINUS = KEY_KP_MINUS;
static const unsigned Key_KEY_KP_PERIOD = KEY_KP_PERIOD;
static const unsigned Key_KEY_KP_DIVIDE = KEY_KP_DIVIDE;
static const unsigned Key_KEY_F1 = KEY_F1;
static const unsigned Key_KEY_F2 = KEY_F2;
static const unsigned Key_KEY_F3 = KEY_F3;
static const unsigned Key_KEY_F4 = KEY_F4;
static const unsigned Key_KEY_F5 = KEY_F5;
static const unsigned Key_KEY_F6 = KEY_F6;
static const unsigned Key_KEY_F7 = KEY_F7;
static const unsigned Key_KEY_F8 = KEY_F8;
static const unsigned Key_KEY_F9 = KEY_F9;
static const unsigned Key_KEY_F10 = KEY_F10;
static const unsigned Key_KEY_F11 = KEY_F11;
static const unsigned Key_KEY_F12 = KEY_F12;
static const unsigned Key_KEY_F13 = KEY_F13;
static const unsigned Key_KEY_F14 = KEY_F14;
static const unsigned Key_KEY_F15 = KEY_F15;
static const unsigned Key_KEY_F16 = KEY_F16;
static const unsigned Key_KEY_F17 = KEY_F17;
static const unsigned Key_KEY_F18 = KEY_F18;
static const unsigned Key_KEY_F19 = KEY_F19;
static const unsigned Key_KEY_F20 = KEY_F20;
static const unsigned Key_KEY_F21 = KEY_F21;
static const unsigned Key_KEY_F22 = KEY_F22;
static const unsigned Key_KEY_F23 = KEY_F23;
static const unsigned Key_KEY_F24 = KEY_F24;
static const unsigned Key_KEY_NUMLOCKCLEAR = KEY_NUMLOCKCLEAR;
static const unsigned Key_KEY_SCROLLLOCK = KEY_SCROLLLOCK;
static const unsigned Key_KEY_LSHIFT = KEY_LSHIFT;
static const unsigned Key_KEY_RSHIFT = KEY_RSHIFT;
static const unsigned Key_KEY_LCTRL = KEY_LCTRL;
static const unsigned Key_KEY_RCTRL = KEY_RCTRL;
static const unsigned Key_KEY_LALT = KEY_LALT;
static const unsigned Key_KEY_RALT = KEY_RALT;
static const unsigned Key_KEY_AC_BACK = KEY_AC_BACK;
static const unsigned Key_KEY_AC_BOOKMARKS = KEY_AC_BOOKMARKS;
static const unsigned Key_KEY_AC_FORWARD = KEY_AC_FORWARD;
static const unsigned Key_KEY_AC_HOME = KEY_AC_HOME;
static const unsigned Key_KEY_AC_REFRESH = KEY_AC_REFRESH;
static const unsigned Key_KEY_AC_SEARCH = KEY_AC_SEARCH;
static const unsigned Key_KEY_AC_STOP = KEY_AC_STOP;
static const unsigned Key_KEY_AGAIN = KEY_AGAIN;
static const unsigned Key_KEY_ALTERASE = KEY_ALTERASE;
static const unsigned Key_KEY_AMPERSAND = KEY_AMPERSAND;
static const unsigned Key_KEY_ASTERISK = KEY_ASTERISK;
static const unsigned Key_KEY_AT = KEY_AT;
static const unsigned Key_KEY_AUDIOMUTE = KEY_AUDIOMUTE;
static const unsigned Key_KEY_AUDIONEXT = KEY_AUDIONEXT;
static const unsigned Key_KEY_AUDIOPLAY = KEY_AUDIOPLAY;
static const unsigned Key_KEY_AUDIOPREV = KEY_AUDIOPREV;
static const unsigned Key_KEY_AUDIOSTOP = KEY_AUDIOSTOP;
static const unsigned Key_KEY_BACKQUOTE = KEY_BACKQUOTE;
static const unsigned Key_KEY_BACKSLASH = KEY_BACKSLASH;
static const unsigned Key_KEY_BRIGHTNESSDOWN = KEY_BRIGHTNESSDOWN;
static const unsigned Key_KEY_BRIGHTNESSUP = KEY_BRIGHTNESSUP;
static const unsigned Key_KEY_CALCULATOR = KEY_CALCULATOR;
static const unsigned Key_KEY_CANCEL = KEY_CANCEL;
static const unsigned Key_KEY_CARET = KEY_CARET;
static const unsigned Key_KEY_CLEAR = KEY_CLEAR;
static const unsigned Key_KEY_CLEARAGAIN = KEY_CLEARAGAIN;
static const unsigned Key_KEY_COLON = KEY_COLON;
static const unsigned Key_KEY_COMMA = KEY_COMMA;
static const unsigned Key_KEY_COMPUTER = KEY_COMPUTER;
static const unsigned Key_KEY_COPY = KEY_COPY;
static const unsigned Key_KEY_CRSEL = KEY_CRSEL;
static const unsigned Key_KEY_CURRENCYSUBUNIT = KEY_CURRENCYSUBUNIT;
static const unsigned Key_KEY_CURRENCYUNIT = KEY_CURRENCYUNIT;
static const unsigned Key_KEY_CUT = KEY_CUT;
static const unsigned Key_KEY_DECIMALSEPARATOR = KEY_DECIMALSEPARATOR;
static const unsigned Key_KEY_DISPLAYSWITCH = KEY_DISPLAYSWITCH;
static const unsigned Key_KEY_DOLLAR = KEY_DOLLAR;
static const unsigned Key_KEY_EJECT = KEY_EJECT;
static const unsigned Key_KEY_EQUALS = KEY_EQUALS;
static const unsigned Key_KEY_EXCLAIM = KEY_EXCLAIM;
static const unsigned Key_KEY_EXSEL = KEY_EXSEL;
static const unsigned Key_KEY_FIND = KEY_FIND;
static const unsigned Key_KEY_GREATER = KEY_GREATER;
static const unsigned Key_KEY_HASH = KEY_HASH;
static const unsigned Key_KEY_HELP = KEY_HELP;
static const unsigned Key_KEY_KBDILLUMDOWN = KEY_KBDILLUMDOWN;
static const unsigned Key_KEY_KBDILLUMTOGGLE = KEY_KBDILLUMTOGGLE;
static const unsigned Key_KEY_KBDILLUMUP = KEY_KBDILLUMUP;
static const unsigned Key_KEY_KP_00 = KEY_KP_00;
static const unsigned Key_KEY_KP_000 = KEY_KP_000;
static const unsigned Key_KEY_KP_A = KEY_KP_A;
static const unsigned Key_KEY_KP_AMPERSAND = KEY_KP_AMPERSAND;
static const unsigned Key_KEY_KP_AT = KEY_KP_AT;
static const unsigned Key_KEY_KP_B = KEY_KP_B;
static const unsigned Key_KEY_KP_BACKSPACE = KEY_KP_BACKSPACE;
static const unsigned Key_KEY_KP_BINARY = KEY_KP_BINARY;
static const unsigned Key_KEY_KP_C = KEY_KP_C;
static const unsigned Key_KEY_KP_CLEAR = KEY_KP_CLEAR;
static const unsigned Key_KEY_KP_CLEARENTRY = KEY_KP_CLEARENTRY;
static const unsigned Key_KEY_KP_COLON = KEY_KP_COLON;
static const unsigned Key_KEY_KP_COMMA = KEY_KP_COMMA;
static const unsigned Key_KEY_KP_D = KEY_KP_D;
static const unsigned Key_KEY_KP_DBLAMPERSAND = KEY_KP_DBLAMPERSAND;
static const unsigned Key_KEY_KP_DBLVERTICALBAR = KEY_KP_DBLVERTICALBAR;
static const unsigned Key_KEY_KP_DECIMAL = KEY_KP_DECIMAL;
static const unsigned Key_KEY_KP_E = KEY_KP_E;
static const unsigned Key_KEY_KP_EQUALS = KEY_KP_EQUALS;
static const unsigned Key_KEY_KP_EQUALSAS400 = KEY_KP_EQUALSAS400;
static const unsigned Key_KEY_KP_EXCLAM = KEY_KP_EXCLAM;
static const unsigned Key_KEY_KP_F = KEY_KP_F;
static const unsigned Key_KEY_KP_GREATER = KEY_KP_GREATER;
static const unsigned Key_KEY_KP_HASH = KEY_KP_HASH;
static const unsigned Key_KEY_KP_HEXADECIMAL = KEY_KP_HEXADECIMAL;
static const unsigned Key_KEY_KP_LEFTBRACE = KEY_KP_LEFTBRACE;
static const unsigned Key_KEY_KP_LEFTPAREN = KEY_KP_LEFTPAREN;
static const unsigned Key_KEY_KP_LESS = KEY_KP_LESS;
static const unsigned Key_KEY_KP_MEMADD = KEY_KP_MEMADD;
static const unsigned Key_KEY_KP_MEMCLEAR = KEY_KP_MEMCLEAR;
static const unsigned Key_KEY_KP_MEMDIVIDE = KEY_KP_MEMDIVIDE;
static const unsigned Key_KEY_KP_MEMMULTIPLY = KEY_KP_MEMMULTIPLY;
static const unsigned Key_KEY_KP_MEMRECALL = KEY_KP_MEMRECALL;
static const unsigned Key_KEY_KP_MEMSTORE = KEY_KP_MEMSTORE;
static const unsigned Key_KEY_KP_MEMSUBTRACT = KEY_KP_MEMSUBTRACT;
static const unsigned Key_KEY_KP_OCTAL = KEY_KP_OCTAL;
static const unsigned Key_KEY_KP_PERCENT = KEY_KP_PERCENT;
static const unsigned Key_KEY_KP_PLUSMINUS = KEY_KP_PLUSMINUS;
static const unsigned Key_KEY_KP_POWER = KEY_KP_POWER;
static const unsigned Key_KEY_KP_RIGHTBRACE = KEY_KP_RIGHTBRACE;
static const unsigned Key_KEY_KP_RIGHTPAREN = KEY_KP_RIGHTPAREN;
static const unsigned Key_KEY_KP_SPACE = KEY_KP_SPACE;
static const unsigned Key_KEY_KP_TAB = KEY_KP_TAB;
static const unsigned Key_KEY_KP_VERTICALBAR = KEY_KP_VERTICALBAR;
static const unsigned Key_KEY_KP_XOR = KEY_KP_XOR;
static const unsigned Key_KEY_LEFTBRACKET = KEY_LEFTBRACKET;
static const unsigned Key_KEY_LEFTPAREN = KEY_LEFTPAREN;
static const unsigned Key_KEY_LESS = KEY_LESS;
static const unsigned Key_KEY_MAIL = KEY_MAIL;
static const unsigned Key_KEY_MEDIASELECT = KEY_MEDIASELECT;
static const unsigned Key_KEY_MENU = KEY_MENU;
static const unsigned Key_KEY_MINUS = KEY_MINUS;
static const unsigned Key_KEY_MODE = KEY_MODE;
static const unsigned Key_KEY_MUTE = KEY_MUTE;
static const unsigned Key_KEY_OPER = KEY_OPER;
static const unsigned Key_KEY_OUT = KEY_OUT;
static const unsigned Key_KEY_PASTE = KEY_PASTE;
static const unsigned Key_KEY_PERCENT = KEY_PERCENT;
static const unsigned Key_KEY_PERIOD = KEY_PERIOD;
static const unsigned Key_KEY_PLUS = KEY_PLUS;
static const unsigned Key_KEY_POWER = KEY_POWER;
static const unsigned Key_KEY_PRIOR = KEY_PRIOR;
static const unsigned Key_KEY_QUESTION = KEY_QUESTION;
static const unsigned Key_KEY_QUOTE = KEY_QUOTE;
static const unsigned Key_KEY_QUOTEDBL = KEY_QUOTEDBL;
static const unsigned Key_KEY_RIGHTBRACKET = KEY_RIGHTBRACKET;
static const unsigned Key_KEY_RIGHTPAREN = KEY_RIGHTPAREN;
static const unsigned Key_KEY_SEMICOLON = KEY_SEMICOLON;
static const unsigned Key_KEY_SEPARATOR = KEY_SEPARATOR;
static const unsigned Key_KEY_SLASH = KEY_SLASH;
static const unsigned Key_KEY_SLEEP = KEY_SLEEP;
static const unsigned Key_KEY_STOP = KEY_STOP;
static const unsigned Key_KEY_SYSREQ = KEY_SYSREQ;
static const unsigned Key_KEY_THOUSANDSSEPARATOR = KEY_THOUSANDSSEPARATOR;
static const unsigned Key_KEY_UNDERSCORE = KEY_UNDERSCORE;
static const unsigned Key_KEY_UNDO = KEY_UNDO;
static const unsigned Key_KEY_VOLUMEDOWN = KEY_VOLUMEDOWN;
static const unsigned Key_KEY_VOLUMEUP = KEY_VOLUMEUP;
static const unsigned Key_KEY_WWW = KEY_WWW;

// enum MaterialQuality : unsigned | File: ../Graphics/GraphicsDefs.h
static const unsigned MaterialQuality_QUALITY_LOW = QUALITY_LOW;
static const unsigned MaterialQuality_QUALITY_MEDIUM = QUALITY_MEDIUM;
static const unsigned MaterialQuality_QUALITY_HIGH = QUALITY_HIGH;
static const unsigned MaterialQuality_QUALITY_MAX = QUALITY_MAX;

// enum MouseButton : unsigned | File: ../Input/InputConstants.h
static const unsigned MouseButton_MOUSEB_NONE = MOUSEB_NONE;
static const unsigned MouseButton_MOUSEB_LEFT = MOUSEB_LEFT;
static const unsigned MouseButton_MOUSEB_MIDDLE = MOUSEB_MIDDLE;
static const unsigned MouseButton_MOUSEB_RIGHT = MOUSEB_RIGHT;
static const unsigned MouseButton_MOUSEB_X1 = MOUSEB_X1;
static const unsigned MouseButton_MOUSEB_X2 = MOUSEB_X2;
static const unsigned MouseButton_MOUSEB_ANY = MOUSEB_ANY;

// enum Qualifier : unsigned | File: ../Input/InputConstants.h
static const unsigned Qualifier_QUAL_NONE = QUAL_NONE;
static const unsigned Qualifier_QUAL_SHIFT = QUAL_SHIFT;
static const unsigned Qualifier_QUAL_CTRL = QUAL_CTRL;
static const unsigned Qualifier_QUAL_ALT = QUAL_ALT;
static const unsigned Qualifier_QUAL_ANY = QUAL_ANY;

// enum Scancode : unsigned | File: ../Input/InputConstants.h
static const unsigned Scancode_SCANCODE_UNKNOWN = SCANCODE_UNKNOWN;
static const unsigned Scancode_SCANCODE_CTRL = SCANCODE_CTRL;
static const unsigned Scancode_SCANCODE_SHIFT = SCANCODE_SHIFT;
static const unsigned Scancode_SCANCODE_ALT = SCANCODE_ALT;
static const unsigned Scancode_SCANCODE_GUI = SCANCODE_GUI;
static const unsigned Scancode_SCANCODE_A = SCANCODE_A;
static const unsigned Scancode_SCANCODE_B = SCANCODE_B;
static const unsigned Scancode_SCANCODE_C = SCANCODE_C;
static const unsigned Scancode_SCANCODE_D = SCANCODE_D;
static const unsigned Scancode_SCANCODE_E = SCANCODE_E;
static const unsigned Scancode_SCANCODE_F = SCANCODE_F;
static const unsigned Scancode_SCANCODE_G = SCANCODE_G;
static const unsigned Scancode_SCANCODE_H = SCANCODE_H;
static const unsigned Scancode_SCANCODE_I = SCANCODE_I;
static const unsigned Scancode_SCANCODE_J = SCANCODE_J;
static const unsigned Scancode_SCANCODE_K = SCANCODE_K;
static const unsigned Scancode_SCANCODE_L = SCANCODE_L;
static const unsigned Scancode_SCANCODE_M = SCANCODE_M;
static const unsigned Scancode_SCANCODE_N = SCANCODE_N;
static const unsigned Scancode_SCANCODE_O = SCANCODE_O;
static const unsigned Scancode_SCANCODE_P = SCANCODE_P;
static const unsigned Scancode_SCANCODE_Q = SCANCODE_Q;
static const unsigned Scancode_SCANCODE_R = SCANCODE_R;
static const unsigned Scancode_SCANCODE_S = SCANCODE_S;
static const unsigned Scancode_SCANCODE_T = SCANCODE_T;
static const unsigned Scancode_SCANCODE_U = SCANCODE_U;
static const unsigned Scancode_SCANCODE_V = SCANCODE_V;
static const unsigned Scancode_SCANCODE_W = SCANCODE_W;
static const unsigned Scancode_SCANCODE_X = SCANCODE_X;
static const unsigned Scancode_SCANCODE_Y = SCANCODE_Y;
static const unsigned Scancode_SCANCODE_Z = SCANCODE_Z;
static const unsigned Scancode_SCANCODE_1 = SCANCODE_1;
static const unsigned Scancode_SCANCODE_2 = SCANCODE_2;
static const unsigned Scancode_SCANCODE_3 = SCANCODE_3;
static const unsigned Scancode_SCANCODE_4 = SCANCODE_4;
static const unsigned Scancode_SCANCODE_5 = SCANCODE_5;
static const unsigned Scancode_SCANCODE_6 = SCANCODE_6;
static const unsigned Scancode_SCANCODE_7 = SCANCODE_7;
static const unsigned Scancode_SCANCODE_8 = SCANCODE_8;
static const unsigned Scancode_SCANCODE_9 = SCANCODE_9;
static const unsigned Scancode_SCANCODE_0 = SCANCODE_0;
static const unsigned Scancode_SCANCODE_RETURN = SCANCODE_RETURN;
static const unsigned Scancode_SCANCODE_ESCAPE = SCANCODE_ESCAPE;
static const unsigned Scancode_SCANCODE_BACKSPACE = SCANCODE_BACKSPACE;
static const unsigned Scancode_SCANCODE_TAB = SCANCODE_TAB;
static const unsigned Scancode_SCANCODE_SPACE = SCANCODE_SPACE;
static const unsigned Scancode_SCANCODE_MINUS = SCANCODE_MINUS;
static const unsigned Scancode_SCANCODE_EQUALS = SCANCODE_EQUALS;
static const unsigned Scancode_SCANCODE_LEFTBRACKET = SCANCODE_LEFTBRACKET;
static const unsigned Scancode_SCANCODE_RIGHTBRACKET = SCANCODE_RIGHTBRACKET;
static const unsigned Scancode_SCANCODE_BACKSLASH = SCANCODE_BACKSLASH;
static const unsigned Scancode_SCANCODE_NONUSHASH = SCANCODE_NONUSHASH;
static const unsigned Scancode_SCANCODE_SEMICOLON = SCANCODE_SEMICOLON;
static const unsigned Scancode_SCANCODE_APOSTROPHE = SCANCODE_APOSTROPHE;
static const unsigned Scancode_SCANCODE_GRAVE = SCANCODE_GRAVE;
static const unsigned Scancode_SCANCODE_COMMA = SCANCODE_COMMA;
static const unsigned Scancode_SCANCODE_PERIOD = SCANCODE_PERIOD;
static const unsigned Scancode_SCANCODE_SLASH = SCANCODE_SLASH;
static const unsigned Scancode_SCANCODE_CAPSLOCK = SCANCODE_CAPSLOCK;
static const unsigned Scancode_SCANCODE_F1 = SCANCODE_F1;
static const unsigned Scancode_SCANCODE_F2 = SCANCODE_F2;
static const unsigned Scancode_SCANCODE_F3 = SCANCODE_F3;
static const unsigned Scancode_SCANCODE_F4 = SCANCODE_F4;
static const unsigned Scancode_SCANCODE_F5 = SCANCODE_F5;
static const unsigned Scancode_SCANCODE_F6 = SCANCODE_F6;
static const unsigned Scancode_SCANCODE_F7 = SCANCODE_F7;
static const unsigned Scancode_SCANCODE_F8 = SCANCODE_F8;
static const unsigned Scancode_SCANCODE_F9 = SCANCODE_F9;
static const unsigned Scancode_SCANCODE_F10 = SCANCODE_F10;
static const unsigned Scancode_SCANCODE_F11 = SCANCODE_F11;
static const unsigned Scancode_SCANCODE_F12 = SCANCODE_F12;
static const unsigned Scancode_SCANCODE_PRINTSCREEN = SCANCODE_PRINTSCREEN;
static const unsigned Scancode_SCANCODE_SCROLLLOCK = SCANCODE_SCROLLLOCK;
static const unsigned Scancode_SCANCODE_PAUSE = SCANCODE_PAUSE;
static const unsigned Scancode_SCANCODE_INSERT = SCANCODE_INSERT;
static const unsigned Scancode_SCANCODE_HOME = SCANCODE_HOME;
static const unsigned Scancode_SCANCODE_PAGEUP = SCANCODE_PAGEUP;
static const unsigned Scancode_SCANCODE_DELETE = SCANCODE_DELETE;
static const unsigned Scancode_SCANCODE_END = SCANCODE_END;
static const unsigned Scancode_SCANCODE_PAGEDOWN = SCANCODE_PAGEDOWN;
static const unsigned Scancode_SCANCODE_RIGHT = SCANCODE_RIGHT;
static const unsigned Scancode_SCANCODE_LEFT = SCANCODE_LEFT;
static const unsigned Scancode_SCANCODE_DOWN = SCANCODE_DOWN;
static const unsigned Scancode_SCANCODE_UP = SCANCODE_UP;
static const unsigned Scancode_SCANCODE_NUMLOCKCLEAR = SCANCODE_NUMLOCKCLEAR;
static const unsigned Scancode_SCANCODE_KP_DIVIDE = SCANCODE_KP_DIVIDE;
static const unsigned Scancode_SCANCODE_KP_MULTIPLY = SCANCODE_KP_MULTIPLY;
static const unsigned Scancode_SCANCODE_KP_MINUS = SCANCODE_KP_MINUS;
static const unsigned Scancode_SCANCODE_KP_PLUS = SCANCODE_KP_PLUS;
static const unsigned Scancode_SCANCODE_KP_ENTER = SCANCODE_KP_ENTER;
static const unsigned Scancode_SCANCODE_KP_1 = SCANCODE_KP_1;
static const unsigned Scancode_SCANCODE_KP_2 = SCANCODE_KP_2;
static const unsigned Scancode_SCANCODE_KP_3 = SCANCODE_KP_3;
static const unsigned Scancode_SCANCODE_KP_4 = SCANCODE_KP_4;
static const unsigned Scancode_SCANCODE_KP_5 = SCANCODE_KP_5;
static const unsigned Scancode_SCANCODE_KP_6 = SCANCODE_KP_6;
static const unsigned Scancode_SCANCODE_KP_7 = SCANCODE_KP_7;
static const unsigned Scancode_SCANCODE_KP_8 = SCANCODE_KP_8;
static const unsigned Scancode_SCANCODE_KP_9 = SCANCODE_KP_9;
static const unsigned Scancode_SCANCODE_KP_0 = SCANCODE_KP_0;
static const unsigned Scancode_SCANCODE_KP_PERIOD = SCANCODE_KP_PERIOD;
static const unsigned Scancode_SCANCODE_NONUSBACKSLASH = SCANCODE_NONUSBACKSLASH;
static const unsigned Scancode_SCANCODE_APPLICATION = SCANCODE_APPLICATION;
static const unsigned Scancode_SCANCODE_POWER = SCANCODE_POWER;
static const unsigned Scancode_SCANCODE_KP_EQUALS = SCANCODE_KP_EQUALS;
static const unsigned Scancode_SCANCODE_F13 = SCANCODE_F13;
static const unsigned Scancode_SCANCODE_F14 = SCANCODE_F14;
static const unsigned Scancode_SCANCODE_F15 = SCANCODE_F15;
static const unsigned Scancode_SCANCODE_F16 = SCANCODE_F16;
static const unsigned Scancode_SCANCODE_F17 = SCANCODE_F17;
static const unsigned Scancode_SCANCODE_F18 = SCANCODE_F18;
static const unsigned Scancode_SCANCODE_F19 = SCANCODE_F19;
static const unsigned Scancode_SCANCODE_F20 = SCANCODE_F20;
static const unsigned Scancode_SCANCODE_F21 = SCANCODE_F21;
static const unsigned Scancode_SCANCODE_F22 = SCANCODE_F22;
static const unsigned Scancode_SCANCODE_F23 = SCANCODE_F23;
static const unsigned Scancode_SCANCODE_F24 = SCANCODE_F24;
static const unsigned Scancode_SCANCODE_EXECUTE = SCANCODE_EXECUTE;
static const unsigned Scancode_SCANCODE_HELP = SCANCODE_HELP;
static const unsigned Scancode_SCANCODE_MENU = SCANCODE_MENU;
static const unsigned Scancode_SCANCODE_SELECT = SCANCODE_SELECT;
static const unsigned Scancode_SCANCODE_STOP = SCANCODE_STOP;
static const unsigned Scancode_SCANCODE_AGAIN = SCANCODE_AGAIN;
static const unsigned Scancode_SCANCODE_UNDO = SCANCODE_UNDO;
static const unsigned Scancode_SCANCODE_CUT = SCANCODE_CUT;
static const unsigned Scancode_SCANCODE_COPY = SCANCODE_COPY;
static const unsigned Scancode_SCANCODE_PASTE = SCANCODE_PASTE;
static const unsigned Scancode_SCANCODE_FIND = SCANCODE_FIND;
static const unsigned Scancode_SCANCODE_MUTE = SCANCODE_MUTE;
static const unsigned Scancode_SCANCODE_VOLUMEUP = SCANCODE_VOLUMEUP;
static const unsigned Scancode_SCANCODE_VOLUMEDOWN = SCANCODE_VOLUMEDOWN;
static const unsigned Scancode_SCANCODE_KP_COMMA = SCANCODE_KP_COMMA;
static const unsigned Scancode_SCANCODE_KP_EQUALSAS400 = SCANCODE_KP_EQUALSAS400;
static const unsigned Scancode_SCANCODE_INTERNATIONAL1 = SCANCODE_INTERNATIONAL1;
static const unsigned Scancode_SCANCODE_INTERNATIONAL2 = SCANCODE_INTERNATIONAL2;
static const unsigned Scancode_SCANCODE_INTERNATIONAL3 = SCANCODE_INTERNATIONAL3;
static const unsigned Scancode_SCANCODE_INTERNATIONAL4 = SCANCODE_INTERNATIONAL4;
static const unsigned Scancode_SCANCODE_INTERNATIONAL5 = SCANCODE_INTERNATIONAL5;
static const unsigned Scancode_SCANCODE_INTERNATIONAL6 = SCANCODE_INTERNATIONAL6;
static const unsigned Scancode_SCANCODE_INTERNATIONAL7 = SCANCODE_INTERNATIONAL7;
static const unsigned Scancode_SCANCODE_INTERNATIONAL8 = SCANCODE_INTERNATIONAL8;
static const unsigned Scancode_SCANCODE_INTERNATIONAL9 = SCANCODE_INTERNATIONAL9;
static const unsigned Scancode_SCANCODE_LANG1 = SCANCODE_LANG1;
static const unsigned Scancode_SCANCODE_LANG2 = SCANCODE_LANG2;
static const unsigned Scancode_SCANCODE_LANG3 = SCANCODE_LANG3;
static const unsigned Scancode_SCANCODE_LANG4 = SCANCODE_LANG4;
static const unsigned Scancode_SCANCODE_LANG5 = SCANCODE_LANG5;
static const unsigned Scancode_SCANCODE_LANG6 = SCANCODE_LANG6;
static const unsigned Scancode_SCANCODE_LANG7 = SCANCODE_LANG7;
static const unsigned Scancode_SCANCODE_LANG8 = SCANCODE_LANG8;
static const unsigned Scancode_SCANCODE_LANG9 = SCANCODE_LANG9;
static const unsigned Scancode_SCANCODE_ALTERASE = SCANCODE_ALTERASE;
static const unsigned Scancode_SCANCODE_SYSREQ = SCANCODE_SYSREQ;
static const unsigned Scancode_SCANCODE_CANCEL = SCANCODE_CANCEL;
static const unsigned Scancode_SCANCODE_CLEAR = SCANCODE_CLEAR;
static const unsigned Scancode_SCANCODE_PRIOR = SCANCODE_PRIOR;
static const unsigned Scancode_SCANCODE_RETURN2 = SCANCODE_RETURN2;
static const unsigned Scancode_SCANCODE_SEPARATOR = SCANCODE_SEPARATOR;
static const unsigned Scancode_SCANCODE_OUT = SCANCODE_OUT;
static const unsigned Scancode_SCANCODE_OPER = SCANCODE_OPER;
static const unsigned Scancode_SCANCODE_CLEARAGAIN = SCANCODE_CLEARAGAIN;
static const unsigned Scancode_SCANCODE_CRSEL = SCANCODE_CRSEL;
static const unsigned Scancode_SCANCODE_EXSEL = SCANCODE_EXSEL;
static const unsigned Scancode_SCANCODE_KP_00 = SCANCODE_KP_00;
static const unsigned Scancode_SCANCODE_KP_000 = SCANCODE_KP_000;
static const unsigned Scancode_SCANCODE_THOUSANDSSEPARATOR = SCANCODE_THOUSANDSSEPARATOR;
static const unsigned Scancode_SCANCODE_DECIMALSEPARATOR = SCANCODE_DECIMALSEPARATOR;
static const unsigned Scancode_SCANCODE_CURRENCYUNIT = SCANCODE_CURRENCYUNIT;
static const unsigned Scancode_SCANCODE_CURRENCYSUBUNIT = SCANCODE_CURRENCYSUBUNIT;
static const unsigned Scancode_SCANCODE_KP_LEFTPAREN = SCANCODE_KP_LEFTPAREN;
static const unsigned Scancode_SCANCODE_KP_RIGHTPAREN = SCANCODE_KP_RIGHTPAREN;
static const unsigned Scancode_SCANCODE_KP_LEFTBRACE = SCANCODE_KP_LEFTBRACE;
static const unsigned Scancode_SCANCODE_KP_RIGHTBRACE = SCANCODE_KP_RIGHTBRACE;
static const unsigned Scancode_SCANCODE_KP_TAB = SCANCODE_KP_TAB;
static const unsigned Scancode_SCANCODE_KP_BACKSPACE = SCANCODE_KP_BACKSPACE;
static const unsigned Scancode_SCANCODE_KP_A = SCANCODE_KP_A;
static const unsigned Scancode_SCANCODE_KP_B = SCANCODE_KP_B;
static const unsigned Scancode_SCANCODE_KP_C = SCANCODE_KP_C;
static const unsigned Scancode_SCANCODE_KP_D = SCANCODE_KP_D;
static const unsigned Scancode_SCANCODE_KP_E = SCANCODE_KP_E;
static const unsigned Scancode_SCANCODE_KP_F = SCANCODE_KP_F;
static const unsigned Scancode_SCANCODE_KP_XOR = SCANCODE_KP_XOR;
static const unsigned Scancode_SCANCODE_KP_POWER = SCANCODE_KP_POWER;
static const unsigned Scancode_SCANCODE_KP_PERCENT = SCANCODE_KP_PERCENT;
static const unsigned Scancode_SCANCODE_KP_LESS = SCANCODE_KP_LESS;
static const unsigned Scancode_SCANCODE_KP_GREATER = SCANCODE_KP_GREATER;
static const unsigned Scancode_SCANCODE_KP_AMPERSAND = SCANCODE_KP_AMPERSAND;
static const unsigned Scancode_SCANCODE_KP_DBLAMPERSAND = SCANCODE_KP_DBLAMPERSAND;
static const unsigned Scancode_SCANCODE_KP_VERTICALBAR = SCANCODE_KP_VERTICALBAR;
static const unsigned Scancode_SCANCODE_KP_DBLVERTICALBAR = SCANCODE_KP_DBLVERTICALBAR;
static const unsigned Scancode_SCANCODE_KP_COLON = SCANCODE_KP_COLON;
static const unsigned Scancode_SCANCODE_KP_HASH = SCANCODE_KP_HASH;
static const unsigned Scancode_SCANCODE_KP_SPACE = SCANCODE_KP_SPACE;
static const unsigned Scancode_SCANCODE_KP_AT = SCANCODE_KP_AT;
static const unsigned Scancode_SCANCODE_KP_EXCLAM = SCANCODE_KP_EXCLAM;
static const unsigned Scancode_SCANCODE_KP_MEMSTORE = SCANCODE_KP_MEMSTORE;
static const unsigned Scancode_SCANCODE_KP_MEMRECALL = SCANCODE_KP_MEMRECALL;
static const unsigned Scancode_SCANCODE_KP_MEMCLEAR = SCANCODE_KP_MEMCLEAR;
static const unsigned Scancode_SCANCODE_KP_MEMADD = SCANCODE_KP_MEMADD;
static const unsigned Scancode_SCANCODE_KP_MEMSUBTRACT = SCANCODE_KP_MEMSUBTRACT;
static const unsigned Scancode_SCANCODE_KP_MEMMULTIPLY = SCANCODE_KP_MEMMULTIPLY;
static const unsigned Scancode_SCANCODE_KP_MEMDIVIDE = SCANCODE_KP_MEMDIVIDE;
static const unsigned Scancode_SCANCODE_KP_PLUSMINUS = SCANCODE_KP_PLUSMINUS;
static const unsigned Scancode_SCANCODE_KP_CLEAR = SCANCODE_KP_CLEAR;
static const unsigned Scancode_SCANCODE_KP_CLEARENTRY = SCANCODE_KP_CLEARENTRY;
static const unsigned Scancode_SCANCODE_KP_BINARY = SCANCODE_KP_BINARY;
static const unsigned Scancode_SCANCODE_KP_OCTAL = SCANCODE_KP_OCTAL;
static const unsigned Scancode_SCANCODE_KP_DECIMAL = SCANCODE_KP_DECIMAL;
static const unsigned Scancode_SCANCODE_KP_HEXADECIMAL = SCANCODE_KP_HEXADECIMAL;
static const unsigned Scancode_SCANCODE_LCTRL = SCANCODE_LCTRL;
static const unsigned Scancode_SCANCODE_LSHIFT = SCANCODE_LSHIFT;
static const unsigned Scancode_SCANCODE_LALT = SCANCODE_LALT;
static const unsigned Scancode_SCANCODE_LGUI = SCANCODE_LGUI;
static const unsigned Scancode_SCANCODE_RCTRL = SCANCODE_RCTRL;
static const unsigned Scancode_SCANCODE_RSHIFT = SCANCODE_RSHIFT;
static const unsigned Scancode_SCANCODE_RALT = SCANCODE_RALT;
static const unsigned Scancode_SCANCODE_RGUI = SCANCODE_RGUI;
static const unsigned Scancode_SCANCODE_MODE = SCANCODE_MODE;
static const unsigned Scancode_SCANCODE_AUDIONEXT = SCANCODE_AUDIONEXT;
static const unsigned Scancode_SCANCODE_AUDIOPREV = SCANCODE_AUDIOPREV;
static const unsigned Scancode_SCANCODE_AUDIOSTOP = SCANCODE_AUDIOSTOP;
static const unsigned Scancode_SCANCODE_AUDIOPLAY = SCANCODE_AUDIOPLAY;
static const unsigned Scancode_SCANCODE_AUDIOMUTE = SCANCODE_AUDIOMUTE;
static const unsigned Scancode_SCANCODE_MEDIASELECT = SCANCODE_MEDIASELECT;
static const unsigned Scancode_SCANCODE_WWW = SCANCODE_WWW;
static const unsigned Scancode_SCANCODE_MAIL = SCANCODE_MAIL;
static const unsigned Scancode_SCANCODE_CALCULATOR = SCANCODE_CALCULATOR;
static const unsigned Scancode_SCANCODE_COMPUTER = SCANCODE_COMPUTER;
static const unsigned Scancode_SCANCODE_AC_SEARCH = SCANCODE_AC_SEARCH;
static const unsigned Scancode_SCANCODE_AC_HOME = SCANCODE_AC_HOME;
static const unsigned Scancode_SCANCODE_AC_BACK = SCANCODE_AC_BACK;
static const unsigned Scancode_SCANCODE_AC_FORWARD = SCANCODE_AC_FORWARD;
static const unsigned Scancode_SCANCODE_AC_STOP = SCANCODE_AC_STOP;
static const unsigned Scancode_SCANCODE_AC_REFRESH = SCANCODE_AC_REFRESH;
static const unsigned Scancode_SCANCODE_AC_BOOKMARKS = SCANCODE_AC_BOOKMARKS;
static const unsigned Scancode_SCANCODE_BRIGHTNESSDOWN = SCANCODE_BRIGHTNESSDOWN;
static const unsigned Scancode_SCANCODE_BRIGHTNESSUP = SCANCODE_BRIGHTNESSUP;
static const unsigned Scancode_SCANCODE_DISPLAYSWITCH = SCANCODE_DISPLAYSWITCH;
static const unsigned Scancode_SCANCODE_KBDILLUMTOGGLE = SCANCODE_KBDILLUMTOGGLE;
static const unsigned Scancode_SCANCODE_KBDILLUMDOWN = SCANCODE_KBDILLUMDOWN;
static const unsigned Scancode_SCANCODE_KBDILLUMUP = SCANCODE_KBDILLUMUP;
static const unsigned Scancode_SCANCODE_EJECT = SCANCODE_EJECT;
static const unsigned Scancode_SCANCODE_SLEEP = SCANCODE_SLEEP;
static const unsigned Scancode_SCANCODE_APP1 = SCANCODE_APP1;
static const unsigned Scancode_SCANCODE_APP2 = SCANCODE_APP2;

// enum SmoothingType : unsigned | File: ../Scene/SmoothedTransform.h
static const unsigned SmoothingType_SMOOTH_NONE = SMOOTH_NONE;
static const unsigned SmoothingType_SMOOTH_POSITION = SMOOTH_POSITION;
static const unsigned SmoothingType_SMOOTH_ROTATION = SMOOTH_ROTATION;

// enum UpdateEvent : unsigned | File: ../Scene/LogicComponent.h
static const unsigned UpdateEvent_USE_NO_EVENT = USE_NO_EVENT;
static const unsigned UpdateEvent_USE_UPDATE = USE_UPDATE;
static const unsigned UpdateEvent_USE_POSTUPDATE = USE_POSTUPDATE;
static const unsigned UpdateEvent_USE_FIXEDUPDATE = USE_FIXEDUPDATE;
static const unsigned UpdateEvent_USE_FIXEDPOSTUPDATE = USE_FIXEDPOSTUPDATE;

// enum VertexMask : unsigned | File: ../Graphics/GraphicsDefs.h
static const unsigned VertexMask_MASK_NONE = MASK_NONE;
static const unsigned VertexMask_MASK_POSITION = MASK_POSITION;
static const unsigned VertexMask_MASK_NORMAL = MASK_NORMAL;
static const unsigned VertexMask_MASK_COLOR = MASK_COLOR;
static const unsigned VertexMask_MASK_TEXCOORD1 = MASK_TEXCOORD1;
static const unsigned VertexMask_MASK_TEXCOORD2 = MASK_TEXCOORD2;
static const unsigned VertexMask_MASK_CUBETEXCOORD1 = MASK_CUBETEXCOORD1;
static const unsigned VertexMask_MASK_CUBETEXCOORD2 = MASK_CUBETEXCOORD2;
static const unsigned VertexMask_MASK_TANGENT = MASK_TANGENT;
static const unsigned VertexMask_MASK_BLENDWEIGHTS = MASK_BLENDWEIGHTS;
static const unsigned VertexMask_MASK_BLENDINDICES = MASK_BLENDINDICES;
static const unsigned VertexMask_MASK_INSTANCEMATRIX1 = MASK_INSTANCEMATRIX1;
static const unsigned VertexMask_MASK_INSTANCEMATRIX2 = MASK_INSTANCEMATRIX2;
static const unsigned VertexMask_MASK_INSTANCEMATRIX3 = MASK_INSTANCEMATRIX3;
static const unsigned VertexMask_MASK_OBJECTINDEX = MASK_OBJECTINDEX;

// enum ViewOverride : unsigned | File: ../Graphics/Camera.h
static const unsigned ViewOverride_VO_NONE = VO_NONE;
static const unsigned ViewOverride_VO_LOW_MATERIAL_QUALITY = VO_LOW_MATERIAL_QUALITY;
static const unsigned ViewOverride_VO_DISABLE_SHADOWS = VO_DISABLE_SHADOWS;
static const unsigned ViewOverride_VO_DISABLE_OCCLUSION = VO_DISABLE_OCCLUSION;

void ASRegisterGeneratedEnums(asIScriptEngine* engine)
{
    // enum AnimationBlendMode | File: ../Graphics/AnimationState.h
    engine->RegisterEnum("AnimationBlendMode");
    engine->RegisterEnumValue("AnimationBlendMode", "ABM_LERP", ABM_LERP);
    engine->RegisterEnumValue("AnimationBlendMode", "ABM_ADDITIVE", ABM_ADDITIVE);

    // enum AnimationChannel : unsigned char | File: ../Graphics/Animation.h
    engine->RegisterTypedef("AnimationChannel", "uint8");
    engine->RegisterGlobalProperty("const uint8 CHANNEL_NONE", (void*)&AnimationChannel_CHANNEL_NONE);
    engine->RegisterGlobalProperty("const uint8 CHANNEL_POSITION", (void*)&AnimationChannel_CHANNEL_POSITION);
    engine->RegisterGlobalProperty("const uint8 CHANNEL_ROTATION", (void*)&AnimationChannel_CHANNEL_ROTATION);
    engine->RegisterGlobalProperty("const uint8 CHANNEL_SCALE", (void*)&AnimationChannel_CHANNEL_SCALE);

    // URHO3D_FLAGSET(AnimationChannel, AnimationChannelFlags) | File: ../Graphics/Animation.h
    engine->RegisterTypedef("AnimationChannelFlags", "uint8");

    // enum AsyncLoadState | File: ../Resource/Resource.h
    engine->RegisterEnum("AsyncLoadState");
    engine->RegisterEnumValue("AsyncLoadState", "ASYNC_DONE", ASYNC_DONE);
    engine->RegisterEnumValue("AsyncLoadState", "ASYNC_QUEUED", ASYNC_QUEUED);
    engine->RegisterEnumValue("AsyncLoadState", "ASYNC_LOADING", ASYNC_LOADING);
    engine->RegisterEnumValue("AsyncLoadState", "ASYNC_SUCCESS", ASYNC_SUCCESS);
    engine->RegisterEnumValue("AsyncLoadState", "ASYNC_FAIL", ASYNC_FAIL);

    // enum AttributeMode | File: ../Core/Attribute.h
    engine->RegisterEnum("AttributeMode");
    engine->RegisterEnumValue("AttributeMode", "AM_EDIT", AM_EDIT);
    engine->RegisterEnumValue("AttributeMode", "AM_FILE", AM_FILE);
    engine->RegisterEnumValue("AttributeMode", "AM_NET", AM_NET);
    engine->RegisterEnumValue("AttributeMode", "AM_DEFAULT", AM_DEFAULT);
    engine->RegisterEnumValue("AttributeMode", "AM_LATESTDATA", AM_LATESTDATA);
    engine->RegisterEnumValue("AttributeMode", "AM_NOEDIT", AM_NOEDIT);
    engine->RegisterEnumValue("AttributeMode", "AM_NODEID", AM_NODEID);
    engine->RegisterEnumValue("AttributeMode", "AM_COMPONENTID", AM_COMPONENTID);
    engine->RegisterEnumValue("AttributeMode", "AM_NODEIDVECTOR", AM_NODEIDVECTOR);
    engine->RegisterEnumValue("AttributeMode", "AM_FILEREADONLY", AM_FILEREADONLY);

    // URHO3D_FLAGSET(AttributeMode, AttributeModeFlags) | File: ../Core/Attribute.h
    engine->RegisterTypedef("AttributeModeFlags", "int");

    // enum AutoRemoveMode | File: ../Scene/Component.h
    engine->RegisterEnum("AutoRemoveMode");
    engine->RegisterEnumValue("AutoRemoveMode", "REMOVE_DISABLED", REMOVE_DISABLED);
    engine->RegisterEnumValue("AutoRemoveMode", "REMOVE_COMPONENT", REMOVE_COMPONENT);
    engine->RegisterEnumValue("AutoRemoveMode", "REMOVE_NODE", REMOVE_NODE);

    // enum BlendMode | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("BlendMode");
    engine->RegisterEnumValue("BlendMode", "BLEND_REPLACE", BLEND_REPLACE);
    engine->RegisterEnumValue("BlendMode", "BLEND_ADD", BLEND_ADD);
    engine->RegisterEnumValue("BlendMode", "BLEND_MULTIPLY", BLEND_MULTIPLY);
    engine->RegisterEnumValue("BlendMode", "BLEND_ALPHA", BLEND_ALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_ADDALPHA", BLEND_ADDALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_PREMULALPHA", BLEND_PREMULALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_INVDESTALPHA", BLEND_INVDESTALPHA);
    engine->RegisterEnumValue("BlendMode", "BLEND_SUBTRACT", BLEND_SUBTRACT);
    engine->RegisterEnumValue("BlendMode", "BLEND_SUBTRACTALPHA", BLEND_SUBTRACTALPHA);
    engine->RegisterEnumValue("BlendMode", "MAX_BLENDMODES", MAX_BLENDMODES);

    // enum BoneCollisionShape : unsigned char | File: ../Graphics/Skeleton.h
    engine->RegisterTypedef("BoneCollisionShape", "uint8");
    engine->RegisterGlobalProperty("const uint8 BONECOLLISION_NONE", (void*)&BoneCollisionShape_BONECOLLISION_NONE);
    engine->RegisterGlobalProperty("const uint8 BONECOLLISION_SPHERE", (void*)&BoneCollisionShape_BONECOLLISION_SPHERE);
    engine->RegisterGlobalProperty("const uint8 BONECOLLISION_BOX", (void*)&BoneCollisionShape_BONECOLLISION_BOX);

    // URHO3D_FLAGSET(BoneCollisionShape, BoneCollisionShapeFlags) | File: ../Graphics/Skeleton.h
    engine->RegisterTypedef("BoneCollisionShapeFlags", "uint8");

    // enum ClearTarget : unsigned | File: ../Graphics/GraphicsDefs.h
    engine->RegisterTypedef("ClearTarget", "uint");
    engine->RegisterGlobalProperty("const uint CLEAR_COLOR", (void*)&ClearTarget_CLEAR_COLOR);
    engine->RegisterGlobalProperty("const uint CLEAR_DEPTH", (void*)&ClearTarget_CLEAR_DEPTH);
    engine->RegisterGlobalProperty("const uint CLEAR_STENCIL", (void*)&ClearTarget_CLEAR_STENCIL);

    // URHO3D_FLAGSET(ClearTarget, ClearTargetFlags) | File: ../Graphics/GraphicsDefs.h
    engine->RegisterTypedef("ClearTargetFlags", "uint");

    // enum CompareMode | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("CompareMode");
    engine->RegisterEnumValue("CompareMode", "CMP_ALWAYS", CMP_ALWAYS);
    engine->RegisterEnumValue("CompareMode", "CMP_EQUAL", CMP_EQUAL);
    engine->RegisterEnumValue("CompareMode", "CMP_NOTEQUAL", CMP_NOTEQUAL);
    engine->RegisterEnumValue("CompareMode", "CMP_LESS", CMP_LESS);
    engine->RegisterEnumValue("CompareMode", "CMP_LESSEQUAL", CMP_LESSEQUAL);
    engine->RegisterEnumValue("CompareMode", "CMP_GREATER", CMP_GREATER);
    engine->RegisterEnumValue("CompareMode", "CMP_GREATEREQUAL", CMP_GREATEREQUAL);
    engine->RegisterEnumValue("CompareMode", "MAX_COMPAREMODES", MAX_COMPAREMODES);

    // enum CompressedFormat | File: ../Resource/Image.h
    engine->RegisterEnum("CompressedFormat");
    engine->RegisterEnumValue("CompressedFormat", "CF_NONE", CF_NONE);
    engine->RegisterEnumValue("CompressedFormat", "CF_RGBA", CF_RGBA);
    engine->RegisterEnumValue("CompressedFormat", "CF_DXT1", CF_DXT1);
    engine->RegisterEnumValue("CompressedFormat", "CF_DXT3", CF_DXT3);
    engine->RegisterEnumValue("CompressedFormat", "CF_DXT5", CF_DXT5);
    engine->RegisterEnumValue("CompressedFormat", "CF_ETC1", CF_ETC1);
    engine->RegisterEnumValue("CompressedFormat", "CF_ETC2_RGB", CF_ETC2_RGB);
    engine->RegisterEnumValue("CompressedFormat", "CF_ETC2_RGBA", CF_ETC2_RGBA);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGB_2BPP", CF_PVRTC_RGB_2BPP);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGBA_2BPP", CF_PVRTC_RGBA_2BPP);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGB_4BPP", CF_PVRTC_RGB_4BPP);
    engine->RegisterEnumValue("CompressedFormat", "CF_PVRTC_RGBA_4BPP", CF_PVRTC_RGBA_4BPP);

    // enum ControllerAxis : unsigned | File: ../Input/InputConstants.h
    engine->RegisterTypedef("ControllerAxis", "uint");
    engine->RegisterGlobalProperty("const uint CONTROLLER_AXIS_LEFTX", (void*)&ControllerAxis_CONTROLLER_AXIS_LEFTX);
    engine->RegisterGlobalProperty("const uint CONTROLLER_AXIS_LEFTY", (void*)&ControllerAxis_CONTROLLER_AXIS_LEFTY);
    engine->RegisterGlobalProperty("const uint CONTROLLER_AXIS_RIGHTX", (void*)&ControllerAxis_CONTROLLER_AXIS_RIGHTX);
    engine->RegisterGlobalProperty("const uint CONTROLLER_AXIS_RIGHTY", (void*)&ControllerAxis_CONTROLLER_AXIS_RIGHTY);
    engine->RegisterGlobalProperty("const uint CONTROLLER_AXIS_TRIGGERLEFT", (void*)&ControllerAxis_CONTROLLER_AXIS_TRIGGERLEFT);
    engine->RegisterGlobalProperty("const uint CONTROLLER_AXIS_TRIGGERRIGHT", (void*)&ControllerAxis_CONTROLLER_AXIS_TRIGGERRIGHT);

    // enum ControllerButton : unsigned | File: ../Input/InputConstants.h
    engine->RegisterTypedef("ControllerButton", "uint");
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_A", (void*)&ControllerButton_CONTROLLER_BUTTON_A);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_B", (void*)&ControllerButton_CONTROLLER_BUTTON_B);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_X", (void*)&ControllerButton_CONTROLLER_BUTTON_X);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_Y", (void*)&ControllerButton_CONTROLLER_BUTTON_Y);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_BACK", (void*)&ControllerButton_CONTROLLER_BUTTON_BACK);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_GUIDE", (void*)&ControllerButton_CONTROLLER_BUTTON_GUIDE);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_START", (void*)&ControllerButton_CONTROLLER_BUTTON_START);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_LEFTSTICK", (void*)&ControllerButton_CONTROLLER_BUTTON_LEFTSTICK);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_RIGHTSTICK", (void*)&ControllerButton_CONTROLLER_BUTTON_RIGHTSTICK);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_LEFTSHOULDER", (void*)&ControllerButton_CONTROLLER_BUTTON_LEFTSHOULDER);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_RIGHTSHOULDER", (void*)&ControllerButton_CONTROLLER_BUTTON_RIGHTSHOULDER);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_DPAD_UP", (void*)&ControllerButton_CONTROLLER_BUTTON_DPAD_UP);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_DPAD_DOWN", (void*)&ControllerButton_CONTROLLER_BUTTON_DPAD_DOWN);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_DPAD_LEFT", (void*)&ControllerButton_CONTROLLER_BUTTON_DPAD_LEFT);
    engine->RegisterGlobalProperty("const uint CONTROLLER_BUTTON_DPAD_RIGHT", (void*)&ControllerButton_CONTROLLER_BUTTON_DPAD_RIGHT);

    // enum Corner | File: ../UI/UIElement.h
    engine->RegisterEnum("Corner");
    engine->RegisterEnumValue("Corner", "C_TOPLEFT", C_TOPLEFT);
    engine->RegisterEnumValue("Corner", "C_TOPRIGHT", C_TOPRIGHT);
    engine->RegisterEnumValue("Corner", "C_BOTTOMLEFT", C_BOTTOMLEFT);
    engine->RegisterEnumValue("Corner", "C_BOTTOMRIGHT", C_BOTTOMRIGHT);
    engine->RegisterEnumValue("Corner", "MAX_UIELEMENT_CORNERS", MAX_UIELEMENT_CORNERS);

    // enum CreateMode | File: ../Scene/Node.h
    engine->RegisterEnum("CreateMode");
    engine->RegisterEnumValue("CreateMode", "REPLICATED", REPLICATED);
    engine->RegisterEnumValue("CreateMode", "LOCAL", LOCAL);

    // enum CubeMapFace | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("CubeMapFace");
    engine->RegisterEnumValue("CubeMapFace", "FACE_POSITIVE_X", FACE_POSITIVE_X);
    engine->RegisterEnumValue("CubeMapFace", "FACE_NEGATIVE_X", FACE_NEGATIVE_X);
    engine->RegisterEnumValue("CubeMapFace", "FACE_POSITIVE_Y", FACE_POSITIVE_Y);
    engine->RegisterEnumValue("CubeMapFace", "FACE_NEGATIVE_Y", FACE_NEGATIVE_Y);
    engine->RegisterEnumValue("CubeMapFace", "FACE_POSITIVE_Z", FACE_POSITIVE_Z);
    engine->RegisterEnumValue("CubeMapFace", "FACE_NEGATIVE_Z", FACE_NEGATIVE_Z);
    engine->RegisterEnumValue("CubeMapFace", "MAX_CUBEMAP_FACES", MAX_CUBEMAP_FACES);

    // enum CubeMapLayout | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("CubeMapLayout");
    engine->RegisterEnumValue("CubeMapLayout", "CML_HORIZONTAL", CML_HORIZONTAL);
    engine->RegisterEnumValue("CubeMapLayout", "CML_HORIZONTALNVIDIA", CML_HORIZONTALNVIDIA);
    engine->RegisterEnumValue("CubeMapLayout", "CML_HORIZONTALCROSS", CML_HORIZONTALCROSS);
    engine->RegisterEnumValue("CubeMapLayout", "CML_VERTICALCROSS", CML_VERTICALCROSS);
    engine->RegisterEnumValue("CubeMapLayout", "CML_BLENDER", CML_BLENDER);

    // enum CullMode | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("CullMode");
    engine->RegisterEnumValue("CullMode", "CULL_NONE", CULL_NONE);
    engine->RegisterEnumValue("CullMode", "CULL_CCW", CULL_CCW);
    engine->RegisterEnumValue("CullMode", "CULL_CW", CULL_CW);
    engine->RegisterEnumValue("CullMode", "MAX_CULLMODES", MAX_CULLMODES);

    // enum CursorShape | File: ../UI/Cursor.h
    engine->RegisterEnum("CursorShape");
    engine->RegisterEnumValue("CursorShape", "CS_NORMAL", CS_NORMAL);
    engine->RegisterEnumValue("CursorShape", "CS_IBEAM", CS_IBEAM);
    engine->RegisterEnumValue("CursorShape", "CS_CROSS", CS_CROSS);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEVERTICAL", CS_RESIZEVERTICAL);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEDIAGONAL_TOPRIGHT", CS_RESIZEDIAGONAL_TOPRIGHT);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEHORIZONTAL", CS_RESIZEHORIZONTAL);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZEDIAGONAL_TOPLEFT", CS_RESIZEDIAGONAL_TOPLEFT);
    engine->RegisterEnumValue("CursorShape", "CS_RESIZE_ALL", CS_RESIZE_ALL);
    engine->RegisterEnumValue("CursorShape", "CS_ACCEPTDROP", CS_ACCEPTDROP);
    engine->RegisterEnumValue("CursorShape", "CS_REJECTDROP", CS_REJECTDROP);
    engine->RegisterEnumValue("CursorShape", "CS_BUSY", CS_BUSY);
    engine->RegisterEnumValue("CursorShape", "CS_BUSY_ARROW", CS_BUSY_ARROW);
    engine->RegisterEnumValue("CursorShape", "CS_MAX_SHAPES", CS_MAX_SHAPES);

    // enum DeferredLightPSVariation | File: ../Graphics/Renderer.h
    engine->RegisterEnum("DeferredLightPSVariation");
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_NONE", DLPS_NONE);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SPOT", DLPS_SPOT);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINT", DLPS_POINT);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTMASK", DLPS_POINTMASK);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SPEC", DLPS_SPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SPOTSPEC", DLPS_SPOTSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTSPEC", DLPS_POINTSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTMASKSPEC", DLPS_POINTMASKSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SHADOW", DLPS_SHADOW);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SPOTSHADOW", DLPS_SPOTSHADOW);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTSHADOW", DLPS_POINTSHADOW);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTMASKSHADOW", DLPS_POINTMASKSHADOW);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SHADOWSPEC", DLPS_SHADOWSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SPOTSHADOWSPEC", DLPS_SPOTSHADOWSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTSHADOWSPEC", DLPS_POINTSHADOWSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTMASKSHADOWSPEC", DLPS_POINTMASKSHADOWSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SHADOWNORMALOFFSET", DLPS_SHADOWNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SPOTSHADOWNORMALOFFSET", DLPS_SPOTSHADOWNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTSHADOWNORMALOFFSET", DLPS_POINTSHADOWNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTMASKSHADOWNORMALOFFSET", DLPS_POINTMASKSHADOWNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SHADOWSPECNORMALOFFSET", DLPS_SHADOWSPECNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_SPOTSHADOWSPECNORMALOFFSET", DLPS_SPOTSHADOWSPECNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTSHADOWSPECNORMALOFFSET", DLPS_POINTSHADOWSPECNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_POINTMASKSHADOWSPECNORMALOFFSET", DLPS_POINTMASKSHADOWSPECNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHO", DLPS_ORTHO);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSPOT", DLPS_ORTHOSPOT);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINT", DLPS_ORTHOPOINT);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTMASK", DLPS_ORTHOPOINTMASK);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSPEC", DLPS_ORTHOSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSPOTSPEC", DLPS_ORTHOSPOTSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTSPEC", DLPS_ORTHOPOINTSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTMASKSPEC", DLPS_ORTHOPOINTMASKSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSHADOW", DLPS_ORTHOSHADOW);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSPOTSHADOW", DLPS_ORTHOSPOTSHADOW);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTSHADOW", DLPS_ORTHOPOINTSHADOW);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTMASKSHADOW", DLPS_ORTHOPOINTMASKSHADOW);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSHADOWSPEC", DLPS_ORTHOSHADOWSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSPOTSHADOWSPEC", DLPS_ORTHOSPOTSHADOWSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTSHADOWSPEC", DLPS_ORTHOPOINTSHADOWSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTMASKSHADOWSPEC", DLPS_ORTHOPOINTMASKSHADOWSPEC);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSHADOWNORMALOFFSET", DLPS_ORTHOSHADOWNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSPOTSHADOWNORMALOFFSET", DLPS_ORTHOSPOTSHADOWNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTSHADOWNORMALOFFSET", DLPS_ORTHOPOINTSHADOWNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTMASKSHADOWNORMALOFFSET", DLPS_ORTHOPOINTMASKSHADOWNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSHADOWSPECNORMALOFFSET", DLPS_ORTHOSHADOWSPECNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOSPOTSHADOWSPECNORMALOFFSET", DLPS_ORTHOSPOTSHADOWSPECNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTSHADOWSPECNORMALOFFSET", DLPS_ORTHOPOINTSHADOWSPECNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "DLPS_ORTHOPOINTMASKSHADOWSPECNORMALOFFSET", DLPS_ORTHOPOINTMASKSHADOWSPECNORMALOFFSET);
    engine->RegisterEnumValue("DeferredLightPSVariation", "MAX_DEFERRED_LIGHT_PS_VARIATIONS", MAX_DEFERRED_LIGHT_PS_VARIATIONS);

    // enum DeferredLightVSVariation | File: ../Graphics/Renderer.h
    engine->RegisterEnum("DeferredLightVSVariation");
    engine->RegisterEnumValue("DeferredLightVSVariation", "DLVS_NONE", DLVS_NONE);
    engine->RegisterEnumValue("DeferredLightVSVariation", "DLVS_DIR", DLVS_DIR);
    engine->RegisterEnumValue("DeferredLightVSVariation", "DLVS_ORTHO", DLVS_ORTHO);
    engine->RegisterEnumValue("DeferredLightVSVariation", "DLVS_ORTHODIR", DLVS_ORTHODIR);
    engine->RegisterEnumValue("DeferredLightVSVariation", "MAX_DEFERRED_LIGHT_VS_VARIATIONS", MAX_DEFERRED_LIGHT_VS_VARIATIONS);

    // enum DragAndDropMode : unsigned | File: ../UI/UIElement.h
    engine->RegisterTypedef("DragAndDropMode", "uint");
    engine->RegisterGlobalProperty("const uint DD_DISABLED", (void*)&DragAndDropMode_DD_DISABLED);
    engine->RegisterGlobalProperty("const uint DD_SOURCE", (void*)&DragAndDropMode_DD_SOURCE);
    engine->RegisterGlobalProperty("const uint DD_TARGET", (void*)&DragAndDropMode_DD_TARGET);
    engine->RegisterGlobalProperty("const uint DD_SOURCE_AND_TARGET", (void*)&DragAndDropMode_DD_SOURCE_AND_TARGET);

    // URHO3D_FLAGSET(DragAndDropMode, DragAndDropModeFlags) | File: ../UI/UIElement.h
    engine->RegisterTypedef("DragAndDropModeFlags", "uint");

    // enum EmitterType | File: ../Graphics/ParticleEffect.h
    engine->RegisterEnum("EmitterType");
    engine->RegisterEnumValue("EmitterType", "EMITTER_SPHERE", EMITTER_SPHERE);
    engine->RegisterEnumValue("EmitterType", "EMITTER_BOX", EMITTER_BOX);
    engine->RegisterEnumValue("EmitterType", "EMITTER_SPHEREVOLUME", EMITTER_SPHEREVOLUME);
    engine->RegisterEnumValue("EmitterType", "EMITTER_CYLINDER", EMITTER_CYLINDER);
    engine->RegisterEnumValue("EmitterType", "EMITTER_RING", EMITTER_RING);

    // enum FaceCameraMode | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("FaceCameraMode");
    engine->RegisterEnumValue("FaceCameraMode", "FC_NONE", FC_NONE);
    engine->RegisterEnumValue("FaceCameraMode", "FC_ROTATE_XYZ", FC_ROTATE_XYZ);
    engine->RegisterEnumValue("FaceCameraMode", "FC_ROTATE_Y", FC_ROTATE_Y);
    engine->RegisterEnumValue("FaceCameraMode", "FC_LOOKAT_XYZ", FC_LOOKAT_XYZ);
    engine->RegisterEnumValue("FaceCameraMode", "FC_LOOKAT_Y", FC_LOOKAT_Y);
    engine->RegisterEnumValue("FaceCameraMode", "FC_LOOKAT_MIXED", FC_LOOKAT_MIXED);
    engine->RegisterEnumValue("FaceCameraMode", "FC_DIRECTION", FC_DIRECTION);

    // enum FileMode | File: ../IO/File.h
    engine->RegisterEnum("FileMode");
    engine->RegisterEnumValue("FileMode", "FILE_READ", FILE_READ);
    engine->RegisterEnumValue("FileMode", "FILE_WRITE", FILE_WRITE);
    engine->RegisterEnumValue("FileMode", "FILE_READWRITE", FILE_READWRITE);

    // enum FillMode | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("FillMode");
    engine->RegisterEnumValue("FillMode", "FILL_SOLID", FILL_SOLID);
    engine->RegisterEnumValue("FillMode", "FILL_WIREFRAME", FILL_WIREFRAME);
    engine->RegisterEnumValue("FillMode", "FILL_POINT", FILL_POINT);

    // enum FocusMode | File: ../UI/UIElement.h
    engine->RegisterEnum("FocusMode");
    engine->RegisterEnumValue("FocusMode", "FM_NOTFOCUSABLE", FM_NOTFOCUSABLE);
    engine->RegisterEnumValue("FocusMode", "FM_RESETFOCUS", FM_RESETFOCUS);
    engine->RegisterEnumValue("FocusMode", "FM_FOCUSABLE", FM_FOCUSABLE);
    engine->RegisterEnumValue("FocusMode", "FM_FOCUSABLE_DEFOCUSABLE", FM_FOCUSABLE_DEFOCUSABLE);

    // enum FontHintLevel | File: ../UI/UI.h
    engine->RegisterEnum("FontHintLevel");
    engine->RegisterEnumValue("FontHintLevel", "FONT_HINT_LEVEL_NONE", FONT_HINT_LEVEL_NONE);
    engine->RegisterEnumValue("FontHintLevel", "FONT_HINT_LEVEL_LIGHT", FONT_HINT_LEVEL_LIGHT);
    engine->RegisterEnumValue("FontHintLevel", "FONT_HINT_LEVEL_NORMAL", FONT_HINT_LEVEL_NORMAL);

    // enum FontType | File: ../UI/Font.h
    engine->RegisterEnum("FontType");
    engine->RegisterEnumValue("FontType", "FONT_NONE", FONT_NONE);
    engine->RegisterEnumValue("FontType", "FONT_FREETYPE", FONT_FREETYPE);
    engine->RegisterEnumValue("FontType", "FONT_BITMAP", FONT_BITMAP);
    engine->RegisterEnumValue("FontType", "MAX_FONT_TYPES", MAX_FONT_TYPES);

    // enum FrustumPlane | File: ../Math/Frustum.h
    engine->RegisterEnum("FrustumPlane");
    engine->RegisterEnumValue("FrustumPlane", "PLANE_NEAR", PLANE_NEAR);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_LEFT", PLANE_LEFT);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_RIGHT", PLANE_RIGHT);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_UP", PLANE_UP);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_DOWN", PLANE_DOWN);
    engine->RegisterEnumValue("FrustumPlane", "PLANE_FAR", PLANE_FAR);

    // enum GeometryType | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("GeometryType");
    engine->RegisterEnumValue("GeometryType", "GEOM_STATIC", GEOM_STATIC);
    engine->RegisterEnumValue("GeometryType", "GEOM_SKINNED", GEOM_SKINNED);
    engine->RegisterEnumValue("GeometryType", "GEOM_INSTANCED", GEOM_INSTANCED);
    engine->RegisterEnumValue("GeometryType", "GEOM_BILLBOARD", GEOM_BILLBOARD);
    engine->RegisterEnumValue("GeometryType", "GEOM_DIRBILLBOARD", GEOM_DIRBILLBOARD);
    engine->RegisterEnumValue("GeometryType", "GEOM_TRAIL_FACE_CAMERA", GEOM_TRAIL_FACE_CAMERA);
    engine->RegisterEnumValue("GeometryType", "GEOM_TRAIL_BONE", GEOM_TRAIL_BONE);
    engine->RegisterEnumValue("GeometryType", "MAX_GEOMETRYTYPES", MAX_GEOMETRYTYPES);
    engine->RegisterEnumValue("GeometryType", "GEOM_STATIC_NOINSTANCING", GEOM_STATIC_NOINSTANCING);

    // enum HatPosition : unsigned | File: ../Input/InputConstants.h
    engine->RegisterTypedef("HatPosition", "uint");
    engine->RegisterGlobalProperty("const uint HAT_CENTER", (void*)&HatPosition_HAT_CENTER);
    engine->RegisterGlobalProperty("const uint HAT_UP", (void*)&HatPosition_HAT_UP);
    engine->RegisterGlobalProperty("const uint HAT_RIGHT", (void*)&HatPosition_HAT_RIGHT);
    engine->RegisterGlobalProperty("const uint HAT_DOWN", (void*)&HatPosition_HAT_DOWN);
    engine->RegisterGlobalProperty("const uint HAT_LEFT", (void*)&HatPosition_HAT_LEFT);

    // enum HighlightMode | File: ../UI/ListView.h
    engine->RegisterEnum("HighlightMode");
    engine->RegisterEnumValue("HighlightMode", "HM_NEVER", HM_NEVER);
    engine->RegisterEnumValue("HighlightMode", "HM_FOCUS", HM_FOCUS);
    engine->RegisterEnumValue("HighlightMode", "HM_ALWAYS", HM_ALWAYS);

    // enum HorizontalAlignment | File: ../UI/UIElement.h
    engine->RegisterEnum("HorizontalAlignment");
    engine->RegisterEnumValue("HorizontalAlignment", "HA_LEFT", HA_LEFT);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_CENTER", HA_CENTER);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_RIGHT", HA_RIGHT);
    engine->RegisterEnumValue("HorizontalAlignment", "HA_CUSTOM", HA_CUSTOM);

    // enum InterpMethod | File: ../Scene/ValueAnimation.h
    engine->RegisterEnum("InterpMethod");
    engine->RegisterEnumValue("InterpMethod", "IM_NONE", IM_NONE);
    engine->RegisterEnumValue("InterpMethod", "IM_LINEAR", IM_LINEAR);
    engine->RegisterEnumValue("InterpMethod", "IM_SPLINE", IM_SPLINE);

    // enum InterpolationMode | File: ../Core/Spline.h
    engine->RegisterEnum("InterpolationMode");
    engine->RegisterEnumValue("InterpolationMode", "BEZIER_CURVE", BEZIER_CURVE);
    engine->RegisterEnumValue("InterpolationMode", "CATMULL_ROM_CURVE", CATMULL_ROM_CURVE);
    engine->RegisterEnumValue("InterpolationMode", "LINEAR_CURVE", LINEAR_CURVE);
    engine->RegisterEnumValue("InterpolationMode", "CATMULL_ROM_FULL_CURVE", CATMULL_ROM_FULL_CURVE);

    // enum Intersection | File: ../Math/MathDefs.h
    engine->RegisterEnum("Intersection");
    engine->RegisterEnumValue("Intersection", "OUTSIDE", OUTSIDE);
    engine->RegisterEnumValue("Intersection", "INTERSECTS", INTERSECTS);
    engine->RegisterEnumValue("Intersection", "INSIDE", INSIDE);

    // enum JSONNumberType | File: ../Resource/JSONValue.h
    engine->RegisterEnum("JSONNumberType");
    engine->RegisterEnumValue("JSONNumberType", "JSONNT_NAN", JSONNT_NAN);
    engine->RegisterEnumValue("JSONNumberType", "JSONNT_INT", JSONNT_INT);
    engine->RegisterEnumValue("JSONNumberType", "JSONNT_UINT", JSONNT_UINT);
    engine->RegisterEnumValue("JSONNumberType", "JSONNT_FLOAT_DOUBLE", JSONNT_FLOAT_DOUBLE);

    // enum JSONValueType | File: ../Resource/JSONValue.h
    engine->RegisterEnum("JSONValueType");
    engine->RegisterEnumValue("JSONValueType", "JSON_NULL", JSON_NULL);
    engine->RegisterEnumValue("JSONValueType", "JSON_BOOL", JSON_BOOL);
    engine->RegisterEnumValue("JSONValueType", "JSON_NUMBER", JSON_NUMBER);
    engine->RegisterEnumValue("JSONValueType", "JSON_STRING", JSON_STRING);
    engine->RegisterEnumValue("JSONValueType", "JSON_ARRAY", JSON_ARRAY);
    engine->RegisterEnumValue("JSONValueType", "JSON_OBJECT", JSON_OBJECT);

    // enum Key : unsigned | File: ../Input/InputConstants.h
    engine->RegisterTypedef("Key", "uint");
    engine->RegisterGlobalProperty("const uint KEY_UNKNOWN", (void*)&Key_KEY_UNKNOWN);
    engine->RegisterGlobalProperty("const uint KEY_A", (void*)&Key_KEY_A);
    engine->RegisterGlobalProperty("const uint KEY_B", (void*)&Key_KEY_B);
    engine->RegisterGlobalProperty("const uint KEY_C", (void*)&Key_KEY_C);
    engine->RegisterGlobalProperty("const uint KEY_D", (void*)&Key_KEY_D);
    engine->RegisterGlobalProperty("const uint KEY_E", (void*)&Key_KEY_E);
    engine->RegisterGlobalProperty("const uint KEY_F", (void*)&Key_KEY_F);
    engine->RegisterGlobalProperty("const uint KEY_G", (void*)&Key_KEY_G);
    engine->RegisterGlobalProperty("const uint KEY_H", (void*)&Key_KEY_H);
    engine->RegisterGlobalProperty("const uint KEY_I", (void*)&Key_KEY_I);
    engine->RegisterGlobalProperty("const uint KEY_J", (void*)&Key_KEY_J);
    engine->RegisterGlobalProperty("const uint KEY_K", (void*)&Key_KEY_K);
    engine->RegisterGlobalProperty("const uint KEY_L", (void*)&Key_KEY_L);
    engine->RegisterGlobalProperty("const uint KEY_M", (void*)&Key_KEY_M);
    engine->RegisterGlobalProperty("const uint KEY_N", (void*)&Key_KEY_N);
    engine->RegisterGlobalProperty("const uint KEY_O", (void*)&Key_KEY_O);
    engine->RegisterGlobalProperty("const uint KEY_P", (void*)&Key_KEY_P);
    engine->RegisterGlobalProperty("const uint KEY_Q", (void*)&Key_KEY_Q);
    engine->RegisterGlobalProperty("const uint KEY_R", (void*)&Key_KEY_R);
    engine->RegisterGlobalProperty("const uint KEY_S", (void*)&Key_KEY_S);
    engine->RegisterGlobalProperty("const uint KEY_T", (void*)&Key_KEY_T);
    engine->RegisterGlobalProperty("const uint KEY_U", (void*)&Key_KEY_U);
    engine->RegisterGlobalProperty("const uint KEY_V", (void*)&Key_KEY_V);
    engine->RegisterGlobalProperty("const uint KEY_W", (void*)&Key_KEY_W);
    engine->RegisterGlobalProperty("const uint KEY_X", (void*)&Key_KEY_X);
    engine->RegisterGlobalProperty("const uint KEY_Y", (void*)&Key_KEY_Y);
    engine->RegisterGlobalProperty("const uint KEY_Z", (void*)&Key_KEY_Z);
    engine->RegisterGlobalProperty("const uint KEY_0", (void*)&Key_KEY_0);
    engine->RegisterGlobalProperty("const uint KEY_1", (void*)&Key_KEY_1);
    engine->RegisterGlobalProperty("const uint KEY_2", (void*)&Key_KEY_2);
    engine->RegisterGlobalProperty("const uint KEY_3", (void*)&Key_KEY_3);
    engine->RegisterGlobalProperty("const uint KEY_4", (void*)&Key_KEY_4);
    engine->RegisterGlobalProperty("const uint KEY_5", (void*)&Key_KEY_5);
    engine->RegisterGlobalProperty("const uint KEY_6", (void*)&Key_KEY_6);
    engine->RegisterGlobalProperty("const uint KEY_7", (void*)&Key_KEY_7);
    engine->RegisterGlobalProperty("const uint KEY_8", (void*)&Key_KEY_8);
    engine->RegisterGlobalProperty("const uint KEY_9", (void*)&Key_KEY_9);
    engine->RegisterGlobalProperty("const uint KEY_BACKSPACE", (void*)&Key_KEY_BACKSPACE);
    engine->RegisterGlobalProperty("const uint KEY_TAB", (void*)&Key_KEY_TAB);
    engine->RegisterGlobalProperty("const uint KEY_RETURN", (void*)&Key_KEY_RETURN);
    engine->RegisterGlobalProperty("const uint KEY_RETURN2", (void*)&Key_KEY_RETURN2);
    engine->RegisterGlobalProperty("const uint KEY_KP_ENTER", (void*)&Key_KEY_KP_ENTER);
    engine->RegisterGlobalProperty("const uint KEY_SHIFT", (void*)&Key_KEY_SHIFT);
    engine->RegisterGlobalProperty("const uint KEY_CTRL", (void*)&Key_KEY_CTRL);
    engine->RegisterGlobalProperty("const uint KEY_ALT", (void*)&Key_KEY_ALT);
    engine->RegisterGlobalProperty("const uint KEY_GUI", (void*)&Key_KEY_GUI);
    engine->RegisterGlobalProperty("const uint KEY_PAUSE", (void*)&Key_KEY_PAUSE);
    engine->RegisterGlobalProperty("const uint KEY_CAPSLOCK", (void*)&Key_KEY_CAPSLOCK);
    engine->RegisterGlobalProperty("const uint KEY_ESCAPE", (void*)&Key_KEY_ESCAPE);
    engine->RegisterGlobalProperty("const uint KEY_SPACE", (void*)&Key_KEY_SPACE);
    engine->RegisterGlobalProperty("const uint KEY_PAGEUP", (void*)&Key_KEY_PAGEUP);
    engine->RegisterGlobalProperty("const uint KEY_PAGEDOWN", (void*)&Key_KEY_PAGEDOWN);
    engine->RegisterGlobalProperty("const uint KEY_END", (void*)&Key_KEY_END);
    engine->RegisterGlobalProperty("const uint KEY_HOME", (void*)&Key_KEY_HOME);
    engine->RegisterGlobalProperty("const uint KEY_LEFT", (void*)&Key_KEY_LEFT);
    engine->RegisterGlobalProperty("const uint KEY_UP", (void*)&Key_KEY_UP);
    engine->RegisterGlobalProperty("const uint KEY_RIGHT", (void*)&Key_KEY_RIGHT);
    engine->RegisterGlobalProperty("const uint KEY_DOWN", (void*)&Key_KEY_DOWN);
    engine->RegisterGlobalProperty("const uint KEY_SELECT", (void*)&Key_KEY_SELECT);
    engine->RegisterGlobalProperty("const uint KEY_PRINTSCREEN", (void*)&Key_KEY_PRINTSCREEN);
    engine->RegisterGlobalProperty("const uint KEY_INSERT", (void*)&Key_KEY_INSERT);
    engine->RegisterGlobalProperty("const uint KEY_DELETE", (void*)&Key_KEY_DELETE);
    engine->RegisterGlobalProperty("const uint KEY_LGUI", (void*)&Key_KEY_LGUI);
    engine->RegisterGlobalProperty("const uint KEY_RGUI", (void*)&Key_KEY_RGUI);
    engine->RegisterGlobalProperty("const uint KEY_APPLICATION", (void*)&Key_KEY_APPLICATION);
    engine->RegisterGlobalProperty("const uint KEY_KP_0", (void*)&Key_KEY_KP_0);
    engine->RegisterGlobalProperty("const uint KEY_KP_1", (void*)&Key_KEY_KP_1);
    engine->RegisterGlobalProperty("const uint KEY_KP_2", (void*)&Key_KEY_KP_2);
    engine->RegisterGlobalProperty("const uint KEY_KP_3", (void*)&Key_KEY_KP_3);
    engine->RegisterGlobalProperty("const uint KEY_KP_4", (void*)&Key_KEY_KP_4);
    engine->RegisterGlobalProperty("const uint KEY_KP_5", (void*)&Key_KEY_KP_5);
    engine->RegisterGlobalProperty("const uint KEY_KP_6", (void*)&Key_KEY_KP_6);
    engine->RegisterGlobalProperty("const uint KEY_KP_7", (void*)&Key_KEY_KP_7);
    engine->RegisterGlobalProperty("const uint KEY_KP_8", (void*)&Key_KEY_KP_8);
    engine->RegisterGlobalProperty("const uint KEY_KP_9", (void*)&Key_KEY_KP_9);
    engine->RegisterGlobalProperty("const uint KEY_KP_MULTIPLY", (void*)&Key_KEY_KP_MULTIPLY);
    engine->RegisterGlobalProperty("const uint KEY_KP_PLUS", (void*)&Key_KEY_KP_PLUS);
    engine->RegisterGlobalProperty("const uint KEY_KP_MINUS", (void*)&Key_KEY_KP_MINUS);
    engine->RegisterGlobalProperty("const uint KEY_KP_PERIOD", (void*)&Key_KEY_KP_PERIOD);
    engine->RegisterGlobalProperty("const uint KEY_KP_DIVIDE", (void*)&Key_KEY_KP_DIVIDE);
    engine->RegisterGlobalProperty("const uint KEY_F1", (void*)&Key_KEY_F1);
    engine->RegisterGlobalProperty("const uint KEY_F2", (void*)&Key_KEY_F2);
    engine->RegisterGlobalProperty("const uint KEY_F3", (void*)&Key_KEY_F3);
    engine->RegisterGlobalProperty("const uint KEY_F4", (void*)&Key_KEY_F4);
    engine->RegisterGlobalProperty("const uint KEY_F5", (void*)&Key_KEY_F5);
    engine->RegisterGlobalProperty("const uint KEY_F6", (void*)&Key_KEY_F6);
    engine->RegisterGlobalProperty("const uint KEY_F7", (void*)&Key_KEY_F7);
    engine->RegisterGlobalProperty("const uint KEY_F8", (void*)&Key_KEY_F8);
    engine->RegisterGlobalProperty("const uint KEY_F9", (void*)&Key_KEY_F9);
    engine->RegisterGlobalProperty("const uint KEY_F10", (void*)&Key_KEY_F10);
    engine->RegisterGlobalProperty("const uint KEY_F11", (void*)&Key_KEY_F11);
    engine->RegisterGlobalProperty("const uint KEY_F12", (void*)&Key_KEY_F12);
    engine->RegisterGlobalProperty("const uint KEY_F13", (void*)&Key_KEY_F13);
    engine->RegisterGlobalProperty("const uint KEY_F14", (void*)&Key_KEY_F14);
    engine->RegisterGlobalProperty("const uint KEY_F15", (void*)&Key_KEY_F15);
    engine->RegisterGlobalProperty("const uint KEY_F16", (void*)&Key_KEY_F16);
    engine->RegisterGlobalProperty("const uint KEY_F17", (void*)&Key_KEY_F17);
    engine->RegisterGlobalProperty("const uint KEY_F18", (void*)&Key_KEY_F18);
    engine->RegisterGlobalProperty("const uint KEY_F19", (void*)&Key_KEY_F19);
    engine->RegisterGlobalProperty("const uint KEY_F20", (void*)&Key_KEY_F20);
    engine->RegisterGlobalProperty("const uint KEY_F21", (void*)&Key_KEY_F21);
    engine->RegisterGlobalProperty("const uint KEY_F22", (void*)&Key_KEY_F22);
    engine->RegisterGlobalProperty("const uint KEY_F23", (void*)&Key_KEY_F23);
    engine->RegisterGlobalProperty("const uint KEY_F24", (void*)&Key_KEY_F24);
    engine->RegisterGlobalProperty("const uint KEY_NUMLOCKCLEAR", (void*)&Key_KEY_NUMLOCKCLEAR);
    engine->RegisterGlobalProperty("const uint KEY_SCROLLLOCK", (void*)&Key_KEY_SCROLLLOCK);
    engine->RegisterGlobalProperty("const uint KEY_LSHIFT", (void*)&Key_KEY_LSHIFT);
    engine->RegisterGlobalProperty("const uint KEY_RSHIFT", (void*)&Key_KEY_RSHIFT);
    engine->RegisterGlobalProperty("const uint KEY_LCTRL", (void*)&Key_KEY_LCTRL);
    engine->RegisterGlobalProperty("const uint KEY_RCTRL", (void*)&Key_KEY_RCTRL);
    engine->RegisterGlobalProperty("const uint KEY_LALT", (void*)&Key_KEY_LALT);
    engine->RegisterGlobalProperty("const uint KEY_RALT", (void*)&Key_KEY_RALT);
    engine->RegisterGlobalProperty("const uint KEY_AC_BACK", (void*)&Key_KEY_AC_BACK);
    engine->RegisterGlobalProperty("const uint KEY_AC_BOOKMARKS", (void*)&Key_KEY_AC_BOOKMARKS);
    engine->RegisterGlobalProperty("const uint KEY_AC_FORWARD", (void*)&Key_KEY_AC_FORWARD);
    engine->RegisterGlobalProperty("const uint KEY_AC_HOME", (void*)&Key_KEY_AC_HOME);
    engine->RegisterGlobalProperty("const uint KEY_AC_REFRESH", (void*)&Key_KEY_AC_REFRESH);
    engine->RegisterGlobalProperty("const uint KEY_AC_SEARCH", (void*)&Key_KEY_AC_SEARCH);
    engine->RegisterGlobalProperty("const uint KEY_AC_STOP", (void*)&Key_KEY_AC_STOP);
    engine->RegisterGlobalProperty("const uint KEY_AGAIN", (void*)&Key_KEY_AGAIN);
    engine->RegisterGlobalProperty("const uint KEY_ALTERASE", (void*)&Key_KEY_ALTERASE);
    engine->RegisterGlobalProperty("const uint KEY_AMPERSAND", (void*)&Key_KEY_AMPERSAND);
    engine->RegisterGlobalProperty("const uint KEY_ASTERISK", (void*)&Key_KEY_ASTERISK);
    engine->RegisterGlobalProperty("const uint KEY_AT", (void*)&Key_KEY_AT);
    engine->RegisterGlobalProperty("const uint KEY_AUDIOMUTE", (void*)&Key_KEY_AUDIOMUTE);
    engine->RegisterGlobalProperty("const uint KEY_AUDIONEXT", (void*)&Key_KEY_AUDIONEXT);
    engine->RegisterGlobalProperty("const uint KEY_AUDIOPLAY", (void*)&Key_KEY_AUDIOPLAY);
    engine->RegisterGlobalProperty("const uint KEY_AUDIOPREV", (void*)&Key_KEY_AUDIOPREV);
    engine->RegisterGlobalProperty("const uint KEY_AUDIOSTOP", (void*)&Key_KEY_AUDIOSTOP);
    engine->RegisterGlobalProperty("const uint KEY_BACKQUOTE", (void*)&Key_KEY_BACKQUOTE);
    engine->RegisterGlobalProperty("const uint KEY_BACKSLASH", (void*)&Key_KEY_BACKSLASH);
    engine->RegisterGlobalProperty("const uint KEY_BRIGHTNESSDOWN", (void*)&Key_KEY_BRIGHTNESSDOWN);
    engine->RegisterGlobalProperty("const uint KEY_BRIGHTNESSUP", (void*)&Key_KEY_BRIGHTNESSUP);
    engine->RegisterGlobalProperty("const uint KEY_CALCULATOR", (void*)&Key_KEY_CALCULATOR);
    engine->RegisterGlobalProperty("const uint KEY_CANCEL", (void*)&Key_KEY_CANCEL);
    engine->RegisterGlobalProperty("const uint KEY_CARET", (void*)&Key_KEY_CARET);
    engine->RegisterGlobalProperty("const uint KEY_CLEAR", (void*)&Key_KEY_CLEAR);
    engine->RegisterGlobalProperty("const uint KEY_CLEARAGAIN", (void*)&Key_KEY_CLEARAGAIN);
    engine->RegisterGlobalProperty("const uint KEY_COLON", (void*)&Key_KEY_COLON);
    engine->RegisterGlobalProperty("const uint KEY_COMMA", (void*)&Key_KEY_COMMA);
    engine->RegisterGlobalProperty("const uint KEY_COMPUTER", (void*)&Key_KEY_COMPUTER);
    engine->RegisterGlobalProperty("const uint KEY_COPY", (void*)&Key_KEY_COPY);
    engine->RegisterGlobalProperty("const uint KEY_CRSEL", (void*)&Key_KEY_CRSEL);
    engine->RegisterGlobalProperty("const uint KEY_CURRENCYSUBUNIT", (void*)&Key_KEY_CURRENCYSUBUNIT);
    engine->RegisterGlobalProperty("const uint KEY_CURRENCYUNIT", (void*)&Key_KEY_CURRENCYUNIT);
    engine->RegisterGlobalProperty("const uint KEY_CUT", (void*)&Key_KEY_CUT);
    engine->RegisterGlobalProperty("const uint KEY_DECIMALSEPARATOR", (void*)&Key_KEY_DECIMALSEPARATOR);
    engine->RegisterGlobalProperty("const uint KEY_DISPLAYSWITCH", (void*)&Key_KEY_DISPLAYSWITCH);
    engine->RegisterGlobalProperty("const uint KEY_DOLLAR", (void*)&Key_KEY_DOLLAR);
    engine->RegisterGlobalProperty("const uint KEY_EJECT", (void*)&Key_KEY_EJECT);
    engine->RegisterGlobalProperty("const uint KEY_EQUALS", (void*)&Key_KEY_EQUALS);
    engine->RegisterGlobalProperty("const uint KEY_EXCLAIM", (void*)&Key_KEY_EXCLAIM);
    engine->RegisterGlobalProperty("const uint KEY_EXSEL", (void*)&Key_KEY_EXSEL);
    engine->RegisterGlobalProperty("const uint KEY_FIND", (void*)&Key_KEY_FIND);
    engine->RegisterGlobalProperty("const uint KEY_GREATER", (void*)&Key_KEY_GREATER);
    engine->RegisterGlobalProperty("const uint KEY_HASH", (void*)&Key_KEY_HASH);
    engine->RegisterGlobalProperty("const uint KEY_HELP", (void*)&Key_KEY_HELP);
    engine->RegisterGlobalProperty("const uint KEY_KBDILLUMDOWN", (void*)&Key_KEY_KBDILLUMDOWN);
    engine->RegisterGlobalProperty("const uint KEY_KBDILLUMTOGGLE", (void*)&Key_KEY_KBDILLUMTOGGLE);
    engine->RegisterGlobalProperty("const uint KEY_KBDILLUMUP", (void*)&Key_KEY_KBDILLUMUP);
    engine->RegisterGlobalProperty("const uint KEY_KP_00", (void*)&Key_KEY_KP_00);
    engine->RegisterGlobalProperty("const uint KEY_KP_000", (void*)&Key_KEY_KP_000);
    engine->RegisterGlobalProperty("const uint KEY_KP_A", (void*)&Key_KEY_KP_A);
    engine->RegisterGlobalProperty("const uint KEY_KP_AMPERSAND", (void*)&Key_KEY_KP_AMPERSAND);
    engine->RegisterGlobalProperty("const uint KEY_KP_AT", (void*)&Key_KEY_KP_AT);
    engine->RegisterGlobalProperty("const uint KEY_KP_B", (void*)&Key_KEY_KP_B);
    engine->RegisterGlobalProperty("const uint KEY_KP_BACKSPACE", (void*)&Key_KEY_KP_BACKSPACE);
    engine->RegisterGlobalProperty("const uint KEY_KP_BINARY", (void*)&Key_KEY_KP_BINARY);
    engine->RegisterGlobalProperty("const uint KEY_KP_C", (void*)&Key_KEY_KP_C);
    engine->RegisterGlobalProperty("const uint KEY_KP_CLEAR", (void*)&Key_KEY_KP_CLEAR);
    engine->RegisterGlobalProperty("const uint KEY_KP_CLEARENTRY", (void*)&Key_KEY_KP_CLEARENTRY);
    engine->RegisterGlobalProperty("const uint KEY_KP_COLON", (void*)&Key_KEY_KP_COLON);
    engine->RegisterGlobalProperty("const uint KEY_KP_COMMA", (void*)&Key_KEY_KP_COMMA);
    engine->RegisterGlobalProperty("const uint KEY_KP_D", (void*)&Key_KEY_KP_D);
    engine->RegisterGlobalProperty("const uint KEY_KP_DBLAMPERSAND", (void*)&Key_KEY_KP_DBLAMPERSAND);
    engine->RegisterGlobalProperty("const uint KEY_KP_DBLVERTICALBAR", (void*)&Key_KEY_KP_DBLVERTICALBAR);
    engine->RegisterGlobalProperty("const uint KEY_KP_DECIMAL", (void*)&Key_KEY_KP_DECIMAL);
    engine->RegisterGlobalProperty("const uint KEY_KP_E", (void*)&Key_KEY_KP_E);
    engine->RegisterGlobalProperty("const uint KEY_KP_EQUALS", (void*)&Key_KEY_KP_EQUALS);
    engine->RegisterGlobalProperty("const uint KEY_KP_EQUALSAS400", (void*)&Key_KEY_KP_EQUALSAS400);
    engine->RegisterGlobalProperty("const uint KEY_KP_EXCLAM", (void*)&Key_KEY_KP_EXCLAM);
    engine->RegisterGlobalProperty("const uint KEY_KP_F", (void*)&Key_KEY_KP_F);
    engine->RegisterGlobalProperty("const uint KEY_KP_GREATER", (void*)&Key_KEY_KP_GREATER);
    engine->RegisterGlobalProperty("const uint KEY_KP_HASH", (void*)&Key_KEY_KP_HASH);
    engine->RegisterGlobalProperty("const uint KEY_KP_HEXADECIMAL", (void*)&Key_KEY_KP_HEXADECIMAL);
    engine->RegisterGlobalProperty("const uint KEY_KP_LEFTBRACE", (void*)&Key_KEY_KP_LEFTBRACE);
    engine->RegisterGlobalProperty("const uint KEY_KP_LEFTPAREN", (void*)&Key_KEY_KP_LEFTPAREN);
    engine->RegisterGlobalProperty("const uint KEY_KP_LESS", (void*)&Key_KEY_KP_LESS);
    engine->RegisterGlobalProperty("const uint KEY_KP_MEMADD", (void*)&Key_KEY_KP_MEMADD);
    engine->RegisterGlobalProperty("const uint KEY_KP_MEMCLEAR", (void*)&Key_KEY_KP_MEMCLEAR);
    engine->RegisterGlobalProperty("const uint KEY_KP_MEMDIVIDE", (void*)&Key_KEY_KP_MEMDIVIDE);
    engine->RegisterGlobalProperty("const uint KEY_KP_MEMMULTIPLY", (void*)&Key_KEY_KP_MEMMULTIPLY);
    engine->RegisterGlobalProperty("const uint KEY_KP_MEMRECALL", (void*)&Key_KEY_KP_MEMRECALL);
    engine->RegisterGlobalProperty("const uint KEY_KP_MEMSTORE", (void*)&Key_KEY_KP_MEMSTORE);
    engine->RegisterGlobalProperty("const uint KEY_KP_MEMSUBTRACT", (void*)&Key_KEY_KP_MEMSUBTRACT);
    engine->RegisterGlobalProperty("const uint KEY_KP_OCTAL", (void*)&Key_KEY_KP_OCTAL);
    engine->RegisterGlobalProperty("const uint KEY_KP_PERCENT", (void*)&Key_KEY_KP_PERCENT);
    engine->RegisterGlobalProperty("const uint KEY_KP_PLUSMINUS", (void*)&Key_KEY_KP_PLUSMINUS);
    engine->RegisterGlobalProperty("const uint KEY_KP_POWER", (void*)&Key_KEY_KP_POWER);
    engine->RegisterGlobalProperty("const uint KEY_KP_RIGHTBRACE", (void*)&Key_KEY_KP_RIGHTBRACE);
    engine->RegisterGlobalProperty("const uint KEY_KP_RIGHTPAREN", (void*)&Key_KEY_KP_RIGHTPAREN);
    engine->RegisterGlobalProperty("const uint KEY_KP_SPACE", (void*)&Key_KEY_KP_SPACE);
    engine->RegisterGlobalProperty("const uint KEY_KP_TAB", (void*)&Key_KEY_KP_TAB);
    engine->RegisterGlobalProperty("const uint KEY_KP_VERTICALBAR", (void*)&Key_KEY_KP_VERTICALBAR);
    engine->RegisterGlobalProperty("const uint KEY_KP_XOR", (void*)&Key_KEY_KP_XOR);
    engine->RegisterGlobalProperty("const uint KEY_LEFTBRACKET", (void*)&Key_KEY_LEFTBRACKET);
    engine->RegisterGlobalProperty("const uint KEY_LEFTPAREN", (void*)&Key_KEY_LEFTPAREN);
    engine->RegisterGlobalProperty("const uint KEY_LESS", (void*)&Key_KEY_LESS);
    engine->RegisterGlobalProperty("const uint KEY_MAIL", (void*)&Key_KEY_MAIL);
    engine->RegisterGlobalProperty("const uint KEY_MEDIASELECT", (void*)&Key_KEY_MEDIASELECT);
    engine->RegisterGlobalProperty("const uint KEY_MENU", (void*)&Key_KEY_MENU);
    engine->RegisterGlobalProperty("const uint KEY_MINUS", (void*)&Key_KEY_MINUS);
    engine->RegisterGlobalProperty("const uint KEY_MODE", (void*)&Key_KEY_MODE);
    engine->RegisterGlobalProperty("const uint KEY_MUTE", (void*)&Key_KEY_MUTE);
    engine->RegisterGlobalProperty("const uint KEY_OPER", (void*)&Key_KEY_OPER);
    engine->RegisterGlobalProperty("const uint KEY_OUT", (void*)&Key_KEY_OUT);
    engine->RegisterGlobalProperty("const uint KEY_PASTE", (void*)&Key_KEY_PASTE);
    engine->RegisterGlobalProperty("const uint KEY_PERCENT", (void*)&Key_KEY_PERCENT);
    engine->RegisterGlobalProperty("const uint KEY_PERIOD", (void*)&Key_KEY_PERIOD);
    engine->RegisterGlobalProperty("const uint KEY_PLUS", (void*)&Key_KEY_PLUS);
    engine->RegisterGlobalProperty("const uint KEY_POWER", (void*)&Key_KEY_POWER);
    engine->RegisterGlobalProperty("const uint KEY_PRIOR", (void*)&Key_KEY_PRIOR);
    engine->RegisterGlobalProperty("const uint KEY_QUESTION", (void*)&Key_KEY_QUESTION);
    engine->RegisterGlobalProperty("const uint KEY_QUOTE", (void*)&Key_KEY_QUOTE);
    engine->RegisterGlobalProperty("const uint KEY_QUOTEDBL", (void*)&Key_KEY_QUOTEDBL);
    engine->RegisterGlobalProperty("const uint KEY_RIGHTBRACKET", (void*)&Key_KEY_RIGHTBRACKET);
    engine->RegisterGlobalProperty("const uint KEY_RIGHTPAREN", (void*)&Key_KEY_RIGHTPAREN);
    engine->RegisterGlobalProperty("const uint KEY_SEMICOLON", (void*)&Key_KEY_SEMICOLON);
    engine->RegisterGlobalProperty("const uint KEY_SEPARATOR", (void*)&Key_KEY_SEPARATOR);
    engine->RegisterGlobalProperty("const uint KEY_SLASH", (void*)&Key_KEY_SLASH);
    engine->RegisterGlobalProperty("const uint KEY_SLEEP", (void*)&Key_KEY_SLEEP);
    engine->RegisterGlobalProperty("const uint KEY_STOP", (void*)&Key_KEY_STOP);
    engine->RegisterGlobalProperty("const uint KEY_SYSREQ", (void*)&Key_KEY_SYSREQ);
    engine->RegisterGlobalProperty("const uint KEY_THOUSANDSSEPARATOR", (void*)&Key_KEY_THOUSANDSSEPARATOR);
    engine->RegisterGlobalProperty("const uint KEY_UNDERSCORE", (void*)&Key_KEY_UNDERSCORE);
    engine->RegisterGlobalProperty("const uint KEY_UNDO", (void*)&Key_KEY_UNDO);
    engine->RegisterGlobalProperty("const uint KEY_VOLUMEDOWN", (void*)&Key_KEY_VOLUMEDOWN);
    engine->RegisterGlobalProperty("const uint KEY_VOLUMEUP", (void*)&Key_KEY_VOLUMEUP);
    engine->RegisterGlobalProperty("const uint KEY_WWW", (void*)&Key_KEY_WWW);

    // enum LayoutMode | File: ../UI/UIElement.h
    engine->RegisterEnum("LayoutMode");
    engine->RegisterEnumValue("LayoutMode", "LM_FREE", LM_FREE);
    engine->RegisterEnumValue("LayoutMode", "LM_HORIZONTAL", LM_HORIZONTAL);
    engine->RegisterEnumValue("LayoutMode", "LM_VERTICAL", LM_VERTICAL);

    // enum LegacyVertexElement | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("LegacyVertexElement");
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_POSITION", ELEMENT_POSITION);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_NORMAL", ELEMENT_NORMAL);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_COLOR", ELEMENT_COLOR);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_TEXCOORD1", ELEMENT_TEXCOORD1);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_TEXCOORD2", ELEMENT_TEXCOORD2);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_CUBETEXCOORD1", ELEMENT_CUBETEXCOORD1);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_CUBETEXCOORD2", ELEMENT_CUBETEXCOORD2);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_TANGENT", ELEMENT_TANGENT);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_BLENDWEIGHTS", ELEMENT_BLENDWEIGHTS);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_BLENDINDICES", ELEMENT_BLENDINDICES);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_INSTANCEMATRIX1", ELEMENT_INSTANCEMATRIX1);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_INSTANCEMATRIX2", ELEMENT_INSTANCEMATRIX2);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_INSTANCEMATRIX3", ELEMENT_INSTANCEMATRIX3);
    engine->RegisterEnumValue("LegacyVertexElement", "ELEMENT_OBJECTINDEX", ELEMENT_OBJECTINDEX);
    engine->RegisterEnumValue("LegacyVertexElement", "MAX_LEGACY_VERTEX_ELEMENTS", MAX_LEGACY_VERTEX_ELEMENTS);

    // enum LightPSVariation | File: ../Graphics/Renderer.h
    engine->RegisterEnum("LightPSVariation");
    engine->RegisterEnumValue("LightPSVariation", "LPS_NONE", LPS_NONE);
    engine->RegisterEnumValue("LightPSVariation", "LPS_SPOT", LPS_SPOT);
    engine->RegisterEnumValue("LightPSVariation", "LPS_POINT", LPS_POINT);
    engine->RegisterEnumValue("LightPSVariation", "LPS_POINTMASK", LPS_POINTMASK);
    engine->RegisterEnumValue("LightPSVariation", "LPS_SPEC", LPS_SPEC);
    engine->RegisterEnumValue("LightPSVariation", "LPS_SPOTSPEC", LPS_SPOTSPEC);
    engine->RegisterEnumValue("LightPSVariation", "LPS_POINTSPEC", LPS_POINTSPEC);
    engine->RegisterEnumValue("LightPSVariation", "LPS_POINTMASKSPEC", LPS_POINTMASKSPEC);
    engine->RegisterEnumValue("LightPSVariation", "LPS_SHADOW", LPS_SHADOW);
    engine->RegisterEnumValue("LightPSVariation", "LPS_SPOTSHADOW", LPS_SPOTSHADOW);
    engine->RegisterEnumValue("LightPSVariation", "LPS_POINTSHADOW", LPS_POINTSHADOW);
    engine->RegisterEnumValue("LightPSVariation", "LPS_POINTMASKSHADOW", LPS_POINTMASKSHADOW);
    engine->RegisterEnumValue("LightPSVariation", "LPS_SHADOWSPEC", LPS_SHADOWSPEC);
    engine->RegisterEnumValue("LightPSVariation", "LPS_SPOTSHADOWSPEC", LPS_SPOTSHADOWSPEC);
    engine->RegisterEnumValue("LightPSVariation", "LPS_POINTSHADOWSPEC", LPS_POINTSHADOWSPEC);
    engine->RegisterEnumValue("LightPSVariation", "LPS_POINTMASKSHADOWSPEC", LPS_POINTMASKSHADOWSPEC);
    engine->RegisterEnumValue("LightPSVariation", "MAX_LIGHT_PS_VARIATIONS", MAX_LIGHT_PS_VARIATIONS);

    // enum LightType | File: ../Graphics/Light.h
    engine->RegisterEnum("LightType");
    engine->RegisterEnumValue("LightType", "LIGHT_DIRECTIONAL", LIGHT_DIRECTIONAL);
    engine->RegisterEnumValue("LightType", "LIGHT_SPOT", LIGHT_SPOT);
    engine->RegisterEnumValue("LightType", "LIGHT_POINT", LIGHT_POINT);

    // enum LightVSVariation | File: ../Graphics/Renderer.h
    engine->RegisterEnum("LightVSVariation");
    engine->RegisterEnumValue("LightVSVariation", "LVS_DIR", LVS_DIR);
    engine->RegisterEnumValue("LightVSVariation", "LVS_SPOT", LVS_SPOT);
    engine->RegisterEnumValue("LightVSVariation", "LVS_POINT", LVS_POINT);
    engine->RegisterEnumValue("LightVSVariation", "LVS_SHADOW", LVS_SHADOW);
    engine->RegisterEnumValue("LightVSVariation", "LVS_SPOTSHADOW", LVS_SPOTSHADOW);
    engine->RegisterEnumValue("LightVSVariation", "LVS_POINTSHADOW", LVS_POINTSHADOW);
    engine->RegisterEnumValue("LightVSVariation", "LVS_SHADOWNORMALOFFSET", LVS_SHADOWNORMALOFFSET);
    engine->RegisterEnumValue("LightVSVariation", "LVS_SPOTSHADOWNORMALOFFSET", LVS_SPOTSHADOWNORMALOFFSET);
    engine->RegisterEnumValue("LightVSVariation", "LVS_POINTSHADOWNORMALOFFSET", LVS_POINTSHADOWNORMALOFFSET);
    engine->RegisterEnumValue("LightVSVariation", "MAX_LIGHT_VS_VARIATIONS", MAX_LIGHT_VS_VARIATIONS);

    // enum LoadMode | File: ../Scene/Scene.h
    engine->RegisterEnum("LoadMode");
    engine->RegisterEnumValue("LoadMode", "LOAD_RESOURCES_ONLY", LOAD_RESOURCES_ONLY);
    engine->RegisterEnumValue("LoadMode", "LOAD_SCENE", LOAD_SCENE);
    engine->RegisterEnumValue("LoadMode", "LOAD_SCENE_AND_RESOURCES", LOAD_SCENE_AND_RESOURCES);

    // enum LockState | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("LockState");
    engine->RegisterEnumValue("LockState", "LOCK_NONE", LOCK_NONE);
    engine->RegisterEnumValue("LockState", "LOCK_HARDWARE", LOCK_HARDWARE);
    engine->RegisterEnumValue("LockState", "LOCK_SHADOW", LOCK_SHADOW);
    engine->RegisterEnumValue("LockState", "LOCK_SCRATCH", LOCK_SCRATCH);

    // enum MaterialQuality : unsigned | File: ../Graphics/GraphicsDefs.h
    engine->RegisterTypedef("MaterialQuality", "uint");
    engine->RegisterGlobalProperty("const uint QUALITY_LOW", (void*)&MaterialQuality_QUALITY_LOW);
    engine->RegisterGlobalProperty("const uint QUALITY_MEDIUM", (void*)&MaterialQuality_QUALITY_MEDIUM);
    engine->RegisterGlobalProperty("const uint QUALITY_HIGH", (void*)&MaterialQuality_QUALITY_HIGH);
    engine->RegisterGlobalProperty("const uint QUALITY_MAX", (void*)&MaterialQuality_QUALITY_MAX);

    // enum MouseButton : unsigned | File: ../Input/InputConstants.h
    engine->RegisterTypedef("MouseButton", "uint");
    engine->RegisterGlobalProperty("const uint MOUSEB_NONE", (void*)&MouseButton_MOUSEB_NONE);
    engine->RegisterGlobalProperty("const uint MOUSEB_LEFT", (void*)&MouseButton_MOUSEB_LEFT);
    engine->RegisterGlobalProperty("const uint MOUSEB_MIDDLE", (void*)&MouseButton_MOUSEB_MIDDLE);
    engine->RegisterGlobalProperty("const uint MOUSEB_RIGHT", (void*)&MouseButton_MOUSEB_RIGHT);
    engine->RegisterGlobalProperty("const uint MOUSEB_X1", (void*)&MouseButton_MOUSEB_X1);
    engine->RegisterGlobalProperty("const uint MOUSEB_X2", (void*)&MouseButton_MOUSEB_X2);
    engine->RegisterGlobalProperty("const uint MOUSEB_ANY", (void*)&MouseButton_MOUSEB_ANY);

    // URHO3D_FLAGSET(MouseButton, MouseButtonFlags) | File: ../Input/InputConstants.h
    engine->RegisterTypedef("MouseButtonFlags", "uint");

    // enum MouseMode | File: ../Input/Input.h
    engine->RegisterEnum("MouseMode");
    engine->RegisterEnumValue("MouseMode", "MM_ABSOLUTE", MM_ABSOLUTE);
    engine->RegisterEnumValue("MouseMode", "MM_RELATIVE", MM_RELATIVE);
    engine->RegisterEnumValue("MouseMode", "MM_WRAP", MM_WRAP);
    engine->RegisterEnumValue("MouseMode", "MM_FREE", MM_FREE);
    engine->RegisterEnumValue("MouseMode", "MM_INVALID", MM_INVALID);

    // enum Orientation | File: ../UI/UIElement.h
    engine->RegisterEnum("Orientation");
    engine->RegisterEnumValue("Orientation", "O_HORIZONTAL", O_HORIZONTAL);
    engine->RegisterEnumValue("Orientation", "O_VERTICAL", O_VERTICAL);

    // enum PassLightingMode | File: ../Graphics/Technique.h
    engine->RegisterEnum("PassLightingMode");
    engine->RegisterEnumValue("PassLightingMode", "LIGHTING_UNLIT", LIGHTING_UNLIT);
    engine->RegisterEnumValue("PassLightingMode", "LIGHTING_PERVERTEX", LIGHTING_PERVERTEX);
    engine->RegisterEnumValue("PassLightingMode", "LIGHTING_PERPIXEL", LIGHTING_PERPIXEL);

    // enum PrimitiveType | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("PrimitiveType");
    engine->RegisterEnumValue("PrimitiveType", "TRIANGLE_LIST", TRIANGLE_LIST);
    engine->RegisterEnumValue("PrimitiveType", "LINE_LIST", LINE_LIST);
    engine->RegisterEnumValue("PrimitiveType", "POINT_LIST", POINT_LIST);
    engine->RegisterEnumValue("PrimitiveType", "TRIANGLE_STRIP", TRIANGLE_STRIP);
    engine->RegisterEnumValue("PrimitiveType", "LINE_STRIP", LINE_STRIP);
    engine->RegisterEnumValue("PrimitiveType", "TRIANGLE_FAN", TRIANGLE_FAN);

    // enum Qualifier : unsigned | File: ../Input/InputConstants.h
    engine->RegisterTypedef("Qualifier", "uint");
    engine->RegisterGlobalProperty("const uint QUAL_NONE", (void*)&Qualifier_QUAL_NONE);
    engine->RegisterGlobalProperty("const uint QUAL_SHIFT", (void*)&Qualifier_QUAL_SHIFT);
    engine->RegisterGlobalProperty("const uint QUAL_CTRL", (void*)&Qualifier_QUAL_CTRL);
    engine->RegisterGlobalProperty("const uint QUAL_ALT", (void*)&Qualifier_QUAL_ALT);
    engine->RegisterGlobalProperty("const uint QUAL_ANY", (void*)&Qualifier_QUAL_ANY);

    // URHO3D_FLAGSET(Qualifier, QualifierFlags) | File: ../Input/InputConstants.h
    engine->RegisterTypedef("QualifierFlags", "uint");

    // enum RayQueryLevel | File: ../Graphics/OctreeQuery.h
    engine->RegisterEnum("RayQueryLevel");
    engine->RegisterEnumValue("RayQueryLevel", "RAY_AABB", RAY_AABB);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_OBB", RAY_OBB);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_TRIANGLE", RAY_TRIANGLE);
    engine->RegisterEnumValue("RayQueryLevel", "RAY_TRIANGLE_UV", RAY_TRIANGLE_UV);

    // enum RenderCommandSortMode | File: ../Graphics/RenderPath.h
    engine->RegisterEnum("RenderCommandSortMode");
    engine->RegisterEnumValue("RenderCommandSortMode", "SORT_FRONTTOBACK", SORT_FRONTTOBACK);
    engine->RegisterEnumValue("RenderCommandSortMode", "SORT_BACKTOFRONT", SORT_BACKTOFRONT);

    // enum RenderCommandType | File: ../Graphics/RenderPath.h
    engine->RegisterEnum("RenderCommandType");
    engine->RegisterEnumValue("RenderCommandType", "CMD_NONE", CMD_NONE);
    engine->RegisterEnumValue("RenderCommandType", "CMD_CLEAR", CMD_CLEAR);
    engine->RegisterEnumValue("RenderCommandType", "CMD_SCENEPASS", CMD_SCENEPASS);
    engine->RegisterEnumValue("RenderCommandType", "CMD_QUAD", CMD_QUAD);
    engine->RegisterEnumValue("RenderCommandType", "CMD_FORWARDLIGHTS", CMD_FORWARDLIGHTS);
    engine->RegisterEnumValue("RenderCommandType", "CMD_LIGHTVOLUMES", CMD_LIGHTVOLUMES);
    engine->RegisterEnumValue("RenderCommandType", "CMD_RENDERUI", CMD_RENDERUI);
    engine->RegisterEnumValue("RenderCommandType", "CMD_SENDEVENT", CMD_SENDEVENT);

    // enum RenderSurfaceUpdateMode | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("RenderSurfaceUpdateMode");
    engine->RegisterEnumValue("RenderSurfaceUpdateMode", "SURFACE_MANUALUPDATE", SURFACE_MANUALUPDATE);
    engine->RegisterEnumValue("RenderSurfaceUpdateMode", "SURFACE_UPDATEVISIBLE", SURFACE_UPDATEVISIBLE);
    engine->RegisterEnumValue("RenderSurfaceUpdateMode", "SURFACE_UPDATEALWAYS", SURFACE_UPDATEALWAYS);

    // enum RenderTargetSizeMode | File: ../Graphics/RenderPath.h
    engine->RegisterEnum("RenderTargetSizeMode");
    engine->RegisterEnumValue("RenderTargetSizeMode", "SIZE_ABSOLUTE", SIZE_ABSOLUTE);
    engine->RegisterEnumValue("RenderTargetSizeMode", "SIZE_VIEWPORTDIVISOR", SIZE_VIEWPORTDIVISOR);
    engine->RegisterEnumValue("RenderTargetSizeMode", "SIZE_VIEWPORTMULTIPLIER", SIZE_VIEWPORTMULTIPLIER);

    // enum ResourceRequest | File: ../Resource/ResourceCache.h
    engine->RegisterEnum("ResourceRequest");
    engine->RegisterEnumValue("ResourceRequest", "RESOURCE_CHECKEXISTS", RESOURCE_CHECKEXISTS);
    engine->RegisterEnumValue("ResourceRequest", "RESOURCE_GETFILE", RESOURCE_GETFILE);

    // enum Scancode : unsigned | File: ../Input/InputConstants.h
    engine->RegisterTypedef("Scancode", "uint");
    engine->RegisterGlobalProperty("const uint SCANCODE_UNKNOWN", (void*)&Scancode_SCANCODE_UNKNOWN);
    engine->RegisterGlobalProperty("const uint SCANCODE_CTRL", (void*)&Scancode_SCANCODE_CTRL);
    engine->RegisterGlobalProperty("const uint SCANCODE_SHIFT", (void*)&Scancode_SCANCODE_SHIFT);
    engine->RegisterGlobalProperty("const uint SCANCODE_ALT", (void*)&Scancode_SCANCODE_ALT);
    engine->RegisterGlobalProperty("const uint SCANCODE_GUI", (void*)&Scancode_SCANCODE_GUI);
    engine->RegisterGlobalProperty("const uint SCANCODE_A", (void*)&Scancode_SCANCODE_A);
    engine->RegisterGlobalProperty("const uint SCANCODE_B", (void*)&Scancode_SCANCODE_B);
    engine->RegisterGlobalProperty("const uint SCANCODE_C", (void*)&Scancode_SCANCODE_C);
    engine->RegisterGlobalProperty("const uint SCANCODE_D", (void*)&Scancode_SCANCODE_D);
    engine->RegisterGlobalProperty("const uint SCANCODE_E", (void*)&Scancode_SCANCODE_E);
    engine->RegisterGlobalProperty("const uint SCANCODE_F", (void*)&Scancode_SCANCODE_F);
    engine->RegisterGlobalProperty("const uint SCANCODE_G", (void*)&Scancode_SCANCODE_G);
    engine->RegisterGlobalProperty("const uint SCANCODE_H", (void*)&Scancode_SCANCODE_H);
    engine->RegisterGlobalProperty("const uint SCANCODE_I", (void*)&Scancode_SCANCODE_I);
    engine->RegisterGlobalProperty("const uint SCANCODE_J", (void*)&Scancode_SCANCODE_J);
    engine->RegisterGlobalProperty("const uint SCANCODE_K", (void*)&Scancode_SCANCODE_K);
    engine->RegisterGlobalProperty("const uint SCANCODE_L", (void*)&Scancode_SCANCODE_L);
    engine->RegisterGlobalProperty("const uint SCANCODE_M", (void*)&Scancode_SCANCODE_M);
    engine->RegisterGlobalProperty("const uint SCANCODE_N", (void*)&Scancode_SCANCODE_N);
    engine->RegisterGlobalProperty("const uint SCANCODE_O", (void*)&Scancode_SCANCODE_O);
    engine->RegisterGlobalProperty("const uint SCANCODE_P", (void*)&Scancode_SCANCODE_P);
    engine->RegisterGlobalProperty("const uint SCANCODE_Q", (void*)&Scancode_SCANCODE_Q);
    engine->RegisterGlobalProperty("const uint SCANCODE_R", (void*)&Scancode_SCANCODE_R);
    engine->RegisterGlobalProperty("const uint SCANCODE_S", (void*)&Scancode_SCANCODE_S);
    engine->RegisterGlobalProperty("const uint SCANCODE_T", (void*)&Scancode_SCANCODE_T);
    engine->RegisterGlobalProperty("const uint SCANCODE_U", (void*)&Scancode_SCANCODE_U);
    engine->RegisterGlobalProperty("const uint SCANCODE_V", (void*)&Scancode_SCANCODE_V);
    engine->RegisterGlobalProperty("const uint SCANCODE_W", (void*)&Scancode_SCANCODE_W);
    engine->RegisterGlobalProperty("const uint SCANCODE_X", (void*)&Scancode_SCANCODE_X);
    engine->RegisterGlobalProperty("const uint SCANCODE_Y", (void*)&Scancode_SCANCODE_Y);
    engine->RegisterGlobalProperty("const uint SCANCODE_Z", (void*)&Scancode_SCANCODE_Z);
    engine->RegisterGlobalProperty("const uint SCANCODE_1", (void*)&Scancode_SCANCODE_1);
    engine->RegisterGlobalProperty("const uint SCANCODE_2", (void*)&Scancode_SCANCODE_2);
    engine->RegisterGlobalProperty("const uint SCANCODE_3", (void*)&Scancode_SCANCODE_3);
    engine->RegisterGlobalProperty("const uint SCANCODE_4", (void*)&Scancode_SCANCODE_4);
    engine->RegisterGlobalProperty("const uint SCANCODE_5", (void*)&Scancode_SCANCODE_5);
    engine->RegisterGlobalProperty("const uint SCANCODE_6", (void*)&Scancode_SCANCODE_6);
    engine->RegisterGlobalProperty("const uint SCANCODE_7", (void*)&Scancode_SCANCODE_7);
    engine->RegisterGlobalProperty("const uint SCANCODE_8", (void*)&Scancode_SCANCODE_8);
    engine->RegisterGlobalProperty("const uint SCANCODE_9", (void*)&Scancode_SCANCODE_9);
    engine->RegisterGlobalProperty("const uint SCANCODE_0", (void*)&Scancode_SCANCODE_0);
    engine->RegisterGlobalProperty("const uint SCANCODE_RETURN", (void*)&Scancode_SCANCODE_RETURN);
    engine->RegisterGlobalProperty("const uint SCANCODE_ESCAPE", (void*)&Scancode_SCANCODE_ESCAPE);
    engine->RegisterGlobalProperty("const uint SCANCODE_BACKSPACE", (void*)&Scancode_SCANCODE_BACKSPACE);
    engine->RegisterGlobalProperty("const uint SCANCODE_TAB", (void*)&Scancode_SCANCODE_TAB);
    engine->RegisterGlobalProperty("const uint SCANCODE_SPACE", (void*)&Scancode_SCANCODE_SPACE);
    engine->RegisterGlobalProperty("const uint SCANCODE_MINUS", (void*)&Scancode_SCANCODE_MINUS);
    engine->RegisterGlobalProperty("const uint SCANCODE_EQUALS", (void*)&Scancode_SCANCODE_EQUALS);
    engine->RegisterGlobalProperty("const uint SCANCODE_LEFTBRACKET", (void*)&Scancode_SCANCODE_LEFTBRACKET);
    engine->RegisterGlobalProperty("const uint SCANCODE_RIGHTBRACKET", (void*)&Scancode_SCANCODE_RIGHTBRACKET);
    engine->RegisterGlobalProperty("const uint SCANCODE_BACKSLASH", (void*)&Scancode_SCANCODE_BACKSLASH);
    engine->RegisterGlobalProperty("const uint SCANCODE_NONUSHASH", (void*)&Scancode_SCANCODE_NONUSHASH);
    engine->RegisterGlobalProperty("const uint SCANCODE_SEMICOLON", (void*)&Scancode_SCANCODE_SEMICOLON);
    engine->RegisterGlobalProperty("const uint SCANCODE_APOSTROPHE", (void*)&Scancode_SCANCODE_APOSTROPHE);
    engine->RegisterGlobalProperty("const uint SCANCODE_GRAVE", (void*)&Scancode_SCANCODE_GRAVE);
    engine->RegisterGlobalProperty("const uint SCANCODE_COMMA", (void*)&Scancode_SCANCODE_COMMA);
    engine->RegisterGlobalProperty("const uint SCANCODE_PERIOD", (void*)&Scancode_SCANCODE_PERIOD);
    engine->RegisterGlobalProperty("const uint SCANCODE_SLASH", (void*)&Scancode_SCANCODE_SLASH);
    engine->RegisterGlobalProperty("const uint SCANCODE_CAPSLOCK", (void*)&Scancode_SCANCODE_CAPSLOCK);
    engine->RegisterGlobalProperty("const uint SCANCODE_F1", (void*)&Scancode_SCANCODE_F1);
    engine->RegisterGlobalProperty("const uint SCANCODE_F2", (void*)&Scancode_SCANCODE_F2);
    engine->RegisterGlobalProperty("const uint SCANCODE_F3", (void*)&Scancode_SCANCODE_F3);
    engine->RegisterGlobalProperty("const uint SCANCODE_F4", (void*)&Scancode_SCANCODE_F4);
    engine->RegisterGlobalProperty("const uint SCANCODE_F5", (void*)&Scancode_SCANCODE_F5);
    engine->RegisterGlobalProperty("const uint SCANCODE_F6", (void*)&Scancode_SCANCODE_F6);
    engine->RegisterGlobalProperty("const uint SCANCODE_F7", (void*)&Scancode_SCANCODE_F7);
    engine->RegisterGlobalProperty("const uint SCANCODE_F8", (void*)&Scancode_SCANCODE_F8);
    engine->RegisterGlobalProperty("const uint SCANCODE_F9", (void*)&Scancode_SCANCODE_F9);
    engine->RegisterGlobalProperty("const uint SCANCODE_F10", (void*)&Scancode_SCANCODE_F10);
    engine->RegisterGlobalProperty("const uint SCANCODE_F11", (void*)&Scancode_SCANCODE_F11);
    engine->RegisterGlobalProperty("const uint SCANCODE_F12", (void*)&Scancode_SCANCODE_F12);
    engine->RegisterGlobalProperty("const uint SCANCODE_PRINTSCREEN", (void*)&Scancode_SCANCODE_PRINTSCREEN);
    engine->RegisterGlobalProperty("const uint SCANCODE_SCROLLLOCK", (void*)&Scancode_SCANCODE_SCROLLLOCK);
    engine->RegisterGlobalProperty("const uint SCANCODE_PAUSE", (void*)&Scancode_SCANCODE_PAUSE);
    engine->RegisterGlobalProperty("const uint SCANCODE_INSERT", (void*)&Scancode_SCANCODE_INSERT);
    engine->RegisterGlobalProperty("const uint SCANCODE_HOME", (void*)&Scancode_SCANCODE_HOME);
    engine->RegisterGlobalProperty("const uint SCANCODE_PAGEUP", (void*)&Scancode_SCANCODE_PAGEUP);
    engine->RegisterGlobalProperty("const uint SCANCODE_DELETE", (void*)&Scancode_SCANCODE_DELETE);
    engine->RegisterGlobalProperty("const uint SCANCODE_END", (void*)&Scancode_SCANCODE_END);
    engine->RegisterGlobalProperty("const uint SCANCODE_PAGEDOWN", (void*)&Scancode_SCANCODE_PAGEDOWN);
    engine->RegisterGlobalProperty("const uint SCANCODE_RIGHT", (void*)&Scancode_SCANCODE_RIGHT);
    engine->RegisterGlobalProperty("const uint SCANCODE_LEFT", (void*)&Scancode_SCANCODE_LEFT);
    engine->RegisterGlobalProperty("const uint SCANCODE_DOWN", (void*)&Scancode_SCANCODE_DOWN);
    engine->RegisterGlobalProperty("const uint SCANCODE_UP", (void*)&Scancode_SCANCODE_UP);
    engine->RegisterGlobalProperty("const uint SCANCODE_NUMLOCKCLEAR", (void*)&Scancode_SCANCODE_NUMLOCKCLEAR);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_DIVIDE", (void*)&Scancode_SCANCODE_KP_DIVIDE);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_MULTIPLY", (void*)&Scancode_SCANCODE_KP_MULTIPLY);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_MINUS", (void*)&Scancode_SCANCODE_KP_MINUS);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_PLUS", (void*)&Scancode_SCANCODE_KP_PLUS);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_ENTER", (void*)&Scancode_SCANCODE_KP_ENTER);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_1", (void*)&Scancode_SCANCODE_KP_1);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_2", (void*)&Scancode_SCANCODE_KP_2);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_3", (void*)&Scancode_SCANCODE_KP_3);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_4", (void*)&Scancode_SCANCODE_KP_4);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_5", (void*)&Scancode_SCANCODE_KP_5);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_6", (void*)&Scancode_SCANCODE_KP_6);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_7", (void*)&Scancode_SCANCODE_KP_7);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_8", (void*)&Scancode_SCANCODE_KP_8);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_9", (void*)&Scancode_SCANCODE_KP_9);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_0", (void*)&Scancode_SCANCODE_KP_0);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_PERIOD", (void*)&Scancode_SCANCODE_KP_PERIOD);
    engine->RegisterGlobalProperty("const uint SCANCODE_NONUSBACKSLASH", (void*)&Scancode_SCANCODE_NONUSBACKSLASH);
    engine->RegisterGlobalProperty("const uint SCANCODE_APPLICATION", (void*)&Scancode_SCANCODE_APPLICATION);
    engine->RegisterGlobalProperty("const uint SCANCODE_POWER", (void*)&Scancode_SCANCODE_POWER);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_EQUALS", (void*)&Scancode_SCANCODE_KP_EQUALS);
    engine->RegisterGlobalProperty("const uint SCANCODE_F13", (void*)&Scancode_SCANCODE_F13);
    engine->RegisterGlobalProperty("const uint SCANCODE_F14", (void*)&Scancode_SCANCODE_F14);
    engine->RegisterGlobalProperty("const uint SCANCODE_F15", (void*)&Scancode_SCANCODE_F15);
    engine->RegisterGlobalProperty("const uint SCANCODE_F16", (void*)&Scancode_SCANCODE_F16);
    engine->RegisterGlobalProperty("const uint SCANCODE_F17", (void*)&Scancode_SCANCODE_F17);
    engine->RegisterGlobalProperty("const uint SCANCODE_F18", (void*)&Scancode_SCANCODE_F18);
    engine->RegisterGlobalProperty("const uint SCANCODE_F19", (void*)&Scancode_SCANCODE_F19);
    engine->RegisterGlobalProperty("const uint SCANCODE_F20", (void*)&Scancode_SCANCODE_F20);
    engine->RegisterGlobalProperty("const uint SCANCODE_F21", (void*)&Scancode_SCANCODE_F21);
    engine->RegisterGlobalProperty("const uint SCANCODE_F22", (void*)&Scancode_SCANCODE_F22);
    engine->RegisterGlobalProperty("const uint SCANCODE_F23", (void*)&Scancode_SCANCODE_F23);
    engine->RegisterGlobalProperty("const uint SCANCODE_F24", (void*)&Scancode_SCANCODE_F24);
    engine->RegisterGlobalProperty("const uint SCANCODE_EXECUTE", (void*)&Scancode_SCANCODE_EXECUTE);
    engine->RegisterGlobalProperty("const uint SCANCODE_HELP", (void*)&Scancode_SCANCODE_HELP);
    engine->RegisterGlobalProperty("const uint SCANCODE_MENU", (void*)&Scancode_SCANCODE_MENU);
    engine->RegisterGlobalProperty("const uint SCANCODE_SELECT", (void*)&Scancode_SCANCODE_SELECT);
    engine->RegisterGlobalProperty("const uint SCANCODE_STOP", (void*)&Scancode_SCANCODE_STOP);
    engine->RegisterGlobalProperty("const uint SCANCODE_AGAIN", (void*)&Scancode_SCANCODE_AGAIN);
    engine->RegisterGlobalProperty("const uint SCANCODE_UNDO", (void*)&Scancode_SCANCODE_UNDO);
    engine->RegisterGlobalProperty("const uint SCANCODE_CUT", (void*)&Scancode_SCANCODE_CUT);
    engine->RegisterGlobalProperty("const uint SCANCODE_COPY", (void*)&Scancode_SCANCODE_COPY);
    engine->RegisterGlobalProperty("const uint SCANCODE_PASTE", (void*)&Scancode_SCANCODE_PASTE);
    engine->RegisterGlobalProperty("const uint SCANCODE_FIND", (void*)&Scancode_SCANCODE_FIND);
    engine->RegisterGlobalProperty("const uint SCANCODE_MUTE", (void*)&Scancode_SCANCODE_MUTE);
    engine->RegisterGlobalProperty("const uint SCANCODE_VOLUMEUP", (void*)&Scancode_SCANCODE_VOLUMEUP);
    engine->RegisterGlobalProperty("const uint SCANCODE_VOLUMEDOWN", (void*)&Scancode_SCANCODE_VOLUMEDOWN);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_COMMA", (void*)&Scancode_SCANCODE_KP_COMMA);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_EQUALSAS400", (void*)&Scancode_SCANCODE_KP_EQUALSAS400);
    engine->RegisterGlobalProperty("const uint SCANCODE_INTERNATIONAL1", (void*)&Scancode_SCANCODE_INTERNATIONAL1);
    engine->RegisterGlobalProperty("const uint SCANCODE_INTERNATIONAL2", (void*)&Scancode_SCANCODE_INTERNATIONAL2);
    engine->RegisterGlobalProperty("const uint SCANCODE_INTERNATIONAL3", (void*)&Scancode_SCANCODE_INTERNATIONAL3);
    engine->RegisterGlobalProperty("const uint SCANCODE_INTERNATIONAL4", (void*)&Scancode_SCANCODE_INTERNATIONAL4);
    engine->RegisterGlobalProperty("const uint SCANCODE_INTERNATIONAL5", (void*)&Scancode_SCANCODE_INTERNATIONAL5);
    engine->RegisterGlobalProperty("const uint SCANCODE_INTERNATIONAL6", (void*)&Scancode_SCANCODE_INTERNATIONAL6);
    engine->RegisterGlobalProperty("const uint SCANCODE_INTERNATIONAL7", (void*)&Scancode_SCANCODE_INTERNATIONAL7);
    engine->RegisterGlobalProperty("const uint SCANCODE_INTERNATIONAL8", (void*)&Scancode_SCANCODE_INTERNATIONAL8);
    engine->RegisterGlobalProperty("const uint SCANCODE_INTERNATIONAL9", (void*)&Scancode_SCANCODE_INTERNATIONAL9);
    engine->RegisterGlobalProperty("const uint SCANCODE_LANG1", (void*)&Scancode_SCANCODE_LANG1);
    engine->RegisterGlobalProperty("const uint SCANCODE_LANG2", (void*)&Scancode_SCANCODE_LANG2);
    engine->RegisterGlobalProperty("const uint SCANCODE_LANG3", (void*)&Scancode_SCANCODE_LANG3);
    engine->RegisterGlobalProperty("const uint SCANCODE_LANG4", (void*)&Scancode_SCANCODE_LANG4);
    engine->RegisterGlobalProperty("const uint SCANCODE_LANG5", (void*)&Scancode_SCANCODE_LANG5);
    engine->RegisterGlobalProperty("const uint SCANCODE_LANG6", (void*)&Scancode_SCANCODE_LANG6);
    engine->RegisterGlobalProperty("const uint SCANCODE_LANG7", (void*)&Scancode_SCANCODE_LANG7);
    engine->RegisterGlobalProperty("const uint SCANCODE_LANG8", (void*)&Scancode_SCANCODE_LANG8);
    engine->RegisterGlobalProperty("const uint SCANCODE_LANG9", (void*)&Scancode_SCANCODE_LANG9);
    engine->RegisterGlobalProperty("const uint SCANCODE_ALTERASE", (void*)&Scancode_SCANCODE_ALTERASE);
    engine->RegisterGlobalProperty("const uint SCANCODE_SYSREQ", (void*)&Scancode_SCANCODE_SYSREQ);
    engine->RegisterGlobalProperty("const uint SCANCODE_CANCEL", (void*)&Scancode_SCANCODE_CANCEL);
    engine->RegisterGlobalProperty("const uint SCANCODE_CLEAR", (void*)&Scancode_SCANCODE_CLEAR);
    engine->RegisterGlobalProperty("const uint SCANCODE_PRIOR", (void*)&Scancode_SCANCODE_PRIOR);
    engine->RegisterGlobalProperty("const uint SCANCODE_RETURN2", (void*)&Scancode_SCANCODE_RETURN2);
    engine->RegisterGlobalProperty("const uint SCANCODE_SEPARATOR", (void*)&Scancode_SCANCODE_SEPARATOR);
    engine->RegisterGlobalProperty("const uint SCANCODE_OUT", (void*)&Scancode_SCANCODE_OUT);
    engine->RegisterGlobalProperty("const uint SCANCODE_OPER", (void*)&Scancode_SCANCODE_OPER);
    engine->RegisterGlobalProperty("const uint SCANCODE_CLEARAGAIN", (void*)&Scancode_SCANCODE_CLEARAGAIN);
    engine->RegisterGlobalProperty("const uint SCANCODE_CRSEL", (void*)&Scancode_SCANCODE_CRSEL);
    engine->RegisterGlobalProperty("const uint SCANCODE_EXSEL", (void*)&Scancode_SCANCODE_EXSEL);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_00", (void*)&Scancode_SCANCODE_KP_00);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_000", (void*)&Scancode_SCANCODE_KP_000);
    engine->RegisterGlobalProperty("const uint SCANCODE_THOUSANDSSEPARATOR", (void*)&Scancode_SCANCODE_THOUSANDSSEPARATOR);
    engine->RegisterGlobalProperty("const uint SCANCODE_DECIMALSEPARATOR", (void*)&Scancode_SCANCODE_DECIMALSEPARATOR);
    engine->RegisterGlobalProperty("const uint SCANCODE_CURRENCYUNIT", (void*)&Scancode_SCANCODE_CURRENCYUNIT);
    engine->RegisterGlobalProperty("const uint SCANCODE_CURRENCYSUBUNIT", (void*)&Scancode_SCANCODE_CURRENCYSUBUNIT);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_LEFTPAREN", (void*)&Scancode_SCANCODE_KP_LEFTPAREN);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_RIGHTPAREN", (void*)&Scancode_SCANCODE_KP_RIGHTPAREN);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_LEFTBRACE", (void*)&Scancode_SCANCODE_KP_LEFTBRACE);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_RIGHTBRACE", (void*)&Scancode_SCANCODE_KP_RIGHTBRACE);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_TAB", (void*)&Scancode_SCANCODE_KP_TAB);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_BACKSPACE", (void*)&Scancode_SCANCODE_KP_BACKSPACE);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_A", (void*)&Scancode_SCANCODE_KP_A);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_B", (void*)&Scancode_SCANCODE_KP_B);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_C", (void*)&Scancode_SCANCODE_KP_C);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_D", (void*)&Scancode_SCANCODE_KP_D);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_E", (void*)&Scancode_SCANCODE_KP_E);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_F", (void*)&Scancode_SCANCODE_KP_F);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_XOR", (void*)&Scancode_SCANCODE_KP_XOR);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_POWER", (void*)&Scancode_SCANCODE_KP_POWER);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_PERCENT", (void*)&Scancode_SCANCODE_KP_PERCENT);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_LESS", (void*)&Scancode_SCANCODE_KP_LESS);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_GREATER", (void*)&Scancode_SCANCODE_KP_GREATER);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_AMPERSAND", (void*)&Scancode_SCANCODE_KP_AMPERSAND);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_DBLAMPERSAND", (void*)&Scancode_SCANCODE_KP_DBLAMPERSAND);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_VERTICALBAR", (void*)&Scancode_SCANCODE_KP_VERTICALBAR);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_DBLVERTICALBAR", (void*)&Scancode_SCANCODE_KP_DBLVERTICALBAR);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_COLON", (void*)&Scancode_SCANCODE_KP_COLON);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_HASH", (void*)&Scancode_SCANCODE_KP_HASH);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_SPACE", (void*)&Scancode_SCANCODE_KP_SPACE);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_AT", (void*)&Scancode_SCANCODE_KP_AT);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_EXCLAM", (void*)&Scancode_SCANCODE_KP_EXCLAM);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_MEMSTORE", (void*)&Scancode_SCANCODE_KP_MEMSTORE);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_MEMRECALL", (void*)&Scancode_SCANCODE_KP_MEMRECALL);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_MEMCLEAR", (void*)&Scancode_SCANCODE_KP_MEMCLEAR);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_MEMADD", (void*)&Scancode_SCANCODE_KP_MEMADD);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_MEMSUBTRACT", (void*)&Scancode_SCANCODE_KP_MEMSUBTRACT);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_MEMMULTIPLY", (void*)&Scancode_SCANCODE_KP_MEMMULTIPLY);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_MEMDIVIDE", (void*)&Scancode_SCANCODE_KP_MEMDIVIDE);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_PLUSMINUS", (void*)&Scancode_SCANCODE_KP_PLUSMINUS);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_CLEAR", (void*)&Scancode_SCANCODE_KP_CLEAR);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_CLEARENTRY", (void*)&Scancode_SCANCODE_KP_CLEARENTRY);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_BINARY", (void*)&Scancode_SCANCODE_KP_BINARY);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_OCTAL", (void*)&Scancode_SCANCODE_KP_OCTAL);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_DECIMAL", (void*)&Scancode_SCANCODE_KP_DECIMAL);
    engine->RegisterGlobalProperty("const uint SCANCODE_KP_HEXADECIMAL", (void*)&Scancode_SCANCODE_KP_HEXADECIMAL);
    engine->RegisterGlobalProperty("const uint SCANCODE_LCTRL", (void*)&Scancode_SCANCODE_LCTRL);
    engine->RegisterGlobalProperty("const uint SCANCODE_LSHIFT", (void*)&Scancode_SCANCODE_LSHIFT);
    engine->RegisterGlobalProperty("const uint SCANCODE_LALT", (void*)&Scancode_SCANCODE_LALT);
    engine->RegisterGlobalProperty("const uint SCANCODE_LGUI", (void*)&Scancode_SCANCODE_LGUI);
    engine->RegisterGlobalProperty("const uint SCANCODE_RCTRL", (void*)&Scancode_SCANCODE_RCTRL);
    engine->RegisterGlobalProperty("const uint SCANCODE_RSHIFT", (void*)&Scancode_SCANCODE_RSHIFT);
    engine->RegisterGlobalProperty("const uint SCANCODE_RALT", (void*)&Scancode_SCANCODE_RALT);
    engine->RegisterGlobalProperty("const uint SCANCODE_RGUI", (void*)&Scancode_SCANCODE_RGUI);
    engine->RegisterGlobalProperty("const uint SCANCODE_MODE", (void*)&Scancode_SCANCODE_MODE);
    engine->RegisterGlobalProperty("const uint SCANCODE_AUDIONEXT", (void*)&Scancode_SCANCODE_AUDIONEXT);
    engine->RegisterGlobalProperty("const uint SCANCODE_AUDIOPREV", (void*)&Scancode_SCANCODE_AUDIOPREV);
    engine->RegisterGlobalProperty("const uint SCANCODE_AUDIOSTOP", (void*)&Scancode_SCANCODE_AUDIOSTOP);
    engine->RegisterGlobalProperty("const uint SCANCODE_AUDIOPLAY", (void*)&Scancode_SCANCODE_AUDIOPLAY);
    engine->RegisterGlobalProperty("const uint SCANCODE_AUDIOMUTE", (void*)&Scancode_SCANCODE_AUDIOMUTE);
    engine->RegisterGlobalProperty("const uint SCANCODE_MEDIASELECT", (void*)&Scancode_SCANCODE_MEDIASELECT);
    engine->RegisterGlobalProperty("const uint SCANCODE_WWW", (void*)&Scancode_SCANCODE_WWW);
    engine->RegisterGlobalProperty("const uint SCANCODE_MAIL", (void*)&Scancode_SCANCODE_MAIL);
    engine->RegisterGlobalProperty("const uint SCANCODE_CALCULATOR", (void*)&Scancode_SCANCODE_CALCULATOR);
    engine->RegisterGlobalProperty("const uint SCANCODE_COMPUTER", (void*)&Scancode_SCANCODE_COMPUTER);
    engine->RegisterGlobalProperty("const uint SCANCODE_AC_SEARCH", (void*)&Scancode_SCANCODE_AC_SEARCH);
    engine->RegisterGlobalProperty("const uint SCANCODE_AC_HOME", (void*)&Scancode_SCANCODE_AC_HOME);
    engine->RegisterGlobalProperty("const uint SCANCODE_AC_BACK", (void*)&Scancode_SCANCODE_AC_BACK);
    engine->RegisterGlobalProperty("const uint SCANCODE_AC_FORWARD", (void*)&Scancode_SCANCODE_AC_FORWARD);
    engine->RegisterGlobalProperty("const uint SCANCODE_AC_STOP", (void*)&Scancode_SCANCODE_AC_STOP);
    engine->RegisterGlobalProperty("const uint SCANCODE_AC_REFRESH", (void*)&Scancode_SCANCODE_AC_REFRESH);
    engine->RegisterGlobalProperty("const uint SCANCODE_AC_BOOKMARKS", (void*)&Scancode_SCANCODE_AC_BOOKMARKS);
    engine->RegisterGlobalProperty("const uint SCANCODE_BRIGHTNESSDOWN", (void*)&Scancode_SCANCODE_BRIGHTNESSDOWN);
    engine->RegisterGlobalProperty("const uint SCANCODE_BRIGHTNESSUP", (void*)&Scancode_SCANCODE_BRIGHTNESSUP);
    engine->RegisterGlobalProperty("const uint SCANCODE_DISPLAYSWITCH", (void*)&Scancode_SCANCODE_DISPLAYSWITCH);
    engine->RegisterGlobalProperty("const uint SCANCODE_KBDILLUMTOGGLE", (void*)&Scancode_SCANCODE_KBDILLUMTOGGLE);
    engine->RegisterGlobalProperty("const uint SCANCODE_KBDILLUMDOWN", (void*)&Scancode_SCANCODE_KBDILLUMDOWN);
    engine->RegisterGlobalProperty("const uint SCANCODE_KBDILLUMUP", (void*)&Scancode_SCANCODE_KBDILLUMUP);
    engine->RegisterGlobalProperty("const uint SCANCODE_EJECT", (void*)&Scancode_SCANCODE_EJECT);
    engine->RegisterGlobalProperty("const uint SCANCODE_SLEEP", (void*)&Scancode_SCANCODE_SLEEP);
    engine->RegisterGlobalProperty("const uint SCANCODE_APP1", (void*)&Scancode_SCANCODE_APP1);
    engine->RegisterGlobalProperty("const uint SCANCODE_APP2", (void*)&Scancode_SCANCODE_APP2);

    // enum ShaderParameterGroup | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("ShaderParameterGroup");
    engine->RegisterEnumValue("ShaderParameterGroup", "SP_FRAME", SP_FRAME);
    engine->RegisterEnumValue("ShaderParameterGroup", "SP_CAMERA", SP_CAMERA);
    engine->RegisterEnumValue("ShaderParameterGroup", "SP_ZONE", SP_ZONE);
    engine->RegisterEnumValue("ShaderParameterGroup", "SP_LIGHT", SP_LIGHT);
    engine->RegisterEnumValue("ShaderParameterGroup", "SP_MATERIAL", SP_MATERIAL);
    engine->RegisterEnumValue("ShaderParameterGroup", "SP_OBJECT", SP_OBJECT);
    engine->RegisterEnumValue("ShaderParameterGroup", "SP_CUSTOM", SP_CUSTOM);
    engine->RegisterEnumValue("ShaderParameterGroup", "MAX_SHADER_PARAMETER_GROUPS", MAX_SHADER_PARAMETER_GROUPS);

    // enum ShaderType | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("ShaderType");
    engine->RegisterEnumValue("ShaderType", "VS", VS);
    engine->RegisterEnumValue("ShaderType", "PS", PS);

    // enum ShadowQuality | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("ShadowQuality");
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_SIMPLE_16BIT", SHADOWQUALITY_SIMPLE_16BIT);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_SIMPLE_24BIT", SHADOWQUALITY_SIMPLE_24BIT);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_PCF_16BIT", SHADOWQUALITY_PCF_16BIT);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_PCF_24BIT", SHADOWQUALITY_PCF_24BIT);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_VSM", SHADOWQUALITY_VSM);
    engine->RegisterEnumValue("ShadowQuality", "SHADOWQUALITY_BLUR_VSM", SHADOWQUALITY_BLUR_VSM);

    // enum SmoothingType : unsigned | File: ../Scene/SmoothedTransform.h
    engine->RegisterTypedef("SmoothingType", "uint");
    engine->RegisterGlobalProperty("const uint SMOOTH_NONE", (void*)&SmoothingType_SMOOTH_NONE);
    engine->RegisterGlobalProperty("const uint SMOOTH_POSITION", (void*)&SmoothingType_SMOOTH_POSITION);
    engine->RegisterGlobalProperty("const uint SMOOTH_ROTATION", (void*)&SmoothingType_SMOOTH_ROTATION);

    // URHO3D_FLAGSET(SmoothingType, SmoothingTypeFlags) | File: ../Scene/SmoothedTransform.h
    engine->RegisterTypedef("SmoothingTypeFlags", "uint");

    // enum StencilOp | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("StencilOp");
    engine->RegisterEnumValue("StencilOp", "OP_KEEP", OP_KEEP);
    engine->RegisterEnumValue("StencilOp", "OP_ZERO", OP_ZERO);
    engine->RegisterEnumValue("StencilOp", "OP_REF", OP_REF);
    engine->RegisterEnumValue("StencilOp", "OP_INCR", OP_INCR);
    engine->RegisterEnumValue("StencilOp", "OP_DECR", OP_DECR);

    // enum TextEffect | File: ../UI/Text.h
    engine->RegisterEnum("TextEffect");
    engine->RegisterEnumValue("TextEffect", "TE_NONE", TE_NONE);
    engine->RegisterEnumValue("TextEffect", "TE_SHADOW", TE_SHADOW);
    engine->RegisterEnumValue("TextEffect", "TE_STROKE", TE_STROKE);

    // enum TextureAddressMode | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("TextureAddressMode");
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_WRAP", ADDRESS_WRAP);
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_MIRROR", ADDRESS_MIRROR);
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_CLAMP", ADDRESS_CLAMP);
    engine->RegisterEnumValue("TextureAddressMode", "ADDRESS_BORDER", ADDRESS_BORDER);
    engine->RegisterEnumValue("TextureAddressMode", "MAX_ADDRESSMODES", MAX_ADDRESSMODES);

    // enum TextureCoordinate | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("TextureCoordinate");
    engine->RegisterEnumValue("TextureCoordinate", "COORD_U", COORD_U);
    engine->RegisterEnumValue("TextureCoordinate", "COORD_V", COORD_V);
    engine->RegisterEnumValue("TextureCoordinate", "COORD_W", COORD_W);
    engine->RegisterEnumValue("TextureCoordinate", "MAX_COORDS", MAX_COORDS);

    // enum TextureFilterMode | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("TextureFilterMode");
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_NEAREST", FILTER_NEAREST);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_BILINEAR", FILTER_BILINEAR);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_TRILINEAR", FILTER_TRILINEAR);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_ANISOTROPIC", FILTER_ANISOTROPIC);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_NEAREST_ANISOTROPIC", FILTER_NEAREST_ANISOTROPIC);
    engine->RegisterEnumValue("TextureFilterMode", "FILTER_DEFAULT", FILTER_DEFAULT);
    engine->RegisterEnumValue("TextureFilterMode", "MAX_FILTERMODES", MAX_FILTERMODES);

    // enum TextureUnit | File: ../Graphics/GraphicsDefs.h
    // Not registered because have @manualbind mark

    // enum TextureUsage | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("TextureUsage");
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_STATIC", TEXTURE_STATIC);
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_DYNAMIC", TEXTURE_DYNAMIC);
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_RENDERTARGET", TEXTURE_RENDERTARGET);
    engine->RegisterEnumValue("TextureUsage", "TEXTURE_DEPTHSTENCIL", TEXTURE_DEPTHSTENCIL);

    // enum TrailType | File: ../Graphics/RibbonTrail.h
    engine->RegisterEnum("TrailType");
    engine->RegisterEnumValue("TrailType", "TT_FACE_CAMERA", TT_FACE_CAMERA);
    engine->RegisterEnumValue("TrailType", "TT_BONE", TT_BONE);

    // enum TransformSpace | File: ../Scene/Node.h
    engine->RegisterEnum("TransformSpace");
    engine->RegisterEnumValue("TransformSpace", "TS_LOCAL", TS_LOCAL);
    engine->RegisterEnumValue("TransformSpace", "TS_PARENT", TS_PARENT);
    engine->RegisterEnumValue("TransformSpace", "TS_WORLD", TS_WORLD);

    // enum TraversalMode | File: ../UI/UIElement.h
    engine->RegisterEnum("TraversalMode");
    engine->RegisterEnumValue("TraversalMode", "TM_BREADTH_FIRST", TM_BREADTH_FIRST);
    engine->RegisterEnumValue("TraversalMode", "TM_DEPTH_FIRST", TM_DEPTH_FIRST);

    // enum UpdateEvent : unsigned | File: ../Scene/LogicComponent.h
    engine->RegisterTypedef("UpdateEvent", "uint");
    engine->RegisterGlobalProperty("const uint USE_NO_EVENT", (void*)&UpdateEvent_USE_NO_EVENT);
    engine->RegisterGlobalProperty("const uint USE_UPDATE", (void*)&UpdateEvent_USE_UPDATE);
    engine->RegisterGlobalProperty("const uint USE_POSTUPDATE", (void*)&UpdateEvent_USE_POSTUPDATE);
    engine->RegisterGlobalProperty("const uint USE_FIXEDUPDATE", (void*)&UpdateEvent_USE_FIXEDUPDATE);
    engine->RegisterGlobalProperty("const uint USE_FIXEDPOSTUPDATE", (void*)&UpdateEvent_USE_FIXEDPOSTUPDATE);

    // URHO3D_FLAGSET(UpdateEvent, UpdateEventFlags) | File: ../Scene/LogicComponent.h
    engine->RegisterTypedef("UpdateEventFlags", "uint");

    // enum UpdateGeometryType | File: ../Graphics/Drawable.h
    engine->RegisterEnum("UpdateGeometryType");
    engine->RegisterEnumValue("UpdateGeometryType", "UPDATE_NONE", UPDATE_NONE);
    engine->RegisterEnumValue("UpdateGeometryType", "UPDATE_MAIN_THREAD", UPDATE_MAIN_THREAD);
    engine->RegisterEnumValue("UpdateGeometryType", "UPDATE_WORKER_THREAD", UPDATE_WORKER_THREAD);

    // enum VariantType | File: ../Core/Variant.h
    engine->RegisterEnum("VariantType");
    engine->RegisterEnumValue("VariantType", "VAR_NONE", VAR_NONE);
    engine->RegisterEnumValue("VariantType", "VAR_INT", VAR_INT);
    engine->RegisterEnumValue("VariantType", "VAR_BOOL", VAR_BOOL);
    engine->RegisterEnumValue("VariantType", "VAR_FLOAT", VAR_FLOAT);
    engine->RegisterEnumValue("VariantType", "VAR_VECTOR2", VAR_VECTOR2);
    engine->RegisterEnumValue("VariantType", "VAR_VECTOR3", VAR_VECTOR3);
    engine->RegisterEnumValue("VariantType", "VAR_VECTOR4", VAR_VECTOR4);
    engine->RegisterEnumValue("VariantType", "VAR_QUATERNION", VAR_QUATERNION);
    engine->RegisterEnumValue("VariantType", "VAR_COLOR", VAR_COLOR);
    engine->RegisterEnumValue("VariantType", "VAR_STRING", VAR_STRING);
    engine->RegisterEnumValue("VariantType", "VAR_BUFFER", VAR_BUFFER);
    engine->RegisterEnumValue("VariantType", "VAR_VOIDPTR", VAR_VOIDPTR);
    engine->RegisterEnumValue("VariantType", "VAR_RESOURCEREF", VAR_RESOURCEREF);
    engine->RegisterEnumValue("VariantType", "VAR_RESOURCEREFLIST", VAR_RESOURCEREFLIST);
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTVECTOR", VAR_VARIANTVECTOR);
    engine->RegisterEnumValue("VariantType", "VAR_VARIANTMAP", VAR_VARIANTMAP);
    engine->RegisterEnumValue("VariantType", "VAR_INTRECT", VAR_INTRECT);
    engine->RegisterEnumValue("VariantType", "VAR_INTVECTOR2", VAR_INTVECTOR2);
    engine->RegisterEnumValue("VariantType", "VAR_PTR", VAR_PTR);
    engine->RegisterEnumValue("VariantType", "VAR_MATRIX3", VAR_MATRIX3);
    engine->RegisterEnumValue("VariantType", "VAR_MATRIX3X4", VAR_MATRIX3X4);
    engine->RegisterEnumValue("VariantType", "VAR_MATRIX4", VAR_MATRIX4);
    engine->RegisterEnumValue("VariantType", "VAR_DOUBLE", VAR_DOUBLE);
    engine->RegisterEnumValue("VariantType", "VAR_STRINGVECTOR", VAR_STRINGVECTOR);
    engine->RegisterEnumValue("VariantType", "VAR_RECT", VAR_RECT);
    engine->RegisterEnumValue("VariantType", "VAR_INTVECTOR3", VAR_INTVECTOR3);
    engine->RegisterEnumValue("VariantType", "VAR_INT64", VAR_INT64);
    engine->RegisterEnumValue("VariantType", "VAR_CUSTOM_HEAP", VAR_CUSTOM_HEAP);
    engine->RegisterEnumValue("VariantType", "VAR_CUSTOM_STACK", VAR_CUSTOM_STACK);
    engine->RegisterEnumValue("VariantType", "MAX_VAR_TYPES", MAX_VAR_TYPES);

    // enum VertexElementSemantic | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("VertexElementSemantic");
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_POSITION", SEM_POSITION);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_NORMAL", SEM_NORMAL);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_BINORMAL", SEM_BINORMAL);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_TANGENT", SEM_TANGENT);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_TEXCOORD", SEM_TEXCOORD);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_COLOR", SEM_COLOR);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_BLENDWEIGHTS", SEM_BLENDWEIGHTS);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_BLENDINDICES", SEM_BLENDINDICES);
    engine->RegisterEnumValue("VertexElementSemantic", "SEM_OBJECTINDEX", SEM_OBJECTINDEX);
    engine->RegisterEnumValue("VertexElementSemantic", "MAX_VERTEX_ELEMENT_SEMANTICS", MAX_VERTEX_ELEMENT_SEMANTICS);

    // enum VertexElementType | File: ../Graphics/GraphicsDefs.h
    engine->RegisterEnum("VertexElementType");
    engine->RegisterEnumValue("VertexElementType", "TYPE_INT", TYPE_INT);
    engine->RegisterEnumValue("VertexElementType", "TYPE_FLOAT", TYPE_FLOAT);
    engine->RegisterEnumValue("VertexElementType", "TYPE_VECTOR2", TYPE_VECTOR2);
    engine->RegisterEnumValue("VertexElementType", "TYPE_VECTOR3", TYPE_VECTOR3);
    engine->RegisterEnumValue("VertexElementType", "TYPE_VECTOR4", TYPE_VECTOR4);
    engine->RegisterEnumValue("VertexElementType", "TYPE_UBYTE4", TYPE_UBYTE4);
    engine->RegisterEnumValue("VertexElementType", "TYPE_UBYTE4_NORM", TYPE_UBYTE4_NORM);
    engine->RegisterEnumValue("VertexElementType", "MAX_VERTEX_ELEMENT_TYPES", MAX_VERTEX_ELEMENT_TYPES);

    // enum VertexLightVSVariation | File: ../Graphics/Renderer.h
    engine->RegisterEnum("VertexLightVSVariation");
    engine->RegisterEnumValue("VertexLightVSVariation", "VLVS_NOLIGHTS", VLVS_NOLIGHTS);
    engine->RegisterEnumValue("VertexLightVSVariation", "VLVS_1LIGHT", VLVS_1LIGHT);
    engine->RegisterEnumValue("VertexLightVSVariation", "VLVS_2LIGHTS", VLVS_2LIGHTS);
    engine->RegisterEnumValue("VertexLightVSVariation", "VLVS_3LIGHTS", VLVS_3LIGHTS);
    engine->RegisterEnumValue("VertexLightVSVariation", "VLVS_4LIGHTS", VLVS_4LIGHTS);
    engine->RegisterEnumValue("VertexLightVSVariation", "MAX_VERTEXLIGHT_VS_VARIATIONS", MAX_VERTEXLIGHT_VS_VARIATIONS);

    // enum VertexMask : unsigned | File: ../Graphics/GraphicsDefs.h
    engine->RegisterTypedef("VertexMask", "uint");
    engine->RegisterGlobalProperty("const uint MASK_NONE", (void*)&VertexMask_MASK_NONE);
    engine->RegisterGlobalProperty("const uint MASK_POSITION", (void*)&VertexMask_MASK_POSITION);
    engine->RegisterGlobalProperty("const uint MASK_NORMAL", (void*)&VertexMask_MASK_NORMAL);
    engine->RegisterGlobalProperty("const uint MASK_COLOR", (void*)&VertexMask_MASK_COLOR);
    engine->RegisterGlobalProperty("const uint MASK_TEXCOORD1", (void*)&VertexMask_MASK_TEXCOORD1);
    engine->RegisterGlobalProperty("const uint MASK_TEXCOORD2", (void*)&VertexMask_MASK_TEXCOORD2);
    engine->RegisterGlobalProperty("const uint MASK_CUBETEXCOORD1", (void*)&VertexMask_MASK_CUBETEXCOORD1);
    engine->RegisterGlobalProperty("const uint MASK_CUBETEXCOORD2", (void*)&VertexMask_MASK_CUBETEXCOORD2);
    engine->RegisterGlobalProperty("const uint MASK_TANGENT", (void*)&VertexMask_MASK_TANGENT);
    engine->RegisterGlobalProperty("const uint MASK_BLENDWEIGHTS", (void*)&VertexMask_MASK_BLENDWEIGHTS);
    engine->RegisterGlobalProperty("const uint MASK_BLENDINDICES", (void*)&VertexMask_MASK_BLENDINDICES);
    engine->RegisterGlobalProperty("const uint MASK_INSTANCEMATRIX1", (void*)&VertexMask_MASK_INSTANCEMATRIX1);
    engine->RegisterGlobalProperty("const uint MASK_INSTANCEMATRIX2", (void*)&VertexMask_MASK_INSTANCEMATRIX2);
    engine->RegisterGlobalProperty("const uint MASK_INSTANCEMATRIX3", (void*)&VertexMask_MASK_INSTANCEMATRIX3);
    engine->RegisterGlobalProperty("const uint MASK_OBJECTINDEX", (void*)&VertexMask_MASK_OBJECTINDEX);

    // URHO3D_FLAGSET(VertexMask, VertexMaskFlags) | File: ../Graphics/GraphicsDefs.h
    engine->RegisterTypedef("VertexMaskFlags", "uint");

    // enum VerticalAlignment | File: ../UI/UIElement.h
    engine->RegisterEnum("VerticalAlignment");
    engine->RegisterEnumValue("VerticalAlignment", "VA_TOP", VA_TOP);
    engine->RegisterEnumValue("VerticalAlignment", "VA_CENTER", VA_CENTER);
    engine->RegisterEnumValue("VerticalAlignment", "VA_BOTTOM", VA_BOTTOM);
    engine->RegisterEnumValue("VerticalAlignment", "VA_CUSTOM", VA_CUSTOM);

    // enum ViewOverride : unsigned | File: ../Graphics/Camera.h
    engine->RegisterTypedef("ViewOverride", "uint");
    engine->RegisterGlobalProperty("const uint VO_NONE", (void*)&ViewOverride_VO_NONE);
    engine->RegisterGlobalProperty("const uint VO_LOW_MATERIAL_QUALITY", (void*)&ViewOverride_VO_LOW_MATERIAL_QUALITY);
    engine->RegisterGlobalProperty("const uint VO_DISABLE_SHADOWS", (void*)&ViewOverride_VO_DISABLE_SHADOWS);
    engine->RegisterGlobalProperty("const uint VO_DISABLE_OCCLUSION", (void*)&ViewOverride_VO_DISABLE_OCCLUSION);

    // URHO3D_FLAGSET(ViewOverride, ViewOverrideFlags) | File: ../Graphics/Camera.h
    engine->RegisterTypedef("ViewOverrideFlags", "uint");

    // enum WindowDragMode | File: ../UI/Window.h
    engine->RegisterEnum("WindowDragMode");
    engine->RegisterEnumValue("WindowDragMode", "DRAG_NONE", DRAG_NONE);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_MOVE", DRAG_MOVE);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_TOPLEFT", DRAG_RESIZE_TOPLEFT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_TOP", DRAG_RESIZE_TOP);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_TOPRIGHT", DRAG_RESIZE_TOPRIGHT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_RIGHT", DRAG_RESIZE_RIGHT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_BOTTOMRIGHT", DRAG_RESIZE_BOTTOMRIGHT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_BOTTOM", DRAG_RESIZE_BOTTOM);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_BOTTOMLEFT", DRAG_RESIZE_BOTTOMLEFT);
    engine->RegisterEnumValue("WindowDragMode", "DRAG_RESIZE_LEFT", DRAG_RESIZE_LEFT);

    // enum WrapMode | File: ../Scene/AnimationDefs.h
    engine->RegisterEnum("WrapMode");
    engine->RegisterEnumValue("WrapMode", "WM_LOOP", WM_LOOP);
    engine->RegisterEnumValue("WrapMode", "WM_ONCE", WM_ONCE);
    engine->RegisterEnumValue("WrapMode", "WM_CLAMP", WM_CLAMP);

#ifdef URHO3D_DATABASE
    // enum DBAPI | File: ../Database/Database.h
    engine->RegisterEnum("DBAPI");
    engine->RegisterEnumValue("DBAPI", "DBAPI_SQLITE", DBAPI_SQLITE);
    engine->RegisterEnumValue("DBAPI", "DBAPI_ODBC", DBAPI_ODBC);
#endif

#ifdef URHO3D_NAVIGATION
    // enum CrowdAgentRequestedTarget | File: ../Navigation/CrowdAgent.h
    engine->RegisterEnum("CrowdAgentRequestedTarget");
    engine->RegisterEnumValue("CrowdAgentRequestedTarget", "CA_REQUESTEDTARGET_NONE", CA_REQUESTEDTARGET_NONE);
    engine->RegisterEnumValue("CrowdAgentRequestedTarget", "CA_REQUESTEDTARGET_POSITION", CA_REQUESTEDTARGET_POSITION);
    engine->RegisterEnumValue("CrowdAgentRequestedTarget", "CA_REQUESTEDTARGET_VELOCITY", CA_REQUESTEDTARGET_VELOCITY);

    // enum CrowdAgentState | File: ../Navigation/CrowdAgent.h
    engine->RegisterEnum("CrowdAgentState");
    engine->RegisterEnumValue("CrowdAgentState", "CA_STATE_INVALID", CA_STATE_INVALID);
    engine->RegisterEnumValue("CrowdAgentState", "CA_STATE_WALKING", CA_STATE_WALKING);
    engine->RegisterEnumValue("CrowdAgentState", "CA_STATE_OFFMESH", CA_STATE_OFFMESH);

    // enum CrowdAgentTargetState | File: ../Navigation/CrowdAgent.h
    engine->RegisterEnum("CrowdAgentTargetState");
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_NONE", CA_TARGET_NONE);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_FAILED", CA_TARGET_FAILED);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_VALID", CA_TARGET_VALID);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_REQUESTING", CA_TARGET_REQUESTING);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_WAITINGFORQUEUE", CA_TARGET_WAITINGFORQUEUE);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_WAITINGFORPATH", CA_TARGET_WAITINGFORPATH);
    engine->RegisterEnumValue("CrowdAgentTargetState", "CA_TARGET_VELOCITY", CA_TARGET_VELOCITY);

    // enum NavigationPathPointFlag | File: ../Navigation/NavigationMesh.h
    engine->RegisterEnum("NavigationPathPointFlag");
    engine->RegisterEnumValue("NavigationPathPointFlag", "NAVPATHFLAG_NONE", NAVPATHFLAG_NONE);
    engine->RegisterEnumValue("NavigationPathPointFlag", "NAVPATHFLAG_START", NAVPATHFLAG_START);
    engine->RegisterEnumValue("NavigationPathPointFlag", "NAVPATHFLAG_END", NAVPATHFLAG_END);
    engine->RegisterEnumValue("NavigationPathPointFlag", "NAVPATHFLAG_OFF_MESH", NAVPATHFLAG_OFF_MESH);

    // enum NavigationPushiness | File: ../Navigation/CrowdAgent.h
    engine->RegisterEnum("NavigationPushiness");
    engine->RegisterEnumValue("NavigationPushiness", "NAVIGATIONPUSHINESS_LOW", NAVIGATIONPUSHINESS_LOW);
    engine->RegisterEnumValue("NavigationPushiness", "NAVIGATIONPUSHINESS_MEDIUM", NAVIGATIONPUSHINESS_MEDIUM);
    engine->RegisterEnumValue("NavigationPushiness", "NAVIGATIONPUSHINESS_HIGH", NAVIGATIONPUSHINESS_HIGH);
    engine->RegisterEnumValue("NavigationPushiness", "NAVIGATIONPUSHINESS_NONE", NAVIGATIONPUSHINESS_NONE);

    // enum NavigationQuality | File: ../Navigation/CrowdAgent.h
    engine->RegisterEnum("NavigationQuality");
    engine->RegisterEnumValue("NavigationQuality", "NAVIGATIONQUALITY_LOW", NAVIGATIONQUALITY_LOW);
    engine->RegisterEnumValue("NavigationQuality", "NAVIGATIONQUALITY_MEDIUM", NAVIGATIONQUALITY_MEDIUM);
    engine->RegisterEnumValue("NavigationQuality", "NAVIGATIONQUALITY_HIGH", NAVIGATIONQUALITY_HIGH);

    // enum NavmeshPartitionType | File: ../Navigation/NavigationMesh.h
    engine->RegisterEnum("NavmeshPartitionType");
    engine->RegisterEnumValue("NavmeshPartitionType", "NAVMESH_PARTITION_WATERSHED", NAVMESH_PARTITION_WATERSHED);
    engine->RegisterEnumValue("NavmeshPartitionType", "NAVMESH_PARTITION_MONOTONE", NAVMESH_PARTITION_MONOTONE);
#endif

#ifdef URHO3D_NETWORK
    // enum HttpRequestState | File: ../Network/HttpRequest.h
    engine->RegisterEnum("HttpRequestState");
    engine->RegisterEnumValue("HttpRequestState", "HTTP_INITIALIZING", HTTP_INITIALIZING);
    engine->RegisterEnumValue("HttpRequestState", "HTTP_ERROR", HTTP_ERROR);
    engine->RegisterEnumValue("HttpRequestState", "HTTP_OPEN", HTTP_OPEN);
    engine->RegisterEnumValue("HttpRequestState", "HTTP_CLOSED", HTTP_CLOSED);

    // enum ObserverPositionSendMode | File: ../Network/Connection.h
    engine->RegisterEnum("ObserverPositionSendMode");
    engine->RegisterEnumValue("ObserverPositionSendMode", "OPSM_NONE", OPSM_NONE);
    engine->RegisterEnumValue("ObserverPositionSendMode", "OPSM_POSITION", OPSM_POSITION);
    engine->RegisterEnumValue("ObserverPositionSendMode", "OPSM_POSITION_ROTATION", OPSM_POSITION_ROTATION);

    // enum PacketType | File: ../Network/Connection.h
    engine->RegisterEnum("PacketType");
    engine->RegisterEnumValue("PacketType", "PT_UNRELIABLE_UNORDERED", PT_UNRELIABLE_UNORDERED);
    engine->RegisterEnumValue("PacketType", "PT_UNRELIABLE_ORDERED", PT_UNRELIABLE_ORDERED);
    engine->RegisterEnumValue("PacketType", "PT_RELIABLE_UNORDERED", PT_RELIABLE_UNORDERED);
    engine->RegisterEnumValue("PacketType", "PT_RELIABLE_ORDERED", PT_RELIABLE_ORDERED);
#endif

#ifdef URHO3D_PHYSICS
    // enum CollisionEventMode | File: ../Physics/RigidBody.h
    engine->RegisterEnum("CollisionEventMode");
    engine->RegisterEnumValue("CollisionEventMode", "COLLISION_NEVER", COLLISION_NEVER);
    engine->RegisterEnumValue("CollisionEventMode", "COLLISION_ACTIVE", COLLISION_ACTIVE);
    engine->RegisterEnumValue("CollisionEventMode", "COLLISION_ALWAYS", COLLISION_ALWAYS);

    // enum ConstraintType | File: ../Physics/Constraint.h
    engine->RegisterEnum("ConstraintType");
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_POINT", CONSTRAINT_POINT);
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_HINGE", CONSTRAINT_HINGE);
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_SLIDER", CONSTRAINT_SLIDER);
    engine->RegisterEnumValue("ConstraintType", "CONSTRAINT_CONETWIST", CONSTRAINT_CONETWIST);

    // enum ShapeType | File: ../Physics/CollisionShape.h
    engine->RegisterEnum("ShapeType");
    engine->RegisterEnumValue("ShapeType", "SHAPE_BOX", SHAPE_BOX);
    engine->RegisterEnumValue("ShapeType", "SHAPE_SPHERE", SHAPE_SPHERE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_STATICPLANE", SHAPE_STATICPLANE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CYLINDER", SHAPE_CYLINDER);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CAPSULE", SHAPE_CAPSULE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CONE", SHAPE_CONE);
    engine->RegisterEnumValue("ShapeType", "SHAPE_TRIANGLEMESH", SHAPE_TRIANGLEMESH);
    engine->RegisterEnumValue("ShapeType", "SHAPE_CONVEXHULL", SHAPE_CONVEXHULL);
    engine->RegisterEnumValue("ShapeType", "SHAPE_TERRAIN", SHAPE_TERRAIN);
    engine->RegisterEnumValue("ShapeType", "SHAPE_GIMPACTMESH", SHAPE_GIMPACTMESH);
#endif

#ifdef URHO3D_URHO2D
    // enum BodyType2D | File: ../Urho2D/RigidBody2D.h
    engine->RegisterEnum("BodyType2D");
    engine->RegisterEnumValue("BodyType2D", "BT_STATIC", BT_STATIC);
    engine->RegisterEnumValue("BodyType2D", "BT_KINEMATIC", BT_KINEMATIC);
    engine->RegisterEnumValue("BodyType2D", "BT_DYNAMIC", BT_DYNAMIC);

    // enum EmitterType2D | File: ../Urho2D/ParticleEffect2D.h
    engine->RegisterEnum("EmitterType2D");
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_GRAVITY", EMITTER_TYPE_GRAVITY);
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_RADIAL", EMITTER_TYPE_RADIAL);

    // enum LoopMode2D | File: ../Urho2D/AnimatedSprite2D.h
    engine->RegisterEnum("LoopMode2D");
    engine->RegisterEnumValue("LoopMode2D", "LM_DEFAULT", LM_DEFAULT);
    engine->RegisterEnumValue("LoopMode2D", "LM_FORCE_LOOPED", LM_FORCE_LOOPED);
    engine->RegisterEnumValue("LoopMode2D", "LM_FORCE_CLAMPED", LM_FORCE_CLAMPED);

    // enum Orientation2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterEnum("Orientation2D");
    engine->RegisterEnumValue("Orientation2D", "O_ORTHOGONAL", O_ORTHOGONAL);
    engine->RegisterEnumValue("Orientation2D", "O_ISOMETRIC", O_ISOMETRIC);
    engine->RegisterEnumValue("Orientation2D", "O_STAGGERED", O_STAGGERED);
    engine->RegisterEnumValue("Orientation2D", "O_HEXAGONAL", O_HEXAGONAL);

    // enum TileMapLayerType2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterEnum("TileMapLayerType2D");
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_TILE_LAYER", LT_TILE_LAYER);
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_OBJECT_GROUP", LT_OBJECT_GROUP);
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_IMAGE_LAYER", LT_IMAGE_LAYER);
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_INVALID", LT_INVALID);

    // enum TileMapObjectType2D | File: ../Urho2D/TileMapDefs2D.h
    engine->RegisterEnum("TileMapObjectType2D");
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_RECTANGLE", OT_RECTANGLE);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_ELLIPSE", OT_ELLIPSE);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_POLYGON", OT_POLYGON);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_POLYLINE", OT_POLYLINE);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_TILE", OT_TILE);
    engine->RegisterEnumValue("TileMapObjectType2D", "OT_INVALID", OT_INVALID);
#endif
}

}
