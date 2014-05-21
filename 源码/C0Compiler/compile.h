#define MYCOMPILER

#define MAXWORD		30				//token和keyword最大长度
#define MAXLENGTH	50				
#define MAXC		50				//符号表的最大容量
#define MAXOP		500				//最大的操作指令条数
#define MAXLEV		10				//最大的层数
#define MAXF		10				//最多的实常量数
#define MAXCASE		50				
#define MAXGO		100				//最大运行栈
#define MAXGOLEV	10				//运行栈最大的调用层
#define	MAXS		5				//printf语句中最多的转换字符数
#define MAXERROR	50				//最多的错误个数,暂设为50个
#define kk			12				//关键词个数
#define CommandNum	8				//命令条数
struct aString						//字符串存储结构
{
char sisstring[100];
char stringname[10];
};

char Word[MAXWORD];					//store token
int num;							//store 整数
char sisstring[MAXLENGTH];			//单个字符串
aString storestring[MAXLENGTH];		//所有字符串和名字
int sym;							//store 获得token的标号
 

char *Keyword[]={					//关键字
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


FILE* FIN, *FOUT;					//输入输出文件指针
char fp[20];						//输入文件名


struct Character{					//符号表
	char *name ;					//名称
	int type;						//变量常量类型
	int lev;						//层次,全局是0,其他的按函数顺序编号,不可能有超过1的
	int adr;						//偏移地址,第一个是0,第二个是4(段内取值第一个是8,第二个是12)
	int kind;						//类型(参数,常量之类)
	int num;						//如果是Int,存储其值
};


struct opr{							//四元式
	char op[20];								//指令代号
	char src1[20];						//第一个源操作数
	char src2[20];						//第二个源操作数					
	char dst[20];						//目标操作数
};



char* err_msg[] =					//定义出错提示信息
{
/*0*/ "",
/*1*/ "标识符或数字过长",
/*2*/ "非法单词",
/*3*/ "缺少符号",
/*4*/ "缺少类型标识符",
/*5*/ "字符串过长或缺少符号",
/*6*/ "此处缺少运算的因子",
/*7*/ "符号表出界",
/*8*/ "标识符重复定义",
/*9*/ "此处应有'='",
/*10*/ "变量使用出错",
/*11*/ "无返回值函数不能用在此处",
/*12*/ "缺少“}”",
/*13*/ "缺少','",
/*14*/ "有返回值函数必须返回一个值",
/*15*/ "无主函数",
/*16*/ "函数调用时参数个数不对",
/*17*/ "缺少'('",
/*18*/ "缺少')'",
/*19*/ "编译生成指令数过多",
/*20*/ "标识符未定义",
/*21*/ "转换符用法错误,为非变量型数据赋值",
/*22*/ "缺少“;”",
/*23*/ "缺少“{”",
/*24*/ "运行栈泄漏"
/*25*/ "函数调用超过了最大的层次数",
/*26*/ "函数返回值与函数类型不匹配",
/*27*/ "此处应为标识符",
/*28*/ "变量的类型和值的类型不匹配",
/*29*/ "无返回值函数不能返回一个值",
/*30*/ "此处应有数字"
};



int getsym();										//词法分析程序
int enter(int lev,int type,int kind);				//把变量填入符号表
int constdeclaration();								//分析常量说明部分
int program();										//分析程序
int charcheck();									//检查标识符是否重复定义
int constdefine( );						//分析常量定义
int vardefine( int type);							//分析变量说明部分  
int returnfunction( int type)	;					//有返回值的函数
int voidfunction( );								//无返回值的函数定义语句
int statementArray( );								//语句列
int statement( );									//语句
int ifstatement( );									//if条件语句
int whilestatement( );								//while循环语句
int scanfstatement( );								//scanf读语句
int printfstatement( );								//printf写语句
int returnstatement( );								//return语句
int assignstatement(char* left);					//赋值语句
int mainfunction( );								//主函数
int call(int a);									//函数调用语句
int expression();									//表达式
int gen(char* op,char* src1,char* src2,char* dst);	//op是指令序号,其他三个是符号表序号
int term();											//项
int factor();										//因子
int find();											//在符号表查找标识符是否存在
int Interpret();									//解释执行程序
//int backout();						//不用的变量要退出符号表
void error_msg(int i);								//错误处理
void gettempname();									//获得临时变量的名字,存放在word中
void getnewlabel(char* templabel);									//获得新的标号
void getstringname();								//获得字符串的名字
int getshellsym();									//类shell脚本程序的词法分析
void toasm();										//生成32位汇编
void gem(char *op);											//生成一条32位汇编

/************************数字意义*****************************

  (1)type,sym:

	标识符			1				内部字符串
	整数			2				整数值
	字符串			5				字符串
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
	＋				31				---
	－				32				---
	*				33				---
	／				34				---
	}				35				---
	）				36				---
	（				37				---
	；				38				---
	，				39				---
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

0	var（变量）、Tn(临时变量)t
1	voidpro(无返回值的函数)、
2	pro(有返回值的函数)、
3	para(参数)、
4	const（常量）、
5	main（主函数）


一个简单程序为例:
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

shell解释程序类型编码
0 compile或c
1 link或l
2 run或r
3 quit或q
4 help或h
5 write或w
6 asm 或a
10 filename
*************************************************  */