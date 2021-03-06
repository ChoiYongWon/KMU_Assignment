# [과제 목적]

> 본 과제의 목적은 fopen, fprintf, fscanf 등의 C 기반 파일 처리 API 를 자유롭게 사용할 수 있는 능력을 배양한다.

 

 

# [과제 설명]

1. 과제 조건: fopen, fprintf, fscanf 등 f- 계열의 함수만 이용하며, 파일은 텍스트 모드로 처리 함.

2. 과제 개요: 회원관리 하는 미니 데이터베이스 프로그램을 만든다.

3. 기능:

	* 신규 회원 저장

	* 회원 정보 수정 -> 추가 점수 항목임..

	* 회원 삭제 -> 삭제 는 어떻게든 단일 유저를 지정해서 지울 수 만 있으면 OK, 세부 UI 는 본인이 설계할 것.

	* 회원 검색

4. 회원 정보에 포함되어야 하는 항목

	* 이름 (한글, 영문 상관 없으니 본인이 편한 형태로 처리), 최대 255 bytes

	* 나이, 최대 200 세

	* 이메일주소, 최대 255 bytes

 

 

# [프로그램 UI 구성]

> 프로그램을 실행하면 다음과 같은 메뉴 텍스트 화면이 나온다.

```
1. 신규회원 저장

2. 회원정보 수정 -> 추가 점수 항목임 (안해도 무방)

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

입력하세요>
```
                                                                                                                                
위 메뉴 텍스트 출력 후 다음 페이지 데모 시나리오 대로 동작 될 수 있도록 구현.

# [데모 시나리오]

PARK GIL DONG 과 LEE GIL DONG 은 미리 데이터 파일에 저장 해 두고 시나리오 실행

한글 이름으로 진행해도 무방하나, 이름과 성은 공백이 있어야 함.

빨간색 폰트는 프로그램 실행 후, 사용자가 직접 키보드로 입력한 값 임.

 
```
1. 신규회원 저장

2. 회원정보 수정 -> 추가 점수 항목임 (안해도 무방)

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

입력하세요> 4

PARK GIL DONG / 22 / parkpark@hotmail.com                    

LEE GIL DONG / 23 / gildonglee@naver.com
```
 
# [과제 데모 시나리오[

```
1. 신규회원 저장

2. 회원정보 수정 -> 추가 점수 항목임 (안해도 무방)

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

입력하세요> 1

이름: HONG GIL DONG

나이: 20

이메일: hong@gmail.com

계속 입력 할까요? (Y/N) Y

 

이름: CHOI GIL

나이: 24

이메일: s11112222@kmu.com

계속 입력 할까요? (Y/N) N

입력이 완료되었습니다.

 

 

1. 신규회원 저장

2. 회원정보 수정 -> 추가 점수 항목임 (안해도 무방)

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

입력하세요> 4

HONG GIL DONG / 20 / hong@gmail.com

PARK GIL DONG / 22 / parkpark@hotmail.com                    

LEE GIL DONG / 23 / gildonglee@naver.com

CHOI GIL DONG / 24 / s11112222@kmu.com

 

 

1. 신규회원 저장

2. 회원정보 수정 -> 추가 점수 항목임 (안해도 무방)

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

입력하세요> 5

 

종료합니다.
```
 

s12341234@kmuce:~$ ./a.out   // 프로그램 다시 실행 후, 데이터가 유지됨을 보여주는 시나리오

```
1. 신규회원 저장

2. 회원정보 수정 -> 추가 점수 항목임 (안해도 무방)

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

입력하세요> 4

HONG GIL DONG / 20 / hong@gmail.com

PARK GIL DONG / 22 / parkpark@hotmail.com                    

LEE GIL DONG / 23 / gildonglee@naver.com

CHOI GIL DONG / 24 / s11112222@kmu.com

 

1. 신규회원 저장

2. 회원정보 수정

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

입력하세요> 3

 

여기서 현재 입력되어 있는 회원중 1명을 삭제 하는 

시나리오를 보이시오. (UI 는 자유롭게 스스로 디자인 하면 됨)





1. 신규회원 저장

2. 회원정보 수정

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

입력하세요> 5

 

종료합니다.
```
 

 

 

 

### [참고]

> 텍스트 파일 구성 시. 파일 포맷을 구상해야 함.

> 예를 들어, 이름이나 이메일 주소의 경우 스트링의 길이가 가변적이므로, 

> 파일에 데이터 저장 시, 스트링의 길이도 같이 저장해두면 파일에서 데이터를 읽을 때 정확한 길이 만큼 읽을 수 있을 것임.

> **데이터 파일 예시 1 : 모든 데이터를 특정 구분자(/) 로 나누어 저장** 

```
HONG GIL DONG / 23 / hong@gmail.com / KIM GIL DONG / 24 /
``` 

**데이터 파일 예시 2: 각 항목별 의미와 길이를 같이 기록**

```
NAME 13 HONG GIL DONG

AGE 23

EMAIL 14 hong@gmail.com
```


**데이터 피일 예시 3: 라인 단위로 모든 데이터 기록**

```
HONG GIL DONG

23

hong@gmail.com

KIM GIL DONG

24
```


# [추가 점수 : 5점]

**메뉴 2 회원 정보 수정 기능 구현  + 이메일 처리 루틴**

1. 신규회원 저장

2. 회원정보 수정 -> 추가 점수 항목임 (안해도 무방)

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

```
입력하세요> 2

수정할 사람 이름을 입력해주세요: HWANG GIL DONG

사용자 HWANG GIL DONG 은 없습니다. 

 

1. 신규회원 저장

2. 회원정보 수정 -> 추가 점수 항목임 (안해도 무방)

3. 회원 삭제

4. 모든 회원 리스트

5. 종료

입력하세요> 2

수정할 사람 이름을 입력해주세요: CHOI GIL

사용자 CHOI GIL 을 수정합니다. 

이름: CHOI GIL DONG

나이: 24

이메일: s11112222@kmu.com

수정 완료 되었습니다.
```
 

**이메일 처리 구현**

신규 회원 자정이나 회원 정보 수정 시,

사용자가 입력한 이메일 주소의 형식이 ---@---.--- 포맷인지 확인해서 이메일 포맷이 맞지 않는 경우 에러 메시지 출력 
