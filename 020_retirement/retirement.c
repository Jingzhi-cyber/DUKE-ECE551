#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

struct _ageAndBalance {
  int age;
  double balance;
};

typedef struct _ageAndBalance ageAndBalance;

ageAndBalance calculateBalance(retire_info bankInfo, int startAge, double initial) {
  int currentAge = startAge;
  double currentBalance = initial;
  ageAndBalance currentAgeAndBalance;

  for (int i = 1; i <= bankInfo.months; i++) {
    printf("Age %3d month %2d you have $%.2f\n",
           currentAge / 12,
           currentAge % 12,
           currentBalance);

    currentBalance =
        currentBalance + currentBalance * bankInfo.rate_of_return + bankInfo.contribution;

    currentAge++;
  }

  currentAgeAndBalance.age = currentAge;
  currentAgeAndBalance.balance = currentBalance;

  return currentAgeAndBalance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  ageAndBalance currentAgeAndBalance = calculateBalance(working, startAge, initial);
  //  printf("\nCurrent age is %3d , current month is %2d, current balence is $%.2f\n",
  //       currentAgeAndBalance.age / 12,
  //       currentAgeAndBalance.age % 12,
  //       currentAgeAndBalance.balance);
  calculateBalance(retired, currentAgeAndBalance.age, currentAgeAndBalance.balance);
}

retire_info setInfo(int months, double contribution, double rate_of_return) {
  retire_info bankInfo;
  bankInfo.months = months;
  bankInfo.contribution = contribution;
  bankInfo.rate_of_return = rate_of_return;

  return bankInfo;
}

int main() {
  retire_info working = setInfo(489, 1000, 0.045 / 12);
  retire_info retired = setInfo(384, -4000, 0.01 / 12);

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
