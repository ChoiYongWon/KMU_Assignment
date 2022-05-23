#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define TMP_FILE_NAME "tmp_file"

//옵션들 비교하기 쉽게 열거형으로 선언
typedef enum Option{
	LIST,
	LINE_COUNT,
	REPLACE,
	ANALYSIS,
	ANALYSIS_DETAIL
} Option;

void printOption();
void exec();
int isOption();
void addOption();
void execList(char *);
void execLineCount(char *);
void execReplace(char *, char *, char *);
void execAnalysis(char *);
void execAnalysisDetail(char *);

//help 옵션
void printOption(){
	printf("-list [file] : 입력파일을 화면에 출력합니다.\n");
	printf("-linecount [file] : 해당 파일의 라인 수를 출력합니다.\n");
	printf("-replace [file] a b : file내에서 a를 b로 치환합니다.\n");
	printf("-analysis [file] : file 에서 사용된 변수와 함수의 갯수를 출력합니다.\n");
	printf("-analysis_detail [file] : file에서 사용된 전역변수의 갯수랑 함수별 분석 결과를 출력합니다.\n");
}

//받은 문자열에 스페이스를 추가해서 반환해주는 함수
char * addMargin(char * str){
	char * result = (char *)malloc(sizeof(char) * strlen(str) + 2);
	for(int i=0;i<strlen(str);i++){
		result[i] = str[i];
	}
	result[strlen(str)] = ' ';

	return result;
}

//옵션 배열대로 싱행해주는 함수
//옵션 한번에  여러개 적어도 작동 되게 구현
void exec(char * fileName, Option *options, int length, char * r_old, char * r_new){

	for(int i=0;i<length;i++){
		switch(options[i]){
			case 0:
				execList(fileName);
				break;
			case 1:
				execLineCount(fileName);
				break;
			case 2:
				execReplace(fileName, r_old, r_new);
				execList(fileName);
				break;
			case 3:
				execAnalysis(fileName);
				break;
			case 4:

				break;
		}
	
	}
	printf("\n");
}

//옵션인지 판별해주는 함수
int isOption(char * op){
	return op[0] == '-';
}

// 옵션 배열에 옵션 추가하는 함수
void addOption(Option * optionArray, Option option, int * length){
	optionArray[*length] = option;
	(*length)++;
	return;
}
//8점 문제
void execList(char * fileName){
	FILE *fp = fopen(fileName, "r");
	if(fp==NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		exit(1);
	}

	while(1){
		char buffer[MAX_LINE];
		//한줄씩 읽어드림
		char * line = fgets(buffer, sizeof(buffer), fp);
		if(line==NULL) break;
		printf("%s", line);// 그대로 출력
	}

	fclose(fp);
}
//10점 문제
void execLineCount(char * fileName){
	FILE *fp = fopen(fileName, "r");
	if(fp==NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		exit(1);
	}
	int lineCount = 0;
	while(1){
		char buffer[MAX_LINE];
		//한줄씩 읽어드림
		char * line = fgets(buffer, sizeof(buffer), fp);
		if(line==NULL) break;
		lineCount++;//줄 count 증가
	}
	fclose(fp);

	printf("%s 파일의 라인 갯수 : %d\n", fileName, lineCount);
}
//12점 문제
void execReplace(char * fileName, char * oldWord, char * newWord){

	//각 단어 뒤에 스페이스 추가 -> printf 내에도 int가 있으므로
	char * old = addMargin(oldWord);
	char * new = addMargin(newWord);
	FILE * old_fp = fopen(fileName, "r");
	FILE * new_fp = fopen(TMP_FILE_NAME, "w");
	
	if(old_fp == NULL || new_fp == NULL){
		fprintf(stderr, "파일을 열 수 없습니다");
		exit(1);
	}
	int flag = 0;
	char buffer[MAX_LINE] = {0};
	int count = 0;	
	while(1){
		char c = fgetc(old_fp);//하나의 알파벳씩 반복
		if(c == EOF) break;		
		if(c == old[flag]){//치환할 문자열의 flag 인덱스랑 같을시
			buffer[flag++] = c;//일단 버퍼에 저장
			buffer[flag] = '\0';//저장한 공간 다음공간을 \0로
			if(flag == strlen(old)){//flag가 치환할 문자열의 길이랑 같을시 일치 판단
			 	fputs(new, new_fp);// 새로운 파일에 치환된 문자열 저장
				flag = 0;//flag 초기화
				count++;// 치환 문자열 카운트
			}
		}else if(flag > 0){//flag가 0보다 클시 -> 일치하지 않다는 판단
			fputs(buffer, new_fp);//버퍼내용을 새로운 파일에 저장
			fputc(c, new_fp);//현재 내용까지 저장, 안그러면 한글자 누락됨
			flag = 0;	//플래그 초기화
		}else{
			fputc(c, new_fp);//이 외에는 한글자씩 새로운 파일에 저장
		}
	}
	
	printf("총 %d개의 %s 가 %s 으로 교체되었습니다.\n", count, oldWord, newWord);

	fclose(old_fp);
	fclose(new_fp);
	free(old);
	free(new);	
	remove(fileName);
	rename(TMP_FILE_NAME, fileName);
}

