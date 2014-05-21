#define MYCOMPILER

#define MAXWORD		30				//token��keyword��󳤶�
#define MAXLENGTH	50				
#define MAXC		50				//���ű���������
#define MAXOP		500				//���Ĳ���ָ������
#define MAXLEV		10				//���Ĳ���
#define MAXF		10				//����ʵ������
#define MAXCASE		50				
#define MAXGO		100				//�������ջ
#define MAXGOLEV	10				//����ջ���ĵ��ò�
#define	MAXS		5				//printf���������ת���ַ���
#define MAXERROR	50				//���Ĵ������,����Ϊ50��
#define kk			12				//�ؼ��ʸ���
#define CommandNum	8				//��������
struct aString						//�ַ����洢�ṹ
{
char sisstring[100];
char stringname[10];
};

char Word[MAXWORD];					//store token
int num;							//store ����
char sisstring[MAXLENGTH];			//�����ַ���
aString storestring[MAXLENGTH];		//�����ַ���������
int sym;							//store ���token�ı��
 

char *Keyword[]={					//�ؼ���
	"const",
	"int",
	"char",
	"void",
	"main",
	"if",
	"else",
	"do",
	"while",
	"scanf",
	"printf",
	"return"
};
char* shell[]=
{
	"compile",
	"link",
	"run",
	"quit",
	"help",
	"write",
	"asm",
	"print",
	"invoke",
};


FILE* FIN, *FOUT;					//��������ļ�ָ��
char fp[20];						//�����ļ���


struct Character{					//���ű�
	char *name ;					//����
	int type;						//������������
	int lev;						//���,ȫ����0,�����İ�����˳����,�������г���1��
	int adr;						//ƫ�Ƶ�ַ,��һ����0,�ڶ�����4(����ȡֵ��һ����8,�ڶ�����12)
	int kind;						//����(����,����֮��)
	int num;						//�����Int,�洢��ֵ
};


struct opr{							//��Ԫʽ
	char op[20];								//ָ�����
	char src1[20];						//��һ��Դ������
	char src2[20];						//�ڶ���Դ������					
	char dst[20];						//Ŀ�������
};



char* err_msg[] =					//���������ʾ��Ϣ
{
/*0*/ "",
/*1*/ "��ʶ�������ֹ���",
/*2*/ "�Ƿ�����",
/*3*/ "ȱ�ٷ���",
/*4*/ "ȱ�����ͱ�ʶ��",
/*5*/ "�ַ���������ȱ�ٷ���",
/*6*/ "�˴�ȱ�����������",
/*7*/ "���ű����",
/*8*/ "��ʶ���ظ�����",
/*9*/ "�˴�Ӧ��'='",
/*10*/ "����ʹ�ó���",
/*11*/ "�޷���ֵ�����������ڴ˴�",
/*12*/ "ȱ�١�}��",
/*13*/ "ȱ��','",
/*14*/ "�з���ֵ�������뷵��һ��ֵ",
/*15*/ "��������",
/*16*/ "��������ʱ������������",
/*17*/ "ȱ��'('",
/*18*/ "ȱ��')'",
/*19*/ "��������ָ��������",
/*20*/ "��ʶ��δ����",
/*21*/ "ת�����÷�����,Ϊ�Ǳ��������ݸ�ֵ",
/*22*/ "ȱ�١�;��",
/*23*/ "ȱ�١�{��",
/*24*/ "����ջй©"
/*25*/ "�������ó��������Ĳ����",
/*26*/ "��������ֵ�뺯�����Ͳ�ƥ��",
/*27*/ "�˴�ӦΪ��ʶ��",
/*28*/ "���������ͺ�ֵ�����Ͳ�ƥ��",
/*29*/ "�޷���ֵ�������ܷ���һ��ֵ",
/*30*/ "�˴�Ӧ������"
};



int getsym();										//�ʷ���������
int enter(int lev,int type,int kind);				//�ѱ���������ű�
int constdeclaration();								//��������˵������
int program();										//��������
int charcheck();									//����ʶ���Ƿ��ظ�����
int constdefine( );						//������������
int vardefine( int type);							//��������˵������  
int returnfunction( int type)	;					//�з���ֵ�ĺ���
int voidfunction( );								//�޷���ֵ�ĺ����������
int statementArray( );								//�����
int statement( );									//���
int ifstatement( );									//if�������
int whilestatement( );								//whileѭ�����
int scanfstatement( );								//scanf�����
int printfstatement( );								//printfд���
int returnstatement( );								//return���
int assignstatement(char* left);					//��ֵ���
int mainfunction( );								//������
int call(int a);									//�����������
int expression();									//���ʽ
int gen(char* op,char* src1,char* src2,char* dst);	//op��ָ�����,���������Ƿ��ű����
int term();											//��
int factor();										//����
int find();											//�ڷ��ű���ұ�ʶ���Ƿ����
int Interpret();									//����ִ�г���
//int backout();						//���õı���Ҫ�˳����ű�
void error_msg(int i);								//������
void gettempname();									//�����ʱ����������,�����word��
void getnewlabel(char* templabel);									//����µı��
void getstringname();								//����ַ���������
int getshellsym();									//��shell�ű�����Ĵʷ�����
void toasm();										//����32λ���
void gem(char *op);											//����һ��32λ���

/************************��������*****************************

  (1)type,sym:

	��ʶ��			1				�ڲ��ַ���
	����			2				����ֵ
	�ַ���			5				�ַ���
    const			10				---
	int				11				---
	void			13				---
	main			14				---
	if				15				---
	else			16				---
	do	(switch)	17				---
	while			18				---
	scanf			19				---
	printf			20				---
	return			21	 			---
	��				31				---
	��				32				---
	*				33				---
	��				34				---
	}				35				---
	��				36				---
	��				37				---
	��				38				---
	��				39				---
	{				40				---
	"				41				---
 	"				42				---
  	'				43				---
	'				44				---
	>				45				---
	<				46				---
	==				47				---
	!=				48				---
	>=				49				---
	<=				50				---	
	=				51				---

 (2) kind:

0	var����������Tn(��ʱ����)t
1	voidpro(�޷���ֵ�ĺ���)��
2	pro(�з���ֵ�ĺ���)��
3	para(����)��
4	const����������
5	main����������


һ���򵥳���Ϊ��:
const int a=10;
int b=12;
int sum(int a,int b)
{
int c;
c=a+b;
return c;
}
int main()
{
int c;
c=sum(1,2);
printf("a+b=",c);
}

shell���ͳ������ͱ���
0 compile��c
1 link��l
2 run��r
3 quit��q
4 help��h
5 write��w
6 asm ��a
10 filename
*************************************************  */