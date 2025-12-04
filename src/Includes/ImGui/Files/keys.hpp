#include "../../../includes/skstr.hpp"

static const char* KeyNames[] = {
	skCrypt("OFF"),                   // 0
	skCrypt("VK_LBUTTON"),            // 1
	skCrypt("VK_RBUTTON"),            // 2
	skCrypt("VK_CANCEL"),             // 3
	skCrypt("VK_MBUTTON"),            // 4
	skCrypt("VK_XBUTTON1"),           // 5
	skCrypt("VK_XBUTTON2"),           // 6
	skCrypt("Unknown"),               // 7
	skCrypt("VK_BACK"),               // 8
	skCrypt("VK_TAB"),                // 9
	skCrypt("Unknown"),               // 10
	skCrypt("Unknown"),               // 11
	skCrypt("VK_CLEAR"),              // 12
	skCrypt("VK_RETURN"),             // 13
	skCrypt("Unknown"),               // 14
	skCrypt("Unknown"),               // 15
	skCrypt("VK_SHIFT"),              // 16
	skCrypt("VK_CONTROL"),            // 17
	skCrypt("VK_MENU"),               // 18
	skCrypt("VK_PAUSE"),              // 19
	skCrypt("VK_CAPITAL"),            // 20
	skCrypt("VK_KANA"),               // 21
	skCrypt("Unknown"),               // 22
	skCrypt("VK_JUNJA"),              // 23
	skCrypt("VK_FINAL"),              // 24
	skCrypt("VK_KANJI"),              // 25
	skCrypt("Unknown"),               // 26
	skCrypt("VK_ESCAPE"),             // 27
	skCrypt("VK_CONVERT"),            // 28
	skCrypt("VK_NONCONVERT"),         // 29
	skCrypt("VK_ACCEPT"),             // 30
	skCrypt("VK_MODECHANGE"),         // 31
	skCrypt("VK_SPACE"),              // 32
	skCrypt("VK_PRIOR"),              // 33
	skCrypt("VK_NEXT"),               // 34
	skCrypt("VK_END"),                // 35
	skCrypt("VK_HOME"),               // 36
	skCrypt("VK_LEFT"),               // 37
	skCrypt("VK_UP"),                 // 38
	skCrypt("VK_RIGHT"),              // 39
	skCrypt("VK_DOWN"),               // 40
	skCrypt("VK_SELECT"),             // 41
	skCrypt("VK_PRINT"),              // 42
	skCrypt("VK_EXECUTE"),            // 43
	skCrypt("VK_SNAPSHOT"),           // 44
	skCrypt("VK_INSERT"),             // 45
	skCrypt("VK_DELETE"),             // 46
	skCrypt("VK_HELP"),               // 47
	skCrypt("0"),                     // 48
	skCrypt("1"),                     // 49
	skCrypt("2"),                     // 50
	skCrypt("3"),                     // 51
	skCrypt("4"),                     // 52
	skCrypt("5"),                     // 53
	skCrypt("6"),                     // 54
	skCrypt("7"),                     // 55
	skCrypt("8"),                     // 56
	skCrypt("9"),                     // 57
	skCrypt("Unknown"),               // 58
	skCrypt("Unknown"),               // 59
	skCrypt("Unknown"),               // 60
	skCrypt("Unknown"),               // 61
	skCrypt("Unknown"),               // 62
	skCrypt("Unknown"),               // 63
	skCrypt("Unknown"),               // 64
	skCrypt("A"),                     // 65
	skCrypt("B"),                     // 66
	skCrypt("C"),                     // 67
	skCrypt("D"),                     // 68
	skCrypt("E"),                     // 69
	skCrypt("F"),                     // 70
	skCrypt("G"),                     // 71
	skCrypt("H"),                     // 72
	skCrypt("I"),                     // 73
	skCrypt("J"),                     // 74
	skCrypt("K"),                     // 75
	skCrypt("L"),                     // 76
	skCrypt("M"),                     // 77
	skCrypt("N"),                     // 78
	skCrypt("O"),                     // 79
	skCrypt("P"),                     // 80
	skCrypt("Q"),                     // 81
	skCrypt("R"),                     // 82
	skCrypt("S"),                     // 83
	skCrypt("T"),                     // 84
	skCrypt("U"),                     // 85
	skCrypt("V"),                     // 86
	skCrypt("W"),                     // 87
	skCrypt("X"),                     // 88
	skCrypt("Y"),                     // 89
	skCrypt("Z"),                     // 90
	skCrypt("VK_LWIN"),               // 91
	skCrypt("VK_RWIN"),               // 92
	skCrypt("VK_APPS"),               // 93
	skCrypt("Unknown"),               // 94
	skCrypt("VK_SLEEP"),              // 95
	skCrypt("VK_NUMPAD0"),            // 96
	skCrypt("VK_NUMPAD1"),            // 97
	skCrypt("VK_NUMPAD2"),            // 98
	skCrypt("VK_NUMPAD3"),            // 99
	skCrypt("VK_NUMPAD4"),            // 100
	skCrypt("VK_NUMPAD5"),            // 101
	skCrypt("VK_NUMPAD6"),            // 102
	skCrypt("VK_NUMPAD7"),            // 103
	skCrypt("VK_NUMPAD8"),            // 104
	skCrypt("VK_NUMPAD9"),            // 105
	skCrypt("VK_MULTIPLY"),           // 106
	skCrypt("VK_ADD"),                // 107
	skCrypt("VK_SEPARATOR"),          // 108
	skCrypt("VK_SUBTRACT"),           // 109
	skCrypt("VK_DECIMAL"),            // 110
	skCrypt("VK_DIVIDE"),             // 111
	skCrypt("VK_F1"),                 // 112
	skCrypt("VK_F2"),                 // 113
	skCrypt("VK_F3"),                 // 114
	skCrypt("VK_F4"),                 // 115
	skCrypt("VK_F5"),                 // 116
	skCrypt("VK_F6"),                 // 117
	skCrypt("VK_F7"),                 // 118
	skCrypt("VK_F8"),                 // 119
	skCrypt("VK_F9"),                 // 120
	skCrypt("VK_F10"),                // 121
	skCrypt("VK_F11"),                // 122
	skCrypt("VK_F12"),                // 123
	skCrypt("VK_F13"),                // 124
	skCrypt("VK_F14"),                // 125
	skCrypt("VK_F15"),                // 126
	skCrypt("VK_F16"),                // 127
	skCrypt("VK_F17"),                // 128
	skCrypt("VK_F18"),                // 129
	skCrypt("VK_F19"),                // 130
	skCrypt("VK_F20"),                // 131
	skCrypt("VK_F21"),                // 132
	skCrypt("VK_F22"),                // 133
	skCrypt("VK_F23"),                // 134
	skCrypt("VK_F24"),                // 135
	skCrypt("Unknown"),               // 136
	skCrypt("Unknown"),               // 137
	skCrypt("Unknown"),               // 138
	skCrypt("Unknown"),               // 139
	skCrypt("Unknown"),               // 140
	skCrypt("Unknown"),               // 141
	skCrypt("Unknown"),               // 142
	skCrypt("Unknown"),               // 143
	skCrypt("VK_NUMLOCK"),            // 144
	skCrypt("VK_SCROLL"),             // 145
	skCrypt("VK_OEM_NEC_EQUAL"),      // 146
	skCrypt("VK_OEM_FJ_MASSHOU"),     // 147
	skCrypt("VK_OEM_FJ_TOUROKU"),     // 148
	skCrypt("VK_OEM_FJ_LOYA"),        // 149
	skCrypt("VK_OEM_FJ_ROYA"),        // 150
	skCrypt("Unknown"),               // 151
	skCrypt("Unknown"),               // 152
	skCrypt("Unknown"),               // 153
	skCrypt("Unknown"),               // 154
	skCrypt("Unknown"),               // 155
	skCrypt("Unknown"),               // 156
	skCrypt("Unknown"),               // 157
	skCrypt("Unknown"),               // 158
	skCrypt("Unknown"),               // 159
	skCrypt("VK_LSHIFT"),             // 160
	skCrypt("VK_RSHIFT"),             // 161
	skCrypt("VK_LCONTROL"),           // 162
	skCrypt("VK_RCONTROL"),           // 163
	skCrypt("VK_LMENU"),              // 164
	skCrypt("VK_RMENU")               // 165
};

