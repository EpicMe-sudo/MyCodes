#include "LEA128.h"

unsigned int delta[8] = {
0xc3efe9db,0x44626b02,0x79e27c8a,0x78df30ec,
0x715ea49e,0xc785da0a,0xe04ef22a,0xe5c40957
};

WORD RotationLeft(WORD word, const unsigned int NumberOfBitToShift) {
	return (word << NumberOfBitToShift) | (word >> (NumberOfBit_Word - NumberOfBitToShift));
}

WORD RotationRight(WORD word, const unsigned int NumberOfBitToShift) {
	return (word >> NumberOfBitToShift) | (word << (NumberOfBit_Word - NumberOfBitToShift));
}

void LeaKeySchedule128(BYTE MK[16], RoundKey RoundKey[24]) {

	// 192bit No.0 Round Key
	RoundKey[0].RK[0] = RotationLeft(((MK[3] << 24) | (MK[2] << 16) | (MK[1] << 8) | MK[0]) + RotationLeft(delta[0], 0), 1);
	RoundKey[0].RK[1] = RoundKey[0].RK[3] = RoundKey[0].RK[5] = RotationLeft(((MK[7] << 24) | (MK[6] << 16) | (MK[5] << 8) | MK[4]) + RotationLeft(delta[0], 1), 3);
	RoundKey[0].RK[2] = RotationLeft(((MK[11] << 24) | (MK[10] << 16) | (MK[9] << 8) | MK[8]) + RotationLeft(delta[0], 2), 6);
	RoundKey[0].RK[4] = RotationLeft(((MK[15] << 24) | (MK[14] << 16) | (MK[13] << 8) | MK[12]) + RotationLeft(delta[0], 3), 11);

	// 192bit No.1 Round Key
	RoundKey[1].RK[0] = RotationLeft(RoundKey[0].RK[0] + RotationLeft(delta[1], 1), 1);
	RoundKey[1].RK[1] = RoundKey[1].RK[3] = RoundKey[1].RK[5] = RotationLeft(RoundKey[0].RK[1] + RotationLeft(delta[1], 2), 3);
	RoundKey[1].RK[2] = RotationLeft(RoundKey[0].RK[2] + RotationLeft(delta[1], 3), 6);
	RoundKey[1].RK[4] = RotationLeft(RoundKey[0].RK[4] + RotationLeft(delta[1], 4), 11);

	// 192bit No.2 Round Key
	RoundKey[2].RK[0] = RotationLeft(RoundKey[1].RK[0] + RotationLeft(delta[2], 2), 1);
	RoundKey[2].RK[1] = RoundKey[2].RK[3] = RoundKey[2].RK[5] = RotationLeft(RoundKey[1].RK[1] + RotationLeft(delta[2], 3), 3);
	RoundKey[2].RK[2] = RotationLeft(RoundKey[1].RK[2] + RotationLeft(delta[2], 4), 6);
	RoundKey[2].RK[4] = RotationLeft(RoundKey[1].RK[4] + RotationLeft(delta[2], 5), 11);

	// 192bit No.3 Round Key
	RoundKey[3].RK[0] = RotationLeft(RoundKey[2].RK[0] + RotationLeft(delta[3], 3), 1);
	RoundKey[3].RK[1] = RoundKey[3].RK[3] = RoundKey[3].RK[5] = RotationLeft(RoundKey[2].RK[1] + RotationLeft(delta[3], 4), 3);
	RoundKey[3].RK[2] = RotationLeft(RoundKey[2].RK[2] + RotationLeft(delta[3], 5), 6);
	RoundKey[3].RK[4] = RotationLeft(RoundKey[2].RK[4] + RotationLeft(delta[3], 6), 11);

	// 192bit No.4 Round Key
	RoundKey[4].RK[0] = RotationLeft(RoundKey[3].RK[0] + RotationLeft(delta[0], 4), 1);
	RoundKey[4].RK[1] = RoundKey[4].RK[3] = RoundKey[4].RK[5] = RotationLeft(RoundKey[3].RK[1] + RotationLeft(delta[0], 5), 3);
	RoundKey[4].RK[2] = RotationLeft(RoundKey[3].RK[2] + RotationLeft(delta[0], 6), 6);
	RoundKey[4].RK[4] = RotationLeft(RoundKey[3].RK[4] + RotationLeft(delta[0], 7), 11);

	// 192bit No.5 Round Key
	RoundKey[5].RK[0] = RotationLeft(RoundKey[4].RK[0] + RotationLeft(delta[1], 5), 1);
	RoundKey[5].RK[1] = RoundKey[5].RK[3] = RoundKey[5].RK[5] = RotationLeft(RoundKey[4].RK[1] + RotationLeft(delta[1], 6), 3);
	RoundKey[5].RK[2] = RotationLeft(RoundKey[4].RK[2] + RotationLeft(delta[1], 7), 6);
	RoundKey[5].RK[4] = RotationLeft(RoundKey[4].RK[4] + RotationLeft(delta[1], 8), 11);

	// 192bit No.6 Round Key (������� ���� ����!)
	RoundKey[6].RK[0] = RotationLeft(RoundKey[5].RK[0] + RotationLeft(delta[2], 6), 1);
	RoundKey[6].RK[1] = RoundKey[6].RK[3] = RoundKey[6].RK[5] = RotationLeft(RoundKey[5].RK[1] + RotationLeft(delta[2], 7), 3);
	RoundKey[6].RK[2] = RotationLeft(RoundKey[5].RK[2] + RotationLeft(delta[2], 8), 6);
	RoundKey[6].RK[4] = RotationLeft(RoundKey[5].RK[4] + RotationLeft(delta[2], 9), 11);

	// 192bit No.7 Round Key
	RoundKey[7].RK[0] = RotationLeft(RoundKey[6].RK[0] + RotationLeft(delta[3], 7), 1);
	RoundKey[7].RK[1] = RoundKey[7].RK[3] = RoundKey[7].RK[5] = RotationLeft(RoundKey[6].RK[1] + RotationLeft(delta[3], 8), 3);
	RoundKey[7].RK[2] = RotationLeft(RoundKey[6].RK[2] + RotationLeft(delta[3], 9), 6);
	RoundKey[7].RK[4] = RotationLeft(RoundKey[6].RK[4] + RotationLeft(delta[3], 10), 11);

	// 192bit No.8 Round Key
	RoundKey[8].RK[0] = RotationLeft(RoundKey[7].RK[0] + RotationLeft(delta[0], 8), 1);
	RoundKey[8].RK[1] = RoundKey[8].RK[3] = RoundKey[8].RK[5] = RotationLeft(RoundKey[7].RK[1] + RotationLeft(delta[0], 9), 3);
	RoundKey[8].RK[2] = RotationLeft(RoundKey[7].RK[2] + RotationLeft(delta[0], 10), 6);
	RoundKey[8].RK[4] = RotationLeft(RoundKey[7].RK[4] + RotationLeft(delta[0], 11), 11);

	// 192bit No.9 Round Key
	RoundKey[9].RK[0] = RotationLeft(RoundKey[8].RK[0] + RotationLeft(delta[1], 9), 1);
	RoundKey[9].RK[1] = RoundKey[9].RK[3] = RoundKey[9].RK[5] = RotationLeft(RoundKey[8].RK[1] + RotationLeft(delta[1], 10), 3);
	RoundKey[9].RK[2] = RotationLeft(RoundKey[8].RK[2] + RotationLeft(delta[1], 11), 6);
	RoundKey[9].RK[4] = RotationLeft(RoundKey[8].RK[4] + RotationLeft(delta[1], 12), 11);

	// 192bit No.10 Round Key
	RoundKey[10].RK[0] = RotationLeft(RoundKey[9].RK[0] + RotationLeft(delta[2], 10), 1);
	RoundKey[10].RK[1] = RoundKey[10].RK[3] = RoundKey[10].RK[5] = RotationLeft(RoundKey[9].RK[1] + RotationLeft(delta[2], 11), 3);
	RoundKey[10].RK[2] = RotationLeft(RoundKey[9].RK[2] + RotationLeft(delta[2], 12), 6);
	RoundKey[10].RK[4] = RotationLeft(RoundKey[9].RK[4] + RotationLeft(delta[2], 13), 11);

	// 192bit No.11 Round Key
	RoundKey[11].RK[0] = RotationLeft(RoundKey[10].RK[0] + RotationLeft(delta[3], 11), 1);
	RoundKey[11].RK[1] = RoundKey[11].RK[3] = RoundKey[11].RK[5] = RotationLeft(RoundKey[10].RK[1] + RotationLeft(delta[3], 12), 3);
	RoundKey[11].RK[2] = RotationLeft(RoundKey[10].RK[2] + RotationLeft(delta[3], 13), 6);
	RoundKey[11].RK[4] = RotationLeft(RoundKey[10].RK[4] + RotationLeft(delta[3], 14), 11);

	// 192bit No.12 Round Key
	RoundKey[12].RK[0] = RotationLeft(RoundKey[11].RK[0] + RotationLeft(delta[0], 12), 1);
	RoundKey[12].RK[1] = RoundKey[12].RK[3] = RoundKey[12].RK[5] = RotationLeft(RoundKey[11].RK[1] + RotationLeft(delta[0], 13), 3);
	RoundKey[12].RK[2] = RotationLeft(RoundKey[11].RK[2] + RotationLeft(delta[0], 14), 6);
	RoundKey[12].RK[4] = RotationLeft(RoundKey[11].RK[4] + RotationLeft(delta[0], 15), 11);

	// 192bit No.13 Round Key
	RoundKey[13].RK[0] = RotationLeft(RoundKey[12].RK[0] + RotationLeft(delta[1], 13), 1);
	RoundKey[13].RK[1] = RoundKey[13].RK[3] = RoundKey[13].RK[5] = RotationLeft(RoundKey[12].RK[1] + RotationLeft(delta[1], 14), 3);
	RoundKey[13].RK[2] = RotationLeft(RoundKey[12].RK[2] + RotationLeft(delta[1], 15), 6);
	RoundKey[13].RK[4] = RotationLeft(RoundKey[12].RK[4] + RotationLeft(delta[1], 16), 11);

	// 192bit No.14 Round Key
	RoundKey[14].RK[0] = RotationLeft(RoundKey[13].RK[0] + RotationLeft(delta[2], 14), 1);
	RoundKey[14].RK[1] = RoundKey[14].RK[3] = RoundKey[14].RK[5] = RotationLeft(RoundKey[13].RK[1] + RotationLeft(delta[2], 15), 3);
	RoundKey[14].RK[2] = RotationLeft(RoundKey[13].RK[2] + RotationLeft(delta[2], 16), 6);
	RoundKey[14].RK[4] = RotationLeft(RoundKey[13].RK[4] + RotationLeft(delta[2], 17), 11);

	// 192bit No.15 Round Key
	RoundKey[15].RK[0] = RotationLeft(RoundKey[14].RK[0] + RotationLeft(delta[3], 15), 1);
	RoundKey[15].RK[1] = RoundKey[15].RK[3] = RoundKey[15].RK[5] = RotationLeft(RoundKey[14].RK[1] + RotationLeft(delta[3], 16), 3);
	RoundKey[15].RK[2] = RotationLeft(RoundKey[14].RK[2] + RotationLeft(delta[3], 17), 6);
	RoundKey[15].RK[4] = RotationLeft(RoundKey[14].RK[4] + RotationLeft(delta[3], 18), 11);

	// 192bit No.16 Round Key
	RoundKey[16].RK[0] = RotationLeft(RoundKey[15].RK[0] + RotationLeft(delta[0], 16), 1);
	RoundKey[16].RK[1] = RoundKey[16].RK[3] = RoundKey[16].RK[5] = RotationLeft(RoundKey[15].RK[1] + RotationLeft(delta[0], 17), 3);
	RoundKey[16].RK[2] = RotationLeft(RoundKey[15].RK[2] + RotationLeft(delta[0], 18), 6);
	RoundKey[16].RK[4] = RotationLeft(RoundKey[15].RK[4] + RotationLeft(delta[0], 19), 11);

	// 192bit No.17 Round Key
	RoundKey[17].RK[0] = RotationLeft(RoundKey[16].RK[0] + RotationLeft(delta[1], 17), 1);
	RoundKey[17].RK[1] = RoundKey[17].RK[3] = RoundKey[17].RK[5] = RotationLeft(RoundKey[16].RK[1] + RotationLeft(delta[1], 18), 3);
	RoundKey[17].RK[2] = RotationLeft(RoundKey[16].RK[2] + RotationLeft(delta[1], 19), 6);
	RoundKey[17].RK[4] = RotationLeft(RoundKey[16].RK[4] + RotationLeft(delta[1], 20), 11);

	// 192bit No.18 Round Key
	RoundKey[18].RK[0] = RotationLeft(RoundKey[17].RK[0] + RotationLeft(delta[2], 18), 1);
	RoundKey[18].RK[1] = RoundKey[18].RK[3] = RoundKey[18].RK[5] = RotationLeft(RoundKey[17].RK[1] + RotationLeft(delta[2], 19), 3);
	RoundKey[18].RK[2] = RotationLeft(RoundKey[17].RK[2] + RotationLeft(delta[2], 20), 6);
	RoundKey[18].RK[4] = RotationLeft(RoundKey[17].RK[4] + RotationLeft(delta[2], 21), 11);

	// 192bit No.19 Round Key
	RoundKey[19].RK[0] = RotationLeft(RoundKey[18].RK[0] + RotationLeft(delta[3], 19), 1);
	RoundKey[19].RK[1] = RoundKey[19].RK[3] = RoundKey[19].RK[5] = RotationLeft(RoundKey[18].RK[1] + RotationLeft(delta[3], 20), 3);
	RoundKey[19].RK[2] = RotationLeft(RoundKey[18].RK[2] + RotationLeft(delta[3], 21), 6);
	RoundKey[19].RK[4] = RotationLeft(RoundKey[18].RK[4] + RotationLeft(delta[3], 22), 11);

	// 192bit No.20 Round Key
	RoundKey[20].RK[0] = RotationLeft(RoundKey[19].RK[0] + RotationLeft(delta[0], 20), 1);
	RoundKey[20].RK[1] = RoundKey[20].RK[3] = RoundKey[20].RK[5] = RotationLeft(RoundKey[19].RK[1] + RotationLeft(delta[0], 21), 3);
	RoundKey[20].RK[2] = RotationLeft(RoundKey[19].RK[2] + RotationLeft(delta[0], 22), 6);
	RoundKey[20].RK[4] = RotationLeft(RoundKey[19].RK[4] + RotationLeft(delta[0], 23), 11);

	// 192bit No.21 Round Key
	RoundKey[21].RK[0] = RotationLeft(RoundKey[20].RK[0] + RotationLeft(delta[1], 21), 1);
	RoundKey[21].RK[1] = RoundKey[21].RK[3] = RoundKey[21].RK[5] = RotationLeft(RoundKey[20].RK[1] + RotationLeft(delta[1], 22), 3);
	RoundKey[21].RK[2] = RotationLeft(RoundKey[20].RK[2] + RotationLeft(delta[1], 23), 6);
	RoundKey[21].RK[4] = RotationLeft(RoundKey[20].RK[4] + RotationLeft(delta[1], 24), 11);

	// 192bit No.22 Round Key
	RoundKey[22].RK[0] = RotationLeft(RoundKey[21].RK[0] + RotationLeft(delta[2], 22), 1);
	RoundKey[22].RK[1] = RoundKey[22].RK[3] = RoundKey[22].RK[5] = RotationLeft(RoundKey[21].RK[1] + RotationLeft(delta[2], 23), 3);
	RoundKey[22].RK[2] = RotationLeft(RoundKey[21].RK[2] + RotationLeft(delta[2], 24), 6);
	RoundKey[22].RK[4] = RotationLeft(RoundKey[21].RK[4] + RotationLeft(delta[2], 25), 11);

	// 192bit No.23 Round Key
	RoundKey[23].RK[0] = RotationLeft(RoundKey[22].RK[0] + RotationLeft(delta[3], 23), 1);
	RoundKey[23].RK[1] = RoundKey[23].RK[3] = RoundKey[23].RK[5] = RotationLeft(RoundKey[22].RK[1] + RotationLeft(delta[3], 24), 3);
	RoundKey[23].RK[2] = RotationLeft(RoundKey[22].RK[2] + RotationLeft(delta[3], 25), 6);
	RoundKey[23].RK[4] = RotationLeft(RoundKey[22].RK[4] + RotationLeft(delta[3], 26), 11);
}

