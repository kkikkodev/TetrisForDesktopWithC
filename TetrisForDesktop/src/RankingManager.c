#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "RankingManager.h"
#include "Util.h"
#include "Constant.h"

#define RANKINGS_CAPACITY 100

#define RANKING_POSITION_X_TO_PRINT 5
#define RANKING_POSITION_Y_TO_PRINT 5

#define TIMESTAMP_FOR_PRINT_SIZE 100

#define RANKING_FILE ".\\..\\res\\tetrisRanking.dat"

static int _RankingManager_GetLength(RankingManager* rankingManager);
static int _RankingManager_GetCapacity(RankingManager* rankingManager);
static int _RankingManager_IsFull(RankingManager* rankingManager);
static Ranking _RankingManager_GetAt(RankingManager* rankingManager, int index);
static void _RankingManager_SortOrderByScore(RankingManager* rankingManager, int** indexes);
static int _CompareRankings(const void* one, const void* other);

void RankingManager_Create(RankingManager* rankingManager){
	Array_Create(&rankingManager->rankings, RANKINGS_CAPACITY, sizeof(Ranking)); // Ranking을 저장할  총 100개의 배열을 생성
}

void RankingManager_Add(RankingManager* rankingManager, Ranking ranking){
	if (!_RankingManager_IsFull(rankingManager)){ //배열이 꽉찾을 경우
		Array_Store(&rankingManager->rankings, rankingManager->rankings.length, &ranking, sizeof(Ranking)); //해당 정보를 배열에 저장
	}
	else{
		Array_AppendFromRear(&rankingManager->rankings, &ranking, sizeof(Ranking)); //현재 위치 다음에 저장
	}
}

int RankingManager_Load(RankingManager* rankingManager){
	FILE* file = fopen(RANKING_FILE, "rb"); //.dat파일에 저장되어진 정보를 로드
	Ranking ranking;
	int readSize;
	if (file){
		while (!feof(file)){
			readSize = fread(&ranking, 1, sizeof(Ranking), file);
			if (readSize < sizeof(Ranking)){
				break;
			}
			RankingManager_Add(rankingManager, ranking);
		}
		fclose(file);
		return True;
	}
	else{
		return False;
	}
}

int RankingManager_Save(RankingManager* rankingManager){ //랭킹을 .dat 파일에 저장
	FILE* file = fopen(RANKING_FILE, "wb");
	Ranking ranking;
	int i;
	if (file){
		for (i = 0; i < _RankingManager_GetLength(rankingManager); i++){ //전체 랭킹을 .dat 파일에 새롭게 저장
			ranking = _RankingManager_GetAt(rankingManager, i);
			fwrite(&ranking, sizeof(Ranking), 1, file);
		}
		fclose(file);
		return True;
	}
	else{
		return False;
	}
}

void RankingManager_Print(RankingManager* rankingManager){ //랭킹 정보를 출력
	int i;
	char timestampForPrint[TIMESTAMP_FOR_PRINT_SIZE];
	struct tm* pTm;
	int x = RANKING_POSITION_X_TO_PRINT;
	int y = RANKING_POSITION_Y_TO_PRINT;
	int* indexes = (int*)calloc(_RankingManager_GetLength(rankingManager), sizeof(int)); //랭킹의 수 전체
	system("cls");
	CursorUtil_GotoXY(x, y++);
	printf("-------------------------- R A N K I N G -----------------------------");
	CursorUtil_GotoXY(x, y++);
	printf("======================================================================");
	CursorUtil_GotoXY(x, y++);
	printf("%3s%11s%8s%8s%8s%10s%22s", "No", "ID", "SCORE", "LEVEL", "LINES", "TIME", "DATE AND TIME");
	CursorUtil_GotoXY(x, y++);
	printf("----------------------------------------------------------------------");
	CursorUtil_GotoXY(x, y++);
	_RankingManager_SortOrderByScore(rankingManager, &indexes); // 점수에 따라 정렬을 함
	for (i = 0; i < _RankingManager_GetLength(rankingManager); i++){
		Ranking ranking;
		Array_GetAt(&rankingManager->rankings, indexes[i], &ranking, sizeof(Ranking)); //배열의 값을 가져옴
		pTm = localtime(&ranking.timestamp); //랭킹에 등록된 시간
		strftime(timestampForPrint, sizeof(timestampForPrint), "%Y-%m-%d %H:%M:%S", pTm);
		printf("%3d%11s%8d%8d%8d  %02d:%02d:%02d%22s", i + 1, ranking.id, ranking.score, ranking.level, ranking.deletedLineCount,
			ranking.totalTime / (60 * 60), ranking.totalTime % (60 * 60) / 60, ranking.totalTime % 60, timestampForPrint);
		CursorUtil_GotoXY(x, y++);
	}
	printf("======================================================================");
	if (indexes){
		free(indexes);
		indexes = NULL;
	}
	getchar();
}

void RankingManager_Destroy(RankingManager* rankingManager){ //전체 랭킹 초기화
	Array_Destroy(&rankingManager->rankings);
}

static int _RankingManager_GetLength(RankingManager* rankingManager){ //전체 등록된 랭킹의 수 리턴
	return rankingManager->rankings.length;
}

static int _RankingManager_GetCapacity(RankingManager* rankingManager){ //
	return rankingManager->rankings.capacity;
}

static int _RankingManager_IsFull(RankingManager* rankingManager){ //100명의 꽉찼는지 확인
	return (_RankingManager_GetCapacity(rankingManager) == _RankingManager_GetLength(rankingManager));
}

static Ranking _RankingManager_GetAt(RankingManager* rankingManager, int index){ //정보 추출
	Ranking ranking;
	Array_GetAt(&rankingManager->rankings, index, &ranking, sizeof(Ranking));
	return ranking;
}

static void _RankingManager_SortOrderByScore(RankingManager* rankingManager, int** indexes){ //정렬
	Array_Indirect_InsertionSort(&rankingManager->rankings, indexes, sizeof(Ranking), _CompareRankings);
}

static int _CompareRankings(const void* one, const void* other){ //등록된 점수들을 비교
	return ((Ranking*)other)->score - ((Ranking*)one)->score;
}