static const int KeyCodes[] = {
	0x0,  // Undefined
	0x01, // VK_LBUTTON (Mouse Left Button)
	0x02, // VK_RBUTTON (Mouse Right Button)
	0x03, // VK_CANCEL
	0x04, // VK_MBUTTON (Mouse Middle Button)
	0x05, // VK_XBUTTON1 (Mouse X1 Button)
	0x06, // VK_XBUTTON2 (Mouse X2 Button)
	0x07, // Undefined
	0x08, // VK_BACK (Backspace)
	0x09, // VK_TAB (Tab)
	0x0A, // Reserved
	0x0B, // Reserved
	0x0C, // VK_CLEAR
	0x0D, // VK_RETURN (Enter)
	0x0E, // Undefined
	0x0F, // Undefined
	0x10, // VK_SHIFT
	0x11, // VK_CONTROL
	0x12, // VK_MENU (Alt)
	0x13, // VK_PAUSE (Pause/Break)
	0x14, // VK_CAPITAL (Caps Lock)
	0x15, // VK_KANA (IME Kana Mode)
	0x16, // Undefined
	0x17, // VK_JUNJA (IME Junja Mode)
	0x18, // VK_FINAL (IME Final Mode)
	0x19, // VK_KANJI (IME Kanji Mode)
	0x1A, // Undefined
	0x1B, // VK_ESCAPE (Esc)
	0x1C, // VK_CONVERT (IME Convert)
	0x1D, // VK_NONCONVERT (IME Non-Convert)
	0x1E, // VK_ACCEPT (IME Accept)
	0x1F, // VK_MODECHANGE (IME Mode Change)
	0x20, // VK_SPACE (Spacebar)
	0x21, // VK_PRIOR (Page Up)
	0x22, // VK_NEXT (Page Down)
	0x23, // VK_END
	0x24, // VK_HOME
	0x25, // VK_LEFT (Arrow Left)
	0x26, // VK_UP (Arrow Up)
	0x27, // VK_RIGHT (Arrow Right)
	0x28, // VK_DOWN (Arrow Down)
	0x29, // VK_SELECT
	0x2A, // VK_PRINT
	0x2B, // VK_EXECUTE
	0x2C, // VK_SNAPSHOT (Print Screen)
	0x2D, // VK_INSERT
	0x2E, // VK_DELETE
	0x2F, // VK_HELP
	0x30, // '0'
	0x31, // '1'
	0x32, // '2'
	0x33, // '3'
	0x34, // '4'
	0x35, // '5'
	0x36, // '6'
	0x37, // '7'
	0x38, // '8'
	0x39, // '9'
	0x3A, // Undefined
	0x3B, // Undefined
	0x3C, // Undefined
	0x3D, // Undefined
	0x3E, // Undefined
	0x3F, // Undefined
	0x40, // Undefined
	0x41, // 'A'
	0x42, // 'B'
	0x43, // 'C'
	0x44, // 'D'
	0x45, // 'E'
	0x46, // 'F'
	0x47, // 'G'
	0x48, // 'H'
	0x49, // 'I'
	0x4A, // 'J'
	0x4B, // 'K'
	0x4C, // 'L'
	0x4D, // 'M'
	0x4E, // 'N'
	0x4F, // 'O'
	0x50, // 'P'
	0x51, // 'Q'
	0x52, // 'R'
	0x53, // 'S'
	0x54, // 'T'
	0x55, // 'U'
	0x56, // 'V'
	0x57, // 'W'
	0x58, // 'X'
	0x59, // 'Y'
	0x5A, // 'Z'
	0x5B, // VK_LWIN (Left Windows key)
	0x5C, // VK_RWIN (Right Windows key)
	0x5D, // VK_APPS (Applications key)
	0x5E, // Undefined
	0x5F, // VK_SLEEP
	0x60, // VK_NUMPAD0
	0x61, // VK_NUMPAD1
	0x62, // VK_NUMPAD2
	0x63, // VK_NUMPAD3
	0x64, // VK_NUMPAD4
	0x65, // VK_NUMPAD5
	0x66, // VK_NUMPAD6
	0x67, // VK_NUMPAD7
	0x68, // VK_NUMPAD8
	0x69, // VK_NUMPAD9
	0x6A, // VK_MULTIPLY
	0x6B, // VK_ADD
	0x6C, // VK_SEPARATOR
	0x6D, // VK_SUBTRACT
	0x6E, // VK_DECIMAL
	0x6F, // VK_DIVIDE
	0x70, // VK_F1
	0x71, // VK_F2
	0x72, // VK_F3
	0x73, // VK_F4
	0x74, // VK_F5
	0x75, // VK_F6
	0x76, // VK_F7
	0x77, // VK_F8
	0x78, // VK_F9
	0x79, // VK_F10
	0x7A, // VK_F11
	0x7B, // VK_F12
	0x7C, // VK_F13
	0x7D, // VK_F14
	0x7E, // VK_F15
	0x7F, // VK_F16
	0x80, // VK_F17
	0x81, // VK_F18
	0x82, // VK_F19
	0x83, // VK_F20
	0x84, // VK_F21
	0x85, // VK_F22
	0x86, // VK_F23
	0x87, // VK_F24
	0x88, // Undefined
	0x89, // Undefined
	0x8A, // Undefined
	0x8B, // Undefined
	0x8C, // Undefined
	0x8D, // Undefined
	0x8E, // Undefined
	0x8F, // Undefined
	0x90, // VK_NUMLOCK
	0x91, // VK_SCROLL
	0x92, // OEM specific
	0x93, // OEM specific
	0x94, // OEM specific
	0x95, // OEM specific
	0x96, // OEM specific
	0x97, // Undefined
	0x98, // Undefined
	0x99, // Undefined
	0x9A, // Undefined
	0x9B, // Undefined
	0x9C, // Undefined
	0x9D, // Undefined
	0x9E, // Undefined
	0x9F, // Undefined
	0xA0, // VK_LSHIFT (Left Shift)
	0xA1, // VK_RSHIFT (Right Shift)
	0xA2, // VK_LCONTROL (Left Ctrl)
	0xA3, // VK_RCONTROL (Right Ctrl)
	0xA4, // VK_LMENU (Left Alt)
	0xA5  // VK_RMENU (Right Alt)
};

