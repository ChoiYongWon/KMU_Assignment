과제 배점이 점점 올라갑니다.

 •여기까지 8점) ./a.out -list analysis.c 까지 푼 경우 8점이 부여뒵니다.


15점 문제는 조금 어렵습니다.
18점 문제는 생각해야 할 것이 많이 있습니다. 풀지 않기를 권장합니다. (18번 문제는 사용하는 파일도 다릅니다.)


[제출 문서에 포함되어야 할 내용]

1. 소스코드 + 주석

2. 각 문제별 시연 결과 캡쳐

3. 과제 후 느낀 점.

4. 제출 파일 명: 

컴공창_파일분석편집기_학번_이름_XX점.doc 또는 hwp, pdf (본인이 해결한 곳 까지의 점수)

과제 
•소스코드 편집/분석기
–조건: fopen, fprintf, fscanf 등의 c 기반 파일 처리 API 를 이용하며, 텍스트 모드로 진행 해야 함
–analysis.c 복사해오기 :  cp /home/data/analysis.c . 
–analysis_hard.c (마지막 문제) 복사해오기 :  cp /home/data/analysis_hard.c . 

•1점) ./a.out 
– 옵션을 입력하라고 출력

•여기까지 풀면 5점) ./a.out -help
– 사용방법을 출력.

•여기까지 풀면 8점) ./a.out -list analysis.c
– 입력 파일을 화면에 출력한다.

•여기까지 풀면 10점) ./a.out -linecount analysis.c
– 총 28 라인으로 구성되어 있습니다.

•여기까지 풀면 12점) ./a.out -replace analysis.c int double
– 총 4개의 int 가 double 으로 교체되었습니다.
– ./a.out –list analysis.c 결과도 출력

•여기까지 풀면 15점) ./a.out -analysis analysis.c 
– 본 소스 코드에서 사용된 변수 6개 (제약조건: 변수는 int 와 double 형만 있음)
•int g_value, int g_dbl_value, int data1, int data2, int data3, double dbl_data;
– 본 소스 코드에서 사용된 함수 3개 (제약조건: 모든 함수는 void 로 시작, 함수 파라미터 없음)
•void main(), void func1(), void func2()


•여기까지 풀면 18점) ./a.out -analysis_detail analysis_hard.c (입력 파일 : analysis_hard.c)
– 본 소스 코드에서 사용된 전역 변수 2개
•int g_value
•double g_dbl_value

– 함수 별 분석
•func1() : 파라미터(1): int value  / 리턴타입: int
– 로컬변수(0) 없음
•func2() : 파라미터(1): double value  / 리턴타입: double
– 로컬변수(2) : int value2, int * ptr
•main() : 파라미터(2): int argc, char* argv[]  / 리턴타입: int
– 로컬변수(5): long data1, long data2, long data3, double dbl_data, int *p;
