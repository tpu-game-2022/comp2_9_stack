#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// mem_size の容量でスタック用のメモリを確保する
void initialize(STACK* s, size_t mem_size)
{
	if (s == NULL) return;// 最低限のチェック

	s->stack_memory = (int*)malloc(mem_size);
	if (NULL == s->stack_memory) return;
	s->end = &s->stack_memory[mem_size/sizeof(int)];
	s->stack_pointer = s->end;
}


// 確保したメモリを解放する
void finalize(STACK* s)
{
	if (s == NULL) return;// 最低限のチェック

	free(s->stack_memory);
	s->stack_memory = s->stack_pointer = s->end = NULL;
}


// valの値をスタックに積む。実行の成否を返す
bool push(STACK* s, int val)
{
	if (s == NULL || NULL == s->stack_memory) return false;// 最低限のチェック

	if (s->stack_pointer - 1 < s->stack_memory) return false;// 格納できるか確認

	*--s->stack_pointer = val;// 値を入れた後にスタックポインタのアドレスを進ませる

	return true;
}


// addrから始まるnum個の整数をスタックに積む。実行の成否を返す
bool push_array(STACK* s, int* addr, int num)
{
	if (s == NULL || NULL == s->stack_memory) return false;// 最低限のチェック
	if (num <= 0) return false;
	if (s->stack_pointer - num < s->stack_memory) return false;// 格納できるか確認

	s->stack_pointer -= num;
	memcpy_s(s->stack_pointer, sizeof(int) * num, addr, sizeof(int) * num);

	return true;
}

// スタックから一つの要素を取り出す
int pop(STACK* s)
{
	// 不具合時は0を返す
	if (s == NULL || NULL == s->stack_memory) return 0;
	if (s->end <= s->stack_pointer) return 0;// 積まれていない

	return *s->stack_pointer++;
}

// addrにスタックからnumの要素を取り出す。取り出せた個数を返す
int pop_array(STACK* s, int* addr, int num)
{
	if (s == NULL || NULL == s->stack_memory) return 0;
	if (s->end <= s->stack_pointer) return 0;// 積まれていない

	int n = (int)(s->end - s->stack_pointer);// 積まれた数
	n = (n < num) ? n : num;
	if (n <= 0) return 0;// 負の数は取り出せない

	memcpy_s(addr, sizeof(int) * n, s->stack_pointer, sizeof(int) * n);
	s->stack_pointer += n;

	return n;
}