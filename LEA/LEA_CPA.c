#include "LEA_CPA.h"

double cov(float* x, float* y, int size) {
	double Sxy = 0, Sx = 0, Sy = 0;
	int i;
	for (i = 0;i < size;i++) {
		Sxy += x[i] * y[i];
		Sx += x[i];
		Sy += y[i];
	}
	return (Sxy - Sx * Sy / (double)size) / (double)size;
}

double corr(float* x, float* y, int size) {
	double Sxy = 0, Sx = 0, Sy = 0, Sxx = 0, Syy = 0;
	int i;
	for (i = 0;i < size;i++) {
		Sxy += x[i] * y[i];
		Sx += x[i];
		Sy += y[i];
		Sxx += x[i] * x[i];
		Syy += y[i] * y[i];
	}
	return ((double)size * Sxy - Sx * Sy) / sqrt(((double)size * Sxx - Sx * Sx) * ((double)size * Syy - Sy * Sy));
}

void subalign(float* data1, float* data2, int windowsize, int stepsize, int threshold, int TraceLength) {
	
	int size, maxcovpos;
	float* x, * y;
	double covval, maxcov;

	for (int m = 0;m < (TraceLength-windowsize);m += stepsize) {
		maxcovpos = 0;
		maxcov = 0;
		for (int j = -threshold;j < threshold;j++) {
			if (j < 0) {
				x = data1 + m;
				y = data2 + m - j;
				size = windowsize + j;
			}
			else {
				x = data1 + m + j;
				y = data2 + m;
				size = windowsize - j;
			}
			covval = cov(x, y, size);
			if (covval > maxcov) {
				maxcovpos = j; 
				maxcov = covval;
			}
		}
		if (maxcovpos < 0) {
			for (int k = m;k < (TraceLength + maxcovpos);k++) {
				data2[k] = data2[k - maxcovpos];
			}
		}
		else {
			for (int k = (TraceLength - maxcovpos - 1);k >= m;k--) {
				data2[k + maxcovpos] = data2[k];
			}
		}
	}

}

void Alignment(){

    int windowsize = 500;
    int stepsize = 450;
    int threshold = 100;
    char buf[256];
    int err, TraceLength, TraceNum;
    FILE* rfp,*wfp;

	TraceLength =10000;
	TraceNum=3000;

    sprintf(buf, "%s", TraceFN);
	if ((wfp = fopen(buf,"wb"))==NULL) {
		perror("error0");
	}
	sprintf(buf, "%s", AlignedTraceFN);
	if ((wfp = fopen(buf, "wb"))==NULL) {
		perror("error");
	}

	float* data,*data1;
	
	data = (float*)calloc(TraceLength, sizeof(float));
	data1 = (float*)calloc(TraceLength, sizeof(float));
	
	/* First wave is the same as the one before alignment */
	fread(data1, sizeof(float), TraceLength, rfp);
	fwrite(data1, sizeof(float), TraceLength, wfp);

	for (int i = 1;i < TraceNum;i++) {
		fread(data1, sizeof(float), TraceLength, rfp);
		subalign(data, data1, windowsize, stepsize, threshold, TraceLength);
		fwrite(data1, sizeof(float), TraceLength, wfp);
	}
	
	//fread(data1, sizeof(float), TraceLength, rfp);
	//subalign(data, data1, windowsize, stepsize, threshold, TraceLength);
	//fwrite(data1, sizeof(float), TraceLength, wfp);
	//printf(".");
	
	fclose(rfp);
	fclose(wfp);

	free(data);
	free(data1);
}

uint8_t KeyRecovery(uint8_t inferredkey,uint8_t number_of_RK){
	
	switch(number_of_RK){
		
		case 0:
		case 1:
		case 2:
			for(int i=23;i=0;i--){
				inferredkey = RotationRight(inferredkey,1)-RotationLeft(delta[i%4],i+number_of_RK);
			}
			return inferredkey;
		break;

		case 4:
			for(int i=23;i=0;i--){
				inferredkey = RotationRight(inferredkey,1)-RotationLeft(delta[i%4],i+number_of_RK-1);
			}
			return inferredkey;
		break;

		default :
			printf("You put wrong number, try again");

	}
}