void Round(unsigned int* Plaintext, unsigned int* Ciphertext, RoundKey* RoundKey)
{

	unsigned int X[4], temp; // 128��Ʈ ���� ���� ����
	// X0 <- P �ʱ� X�� �򹮰� �Ҵ�
	X[0] = Plaintext[0];
	X[1] = Plaintext[1];
	X[2] = Plaintext[2];
	X[3] = Plaintext[3];
	//printf("X0 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X1
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[0].RK[0]) + (X[1] ^ RoundKey[0].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[0].RK[2]) + (X[2] ^ RoundKey[0].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[0].RK[4]) + (X[3] ^ RoundKey[0].RK[5]), 3);
	X[3] = temp;
	//printf("X1 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X2
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[1].RK[0]) + (X[1] ^ RoundKey[1].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[1].RK[2]) + (X[2] ^ RoundKey[1].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[1].RK[4]) + (X[3] ^ RoundKey[1].RK[5]), 3);
	X[3] = temp;
	//printf("X2 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X3
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[2].RK[0]) + (X[1] ^ RoundKey[2].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[2].RK[2]) + (X[2] ^ RoundKey[2].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[2].RK[4]) + (X[3] ^ RoundKey[2].RK[5]), 3);
	X[3] = temp;
	//printf("X3 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X4
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[3].RK[0]) + (X[1] ^ RoundKey[3].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[3].RK[2]) + (X[2] ^ RoundKey[3].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[3].RK[4]) + (X[3] ^ RoundKey[3].RK[5]), 3);
	X[3] = temp;
	//printf("X4 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X5
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[4].RK[0]) + (X[1] ^ RoundKey[4].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[4].RK[2]) + (X[2] ^ RoundKey[4].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[4].RK[4]) + (X[3] ^ RoundKey[4].RK[5]), 3);
	X[3] = temp;
	//printf("X5 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X6
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[5].RK[0]) + (X[1] ^ RoundKey[5].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[5].RK[2]) + (X[2] ^ RoundKey[5].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[5].RK[4]) + (X[3] ^ RoundKey[5].RK[5]), 3);
	X[3] = temp;
	//printf("X6 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X7
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[6].RK[0]) + (X[1] ^ RoundKey[6].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[6].RK[2]) + (X[2] ^ RoundKey[6].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[6].RK[4]) + (X[3] ^ RoundKey[6].RK[5]), 3);
	X[3] = temp;
	//printf("X7 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X8
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[7].RK[0]) + (X[1] ^ RoundKey[7].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[7].RK[2]) + (X[2] ^ RoundKey[7].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[7].RK[4]) + (X[3] ^ RoundKey[7].RK[5]), 3);
	X[3] = temp;
	//printf("X8 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X9
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[8].RK[0]) + (X[1] ^ RoundKey[8].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[8].RK[2]) + (X[2] ^ RoundKey[8].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[8].RK[4]) + (X[3] ^ RoundKey[8].RK[5]), 3);
	X[3] = temp;
	//printf("X9 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X10
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[9].RK[0]) + (X[1] ^ RoundKey[9].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[9].RK[2]) + (X[2] ^ RoundKey[9].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[9].RK[4]) + (X[3] ^ RoundKey[9].RK[5]), 3);
	X[3] = temp;
	//printf("X10 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X11
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[10].RK[0]) + (X[1] ^ RoundKey[10].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[10].RK[2]) + (X[2] ^ RoundKey[10].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[10].RK[4]) + (X[3] ^ RoundKey[10].RK[5]), 3);
	X[3] = temp;
	//printf("X11 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X12
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[11].RK[0]) + (X[1] ^ RoundKey[11].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[11].RK[2]) + (X[2] ^ RoundKey[11].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[11].RK[4]) + (X[3] ^ RoundKey[11].RK[5]), 3);
	X[3] = temp;
	//printf("X12 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X13
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[12].RK[0]) + (X[1] ^ RoundKey[12].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[12].RK[2]) + (X[2] ^ RoundKey[12].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[12].RK[4]) + (X[3] ^ RoundKey[12].RK[5]), 3);
	X[3] = temp;
	//printf("X13 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X14
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[13].RK[0]) + (X[1] ^ RoundKey[13].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[13].RK[2]) + (X[2] ^ RoundKey[13].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[13].RK[4]) + (X[3] ^ RoundKey[13].RK[5]), 3);
	X[3] = temp;
	//printf("X14 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X15
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[14].RK[0]) + (X[1] ^ RoundKey[14].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[14].RK[2]) + (X[2] ^ RoundKey[14].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[14].RK[4]) + (X[3] ^ RoundKey[14].RK[5]), 3);
	X[3] = temp;
	//printf("X15 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X16
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[15].RK[0]) + (X[1] ^ RoundKey[15].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[15].RK[2]) + (X[2] ^ RoundKey[15].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[15].RK[4]) + (X[3] ^ RoundKey[15].RK[5]), 3);
	X[3] = temp;
	//printf("X16 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X17
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[16].RK[0]) + (X[1] ^ RoundKey[16].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[16].RK[2]) + (X[2] ^ RoundKey[16].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[16].RK[4]) + (X[3] ^ RoundKey[16].RK[5]), 3);
	X[3] = temp;
	//printf("X17 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X18
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[17].RK[0]) + (X[1] ^ RoundKey[17].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[17].RK[2]) + (X[2] ^ RoundKey[17].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[17].RK[4]) + (X[3] ^ RoundKey[17].RK[5]), 3);
	X[3] = temp;
	//printf("X18 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X19
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[18].RK[0]) + (X[1] ^ RoundKey[18].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[18].RK[2]) + (X[2] ^ RoundKey[18].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[18].RK[4]) + (X[3] ^ RoundKey[18].RK[5]), 3);
	X[3] = temp;
	//printf("X19 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X20
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[19].RK[0]) + (X[1] ^ RoundKey[19].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[19].RK[2]) + (X[2] ^ RoundKey[19].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[19].RK[4]) + (X[3] ^ RoundKey[19].RK[5]), 3);
	X[3] = temp;
	//printf("X20 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X21
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[20].RK[0]) + (X[1] ^ RoundKey[20].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[20].RK[2]) + (X[2] ^ RoundKey[20].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[20].RK[4]) + (X[3] ^ RoundKey[20].RK[5]), 3);
	X[3] = temp;
	//printf("X21 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X22
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[21].RK[0]) + (X[1] ^ RoundKey[21].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[21].RK[2]) + (X[2] ^ RoundKey[21].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[21].RK[4]) + (X[3] ^ RoundKey[21].RK[5]), 3);
	X[3] = temp;
	//printf("X22 : %08x %08x %08x, %08x\n", X[0], X[1], X[2], X[3]);
	//X23
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[22].RK[0]) + (X[1] ^ RoundKey[22].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[22].RK[2]) + (X[2] ^ RoundKey[22].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[22].RK[4]) + (X[3] ^ RoundKey[22].RK[5]), 3);
	X[3] = temp;
	//printf("X23 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);
	//X24
	temp = X[0];
	X[0] = RotationLeft((X[0] ^ RoundKey[23].RK[0]) + (X[1] ^ RoundKey[23].RK[1]), 9);
	X[1] = RotationRight((X[1] ^ RoundKey[23].RK[2]) + (X[2] ^ RoundKey[23].RK[3]), 5);
	X[2] = RotationRight((X[2] ^ RoundKey[23].RK[4]) + (X[3] ^ RoundKey[23].RK[5]), 3);
	X[3] = temp;
	//printf("X24 : %08x %08x %08x %08x\n", X[0], X[1], X[2], X[3]);

	// Ciphertext <- X24
	Ciphertext[0] = X[0];
	Ciphertext[1] = X[1];
	Ciphertext[2] = X[2];
	Ciphertext[3] = X[3];
}

void LEA_Encryption128(unsigned int* Plaintext, unsigned int* Ciphertext, RoundKey* RoundKey)
{
	Round(Plaintext, Ciphertext, RoundKey);  // ���� �Լ� 

}
