#pragma once

#ifndef GRAPHIE_INPUT_H
#define GRAPHIE_INPUT_H

#include "grpch.h"

#include "Graphite/EventCore/grEvents.h"
#include "Graphite/Core/Core.h"
#include "Graphite/Core/Application.h"

#include "GLFW/glfw3.h"

#define GR_KEY_UNKNOWN						 -1

// glfw keys standardized for Graphite to be used in different window APIs if needed in the future
#define GR_KEY_SPACE						 32
#define GR_KEY_APOSTROPHE					 39  /* ' */
#define GR_KEY_COMMA						 44  /* , */
#define GR_KEY_MINUS						 45  /* - */
#define GR_KEY_PERIOD						 46  /* . */
#define GR_KEY_SLASH						 47  /* / */
#define GR_KEY_0							 48
#define GR_KEY_1							 49
#define GR_KEY_2							 50
#define GR_KEY_3							 51
#define GR_KEY_4							 52
#define GR_KEY_5							 53
#define GR_KEY_6							 54
#define GR_KEY_7							 55
#define GR_KEY_8							 56
#define GR_KEY_9							 57
#define GR_KEY_SEMICOLON					 59  /* ; */
#define GR_KEY_EQUAL						 61  /* = */
#define GR_KEY_A							 65
#define GR_KEY_B							 66
#define GR_KEY_C							 67
#define GR_KEY_D							 68
#define GR_KEY_E							 69
#define GR_KEY_F							 70
#define GR_KEY_G							 71
#define GR_KEY_H							 72
#define GR_KEY_I							 73
#define GR_KEY_J							 74
#define GR_KEY_K							 75
#define GR_KEY_L							 76
#define GR_KEY_M							 77
#define GR_KEY_N							 78
#define GR_KEY_O							 79
#define GR_KEY_P							 80
#define GR_KEY_Q							 81
#define GR_KEY_R							 82
#define GR_KEY_S							 83
#define GR_KEY_T							 84
#define GR_KEY_U							 85
#define GR_KEY_V							 86
#define GR_KEY_W							 87
#define GR_KEY_X							 88
#define GR_KEY_Y							 89
#define GR_KEY_Z							 90
#define GR_KEY_LEFT_BRACKET					 91  /* [ */
#define GR_KEY_BACKSLASH					 92  /* \ */
#define GR_KEY_RIGHT_BRACKET				 93  /* ] */
#define GR_KEY_GRAVE_ACCENT					 96  /* ` */
#define GR_KEY_WORLD_1						 161 /* non-US #1 */
#define GR_KEY_WORLD_2						 162 /* non-US #2 */

/* Function keys */
#define GR_KEY_ESCAPE						 256
#define GR_KEY_ENTER						 257
#define GR_KEY_TAB							 258
#define GR_KEY_BACKSPACE					 259
#define GR_KEY_INSERT						 260
#define GR_KEY_DELETE						 261
#define GR_KEY_RIGHT						 262
#define GR_KEY_LEFT							 263
#define GR_KEY_DOWN							 264
#define GR_KEY_UP							 265
#define GR_KEY_PAGE_UP						 266
#define GR_KEY_PAGE_DOWN					 267
#define GR_KEY_HOME							 268
#define GR_KEY_END							 269
#define GR_KEY_CAPS_LOCK					 280
#define GR_KEY_SCROLL_LOCK					 281
#define GR_KEY_NUM_LOCK						 282
#define GR_KEY_PRINT_SCREEN					 283
#define GR_KEY_PAUSE						 284
#define GR_KEY_F1							 290
#define GR_KEY_F2							 291
#define GR_KEY_F3							 292
#define GR_KEY_F4							 293
#define GR_KEY_F5							 294
#define GR_KEY_F6							 295
#define GR_KEY_F7							 296
#define GR_KEY_F8							 297
#define GR_KEY_F9							 298
#define GR_KEY_F10							 299
#define GR_KEY_F11							 300
#define GR_KEY_F12							 301
#define GR_KEY_F13							 302
#define GR_KEY_F14							 303
#define GR_KEY_F15							 304
#define GR_KEY_F16							 305
#define GR_KEY_F17							 306
#define GR_KEY_F18							 307
#define GR_KEY_F19							 308
#define GR_KEY_F20							 309
#define GR_KEY_F21							 310
#define GR_KEY_F22							 311
#define GR_KEY_F23							 312
#define GR_KEY_F24							 313
#define GR_KEY_F25							 314
#define GR_KEY_KP_0							 320
#define GR_KEY_KP_1							 321
#define GR_KEY_KP_2							 322
#define GR_KEY_KP_3							 323
#define GR_KEY_KP_4							 324
#define GR_KEY_KP_5							 325
#define GR_KEY_KP_6							 326
#define GR_KEY_KP_7							 327
#define GR_KEY_KP_8							 328
#define GR_KEY_KP_9							 329
#define GR_KEY_KP_DECIMAL					 330
#define GR_KEY_KP_DIVIDE					 331
#define GR_KEY_KP_MULTIPLY					 332
#define GR_KEY_KP_SUBTRACT					 333
#define GR_KEY_KP_ADD						 334
#define GR_KEY_KP_ENTER						 335
#define GR_KEY_KP_EQUAL						 336
#define GR_KEY_LEFT_SHIFT					 340
#define GR_KEY_LEFT_CONTROL					 341
#define GR_KEY_LEFT_ALT						 342
#define GR_KEY_LEFT_SUPER					 343
#define GR_KEY_RIGHT_SHIFT					 344
#define GR_KEY_RIGHT_CONTROL				 345
#define GR_KEY_RIGHT_ALT					 346
#define GR_KEY_RIGHT_SUPER					 347
#define GR_KEY_MENU							 348

