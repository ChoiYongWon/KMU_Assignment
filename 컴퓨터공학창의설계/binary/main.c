#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_SIZE 255
#define AGE_SIZE 1
#define HP_SIZE 1
#define COORD_SIZE 1
#define ALLIANCE_SIZE 255

#define INDEX_FILE "b_index"
#define TMP_INDEX_FILE "b_index_tmp"

typedef struct Player {
	char id[255];
	int age;
	unsigned short hp;
	double x;
	double y;
	char alliance[255][255];
	int allianceLength; //동맹 수
} Player;	

//함수 호이스팅
void init();
int exists(char *);
int checkAge(int );
void registerPlayer(struct Player *);
void readAllPlayer();
void createPlayer(struct Player *);
struct Player * setPlayer();
struct Player * getPlayer(char[]);
void printPlayer(Player *);
void deletePlayer(char []);
void unregisterPlayer(char []);
void run();

//파일이 존재하는지 여부 반환
int exists(char *filename){
	FILE* fp;
	fp = fopen(filename, "r");
	if(fp==NULL) return 0;
	fclose(fp); return 1;
}

//나이 범위 확인 함수
int checkAge(int age){
	return (age >= 0 && age < 128);
}
// 맨처음 시작할때 실행
// 파일이 존재하면 X 존재안하면 b_index파일 생성
// 사용자 명수 기록
void init(){
	if(exists(INDEX_FILE)) return;
	FILE * fp = fopen(INDEX_FILE, "wb");
	if(fp==NULL) exit(0);
	int playerLength = 0;
	fwrite(&playerLength, sizeof(int), 1, fp);
	fclose(fp);
}

//플레이어 ID를 b_index에 기록하는 함수
void registerPlayer(Player * player){
	FILE * fp;
	int playerLength;
	fp = fopen(INDEX_FILE, "r+b");
	if(fp==NULL) exit(0);

	//맨처음 플레이어 명수 읽어옴
	fread(&playerLength, sizeof(int), 1, fp);

	fseek(fp, 0, SEEK_SET); // 파일 제일 처음으로 커서 이동
	playerLength++;
	fwrite(&playerLength, sizeof(int), 1, fp); // 한명 증가한 값으로 수정
	
	fseek(fp, 0, SEEK_END);//파일 맨 뒤로 이동
	fwrite(player->id, sizeof(char), ID_SIZE, fp);// 새로운 플레이어 ID 저장

	fclose(fp);
}

//플레이어 ID를 b_index에서 삭제하는 함수
void unregisterPlayer(char targetId[255]){
	FILE * old_fp = fopen(INDEX_FILE, "rb");
	FILE * new_fp = fopen(TMP_INDEX_FILE, "wb");
	int playerLength;

	if(old_fp == NULL || new_fp == NULL ) exit(1);

	//플레이어 명수 읽어옴
	fread(&playerLength, sizeof(int), 1, old_fp);
	
	playerLength--; // 한명 감소

	//새로운 파일에 기록
	fwrite(&(playerLength), sizeof(int), 1, new_fp);
	
	//그 다음 명수대로 반복해서 플레이어 ID 읽어오는 과정
	for(int i=0;i<playerLength+1; i++){
		char id[255];
		fread(id, sizeof(char), ID_SIZE, old_fp);//255칸씩 읽어서 id에 대입
		//함수 인자인 targetId랑 비교해서 맞으면 새로운 파일에 기록안함
		if(strcmp(id, targetId) != 0) fwrite(id, sizeof(char), ID_SIZE, new_fp);
	}

	fclose(old_fp);
	fclose(new_fp);

	remove(INDEX_FILE);//기존 파일 지움
	rename(TMP_INDEX_FILE, INDEX_FILE);//임시 파일을 기존파일로 대체
	
	printf("%s 삭제완료.\n", targetId);
}

//ID로 된 파일을 삭제해주는 함수
void deletePlayer(char targetId[255]){
	int result = remove(targetId);
	if(result==-1) printf("파일 삭제 오류\n");
}

//모든 플레이어 읽어주는 함수
void readAllPlayer(){
	FILE * fp;
	int playerLength;

	fp = fopen(INDEX_FILE, "rb");
	if(fp == NULL) exit(0);

	//플레이어 명수 읽어옴
	fread(&playerLength, sizeof(int), 1, fp);
	
	printf("\n총 %d명의 플레이어가 기록되어 있습니다.\n", playerLength);

	//명수대로 반복해서 ID읽어옴
	for(int i=0;i<playerLength;i++){
		char id[ID_SIZE];
		fread(id, sizeof(char), ID_SIZE, fp);
		printf("\n[플레이어%d]\n", i+1);
		//id를 기반으로 파일을 읽어오는 함수 Player 구조체를 반환해주는 함수 호출
		Player* player = getPlayer(id);
		printPlayer(player);// player 정보 출력 함수
		free(player);	
	}

	printf("\n완료되었습니다.\n");
	fclose(fp);

}

