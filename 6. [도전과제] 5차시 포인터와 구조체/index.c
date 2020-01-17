/**
 * @name 포인터로 메모리 할당하기
 * @author 박민혁
 */

#include <stdio.h> // Standard I/O
#include <stdlib.h> // 동적 할당을 위해 stdlib.h 사용

// 일정 구조체
typedef struct {
  struct { int year, month, date } date; // 날짜 저장
  struct { int hour, minute } time; // 시간 저장
  int important; // 중요도 저장
  char title[127]; // 일정 제목 저장
  char description[127]; // 일정 내용 저장
} Schedule;

// 프로그램 실행시 최초 동작 함수
int main () {
  int total; // 총 일정 수 저장
  Schedule *schedule; // 동적 할당을 위한 자료형 Schedule의 포인터
  scanf("%d", &total); // 총 일정 수 입력
  
  schedule = (Schedule *) malloc(sizeof(Schedule) * total); // Schedule을 total개 저장할 수 있도록 동적 할당

  // 일정을 각각 입력 받기
  for (int c = 0; c < total; c++) {
    int date; // 날짜를 임시로 저장할 yyyyMMdd 형식의 int
    int time; // 시간을 임시로 저장할 hhmm 형식의 int
    scanf("%d %d %d %s %s", // 날짜, 시간, 중요도, 제목, 내용을 입력받는다
      &date,
      &time,
      &schedule[c].important,
      &schedule[c].title,
      &schedule[c].description );

    schedule[c].date.date = date % 100; // 날짜의 년도 계산
    schedule[c].date.month = (int) date % 10000 / 100; // 날짜의 월 계산
    schedule[c].date.year = (int) date / 10000; // 날짜의 일 계산

    schedule[c].time.minute = time % 100; // 시간의 분 계산
    schedule[c].time.hour = (int) time / 100; // 시간의 시 계산
  }

  // 일정을 각각 출력하기
  for (int c = 0; c < total; c++) {
    printf("%04d.%02d.%02d. %02d:%02d %d %s %s\n", // yyyy.MM.dd형식에 따라 날짜 출력 & hh:mm형식에 따라 시간 출력
      schedule[c].date.year,
      schedule[c].date.month,
      schedule[c].date.date,
      schedule[c].time.hour,
      schedule[c].time.minute,
      schedule[c].important,
      schedule[c].title,
      schedule[c].description );
  }

  free(schedule); // 메모리 할당 해제
}
