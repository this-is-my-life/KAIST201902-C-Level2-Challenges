/**
 * 여러가지 통계 수치 구하기
 * Made by 박민혁
 */

#include <stdio.h> // Standard I/O
#include <math.h> // Math

// 평균을 계산하는 함수 (배열과 그 길이를 받는다)
double avg (int arr[], int count) {
  int sum = 0; // 변량들의 합이 저장될 변수
  for (int c = 0; c < count; c++) {
    sum += arr[c];
  }
  return sum / count; // 변량들의 합에서 변량의 갯수를 나누어 반환
}

// 분산을 계산하는 함수 (배열과 그 길이를 받는다)
double vari (int arr[], int count) {
  double avgv = avg(arr, count); // 변량들의 평균값을 구한다
  double sum = 0;
  for (int c = 0; c < count; c++) {
    sum += pow(arr[c] - avgv, 2); // 각각의 변량에서 평균을 뺀 값을 제곱하여 모두 더하기
  }
  return sum / count; // 변량의 갯수로 나누어 반환
}

// 최댓값을 계산하는 함수 (배열과 그 길이를 받는다)
int max (int arr[], int count) {
  int temp = arr[0]; // 계산 중 최댓값이 임시로 저장될 변수
  for (int c = 1; c < count; c++) { // 윗줄에서 arr[0]을 사용하였으므로 0번째 변량은 계산할 필요가 없다
    if (temp < arr[c]) { // 임시로 저장된 값보다 클경우
      temp = arr[c]; // 임시로 저장된 값을 갈아치운다
    }
  }
  return temp; // 확정된 최댓값 반환
}

// 최솟값을 계산하는 함수 (배열과 그 길이를 받는다)
int min (int arr[], int count) {
  int temp = arr[0]; // 계산 중 최솟값이 임시로 저장될 변수
  for (int c = 1; c < count; c++) { // 윗줄에서 arr[0]을 사용하였으므로 0번째 변량은 계산할 필요가 없다
    if (temp > arr[c]) { // 임시로 저장된 값보다 작을경우
      temp = arr[c]; // 임시로 저장된 값을 갈아치운다
    }
  }
  return temp; // 확정된 최솟값 반환
}

// 최초 실행될 함수
int main (void) {
  int arr[100]; // 변량들이 저장될 배열
  int count; // 입력받을 변량의 개수

  printf("변량의 개수> "); // 프롬포트
  scanf("%d", &count); // 변량의 개수를 입력받는다

  for (int c = 0; c < count; c++) {
    printf("%d번째 변량> ", c + 1); // 프롬포트
    scanf("%d", &arr[c]); // 개수 만큼의 변량들을 입력 받는다
  }

  double avgResult = avg(arr, count); // 평균 계산 결과
  double variResult = vari(arr, count); // 분산 계산 결과
  int maxResult = max(arr, count); // 최댓값 계산 결과
  int minResult = min(arr, count); // 최솟값 계산 결과
  printf("\n%.4lf\n%.4lf\n%d\n%d", avgResult, variResult, maxResult, minResult); // 계산 결과값들을 출력한다

  return 0; // 정상종료 (이거 안하면 리눅셸이 뭐라 함)
}
