#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define DB_NAME "db.txt"
#define DB_TMP_NAME "db_tmp.txt"
#define NAME_BYTE 255
#define EMAIL_BYTE 255
#define USER_BYTE 255 + 255 + 4
#define LINE_BYTE 255 + 1 + 4 + 1 + 255 + 2

void create();
void read();
void update(char * name);
void delete(char * name, int print);
void printChoices();
int getInputChoice();
int proceed();
int isEmail(char * email);

typedef struct {
	char name[NAME_BYTE];
	int age;
	char email[EMAIL_BYTE];
} User;

void printChoices(){
	printf("1. 신규회원 저장\n");
	printf("2. 회원 정보 수정\n");
	printf("3. 회원 삭제\n");
	printf("4. 모든 회원 리스트\n");
	printf("5. 종료\n");
	printf("입력하세요 > ");
}

int getInputChoice(){
	int n;
	scanf("%d", &n);
	getchar();//입력 버퍼에 \n 없앰
	return n;	
}

int proceed(){
	printf("계속 입력할까요? (Y/N) : ");
	char input = getchar();
	getchar(); //입력 버퍼에 \n없앰
	if(input == 'Y') return 1;
	if(input == 'N') return 0;
	return -1;
}

int isEmail(char * email){
	regex_t regex;
	int reti;
	//정규 표현식 컴파일
	//확장 정규표현식 지원
	//대소문자 구분 X
	reti = regcomp(&regex, "^[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*@[0-9a-zA-Z]([-_.]?[0-9a-zA-Z])*.[a-zA-Z]{2,3}$", REG_EXTENDED | REG_ICASE);
	if (reti) {//컴파일 될시 reti = 1
  	fprintf(stderr, "정규표현식 컴파일 실패\n");
    exit(1);
	}
	//정규표현식 매칭 결과 저장 
	//매칭 완료시 0이므로 !로 반환
	int result = !regexec(&regex, email, 0, NULL, 0);
	regfree(&regex);//정규표현식 메모리 다시 회수
	return result;
}

int isExist(char * inputName){
	FILE * fp;
	fp = fopen(DB_NAME, "r");
	
	if(fp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		return -1;
	}

	while(1){
		char line[LINE_BYTE];
		//한 행씩 읽어와서 line에 저장
		char *strptr = fgets(line, LINE_BYTE, fp);
		//fgets가 NULL일때까지 반복
		if(strptr == NULL) break;
		char *name = strtok(line, "/");//line을 구분자 /을 기준으로 토큰화해서 첫번째 요소 저장
		//name과 inputName을 비교해서 같으면  1반환
		if(strcmp(name, inputName) == 0) return 1;// 사용자가 존재할시 1 반환
	}
	
	fclose(fp);
	return 0;// 여기까지오면 사용자가 존재하지 않는다는 뜻이므로 0반환
}

void create(){
	FILE *fp;
	User user;
	printf("\n");
	printf("이름 : ");
	scanf("%[^\n]", user.name);	
	
	printf("나이 : ");
	scanf("%d", &user.age);
	if(user.age < 0 || user.age > 200 ){
		printf("나이 범위는 0 ~ 200 입니다\n");
		getchar();// 입력버퍼에 \n 제거
		return;
	}	
	printf("이메일 : ");
	scanf("%s", user.email);
	if(!isEmail(user.email)){
		printf("이메일 형식이 알맞지 않습니다.\n");
		getchar();
		return;
	}
	fp = fopen(DB_NAME, "a");
	if(fp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		return;
	}

	fprintf(fp, "%s/%d/%s\n", user.name, user.age, user.email);
	fclose(fp);
	
	getchar(); //입력버퍼에 \n 없앰
}

void read(){
	FILE *fp;
	fp = fopen(DB_NAME, "r");
	if(fp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		return;
	}
	//위에 isExist랑 같은 원리
	while(1){
		char info[LINE_BYTE];
		char *str = fgets(info, LINE_BYTE, fp);
		if(str == NULL) break;
		printf("%s", str);
	}
	fclose(fp);
}

//먼저 사용자가 존재할시 사용자의 수정 정보를 입력받고 기존 사용자 정보를 지운다음 맨뒤에 추가하는 방식이다
void update(char * inputName){
	
	if(!isExist(inputName)){
		printf("사용자 %s는 없습니다\n", inputName);
		return;
	}
	User user;
	printf("사용자 %s를 수정합니다\n", inputName);
	
	printf("이름 : ");
	scanf("%[^\n]", user.name);	
	
	printf("나이 : ");
	scanf("%d", &user.age);
	if(user.age < 0 || user.age > 200 ){
		printf("나이 범위는 0 ~ 200 입니다\n");
		getchar();
		return;
	}	
	
	printf("이메일 : ");
	scanf("%s", user.email);	
	if(!isEmail(user.email)){
		printf("이메일 형식이 알맞지 않습니다.\n");
		getchar();
		return;
	}

	//기존 사용자 정보 제거
	delete(inputName, 0);

	FILE *fp;
	fp = fopen(DB_NAME, "a");
	
	if(fp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		return;
	}

	//새로운 사용자 정보 추가
	fprintf(fp, "%s/%d/%s\n", user.name, user.age, user.email);
	fclose(fp);
	printf("수정 완료 되었습니다.\n");
}

//update에서 delete함수를 재사용하기 위해서 print 매개변수 추가
//0은 결과 미출력
//1은 결과 출력
void delete(char * inputName, int print){
	if(!isExist(inputName)){
		printf("사용자 %s는 없습니다\n", inputName);
		return;
	}
	FILE *fp;
	FILE *newFp;
	fp = fopen(DB_NAME, "r");
	newFp = fopen(DB_TMP_NAME, "w");//inputName을 제외한 새로운 사용자 목록
	
	if(fp == NULL || newFp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		return;
	}

	while(1){
		char line[LINE_BYTE];
		char tmp[LINE_BYTE];//strtok때문에 line을 저장하는 변수가 하나 더 필요
			
		//한줄 읽어와서 line에 wjwkd
		char *strptr = fgets(line, LINE_BYTE, fp);
		strcpy(tmp, line);//tmp에 line내용 복사

		if(strptr == NULL) break;
		char *name = strtok(tmp, "/");//구분자 \을 기준으로 첫번째 요소인 이름
		//비교해서 inputName이랑 해당 line에 name이 다른 라인만 새로운 파일에 저장
		if(strcmp(name, inputName) != 0) fputs(line, newFp);
	}
	
	fclose(fp);
	fclose(newFp);

	remove(DB_NAME);
	rename(DB_TMP_NAME, DB_NAME);
	
	if(print) printf("삭제가 완료되었습니다.\n");

}




int main() {
	
	while(1){
		int choice;
		char inputName[20];

		printChoices();
		choice = getInputChoice();
		switch(choice){
			case 1:
				while(1){
					create();
					if(!proceed()) break;
				}
				printf("입력이 완료되었습니다.\n");
				
				break;
			case 2:
				printf("수정할 이름을 적어주세요 : ");
				scanf("%[^\n]",inputName);
 				getchar(); //입력버퍼 \n 제거	
				update(inputName);
				break;
			case 3:
				printf("삭제할 이름을 적어주세요 : ");
				scanf("%[^\n]",inputName);
 				getchar(); //입력버퍼 \n 제거
	
				delete(inputName, 1);
				break;
			case 4:
				read();
				break;
			case 5:
				printf("종료합니다\n");
				return 0;
				break;
		}
		printf("\n");
	}

	return 0;
}
