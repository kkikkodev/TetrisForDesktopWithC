#ifndef _CONSTANT_H
#define _CONSTANT_H
//헤더파일을 중복 포함되지 않게 하기 위한 guard

enum Boolean{//열거형 상수를 정의 F=0,T=1
	False, True
};

enum Direction{//방향 UP=0, RIGHT=1,DOWN=2,LEFT=3으로 정의
	UP, RIGHT, DOWN, LEFT
};

enum ProcessType{//게임 진행 종류
	DIRECTION, 
	DIRECT_DOWN, 
	AUTO
};

enum KeyCode{//사용자로 부터 입력받은 키보드 값을 정수값으로 표현
	UP_KEY_CODE = 72, 
	LEFT_KEY_CODE = 75,
	RIGHT_KEY_CODE = 77,
	DOWN_KEY_CODE = 80,
	SPACE_BAR_KEY_CODE = 32,
	ESC_KEY_CODE = 27,
	L_KEY_CODE = 108, 
	ENTER_KEY_CODE = 13,//Enter 키
	Z_KEY_CODE = 122 //Hold
	X_KEY_CODE = 120 // 3,6,9 ITEM키
};

enum FontColor{ //Fontcolor
	BLACK, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE, WHITE_INVERSION = 240
};

enum BoardType {//테트리스 판의 각 위치에 대한 종류
	EMPTY,
	MOVING_BLOCK, 
	FIXED_BLOCK,
	SHADOW_BLOCK,
	LEFT_WALL, RIGHT_WALL,BOTTOM_WALL, TOP_WALL,
	LEFT_TOP_EDGE, RIGHT_TOP_EDGE, LEFT_BOTTOM_EDGE, RIGHT_BOTTOM_EDGE,
	DRAW_BLOCK 
};

enum MainMenu{ //메인 메뉴
	START_MAIN_MENU = 1, 
	RANKING_MAIN_MENU, 
	SETTING_MAIN_MENU,
	MISION_MAIN_MENU,
	EXIT_MAIN_MENU
};

enum PauseMenu{ //게임을 일시 정지 했을 경우
	RESUME_PAUSE_MENU = 1, MAIN_MENU_PAUSE_MENU
};

enum MissionMenu {//메인 화면에서 Mission을 선택했을 때

	CHOOSE_LEVEL = 1, 
	EXIT_MISSION_MENU
};

enum EndMenu{
	RANKING_END_MENU = 1, MAIN_MENU_END_MENU, EXIT_END_MENU
};

#define MAX_SPEED_LEVEL 10
#define MIN_SPEED_LEVEL 1 

#define MAX_MISSION_LEVEL 10 
#define MIN_MISSION_LEVEL 1

#define DEFAULT_FONT_COLOR LIGHT_WHITE 

#endif
