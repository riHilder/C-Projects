/*
23
https://pan.quark.cn/s/ce8e49f4f903#/list/share
   
21
https://pan.baidu.com/share/init?surl=JB7QVdlKXePQchsq-xXKQg
kf9c
    
19
https://pan.baidu.com/share/init?surl=DwVJ7TidujvV-vXhT0Tegw
b5g5


https://zjj.sz.gov.cn/szzjxx/web/pc/index
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int sum_squared_digits(int n) {
    int sum = 0;

    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }

    return sum;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]);

    int slow = number;
    int fast = sum_squared_digits(number);

    while (fast != 1 && slow != fast) {
        slow = sum_squared_digits(slow);
        fast = sum_squared_digits(sum_squared_digits(fast));
    }

    if (fast == 1) {
        printf("CONGRATULATION, %d IS A HAPPY NUMBER!\n", number);
    } else {
        printf("SORRY, %d IS NOT A HAPPY NUMBER.\n", number);
    }

    return 0;
}