//15점 문제
void execAnalysis(char * fileName){
	
	FILE * fp = fopen(fileName, "r");

	if(fp == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(1);
	}

	//타입들 저장
	char * type[] = {"int ", "double ", "void "};
	int typec = 3;
	
	char * varList[100];// 변수들 추출해서 저장하는 배열
	char * funcList[100];// 함수들 추출해서 저장하는 배열

	int varCount = 0;// 변수들 갯수
	int funcCount = 0;// 함수들 갯수

	while(1){//한 줄씩 반복 하는 while문
		char line[MAX_LINE];
		char * linep = fgets(line, MAX_LINE, fp);
		if(linep == NULL) break;

		for(int i=0;i<typec;i++){//타입 별로 반복
			char * ptr = strstr(line, type[i]);//그 한줄 내에서 해당 타입이 존재할시 문자열 시작 포인터 반환

			while(ptr!=NULL){//있을때 까지 반복
				char buffer[100] = {0};
				int seek = 0;
				while(1){ // 시작 포인터에서 변수의 종료시점이나 함수의 종료 시점까지 반복하여 변수인지 함수인지 판별
					if(ptr[seek] != '=' && ptr[seek] != ';' && ptr[seek] != ')'){
						buffer[seek] = ptr[seek];// = ; ) 이 아니면 buffer에 저장
					}

					else if(ptr[seek] == '=' || ptr[seek] == ';'){// 변수일 경우
						varList[varCount] = (char*)malloc(sizeof(buffer));//varList에 저장
						strcpy(varList[varCount], buffer);
						varCount ++;
						break;
					}
					else if(ptr[seek] == ')'){// 함수일 경우
						buffer[seek] = ptr[seek];
						funcList[funcCount] = (char*)malloc(sizeof(buffer));//funcList에 저장
						strcpy(funcList[funcCount], buffer);
						funcCount ++;

						break;
					}

					seek++;
				}

				ptr = strstr(ptr+1, type[i]);//다음 타입으로 포인터 이동
			}

		}

	}

	fclose(fp);
		
	printf("본 소스 코드에서 사용된 변수 %d개\n", varCount);
	for(int i=0;i<varCount;i++){
		printf("%s", varList[i]);
		if(i!=varCount-1) printf(", ");
		free(varList[i]);
	}
	printf("\n");
	printf("본 소스 코드에서 사용된 함수 %d개\n", funcCount);
	for(int i=0;i<funcCount;i++){
		printf("%s", funcList[i]);
		if(i!=funcCount-1) printf(", ");
		free(funcList[i]);
	}
	printf("\n");

}

void execAnalysisDetail(char * fileName){

}



int main(int argc, char * argv[]){
	
	Option options[5]; //옵션을 저장하는 배열
	int optionsLength = 0; //총 옵션 갯수
	int replace = 0; //replace옵션 여부
	
	if(argc == 1) { printf("옵션은 필수 입니다. --help 로 옵션종류를 알아 볼 수 있습니다."); return 0; }
	for(int i=1;i<argc;i++){//argv 반복
		char * token = argv[i];
		
		if(isOption(token)){// 옵션인지 판별
			if(strcmp(argv[i], "-help")==0) printOption();
			//옵션들을 큐 형식으로 options 배열에 저장
			else if (strcmp(argv[i], "-list")==0) addOption(options, LIST, &optionsLength);
			else if (strcmp(argv[i], "-linecount")==0)  addOption(options, LINE_COUNT, &optionsLength);
			else if (strcmp(argv[i], "-replace")==0) { 
				addOption(options, REPLACE, &optionsLength);
				replace = 1;
			}
			else if (strcmp(argv[i], "-analysis")==0)  addOption(options, ANALYSIS, &optionsLength);
			else if (strcmp(argv[i], "-analysis_detail")==0)  addOption(options, ANALYSIS_DETAIL, &optionsLength);
			else printf("%s 옵션은 존재하지 않습니다\n", argv[i]);	
		}else {// 옵션이 아닐시
			if(replace) {//replace 옵션이 존재할시 파라미터 두개 더 받는 부분
				char * old = argv[i+1];
				char * new = argv[i+2];
				if(old == NULL || new == NULL){
					printf("-replace 할 단어를 적어주세요\n");
					return 0;
				}
				//options에 저장되어있는 옵션들을 차례대로 실행
				exec(argv[i], options, optionsLength, old, new);
				i = i + 2;// replace 인자 두개 받았으니 i + 2 해줌
			}
			else exec(argv[i], options, optionsLength, "", "");
		}

	}
	
	return 0;
}