#define GR_KEY_LAST							 GR_KEY_MENU


#define GR_MOUSE_BUTTON_1					 0
#define GR_MOUSE_BUTTON_2					 1
#define GR_MOUSE_BUTTON_3					 2
#define GR_MOUSE_BUTTON_4					 3
#define GR_MOUSE_BUTTON_5					 4
#define GR_MOUSE_BUTTON_6					 5
#define GR_MOUSE_BUTTON_7					 6
#define GR_MOUSE_BUTTON_8					 7
#define GR_MOUSE_BUTTON_LAST				 GR_MOUSE_BUTTON_8
#define GR_MOUSE_BUTTON_LEFT				 GR_MOUSE_BUTTON_1
#define GR_MOUSE_BUTTON_RIGHT				 GR_MOUSE_BUTTON_2
#define GR_MOUSE_BUTTON_MIDDLE				 GR_MOUSE_BUTTON_3


//For later implementation, to possibly support custom or differently mapped game controllers
 
#define GR_JOYSTICK_1						 0
#define GR_JOYSTICK_2						 1
#define GR_JOYSTICK_3						 2
#define GR_JOYSTICK_4						 3
#define GR_JOYSTICK_5						 4
#define GR_JOYSTICK_6						 5
#define GR_JOYSTICK_7						 6
#define GR_JOYSTICK_8						 7
#define GR_JOYSTICK_9						 8
#define GR_JOYSTICK_10						 9
#define GR_JOYSTICK_11						 10
#define GR_JOYSTICK_12						 11
#define GR_JOYSTICK_13						 12
#define GR_JOYSTICK_14						 13
#define GR_JOYSTICK_15					     14
#define GR_JOYSTICK_16						 15
#define GR_JOYSTICK_LAST					 GR_JOYSTICK_16




#define GR_CONTROLLER_BUTTON_A               0
#define GR_CONTROLLER_BUTTON_B               1
#define GR_CONTROLLER_BUTTON_X               2
#define GR_CONTROLLER_BUTTON_Y               3
#define GR_CONTROLLER_BUTTON_LEFT_BUMPER     4
#define GR_CONTROLLER_BUTTON_RIGHT_BUMPER    5
#define GR_CONTROLLER_BUTTON_BACK            6
#define GR_CONTROLLER_BUTTON_START           7
#define GR_CONTROLLER_BUTTON_GUIDE           8
#define GR_CONTROLLER_BUTTON_LEFT_THUMB      9
#define GR_CONTROLLER_BUTTON_RIGHT_THUMB     10
#define GR_CONTROLLER_BUTTON_DPAD_UP         11
#define GR_CONTROLLER_BUTTON_DPAD_RIGHT      12
#define GR_CONTROLLER_BUTTON_DPAD_DOWN       13
#define GR_CONTROLLER_BUTTON_DPAD_LEFT       14
#define GR_CONTROLLER_BUTTON_LAST            GR_CONTROLLER_BUTTON_DPAD_LEFT

#define GR_CONTROLLER_BUTTON_CROSS			 GR_CONTROLLER_BUTTON_A
#define GR_CONTROLLER_BUTTON_CIRCLE			 GR_CONTROLLER_BUTTON_B
#define GR_CONTROLLER_BUTTON_SQUARE			 GR_CONTROLLER_BUTTON_X
#define GR_CONTROLLER_BUTTON_TRIANGLE		 GR_CONTROLLER_BUTTON_Y


#define GR_CONTROLLER_AXIS_LEFT_X			 0
#define GR_CONTROLLER_AXIS_LEFT_Y			 1
#define GR_CONTROLLER_AXIS_RIGHT_X			 2
#define GR_CONTROLLER_AXIS_RIGHT_Y			 3
#define GR_CONTROLLER_AXIS_LEFT_TRIGGER		 4
#define GR_CONTROLLER_AXIS_RIGHT_TRIGGER	 5
#define GR_CONTROLLER_AXIS_LAST				 GR_CONTROLLER_AXIS_RIGHT_TRIGGER




namespace Graphite
{
	/// <summary>
	/// grInput class, used for supporting the event polling
	/// </summary>
	class GRAPHITE_API grInput
	{
	public:
		static bool grIsKeyPressed(int keycode);
		static bool grIsMouseButtonPressed(int keycode);
		static bool grIsMouseInWindow();

		static std::pair<double, double> grGetMousePosition();
	};
}


#endif
