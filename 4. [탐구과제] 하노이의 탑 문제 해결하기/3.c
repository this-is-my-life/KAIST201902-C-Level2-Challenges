  #include <stdio.h> // Standard I/O
  #include <unistd.h> // Unix Sleep functions
  #include <string.h> // String functions

  #define MAX_PLATE 50 // 원판의 최대 개수
  #define MAX_POLE 10 // 기둥의 최대 개수

  struct {
    int plate[MAX_PLATE];
    int length;
  } poles[MAX_POLE]; // 기둥을 만든다

  // 보기 쉽도록, 함수를 미리 선언 해둔다 (여기서 추가된 Limit는 마지막으로 사용할 수 있는 기둥의 index값을 의미 한다)
  int move (), manual (), automatic (), checkFinish (), try = 0, limit;
  void printTower (), solveProc ();

  // 초기 실행 함수
  int main () {
    int count, moveTo, mode; // count: 원판의 개수, moveTo: 이동할 기둥, mode: 수동, 자동 선택
    
    // CUI

    // 출력할 문자열
    char str[] = "===================\n하노이의 탑\nCreated By 박민혁\n===================\n\n원판의 개수를 입력하세요> \n옮길 기둥 번호를 입력하세요> \n직접 실행은 1번, 자동 실행은 2번을 입력하세요> \n===================\n\n";

    // str의 한글자, 한글자 마다...
    for (int c = 0; c < strlen(str); c++) {
      
      printf("%c", str[c]); // 그 글자를 출력한다

      // Prompt
      switch (c) {
        case 115: // 115번째 글자가 출력되었을때..
          scanf("%d", &count); // count를 물어본다
          break;

        case 157: // 157번째 글자가 출력되었을때..
          scanf("%d", &moveTo); // moveTo를 물어본다
          break;

        case 223: // 223번째 글자가 출력되었을대..
          scanf("%d", &mode); // mode를 물어본다
          break;

        default: // 아무것도 속하지 못하면..
          usleep(10000); // 0.01초 대기한다 (짧은거 같아 보여도, 한줄 출력에 0.5초?)
          break;
      }
    }

    // 사용 할 수 있는 마지막 기둥의 index값을 정해준다 (이 값을 증가시키면 사용할 수 있는 기둥의 개수가 늘어나 난이도가 더 쉬워진다)
    limit = moveTo;

    // 원판의 개수와 옮길 기둥을 검사한다
    if (count > MAX_PLATE || moveTo < 2 || moveTo > MAX_POLE) printf("오류) 원판은 %d개 이하, 옮길 기둥은 2이상, %d이하여야 합니다", MAX_PLATE, MAX_POLE);

    // 입력된 mode에 따라 manual과 automatic함수를 실행한다
    else if (mode == 1) manual(count, moveTo);
    else if (mode == 2) automatic(count, moveTo);

    // 입력이 에초에 잘못되었거나, 모드가 없는 모드라면 출력한다
    else printf("오류) 저런! %d는 없는 모드입니다!", mode);
    return 0;
  }

  // 수동 모드 함수 (수동 모드를 선택 했을때 실행된다)
  int manual (int count, int moveTo) {
    
    // 0번째 기둥에 원판 넣기
    for (int c = count; c > 0; c--) {
      poles[0].plate[count - c] = c;
    }

    // 기둥들의 원판 개수 대입 
    for (int c = 0; c < moveTo; c++) {
      poles[c].length = c < 1 ? count : 0;
    }

    printTower();

    int from, to; // "from에서 to로 원판을 이동"을 저장하기 위한 변수들 

    while (1) {
      printf("어디서 어디로 원판을 이동할까요?> ");
      scanf("%d %d", &from, &to);
      if (move(from, to)) { // move를 시도하고 결과가 실패(1)일 경우
        printf("오류) 저런! %d에서 %d로 이동할 수 없어요!\n", from, to);
        usleep(10000);
      }
      if (checkFinish(count, moveTo)) break; // 성공했다면, 반복문 나가기
    }
    printf("\n%d번째 만에 성공하셨습니다!", try); // 시도 횟수 출력
    return 0;
  }

  // 자동 모드 함수 (자동 모드를 선택했을때 실행된다)
  int automatic (int count, int moveTo) {
    
    // 수동과 동일
    for (int c = count; c > 0; c--) {
      poles[0].plate[count - c] = c;
    }

    // 수동과 동일
    for (int c = 0; c < moveTo; c++) {
      poles[c].length = c < 1 ? count : 0;
    }

    printTower();
    
    // count개의 원판을 moveTo개의 기둥 중 0번 기둥에서 1기둥을 통해 moveTo로 간다
    solveProc(count, 0, 1, moveTo);
    
    printf("\n%d번째 만에 성공하였습니다!", try);
    return 0;
  }

  // 하노이의 탑 풀기
  void solveProc (int n, int from, int sub, int to) { // n개의 원판을 from번째 기둥에서 sub번째 기둥를 통해 to번째 기둥으로..
    if (n == 1) { // 처리할 원판이 1개일 경우 to번째 기둥으로 옮기고 끝내기
      usleep(1000000);
      move(from, to);
    } else {
      solveProc(n - 1, from, to, sub); // 임시로 n - 1개를 sub번째 기둥으로 옮겨놓기
      usleep(1000000);
      move(from, to); // 남은 1개(가장 큰 원판을)를 to번째 기둥으로 옮기기
      solveProc(n - 1, sub, from, to); // sub번째 기둥에 임시로 옮겨둔 원판을 to번째 기둥으로 옮기기
    }
  }

  // 원판 이동 함수
  int move (int from, int to) {
    if (from < 0 || to < 0 || from > limit || to > limit) return 1; // from과 to가 없는 기둥을 가르키면 이동 금지
    if (poles[from].length < 1) return 1; // from의 원판에 개수가 1보다 작음 = 원판이 없음 = 이동 불가능
    if (poles[to].length > 0 && poles[to].plate[poles[to].length - 1] < poles[from].plate[poles[from].length - 1]) return 1;  // to의 원판에 원판이 있을경우, 기존의 원판이 새로 위에 쌓을 원판의 크기보다 작음 = 이동 불가능

    try++; // 이동 횟수 증가

    printf("\n (%d번째 기둥의 %d원판이 %d번째의 기둥으로 이동하였습니다)\n", from, poles[from].plate[poles[from].length - 1], to + 1);
    
    poles[to].plate[poles[to].length] = poles[from].plate[poles[from].length - 1]; // to기둥의 기존의 원판 위에 쌓기
    poles[from].plate[poles[from].length - 1] = 0; // 이미 이동한 from기둥의 원판은 사라짐
    poles[to].length++; // to기둥의 원판 개수가 1 늘어남
    poles[from].length--; // from기둥의 원판 개수가 1 줄어듬
    
    printTower();
    return 0;
  }

  // 기둥 출력 함수
  void printTower () {
    int i, j;
    printf("\n==== %d번째 이동하셨습니다 ====\n", try);
    for (i = 0; i < limit + 1; i++) { // 기둥 마다...
      printf("%d: ", i);
      if (poles[i].length < 1) printf("x"); // 만약 원판이 없을때..
      else {
        for (j = 0; j < poles[i].length; j++) { // 원판 마다...
          printf("%d ", poles[i].plate[j]);
        }
      }
      printf("\n"); // LF (Line Feed)
    }
    printf("================\n");
  }

  // 게임의 끝을 알려주는 함수
  int checkFinish (int count, int moveTo) {
    if (poles[moveTo].length == count) return 1; // 이동하기로 한 기둥의 원판 개수가 처음의 전체 원판의 개수와 동일 = 이동하기로 한 기둥으로 원판이 전부 이동했다 = 게임이 끝났다
    else return 0;
  }
