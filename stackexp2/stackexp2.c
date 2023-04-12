#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef char element;

typedef struct {
    element stack[MAX];
    int top;
} Stacktype;

void init_stack(Stacktype* s) {
    s->top = -1;
}

int is_empty(Stacktype* s) {
    return (s->top == -1);
}

int is_full(Stacktype* s) {
    return (s->top == (MAX - 1));
}

void push(Stacktype* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "���� ���� ��\n");
        return;
    }
    else {
        s->stack[++(s->top)] = item;
    }
}

element pop(Stacktype* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ��\n");
        return 0;
    }
    else {
        return s->stack[(s->top)--];
    }
}

element peek(Stacktype* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ��\n");
        return 0;
    }
    else {
        return s->stack[(s->top)];
    }
}
int is_number(char ch) {
    return (ch >= '0' && ch <= '9');
}
int is_operator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}
int evaluate(char postfix[]) {
    int i = 0, op1, op2;
    char ch1;
    int len = strlen(postfix);
    Stacktype s;

    init_stack(&s);

    for (i = 0; i < len; i++) {
        ch1 = postfix[i];
        if (is_number(ch1)) {
            push(&s, ch1 - '0');
        }
        else if (is_operator(ch1)) {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch1) {
            case '+':
                push(&s, op1 + op2);
                break;
            case '-':
                push(&s, op1 - op2);
                break;
            case '*':
                push(&s, op1 * op2);
                break;
            case '/':
                push(&s, op1 / op2);
                break;
            }
        }
        else {
            fprintf(stderr, "�߸��� �Է�");
            return -1;  // �Է��� �߸��Ǿ��� �� -1 ��ȯ
        }
    }
    return pop(&s);
}

int prec(char op) {
    switch (op) {
    case '(':case')':return 0;
    case '+':case'-':return 1;
    case '*':case'/':return 2;
    }
    return -1;
}

int infix_to_postfix(char infix[], char postfix[]) {
    int i = 0;
    char ch, top_op;
    int len = strlen(infix);
    Stacktype s;

    init_stack(&s);

    for (i = 0; i < len; i++) {
        ch = infix[i];
        switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
            while (!is_empty(&s) && (prec(ch) <= prec(peek(&s)))) {
                postfix[strlen(postfix)] = pop(&s);
            }
            push(&s, ch);
            break;

        case '(':
            push(&s, ch);
            break;
        case ')':
            top_op = pop(&s);
            while (top_op != '(') {
                postfix[strlen(postfix)] = top_op;
                top_op = pop(&s);
            }
            break;

        default:
            // �ǿ������� ��
            postfix[strlen(postfix)] = ch;
            break;
        }
    }

    while (!is_empty(&s)) {
        postfix[strlen(postfix)] = pop(&s);
    }

    postfix[strlen(postfix)] = '\0'; // ���ڿ��� ���� �� ���� �߰�
    return evaluate(postfix);
}


int main(void) {

    char exp[MAX] = { NULL };
    char post[MAX] = { NULL };
    int result = 0;

    printf("���� ǥ��� �Է�: ");
    scanf_s("%s", exp, MAX);

    result = infix_to_postfix(exp, post);
    if (result == -1) {
        printf("�߸��� �Է��Դϴ�.\n");
        return 0;
    }

    printf("���� ǥ���: %s\n", post);

    result = evaluate(post);
    if (result == -1) {
        printf("�߸��� �Է��Դϴ�.\n");
        return 0;
    }

    printf("��� ���: %d\n", result);

    return 0;
}