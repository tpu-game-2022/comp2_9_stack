﻿#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>
#include "../include/lib_func.h"
// mem_size の容量でスタック用のメモリを確保する
void initialize(STACK* s, size_t mem_size)
{
	if (s == NULL) return;

	// ToDo: mem_sizeでメモリを確保しよう
	if (mem_size > 0)
	{
		s->stack_memory = malloc(mem_size);
		s->stack_pointer = s->stack_memory + mem_size / sizeof(int);
		s->end = s->stack_pointer;
	}
	else
	{
		s->stack_memory = NULL;
	}
}


// 確保したメモリを解放する
void finalize(STACK* s)
{
	// ToDo: Initializeで確保したメモリを解放しよう
	if (s == NULL || s->stack_memory == NULL) return;

	free(s->stack_memory);

	s->stack_memory = NULL;
	s->stack_pointer = NULL;
	s->end = NULL;
}


// valの値をスタックに積む。実行の成否を返す
bool push(STACK* s, int val)
{
	// ToDo: valの値をスタックに保存しよう
	if (s == NULL || s->stack_memory == NULL) return false;

	if (s->stack_pointer <= s->stack_memory) return false;

	s->stack_pointer--;
	*s->stack_pointer = val;

	return true;
}


// addrから始まるnum個の整数をスタックに積む。実行の成否を返す
bool push_array(STACK* s, int* addr, int num)
{
	if (s == NULL || addr == NULL || num <= 0) return false;

	if (s->stack_pointer - num < s->stack_memory) return false;

	// ToDo: addrからはじまるnum個の整数をスタックに保存しよう
	for (int i = num - 1; i >= 0; i--)
	{
		if (!push(s, addr[i])) return false;
	}

	return true;
}

// スタックから一つの要素を取り出す
int pop(STACK* s)
{
	// ToDo: スタックの最上位の値を取り出して返そう
	// 不具合時は0を返す
	if (s == NULL || s->stack_memory == NULL) return 0;

	if (s->stack_pointer >= s->end) return 0;

	s->stack_pointer++;
	return *(s->stack_pointer - 1);
}

// addrにスタックからnumの要素を取り出す。取り出せた個数を返す
int pop_array(STACK* s, int* addr, int num)
{
	// ToDo: スタックからnum個の値を取り出してaddrから始まるメモリに保存しよう
	// スタックにnum個の要素がたまっていなかったら、積まれている要素を返して、
	// 積んだ要素数を返り値として返そう
	if (addr == NULL || num <= 0) return 0;

	int count = 0;

	for (int i = 0; i < num; i++)
	{
		int value = pop(s);

		if (value == 0) break;

		addr[i] = value;
		count++;
	}

	return count;
}