void PCtest(){
	
	unsigned int** plaintext=NULL,**ciphertext=NULL;
	FILE* rfp,*wfp;
	unsigned char buf[256];
	BYTE MK[16] = { 0x0f,0x1e,0x2d,0x3c,0x4b,0x5a,0x69,0x78,0x87,0x96,0xa5,0xb4,0xc3,0xd2,0xe1,0xf0 };
    RoundKey RK128[24];
	LeaKeySchedule128(MK,RK128);

	sprintf(buf,"%s%s",_FOLD_,PlaintextFN);
	if((rfp=fopen(buf,"rb"))==NULL){
		perror("plaintext open error");
	}

	uint8_t TraceNum = 3000;
	plaintext = (unsigned int**)calloc(TraceNum,sizeof(unsigned int*));
	for(int i=0;i<TraceNum;i++){
		plaintext[i] = (unsigned int*)calloc(4,sizeof(unsigned int));
	}

	fseek(rfp,128,SEEK_SET);
	for (int i = 0;i < TraceNum;i++) {
		fread(plaintext[i],sizeof(int),4,rfp);
	}


	sprintf(buf,"%s%s",_FOLD_,CiphertextFN);
	if((rfp=fopen(buf,"rb"))==NULL){
		perror("Ciphertext open error");
	}
	ciphertext = (unsigned int**)calloc(TraceNum,sizeof(unsigned int*));
	for(int i=0;i<TraceNum;i++){
		ciphertext[i] = (unsigned int*)calloc(4,sizeof(unsigned int));
	}
	fseek(rfp,128,SEEK_SET);
	for (int i = 0;i < TraceNum;i++) {
		fread(ciphertext[i],sizeof(int),4,rfp);
	}

	fclose(rfp);

	for(int i=0;i<TraceNum;i++){	
		LEA_Encryption128(plaintext[i],plaintext[i],RK128);
		for(int j=0;j<4;j++){
			if(plaintext[i][j]!=ciphertext[i][j]){
				printf("Encryption Failed!");
				return -1;
			}
		}
	}

	printf("Perfect HAHAHA\n");                                             

}

