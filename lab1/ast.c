#include "def.h"

struct ASTNode * mknode(int num,int kind,int pos,...){
    struct ASTNode *T=(struct ASTNode *)calloc(sizeof(struct ASTNode),1);
    int i=0;
    T->kind=kind;
    T->pos=pos;
    va_list pArgs ;
    va_start(pArgs, pos);
    for(i=0;i<num;i++)
        T->ptr[i]= va_arg(pArgs, struct ASTNode *);
    while (i<4) T->ptr[i++]=NULL;
    va_end(pArgs);
    return T;
}

void dfs_arr(struct ASTNode *T,int indent); 

void dfs_arr_call(struct ASTNode *T,int indent) ;

void display(struct ASTNode *T,int indent)
{//对抽象语法树的先根遍历
  int i=1;
  struct ASTNode *T0;
  //printf("start");
  //fflush(stdout);
  if (T)
	{
	switch (T->kind) {
	case EXT_DEF_LIST:  display(T->ptr[0],indent);    //显示该外部定义（外部变量和函数）列表中的第一个
                        display(T->ptr[1],indent);    //显示该外部定义列表中的其它外部定义
                        break;
	case EXT_VAR_DEF:   printf("%*c外部变量定义：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);        //显示外部变量类型
                        printf("%*c变量名：\n",indent+3,' ');
                        display(T->ptr[1],indent+6);        //显示变量列表
                        break;
	case TYPE:          printf("%*c类型： %s\n",indent,' ',T->type_id);
                        break;
    case EXT_DEC_LIST:  display(T->ptr[0],indent);     //依次显示外部变量名，
                        display(T->ptr[1],indent);     //后续还有相同的，仅显示语法树此处理代码可以和类似代码合并
                        break;
	case FUNC_DEF:      printf("%*c函数定义：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);      //显示函数返回类型
                        display(T->ptr[1],indent+3);      //显示函数名和参数
                        display(T->ptr[2],indent+3);      //显示函数体
                        break;
	case FUNC_DEC:      printf("%*c函数名：%s\n",indent,' ',T->type_id);
                        if (T->ptr[0]) {
                                printf("%*c函数形参：\n",indent,' ');
                                display(T->ptr[0],indent+3);  //显示函数参数列表
                                }
                        else printf("%*c无参函数\n",indent+3,' ');
                        break;
	case PARAM_LIST:    display(T->ptr[0],indent);     //依次显示全部参数类型和名称，
                        display(T->ptr[1],indent);
                        break;
	case PARAM_DEC:     printf("%*c类型：",indent,' ');
                        if(T->ptr[0]->kind == STRUCT_DEF)printf("结构体变量 ");
                        printf("%s",T->ptr[0]->type_id);
                        printf(", 参数名：%s\n",T->ptr[1]->type_id);
                        break;
	case EXP_STMT:      printf("%*c表达式语句：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);
                        break;
	case RETURN:        printf("%*c返回语句：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);
                        break;
	case COMP_STM:      printf("%*c复合语句：(%d)\n",indent,' ',T->pos);
                        printf("%*c复合语句的变量定义部分：\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //显示定义部分
                        printf("%*c复合语句的语句部分：\n",indent+3,' ');
                        display(T->ptr[1],indent+6);      //显示语句部分
                        break;
	case STM_LIST:      display(T->ptr[0],indent);      //显示第一条语句
                        display(T->ptr[1],indent);        //显示剩下语句
                        break;
	case WHILE:         printf("%*cwhile循环语句：(%d)\n",indent,' ',T->pos);
                        printf("%*cwhile循环条件：\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //显示循环条件
                        printf("%*cwhile循环体：(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[1],indent+6);      //显示循环体
                        break;
	case IF_THEN:       printf("%*c条件语句(IF_THEN)：(%d)\n",indent,' ',T->pos);
                        printf("%*c条件：\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //显示条件
                        printf("%*cIF子句：(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[1],indent+6);      //显示if子句
                        break;
	case IF_THEN_ELSE:  printf("%*c条件语句(IF_THEN_ELSE)：(%d)\n",indent,' ',T->pos);
                        printf("%*c条件：\n",indent+3,' ');
                        display(T->ptr[0],indent+6);      //显示条件
                        printf("%*cIF子句：(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[1],indent+6);      //显示if子句
                        printf("%*cELSE子句：(%d)\n",indent+3,' ',T->pos);
                        display(T->ptr[2],indent+6);      //显示else子句
                        break;
    case DEF_LIST:      display(T->ptr[0],indent);    //显示该局部变量定义列表中的第一个
                        display(T->ptr[1],indent);    //显示其它局部变量定义
                        break;
    case VAR_DEF:       printf("%*c局部变量定义：(%d)\n",indent,' ',T->pos);
                        display(T->ptr[0],indent+3);   //显示变量类型
                        display(T->ptr[1],indent+3);   //显示该定义的全部变量名
                        break;
    case DEC_LIST:      printf("%*c变量名：\n",indent,' ');
                        T0=T;
                        while (T0) {
                            if (T0->ptr[0]->kind==ID)
                                printf("%*c %s\n",indent+6,' ',T0->ptr[0]->type_id);
                            else if(T0->ptr[0]->kind==ARRAY){
                                dfs_arr(T,indent+6);
                                printf("\n");
                            }
                            else if (T0->ptr[0]->kind==ASSIGNOP)
                                {
                                printf("%*c %s ASSIGNOP\n ",indent+6,' ',T0->ptr[0]->ptr[0]->type_id);
                                display(T0->ptr[0]->ptr[1],indent+strlen(T0->ptr[0]->ptr[0]->type_id)+7);        //显示初始化表达式
                                }
                            T0=T0->ptr[1];
                            }
                        break;
	case ID:	        printf("%*cID： %s\n",indent,' ',T->type_id);
                        break;
	case INT:	        printf("%*cINT：%d\n",indent,' ',T->type_int);
                        break;
	case FLOAT:	        printf("%*cFLAOT：%f\n",indent,' ',T->type_float);
                        break;
	case ASSIGNOP:
	case AND:
	case OR:
	case RELOP:
	case PLUS:
	case MINUS:
	case STAR:
	case DIV:
                    printf("%*c%s\n",indent,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    display(T->ptr[1],indent+3);
                    break;
	case NOT:
	case UMINUS:    printf("%*c%s\n",indent,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    break;
    case FUNC_CALL: printf("%*c函数调用：(%d)\n",indent,' ',T->pos);
                    printf("%*c函数名：%s\n",indent+3,' ',T->type_id);
                    display(T->ptr[0],indent+3);
                    break;
	case ARGS:      i=1;
                    while (T) {  //ARGS表示实际参数表达式序列结点，其第一棵子树为其一个实际参数表达式，第二棵子树为剩下的
                        struct ASTNode *T0=T->ptr[0];
                        printf("%*c第%d个实际参数表达式：\n",indent,' ',i++);
                        display(T0,indent+3);
                        T=T->ptr[1];
                        }
//                    printf("%*c第%d个实际参数表达式：\n",indent,' ',i);
  //                  display(T,indent+3);
                    printf("\n");
                    break;
    case STRUCT_DEF:
        printf("%*c结构体\n",indent,' ');
        printf("%*c结构体名:\n",indent,' ');
        display(T->ptr[0],indent+3);
        if((T->ptr[1])!=NULL){
            printf("%*c结构体成员定义:\n",indent,' ');
            display(T->ptr[1],indent+3);
        }
        else printf("%*c%s\n",indent+6,' ',T->type_id);
        break;
    case ARRAY:
        dfs_arr(T,indent);
        printf("\n");
        break;
    case FOR:
        printf("%*cfor循环语句：(%d)\n",indent,' ',T->pos);
        printf("%*cfor循环条件：\n",indent+3,' ');
        display(T->ptr[0],indent+6);      //显示循环条件
        printf("%*cfor循环体：(%d)\n",indent+3,' ',T->pos);
        display(T->ptr[1],indent+6);      //显示循环体
        break;
    case FOREXP:
        printf("%*cfor循环循环变量：\n",indent,' ');
        display(T->ptr[0], indent + 3); //变量
        printf("%*cfor循环循环终止条件：\n",indent,' ');
        display(T->ptr[1], indent + 3); //条件
        printf("%*cfor循环每次对变量的运算：\n",indent,' ');
        display(T->ptr[2], indent + 3); //步长
        break;
    case ARRAY_CALL:
        printf("%*c数组：\n", indent, ' ');
        display(T->ptr[0], indent+3);
        printf("%*c数组下标：\n", indent, ' ');
        display(T->ptr[1], indent+3);
        break;
    case CALC_LIST:
        display(T->ptr[0], indent);
        display(T->ptr[1], indent);
        break;
    case DPLUS:
        printf("%*c自增运算，顺序为：\n", indent, ' ');
        display(T->ptr[0], indent+3); 
        printf("%*c++\n", indent+3, ' ');
        display(T->ptr[1], indent+3); 
        break;
    case DMINUS:
        printf("%*c自减运算，顺序为：\n", indent, ' ');
        display(T->ptr[0], indent+3); 
        printf("%*c--\n", indent+3, ' ');
        display(T->ptr[1], indent+3); 
        break;
    case ADDASSIGN:
        printf("%*c+=\n", indent, ' ');
        display(T->ptr[0], indent+3); 
        display(T->ptr[1], indent+3);
        break;
    case MINUSASSIGN:
        printf("%*c-=\n", indent, ' ');
        display(T->ptr[0], indent+3); 
        display(T->ptr[1], indent+3);
        break;
    case STARASSIGN:
        printf("%*c*=\n", indent, ' ');
        display(T->ptr[0], indent+3); 
        display(T->ptr[1], indent+3);
        break;
    case DIVASSIGN:
        printf("%*c\\=\n", indent, ' ');
        display(T->ptr[0], indent+3); 
        display(T->ptr[1], indent+3);
        break;
    case BREAK:
        printf("%*cBreak返回语句：(%d)\n",indent,' ',T->pos);
        break;
    case CONTINUE:
        printf("%*cContinue返回语句：(%d)\n",indent,' ',T->pos);
        break;
    case STRUCT_CALL:
        printf("%*c结构体名：\n", indent, ' ');
        display(T->ptr[0], indent);
        printf("%*c引用成员：\n", indent+3, ' ');
        display(T->ptr[1], indent);
        break;
    case VAR_CALL:
        T=T->ptr[0];
        if(T->kind == ID)
            printf("%*c调用变量：%s\n", indent, ' ',T->type_id);
        else if(T->kind == ARRAY){
            dfs_arr_call(T,indent);
            printf("\n");
        }
        break;
    case CHAR:
        printf("%*c字符常量为:'%c'\n", indent, ' ', T->type_char);
        break;
    case STR_CONST:
        printf("%*c字符串常量为:\"%s\"\n", indent, ' ', T->type_string);
        break;
         }
      }
}

void dfs_arr_call(struct ASTNode *T,int indent){
    if(T->kind == ID){
        printf("%*c数组名为:%s\n",indent,' ',T->type_id);
        printf("%*c数组下标为: ",indent,' ');
        return ;
    }
    dfs_arr_call(T->ptr[0],indent);
    if(T->size)printf("%d ",T->size);
}

void dfs_arr(struct ASTNode *T,int indent){
    if(T->kind == ID){
        printf("%*c数组名为:%s\n",indent,' ',T->type_id);
        printf("%*c数组维数大小为: ",indent,' ');
        return ;
    }
    dfs_arr(T->ptr[0],indent);
    if(T->size)printf("%d ",T->size);
}