static const char* KeyNamesText[] = {
	"OFF",                    // 0
	"Left Mouse Button",      // 1
	"Right Mouse Button",     // 2
	"Cancel",                 // 3
	"Middle Mouse Button",    // 4
	"X1 Mouse Button",        // 5
	"X2 Mouse Button",        // 6
	"Unknown",                // 7
	"Backspace",              // 8
	"Tab",                    // 9
	"Unknown",                // 10
	"Unknown",                // 11
	"Clear",                  // 12
	"Enter",                  // 13
	"Unknown",                // 14
	"Unknown",                // 15
	"Shift",                  // 16
	"Control",                // 17
	"Alt",                    // 18
	"Pause",                  // 19
	"Caps Lock",              // 20
	"Kana",                   // 21
	"Unknown",                // 22
	"Junja",                  // 23
	"Final",                  // 24
	"Kanji",                  // 25
	"Unknown",                // 26
	"Escape",                 // 27
	"Convert",                // 28
	"Nonconvert",             // 29
	"Accept",                 // 30
	"Mode Change",            // 31
	"Space",                  // 32
	"Page Up",                // 33
	"Page Down",              // 34
	"End",                    // 35
	"Home",                   // 36
	"Left Arrow",             // 37
	"Up Arrow",               // 38
	"Right Arrow",            // 39
	"Down Arrow",             // 40
	"Select",                 // 41
	"Print",                  // 42
	"Execute",                // 43
	"Print Screen",           // 44
	"Insert",                 // 45
	"Delete",                 // 46
	"Help",                   // 47
	"0",                      // 48
	"1",                      // 49
	"2",                      // 50
	"3",                      // 51
	"4",                      // 52
	"5",                      // 53
	"6",                      // 54
	"7",                      // 55
	"8",                      // 56
	"9",                      // 57
	"Unknown",                // 58
	"Unknown",                // 59
	"Unknown",                // 60
	"Unknown",                // 61
	"Unknown",                // 62
	"Unknown",                // 63
	"Unknown",                // 64
	"A",                      // 65
	"B",                      // 66
	"C",                      // 67
	"D",                      // 68
	"E",                      // 69
	"F",                      // 70
	"G",                      // 71
	"H",                      // 72
	"I",                      // 73
	"J",                      // 74
	"K",                      // 75
	"L",                      // 76
	"M",                      // 77
	"N",                      // 78
	"O",                      // 79
	"P",                      // 80
	"Q",                      // 81
	"R",                      // 82
	"S",                      // 83
	"T",                      // 84
	"U",                      // 85
	"V",                      // 86
	"W",                      // 87
	"X",                      // 88
	"Y",                      // 89
	"Z",                      // 90
	"Left Windows",           // 91
	"Right Windows",          // 92
	"Apps",                   // 93
	"Unknown",                // 94
	"Sleep",                  // 95
	"Numpad 0",               // 96
	"Numpad 1",               // 97
	"Numpad 2",               // 98
	"Numpad 3",               // 99
	"Numpad 4",               // 100
	"Numpad 5",               // 101
	"Numpad 6",               // 102
	"Numpad 7",               // 103
	"Numpad 8",               // 104
	"Numpad 9",               // 105
	"Numpad Multiply",        // 106
	"Numpad Add",             // 107
	"Numpad Separator",       // 108
	"Numpad Subtract",        // 109
	"Numpad Decimal",         // 110
	"Numpad Divide",          // 111
	"F1",                     // 112
	"F2",                     // 113
	"F3",                     // 114
	"F4",                     // 115
	"F5",                     // 116
	"F6",                     // 117
	"F7",                     // 118
	"F8",                     // 119
	"F9",                     // 120
	"F10",                    // 121
	"F11",                    // 122
	"F12",                    // 123
	"F13",                    // 124
	"F14",                    // 125
	"F15",                    // 126
	"F16",                    // 127
	"F17",                    // 128
	"F18",                    // 129
	"F19",                    // 130
	"F20",                    // 131
	"F21",                    // 132
	"F22",                    // 133
	"F23",                    // 134
	"F24",                    // 135
	"Unknown",                // 136
	"Unknown",                // 137
	"Unknown",                // 138
	"Unknown",                // 139
	"Unknown",                // 140
	"Unknown",                // 141
	"Unknown",                // 142
	"Unknown",                // 143
	"Num Lock",               // 144
	"Scroll Lock",            // 145
	"OEM NEC Equal",          // 146
	"OEM FJ Masshou",         // 147
	"OEM FJ Tourok",          // 148
	"OEM FJ Loya",            // 149
	"OEM FJ Roya",            // 150
	"Unknown",                // 151
	"Unknown",                // 152
	"Unknown",                // 153
	"Unknown",                // 154
	"Unknown",                // 155
	"Unknown",                // 156
	"Unknown",                // 157
	"Unknown",                // 158
	"Unknown",                // 159
	"Left Shift",             // 160
	"Right Shift",            // 161
	"Left Control",           // 162
	"Right Control",          // 163
	"Left Alt",               // 164
	"Right Alt"               // 165
};