void CPA() {

	unsigned int** ciphertext = NULL; // 2000개의 16byte의 평문을 2000*16d의 배열에 저장
	float** data; //정렬된 파형을 한번에 메모리에 올려서 작업
	double* Sx, * Sxx, * Sxy, * corrT;
	double Sy, Syy;
	char* temp;
	unsigned char x, y;
	char buf[256];
	int err, TraceLength, TraceNum,SubTraceNum; 
	FILE* rfp, * wfp;

	TraceLength = 6000;
	SubTraceNum =10000;
	TraceNum = 50000;

	/* Load Data */
	data = (float**)calloc(TraceNum,sizeof(float*));
		for (int i = 0;i < TraceNum;i++) {
			data[i] = (float*)calloc(TraceLength, sizeof(float));
	}
	
	sprintf(buf, "%s%s", _FOLD_ , _1TraceFN);
	if ((rfp = fopen(buf, "rb"))==NULL) {
		perror("error-1Trace");
	}
	for (int i = 0;i < SubTraceNum;i++) {
		fread(data[i], sizeof(float), TraceLength, rfp);
	}


	/* Load Ciphertext */
	sprintf(buf, "%s%s", _FOLD_ ,CiphertextFN);
	if ((rfp = fopen(buf, "rb"))==NULL) {
		perror("ciphertext - error");
	}

	ciphertext = (unsigned int**)calloc(TraceNum, sizeof(unsigned int*));
	for (int i = 0;i < TraceNum;i++) {
		ciphertext[i] = (unsigned int*)calloc(16,sizeof(unsigned int));
	}

	fseek(rfp,128,SEEK_SET);
	for (int i = 0;i < TraceNum;i++) {
		fread(ciphertext[i],sizeof(int),4,rfp);
	}

	fclose(rfp);

	/* Correlation Power Ananlysis for Ciphertext */
	Sx = (double*)calloc(TraceLength, sizeof(double));
	Sxx = (double*)calloc(TraceLength, sizeof(double));
	Sxy = (double*)calloc(TraceLength, sizeof(double));
	corrT = (double*)calloc(TraceLength, sizeof(double));

	for (int i = 0;i < TraceNum;i++) {
		for (int j = startpoint;j < endpoint;j++) {
			Sx[j] += data[i][j];
			Sxx[j] += data[i][j] * data[i][j];
		}
	}

	uint32_t key,X[4]={0,};
	uint32_t iv;
	uint8_t hw_iv;
	double max;
	uint32_t maxkey;

	max = 0;
	maxkey = 0;
	
	/* Ciphertext Correlation Check */
	for(int i=0;i<4;i++){
		Sy = 0;
		Syy = 0;
		memset(Sxy, 0, sizeof(double) *TraceLength);
		for (int j = 0;j < TraceNum;j++) {
			iv = ciphertext[j][i];
			hw_iv = 0;
			for (int k = 0;k < 32;k++) hw_iv += ((iv >> k) & 1);
			Sy += hw_iv;
			Syy += hw_iv * hw_iv;
			for (int k = startpoint;k < endpoint;k++) {
				Sxy[k] += hw_iv * data[j][k];
			}
		}
		for (int k = startpoint;k < endpoint;k++) {
			corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));
			if (fabs(corrT[k]) > max) {
				maxkey = key;
				max = fabs(corrT[k]);
			}		
		}
		sprintf(buf, "%scorrtrace/%dth_block.corrtrace", _FOLD_,i);
		if ((wfp = fopen(buf, "wb"))==NULL) {
			perror("File Open Error! \n");
		}
		fwrite(corrT, sizeof(double), TraceLength, wfp);
		fclose(wfp);
		printf(".\n");
	}

/*
	for (key = 0;key < (1<<31);key++) {
		Sy = 0;
		Syy = 0;
		memset(Sxy, 0, sizeof(double) *TraceLength);
		for (int j = 0;j < TraceNum;j++) {
			ciphertext[i]
			iv = RotationRight(X[0],9)-(X[3]^key);
			hw_iv = 0;
			for (int k = 0;k < 32;k++) hw_iv += ((iv >> k) & 1);
			Sy += hw_iv;
			Syy += hw_iv * hw_iv;
			for (int k = startpoint;k < endpoint;k++) {
				Sxy[k] += hw_iv * data[j][k];
			}
		}
		for (int k = startpoint;k < endpoint;k++) {
			corrT[k] = ((double)TraceNum * Sxy[k] - Sx[k] * Sy) / sqrt(((double)TraceNum * Sxx[k] - Sx[k] * Sx[k]) * ((double)TraceNum * Syy - Sy * Sy));
			if (fabs(corrT[k]) > max) {
				maxkey = key;
				max = fabs(corrT[k]);
			}		
		}
		sprintf(buf, "%scorrtrace/first_block_%02x.corrtrace", _FOLD_,key);
		if ((wfp = fopen(buf, "wb"))) {
			perror("File Open Error! \n");
		}
		fwrite(corrT, sizeof(double), TraceLength, wfp);
		fclose(wfp);
		printf(".");
	}
	printf("First_block : maxkey(%02x), maxcorr(%lf)\n",maxkey, max);
	*/

	free(Sx);
	free(Sxx);
	free(Sxy);
	free(corrT);
	free(data);
	free(ciphertext);
}
