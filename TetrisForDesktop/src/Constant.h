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
	DIRECTION, //(=0) 사용자가 방향키를 눌렀을 경우
	DIRECT_DOWN, //(=1) 사용자가 스페이스 바를 눌렀을 경우
	AUTO//(=2) 지정해 놓은 속도에 따라 블럭이 밑으로 한칸 내려오는 경우
};

enum KeyCode{//사용자로 부터 입력받은 키보드 값을 정수값으로 표현
	UP_KEY_CODE = 72, //화살표 위
	LEFT_KEY_CODE = 75,//화살표 왼쪽
	RIGHT_KEY_CODE = 77,//화살표 오른쪽
	DOWN_KEY_CODE = 80,//화살표 아래
	SPACE_BAR_KEY_CODE = 32,//스페이스바 키
	ESC_KEY_CODE = 27,//ESC키 
	L_KEY_CODE = 108, 
	ENTER_KEY_CODE = 13,//Enter 키
	Z_KEY_CODE = 122 //Hold
};

enum FontColor{ //Fontcolor
	BLACK, BLUE, GREEN, JADE, RED, PURPLE, YELLOW, WHITE, GRAY,
	LIGHT_BLUE, LIGHT_GREEN, LIGHT_JADE, LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, LIGHT_WHITE, WHITE_INVERSION = 240
};

enum BoardType {//테트리스 판의 각 위치에 대한 종류
	EMPTY,//아무것도 없는 비어 있는 상태
	MOVING_BLOCK, //움직이는 블럭
	FIXED_BLOCK, //움직이지 못하고 굳어진 블럭
	SHADOW_BLOCK,//움직이는 블럭이 내려올 곳을 보여주는 블럭
	LEFT_WALL, RIGHT_WALL,BOTTOM_WALL, TOP_WALL,//왼쪽,오른쪽,아래,위쪽 벽
	LEFT_TOP_EDGE, RIGHT_TOP_EDGE, LEFT_BOTTOM_EDGE, RIGHT_BOTTOM_EDGE, //왼쪽 위, 오른쪽 위, 왼쪽 아래, 오른쪽 아래 모서리
	DRAW_BLOCK //미션에서 fopen으로 인해 그려진 블럭을 표현하기 위한 변수
};

enum MainMenu{ //메인 메뉴
	START_MAIN_MENU = 1, 
	RANKING_MAIN_MENU, 
	SETTING_MAIN_MENU,
	MISION_MAIN_MENU, //메인 화면에서 Mission을 선택했을 때
	EXIT_MAIN_MENU
};

enum PauseMenu{ //게임을 일시 정지 했을 경우
	RESUME_PAUSE_MENU = 1, MAIN_MENU_PAUSE_MENU
};

enum MissionMenu {//메인 화면에서 Mission을 선택했을 때

	CHOOSE_LEVEL = 1, //level을 선택하는
	EXIT_MISSION_MENU // 미션 종료
};

enum EndMenu{ // 게임 종료했을 때
	RANKING_END_MENU = 1, MAIN_MENU_END_MENU,EXIT_END_MENU
};

#define MAX_SPEED_LEVEL 10 //속도의 최대 레벨
#define MIN_SPEED_LEVEL 1 // 속도의 최소 레벨

#define MAX_MISSION_LEVEL 10 //미션의 최대 레벨
#define MIN_MISSION_LEVEL 1 // 미션의 최소 레벨

#define DEFAULT_FONT_COLOR LIGHT_WHITE //기본 폰트 컬러는 하얀색

#endif
