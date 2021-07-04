#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

static string one_to_one[10] = {u8"����",u8"����",u8"����",u8"�̧�",u8"�n�n",u8"�f�f",u8"��l",u8"�k��",u8"�d�l",u8"�V��" };
static string out_family[67] = { /*0.*/"�ۤv",/*1.*/"����", /*2.*/"����",/* 3.*/"����",/* 4.*/"�~����", /*5.*/"�~����",/*6.*/"����", /*7.*/"�B��"/*(���~��)*/, /*8.*/"�B��",/* 9.*/"����"/*(���~��)*/, /*10.*/"�T�T", /*11.*/"�h��"/* * */,/*12.*/"�h�V",/*13.*/"����",/* 14.*/"����" /***/,/* 15.*/"���� ",/*16.*/"����"/* * */,/*17.*/"���V",/*18.*/"��S",/* 19.*/"���" ,/*20.*/"��n ",/*21.*/"��f ",/*22.*/"��S",/* 23.*/"���",/* 24.*/"��n",/* 25.*/"��f",/*26.*/"����",/* 27.*/"�A�A",/* 28.*/"�̧�", /*29.*/"�̷@", /*30.*/"�n�n",/* 31.*/"�n��", /*32.*/"�f�f", /*33.*/"�f��", /*34.*/"���l", /*35.*/"���k",/* 36.*/"�~�c",/* 37.*/"�~�c�k",/*38.*/"��l",/* 39.*/"�@��",/*40.*/"�]�l",/* 41.*/"�]�k",/* 42.*/"�k��",/* 43.*/"�k�B",/* 44.*/"�~�]",/*45.*/"��",/* 46.*/"�Ҥ�",/* 47.*/"�ҥ�",/* 48.*/"�ҥS", /*49.*/"�ҥS�A",/* 50.*/"�ҧ�",/* 51.*/"�ҧ̷@",/* 52.*/"�ҩn",/* 53.*/"�ҩn��",/* 54.*/"�ҩf",/* 55.*/"�ҩf��",/*56.*/"�d",/* 57.*/"�d��",/* 58.*/"�d��",/* 59.*/"�d�S",/* 60.*/"�d�S�A",/* 61.*/"�d��",/* 62.*/"�d�̷@",/* 63.*/"�d�n",/* 64.*/"�d�n��",/* 65.*/"�d�f",/* 66.*/"�d�f��" };
static int list[67][10] = {
	/*0�ۤv*/{6,13,26,28,30,32,38,42,56,45},
	/*1����*/{-1,-1,-1,-1,-1,-1,-2/*���ˡG2/���ˡG4*/,-2/*���ˡG3/���ˡG5*/,1,1},
	/*2����*/{1,1,-1,-1,-1,-1,-2/*�~���G9/�~���G7*/,11,3,-1},
	/*3����*/{1,1,-1,-1,-1,-1,-2/*�~���G9/�~���G7*/,11,-1,2},
	/*4�~����*/{1,1,-1,-1,-1,-1,14,16,5,-1},
	/*5�~����*/{1,1,-1,-1,-1,-1,14,16,-1,4},
	/*6����*/{2,3,7,9,11,11,-2/*�~���G28/�~���G26*/,-2/*�~���G32/�~���G30*/,13,-1},
	/*7�B��*/{2,3,7,9,11,11,-2/*�~���G19/�~���G18*/,-2/*�~���G21/�~���G20*/,8,-1},
	/*8�B��*/{-1,-1,-1,-1,-1,-1,-2/*�~���G19/�~���G18*/,-2/*�~���G21/�~���G20*/,-1,7},
	/*9����*/{2,3,7,9,11,11,-2/*�~���G19/�~���G18*/,-2/*�~���G21/�~���G20*/,10,-1},
	/*10�T�T*/{-1,-1,-1,-1,-1,-1,-2/*�~���G19/�~���G18*/,-2/*�~���G21/�~���G20*/,-1,9},
	/*11�h��*/{2,3,7,9,11,11,-2/*�~���G23/�~���G22*/,-2/*�~���G25/�~���G24*/,-1,12},
	/*12�h�V*/{-1,-1,-1,-1,-1,-1,-2/*�~���G23/�~���G22*/,-2/*�~���G25/�~���G24*/,11,-1},
	/*13����*/{4,5,14,14,16,16,-2/*�~���G28/�~���G26*/,-2/*�~���G32/�~���G30*/,-1,6},
	/*14����*/{4,5,14,14,16,16,-2/*�~���G23/�~���G22*/,-2/*�~���G25/�~���G24*/,15,-1},
	/*15����*/{-1,-1,-1,-1,-1,-1,-2/*�~���G23/�~���G22*/,-2/*�~���G25/�~���G24*/,-1,14},
	/*16����*/{4,5,14,14,16,16,-2/*�~���G23/�~���G22*/,-2/*�~���G25/�~���G24*/,-1,17},
	/*17���V*/{-1,-1,-1,-1,-1,-1,-2/*�~���G23/�~���G22*/,-2/*�~���G25/�~���G24*/,16,-1},
	/*18��S*/{-2/* 7/9 */,-2/* 8/10 */,18,19,20,21,-1,-1,-1,-1},
	/*19���*/{-2/* 7/9 */,-2/* 8/10 */,18,19,20,21,-1,-1,-1,-1},
	/*20��n*/{-2/* 7/9 */,-2/* 8/10 */,18,19,20,21,-1,-1,-1,-1},
	/*21��f*/{-2/* 7/9 */,-2/* 8/10 */,18,19,20,21,-1,-1,-1,-1},
	/*22��S*/{-2/* 12/14/17 */,-2/* 11/15/16 */,22,23,24,25,-1,-1,-1,-1},
	/*23���*/{-2/* 12/14/17 */,-2/* 11/15/16 */,22,23,24,25,-1,-1,-1,-1},
	/*24��n*/{-2/* 12/14/17 */,-2/* 11/15/16 */,22,23,24,25,-1,-1,-1,-1},
	/*25��f*/{-2/* 12/14/17 */,-2/* 11/15/16 */,22,23,24,25,-1,-1,-1,-1},
	/*26����*/{6,13,26,28,30,32,34,35,27,-1},
	/*27�A�A*/{-1,-1,-1,-1,-1,-1,34,35,-1,26},
	/*28�̧�*/{6,13,26,28,30,32,34,35,29,-1},
	/*29�̷@*/{-1,-1,-1,-1,-1,-1,34,35,-1,28},
	/*30�n�n*/{6,13,26,28,30,32,36,37,-1,31},
	/*31�n��*/{-1,-1,-1,-1,-1,-1,36,37,30,-1},
	/*32�f�f*/{6,13,26,28,30,32,36,37,-1,33},
	/*33�f��*/{-1,-1,-1,-1,-1,-1,36,37,32,-1},
	/*34���l*/{-2/* 26/28/48/50 */,-2/* 27/29/49/51 */,34,34,35,35,-1,-1,-1,-1},
	/*35���k*/{-2/* 26/28/48/50 */,-2/* 27/29/49/51 */,34,34,35,35,-1,-1,-1,-1},
	/*36�~�c*/{-2/* 31/33/53/55/59/61/64/66 */,-2/* 30/32/52/54/60/62/63/65 */,36,36,37,37,-1,-1,-1,-1},
	/*37�~�c�k*/{-2/* 31/33/53/55/59/61/64/66 */,-2/* 30/32/52/54/60/62/63/65 */,36,36,37,37,-1,-1,-1,-1},
	/*38��l*/{-2/* 0/45 */,-2/* 0/56 */,38,38,42,42,40,41,39,-1},
	/*39�@��*/{-1,-1,-1,-1,-1,-1,40,41,-1,38},
	/*40�]�l*/{38,39,40,40,41,41,-1,-1,-1,-1},
	/*41�]�k*/{38,39,40,40,41,41,-1,-1,-1,-1},
	/*42�k��*/{-2/* 0/45 */,-2/* 0/56 */,38,38,42,42,44,44,-1,43},
	/*43�k�B*/{-1,-1,-1,-1,-1,-1,44,44,42,-1},
	/*44�~�]*/{43,42,44,44,44,44,-1,-1,-1,-1},
	/*45�V��*/{46,47,48,50,52,54,38,42,0,-1},
	/*46�Ҥ�*/{-1,-1,-1,-1,-1,-1,-2/*�~���G50/�~���G48*/,-2/*�~���G54/�~���G52*/,47,-1},
	/*47�ҥ�*/{-1,-1,-1,-1,-1,-1,-2/*�~���G50/�~���G48*/,-2/*�~���G54/�~���G52*/,-1,46},
	/*48�ҥS*/{46,47,48,50,52,54,34,35,49,-1},
	/*49�ҥS�A*/{-1,-1,-1,-1,-1,-1,34,35,-1,48},
	/*50�ҧ�*/{46,47,48,50,52,54,34,35,51,-1},
	/*51�ҧ̷@*/{-1,-1,-1,-1,-1,-1,34,35,-1,50},
	/*52�ҩn*/{46,47,48,50,52,54,36,37,-1,53},
	/*53�ҩn��*/{-1,-1,-1,-1,-1,-1,36,37,52,-1},
	/*54�ҩf*/{46,47,48,50,52,54,36,37,-1,55},
	/*55�ҩf��*/{-1,-1,-1,-1,-1,-1,36,37,54,-1},
	/*56�d�l*/{57,58,59,61,63,65,38,42,-1,0},
	/*57�d��*/{-1,-1,-1,-1,-1,-1,-2/*�~���G61/�~���G59*/,-2/*�~���G65/�~���G63*/,58,-1},
	/*58�d��*/{-1,-1,-1,-1,-1,-1,-2/*�~���G61/�~���G59*/,-2/*�~���G65/�~���G63*/,-1,57},
	/*59�d�S*/{57,58,59,61,63,65,36,37,60,-1},
	/*60�d�S�A*/{-1,-1,-1,-1,-1,-1,36,37,-1,59},
	/*61�d��*/{57,58,59,61,63,65,36,37,62,-1},
	/*62�d�̷@*/{-1,-1,-1,-1,-1,-1,36,37,-1,61},
	/*63�d�n*/{57,58,59,61,63,65,36,37,-1,64},
	/*64�d�n��*/{-1,-1,-1,-1,-1,-1,36,37,63,-1},
	/*65�d�f*/{57,58,59,61,63,65,36,37,-1,66},
	/*66�d�f��*/{-1,-1,-1,-1,-1,-1,36,37,65,-1},
};