//플레이어 정보가 담긴 파일을 생성해주는 함수
void createPlayer(Player * player){
	FILE * fp = fopen(player->id, "wb");
	if(fp == NULL){ exit(0); }
	fwrite(player->id, sizeof(char), ID_SIZE, fp);
	fwrite(&player->age, sizeof(int), AGE_SIZE, fp);
	fwrite(&player->hp, sizeof(unsigned short), HP_SIZE, fp);
	fwrite(&player->x, sizeof(double), COORD_SIZE, fp);
	fwrite(&player->y, sizeof(double), COORD_SIZE, fp);
	fwrite(&player->allianceLength, sizeof(int), 1, fp);
	fwrite(player->alliance, sizeof(char) * ID_SIZE, ALLIANCE_SIZE, fp);
	fclose(fp);
}

//플레이어 정보를 입력받아 Player 구조체를 반환해주는 함수
Player * setPlayer(){
	Player * player = (Player *)malloc(sizeof(Player));
	player->allianceLength = 0;
	printf("ID를 입력하세요 : "); scanf("%s", player->id); getchar();
	while(1){
		printf("나이를 입력하세요 : "); scanf("%d", &player->age); getchar();
		if(!checkAge(player->age))	printf("나이 범위는 0 ~ 127 입니다\n");
		else break;
	}
	printf("HP를 입력하세요 : "); scanf("%hu", &player->hp); getchar();
	printf("X 좌표를 입력하세요 : "); scanf("%lf", &player->x); getchar();
	printf("Y 좌표를 입력하세요 : "); scanf("%lf", &player->y); getchar();
	do{
		printf("동맹 ID를 입력하세요 : "); scanf("%s", player->alliance[player->allianceLength++]);
		getchar();
		printf("동맹을 계속 추가할까요? (N/Y) : ");
		char a = getchar(); getchar();
		if(a=='N'){
			printf("\n완료되었습니다.\n");
			break;
		}
	}while(1);
	
	return player;
}

/*플레이어 ID를 매개변수로 입력받아 매핑되는 파일을 읽고
Player 객체로 반환해주는 함수*/
Player * getPlayer(char id[255]){
	FILE * fp = fopen(id, "rb");
	if(fp==NULL) { exit(1); }

	Player * player = (Player *)malloc(sizeof(Player));

	fread(player->id, sizeof(char), 255, fp);
	fread(&player->age, sizeof(int), 1, fp);
	fread(&player->hp, sizeof(unsigned short), 1, fp);
	fread(&player->x, sizeof(double), 1, fp);
	fread(&player->y, sizeof(double), 1, fp);
	fread(&player->allianceLength, sizeof(int), 1, fp);
	fread(player->alliance, sizeof(char) * 255, 255, fp);

	fclose(fp);
	return player;
}

void printPlayer(Player *player){
	printf("ID: %s", player->id); printf(" / ");
	printf("나이: %d", player->age); printf(" / ");
	printf("HP: %hu", player->hp); printf(" / ");
	printf("좌표: %.3lf, %.3lf\n", player->x, player->y);
	printf("등록된 동맹 수: %d명\n", player->allianceLength);
	for(int i=0;i<player->allianceLength;i++){
		printf("%s",player->alliance[i]);
		if(i!=player->allianceLength-1) printf(" / ");
	}
	printf("\n");
}

//입력 로직
void run(){
	while(1){
		printf("1. 신규 플레이어 정보 기록\n");
		printf("2. 기록된 모든 플레이어 정보 확인\n");
		printf("3. 플레이어 삭제\n");
		printf("4. 종료\n");
		printf("입력하세요 > ");
		char choice = getchar(); getchar();// 입력 버퍼 비우기
		switch(choice){
			case '1':
				{
					Player * player = setPlayer(); //입력받은 결과로 player 구조체 할당
					createPlayer(player); // 플레이어 파일 생성
					registerPlayer(player); // b_index 파일에 플레이어 ID 등록
					free(player); //할당 받은 메모리 free
					break;
				}
			case '2':
				readAllPlayer(); // 모든 플레이어 읽기
				break;
				
			case '3':
				{
					char id[255];
					printf("삭제할 ID를 입력하세요 : ");
					scanf("%s", id); getchar();
					if(exists(id)){// 입력 받은 ID 파일이 존재하는지
						deletePlayer(id); // 해당 ID 파일 삭제
						unregisterPlayer(id); // b_index 파일에서 플레이어 ID 삭제
					}else printf("유저가 존재하지 않습니다\n");
				}
				break;

			case '4':

				return;
			default: 
				printf("해당 번호는 존재하지 않습니다\n");
				break;
		}

	}
}

int main(){
	init();
	run();
	return 0;
}
