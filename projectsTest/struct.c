#include <stdio.h>

typedef struct  {
    int midGerm;
    int finalGrade;
} student;


int setGRade(student* student) {
    student->midGerm = 70;
    return 0;
}
int main(void) {
    student st;
    setGRade(&st);
    printf("student.midGerm = %d\n", st.midGerm);
    return 0;
}