int main(int argc, char* argv[]) {
	int i, j, k;
	string input;
	ifstream fin;
	//system("chcp 65001 && cls");//G++�S���䴩
	fin.open(argv[1]/*"text0.txt"*/);
	if (!fin) {
		cout << "file couldn't open." << endl;
		exit(1);
	}
	while (getline(fin, input)) {
		//cout << input << endl;
		string s;
		int pos = 0;
		int f=0, l=0;
		s = input;
		vector<int> pre_previous;//�e�@�ӤH������
		int previous = 0;//�e�@�ӤH���N�X
		int person = 0;//�{�b��
		int sex = 0;//�k��1 �k��2
		if (s.find(u8"��(�k)") != -1 || s.find(u8"�ڪ��V��") != -1|| s.substr(0, 6) == u8"�V��") sex = 1;
		else if (s.find(u8"��(�k)") != -1 || s.find(u8"�ڪ��d�l") != -1|| s.substr(0, 6) == u8"�d�l") sex = 2;
		//sex �k��1 �k��2
		 do{
			pos = input.find(u8"��", pos);			
			if (pos - f < 0)l = s.size() - f;
			else l = pos - f;
			s = s.substr(f, /*pos - f*/l);			
			if (s.find(u8"��") == -1) {
				for (i = 0; i < 10; i++) {
					if (s.find(one_to_one[i]) != -1) {
						break;
					}
				}//i����10�Ӫ�������m
				person = list[previous][i];
				if (person == -2) {
					if (previous == 2 || previous == 3) {
						if (s.find(u8"�~��") != -1) person = 9;
						else person = 7;
					}//������
					else if (previous == 6 || previous == 13) {
						if (i == 6) {
							if (s.find(u8"�~��") != -1) person = 28;
							else person = 26;
						}//��l
						else {
							if (s.find(u8"�~��") != -1) person = 32;
							else person = 30;
						}//�k��
					}//����
					else if (previous == 7 || previous == 8 || previous == 9 || previous == 10) {
						if (i == 6) {
							if (s.find(u8"�~��") != -1) person = 19;
							else person = 18;
						}//��l
						else {
							if (s.find(u8"�~��") != -1) person = 21;
							else person = 20;
						}//�k��
					}//�B���B�������T�T
					else if (previous == 11 || previous == 12 || previous == 14 || previous == 15 || previous == 16 || previous == 17) {
						if (i == 6) {
							if (s.find(u8"�~��") != -1) person = 23;
							else person = 22;
						}//��l
						else {
							if (s.find(u8"�~��") != -1) person = 25;
							else person = 24;
						}//�k��
					}//�h���h�V���������������V
					else if (previous == 18 || previous == 19 || previous == 20 || previous == 21) {
						while (pre_previous[pre_previous.size() - 1] == 18 || pre_previous[pre_previous.size() - 1] == 19 || pre_previous[pre_previous.size() - 1] == 20 || pre_previous[pre_previous.size() - 1] == 21)pre_previous.pop_back();
						if (i == 0) {
							if (pre_previous[pre_previous.size() - 1] == 7 || pre_previous[pre_previous.size() - 1] == 8) person = 7;
							else person = 9;
						}//����
						else {
							if (pre_previous[pre_previous.size() - 1] == 7 || pre_previous[pre_previous.size() - 1] == 8) person = 8;
							else person = 10;
						}//����
					}//��S�̩n�f
					else if (previous == 22 || previous == 23 || previous == 24 || previous == 25) {
						while (pre_previous[pre_previous.size() - 1] == 22 || pre_previous[pre_previous.size() - 1] == 23 || pre_previous[pre_previous.size() - 1] == 24 || pre_previous[pre_previous.size() - 1] == 25)pre_previous.pop_back();						
						if (i == 0) {
							if (pre_previous[pre_previous.size() - 1] == 11 || pre_previous[pre_previous.size() - 1] == 12) person = 12;
							else if (pre_previous[pre_previous.size() - 1] == 14 || pre_previous[pre_previous.size() - 1] == 15)person = 14;
							else person = 17;
						}//����
						else {
							if (pre_previous[pre_previous.size() - 1] == 11 || pre_previous[pre_previous.size() - 1] == 12) person = 11;
							else if (pre_previous[pre_previous.size() - 1] == 14 || pre_previous[pre_previous.size() - 1] == 15)person = 15;
							else person = 16;
						}//����
					}//��S�̩n�f
					else if (previous == 34 || previous == 35) {
						while (pre_previous[pre_previous.size() - 1] == 34|| pre_previous[pre_previous.size() - 1] == 35)pre_previous.pop_back();
						if (i == 0) {
							if (pre_previous[pre_previous.size() - 1] == 26 || pre_previous[pre_previous.size() - 1] == 27) person = 26;
							else if (pre_previous[pre_previous.size() - 1] == 28 || pre_previous[pre_previous.size() - 1] == 29)person = 28;
							else if (pre_previous[pre_previous.size() - 1] == 48 || pre_previous[pre_previous.size() - 1] == 49)person = 48;
							else person = 50;
						}//����
						else {
							if (pre_previous[pre_previous.size() - 1] == 26 || pre_previous[pre_previous.size() - 1] == 27) person = 27;
							else if (pre_previous[pre_previous.size() - 1] == 28 || pre_previous[pre_previous.size() - 1] == 29)person = 29;
							else if (pre_previous[pre_previous.size() - 1] == 48 || pre_previous[pre_previous.size() - 1] == 49)person = 49;
							else person = 51;
						}//����
					}//���l�k
					else if (previous == 36 || previous == 37) {
						while (pre_previous[pre_previous.size() - 1] == 36 || pre_previous[pre_previous.size() - 1] == 37)pre_previous.pop_back();
						if (i == 0) {
							if (pre_previous[pre_previous.size() - 1] == 31 || pre_previous[pre_previous.size() - 1] == 30) person = 31;
							else if (pre_previous[pre_previous.size() - 1] == 33 || pre_previous[pre_previous.size() - 1] == 32)person = 33;
							else if (pre_previous[pre_previous.size() - 1] == 53 || pre_previous[pre_previous.size() - 1] == 52)person = 53;
							else if (pre_previous[pre_previous.size() - 1] == 55 || pre_previous[pre_previous.size() - 1] == 54)person = 55;
							else if (pre_previous[pre_previous.size() - 1] == 59 || pre_previous[pre_previous.size() - 1] == 60)person = 59;
							else if (pre_previous[pre_previous.size() - 1] == 61 || pre_previous[pre_previous.size() - 1] == 62)person = 61;
							else if (pre_previous[pre_previous.size() - 1] == 64 || pre_previous[pre_previous.size() - 1] == 63)person = 64;
							else person = 66;
						}//����
						else {
							if (pre_previous[pre_previous.size() - 1] == 31 || pre_previous[pre_previous.size() - 1] == 30) person = 30;
							else if (pre_previous[pre_previous.size() - 1] == 33 || pre_previous[pre_previous.size() - 1] == 32)person = 32;
							else if (pre_previous[pre_previous.size() - 1] == 53 || pre_previous[pre_previous.size() - 1] == 52)person = 52;
							else if (pre_previous[pre_previous.size() - 1] == 55 || pre_previous[pre_previous.size() - 1] == 54)person = 54;
							else if (pre_previous[pre_previous.size() - 1] == 59 || pre_previous[pre_previous.size() - 1] == 60)person = 60;
							else if (pre_previous[pre_previous.size() - 1] == 61 || pre_previous[pre_previous.size() - 1] == 62)person = 62;
							else if (pre_previous[pre_previous.size() - 1] == 64 || pre_previous[pre_previous.size() - 1] == 63)person = 63;
							else person = 65;
						}//����
					}//�~�c �k
					else if (previous == 38 || previous == 42) {
						if (i == 0) {
							if (sex==2) person = 0;						
							else person = 45;
						}//����
						else {
							if (sex == 1) person = 0;
							else person = 56;
						}//����
					}//��l�k��
					else if (previous == 46 || previous == 47) {
						if (i == 6) {
							if (s.find(u8"�~��") != -1) person = 50;
							else person = 48;
						}//��l
						else {
							if (s.find(u8"�~��") != -1) person = 54;
							else person = 52;
						}//�k��
					}//�Ҥ��ҥ�
					else if (previous == 57 || previous == 58) {
						if (i == 6) {
							if (s.find(u8"�~��") != -1) person = 61;
							else person = 59;
						}//��l
						else {
							if (s.find(u8"�~��") != -1) person = 65;
							else person = 63;
						}//�k��
					}//�d���d��
				}
				pre_previous.push_back(previous);				
				previous = person;
			}			
			/*move to the next word*/
			f = pos + 3;
			if (pos != -1)pos++;
			s = input;
		 } while (pos != -1);
		 cout << out_family[person] << endl;
		
	}
	
	return 0;
}