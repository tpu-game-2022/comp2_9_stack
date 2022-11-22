#pragma once // �C���N���[�h�K�[�h

#include <stdbool.h>

// C++ ��C�̃��C�u�������g���Ƃ��̂��܂��Ȃ�
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	int stack_pointer;
	int* stack_memory;
	int end;          // �X�^�b�N������������m�F���邽�߂̃|�C���^�i�\���̂�ύX���ĕʎ����ɂ��Ă��ǂ��j
}STACK;

void initialize(STACK* s, size_t mem_size);   // mem_size �̗e�ʂŃX�^�b�N�p�̃��������m�ۂ���
void finalize(STACK* s);                      // �m�ۂ������������������

bool push(STACK* s, int val);                 // val�̒l���X�^�b�N�ɐςށB���s�̐��ۂ�Ԃ�
bool push_array(STACK* s, int* addr, int num);// addr����n�܂�num�̐������X�^�b�N�ɐςށB���s�̐��ۂ�Ԃ�

int pop(STACK* s);                            // �X�^�b�N�����̗v�f�����o��(�s�����0��Ԃ�)
int pop_array(STACK* s, int* addr, int num);  // addr�ɃX�^�b�N����num�̗v�f�����o���B���o��������Ԃ�


	// C++ ��C�̃��C�u�������g���Ƃ��̂��܂��Ȃ�
#ifdef __cplusplus
} // extern "C"
#endif
