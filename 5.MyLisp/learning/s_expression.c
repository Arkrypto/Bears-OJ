//#include "mpc.h"
//#ifdef _WIN32
//
//// * 1100000000000 10000000000�����ܴ���һЩ����
//
// 
//static char* buffer[2084];
//
//char* readLine(char* prompt) {
//	fputs(prompt, stdout);
//	fgets(buffer, 2084, stdin);
//	
//	//ǿתһ�£���þ��� 
//	char* cpy = (char*)malloc(strlen(buffer)+1); 
//	strcpy(cpy, buffer);
//	
//	cpy[strlen(buffer)-1] = '\0';
//	return cpy;
//}
//
//void add_history(char* unused){}
//
//#else
//#include <readline/readline.h>
//#include <readline/history.h>
//#endif
//
///**
// * prompt:��ʹ 
// * lvalue:��ֵ
// * expression:���ʽ
// * evalution:��ֵ 
// * parser:���� 
// * S-expression:lisp���еı��ʽ 
// * mpc_ast_t:��mpc_parser_t(������)�Ľ��ʽ(tree.output)��һ���﷨�� 
// * errno\ERANGE:��c����stdlib.h���еĶ���Ĵ����룬����Ϊ����ֵ�ĺ� 
//*/ 
//
////���� 
//enum{ LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR };
//
//
//typedef struct lval{
//	int type;
//	long num;
//	//���ַ�������ʾ����ͷ��Ÿ�������Ч 
//	char* err;
//	char* sym;
//	//��¼��ǰ��ֵ���Ƴ��ı��ʽ����
//	int count;
//	//������ʽ������Ϊlval*������lval*��ָ�봢�棬��˫ָ��lval** 
//	struct lval** cell; 
//} lval;
//
//
//
////ʹ��ָ�빹������Ч�� 
//lval* lval_num(long x){
//	lval* v = malloc(sizeof(lval));
//	v->type = LVAL_NUM;
//	v->num = x;
//	return v;
//}
//
//
//
//lval* lval_err(char* m){
//	lval* v = malloc(sizeof(lval));
//	v->type = LVAL_ERR;
//	v->err = malloc(strlen(m)+1);
//	strcpy(v->err, m);
//	return v;
//}
//
//
//
//lval* lval_sym(char* s){
//	lval* v = malloc(sizeof(lval));
//	v->type = LVAL_SYM;
//	v->sym = malloc(strlen(s)+1);
//	strcpy(v->sym, s);
//	return v;
//}
//
//
//
//lval* lval_sexpr(void){
//	lval* v = malloc(sizeof(lval));
//	v->type = LVAL_SEXPR;
//	v->count = 0;
//	v->cell = NULL;
//	return v; 
//}
//
//
//
//void lval_del(lval* v){
//	
//	switch(v->type){
//		case LVAL_NUM: break;
//		//�ͷ��ַ�ָ�� 
//		case LVAL_ERR: free(v->err); break;
//		case LVAL_SYM: free(v->sym); break;
//		
//		case LVAL_SEXPR:{
//			int i;
//			//����̱��ʽ�����ͷţ��ݹ����lval_del
//			for(i = 0; i < v->count; i++){
//				lval_del(v->cell[i]);
//			}
//			//�ͷ�lval˫ָ�� 
//			free(v->cell);
//			break;
//		}
//	}
//	//�ͷ�����lvalָ�� 
//	free(v);
//}
//
//
//
////realloc���������¶�ָ�����ռ��С 
//lval* lval_add(lval* v, lval* x){
//	v->count++;
//	v->cell = realloc(v->cell, sizeof(lval*)*v->count);
//	v->cell[v->count-1] = x;
//	return v;
//}
//
//
////��ָ���ӽڵ㵯ջ��ͬʱ�ض���ָ��ռ� 
//lval* lval_pop(lval* v, int i){
//	lval* x = v->cell[i];
//	
//	memmove(&v->cell[i], &v->cell[i+1], sizeof(lval*)*(v->count-i-1));
//	
//	v->count--;
//	v->cell = realloc(v->cell, sizeof(lval*)*v->count);
//	return x;
//}
//
//lval* lval_take(lval* v, int i){
//	lval* x = lval_pop(v, i);
//	lval_del(v);
//	return x; 
//}
//
//
//
////��ӡ 
////��ӡ���һ�����Ƶ������ӡ���һ��s-express���ʽ����Ƕ�ף�ʵ�ֱ��ʽ�Ĵ�ӡ 
//void lval_expr_print(lval* v, char open, char close);
//
//void lval_print(lval* v){
//	switch(v->type){
//		case LVAL_NUM: printf("%li", v->num); break;
//		case LVAL_ERR: printf("Error: %s", v->err); break;
//		case LVAL_SYM: printf("%s", v->sym); break;
//		case LVAL_SEXPR: lval_expr_print(v, '(', ')'); break;
//	}
//}
//
//void lval_expr_print(lval* v, char open, char close){
//	putchar(open);
//	int i;
//	for(i = 0; i < v->count; i++){
//		lval_print(v->cell[i]);
//		if(i == v->count-1){
//			putchar(' ');
//		}
//	}
//	putchar(close);
//}
//
//void lval_println(lval* v){
//	lval_print(v);
//	putchar('\n');
//}
//
//
//
//lval* builtin_op(lval* a, char* op){
//	int i;
//	for(i = 0; i < a->count; i++){
//		if(a->cell[i]->type != LVAL_NUM){
//			lval_del(a);
//			return lval_err("Cannot operate on non-number!");
//		}
//	}
//	
//	//��ʼ��ջ�����м��� 
//	lval* x = lval_pop(a, 0);
//	if((strcmp(op, "-") == 0) && a->count == 0){
//		x->num = -x->num;
//	}
//	
//	//��Ϊ�Ѿ����﷨��������˼���˳���Ѿ����ǹ������ȼ����� 
//	while(a->count > 0){
//		lval* y = lval_pop(a, 0);
//		
//		if(strcmp(op, "+") == 0){
//			x->num += y->num;
//		}else if(strcmp(op, "-") == 0){
//			x->num -= y->num;
//		}else if(strcmp(op, "*") == 0){
//			x->num *= y->num;
//		}else if(strcmp(op, "/") == 0){
//			if(y->num == 0){
//				//�ͷſռ� 
//				lval_del(x);
//				lval_del(y);
//				x = lval_err("Division By Zero!");
//				break;
//			}
//			x->num /= y->num;
//		}
//		lval_del(y);
//	}
//	
//	lval_del(a);
//	return x;
//}
//
//
//
////����
//lval* lval_eval(lval* v); 
//lval* lval_eval_sexpr(lval* v){
//	//�����ӽڵ�
//	int i;
//	for(i = 0; i < v->count; i++){
//		v->cell[i] = lval_eval(v->cell[i]);
//	}
//	for(i = 0; i < v->count; i++){
//		if(v->cell[i]->type == LVAL_ERR){
//			return lval_take(v, i);
//		}
//	}
//	
//	if(v->count == 0)	return v;
//	if(v->count == 1)	return lval_take(v, 0);
//	
//	lval* f = lval_pop(v, 0);
//	if(f->type != LVAL_SYM){
//		lval_del(f);
//		lval_del(v);
//		return lval_err("S-expression Does not start with symbol!");
//	}
//	
//	lval* result = builtin_op(v, f->sym);
//	lval_del(f);
//	return result;
//}
//
//lval* lval_eval(lval* v){
//	if(v->type == LVAL_SEXPR){
//		return lval_eval_sexpr(v);
//	}
//	return v;
//}
//
//
//
////���﷨�������ֲ���ת��Ϊtoken���� 
//lval* lval_read_num(mpc_ast_t* t){
//	errno = 0;
//	//strtol:���ַ���ת��Ϊ�����ͣ��ڶ�������Ϊָ�򲻿�ת����char*��λ��(���ڴ˴�ֹͣת��)��10Ϊ���� 
//	long x = strtol(t->contents, NULL, 10);
//	return errno != ERANGE ?
//		lval_num(x): lval_err("invalid number"); 
//}
//
////�����ɵĳ����﷨��ת��Ϊs-expression���ʽ 
//lval* lval_read(mpc_ast_t* t){
//	//strstr:ƥ�����ַ��� 
//	if(strstr(t->tag, "number"))	return lval_read_num(t);
//	if(strstr(t->tag, "symbol"))	return lval_sym(t->contents);
//	
//	lval* x = NULL;
//	//strcmp:�Ƚ����ַ����������ַ���(��С)str1-str2����Ϊ0������ͬ 
//	if(strcmp(t->tag, ">") == 0 || strstr(t->tag, "sexpr"))	x = lval_sexpr();
//	
//	int i;
//	for(i = 0; i< t->children_num; i++){
//		if(strcmp(t->children[i]->contents, "(") == 0
//			|| strcmp(t->children[i]->contents, ")") == 0
//			|| strcmp(t->children[i]->contents, "{") == 0
//			|| strcmp(t->children[i]->contents, "}") == 0
//			|| strcmp(t->children[i]->tag, "regex") == 0)
//			{
//			continue;
//		}
//		x = lval_add(x, lval_read(t->children[i]));
//	}		
//	return x;
//}
//
//
// 
//int main(){
//	
//	//�����µ��ķ� 
//	mpc_parser_t* Number = mpc_new("number");	
//	mpc_parser_t* Symbol = mpc_new("symbol");	
//	mpc_parser_t* Sexpr = mpc_new("sexpr");	
//	mpc_parser_t* Expr = mpc_new("expr");	
//	mpc_parser_t* Lispy = mpc_new("lispy");	
//	mpca_lang(MPCA_LANG_DEFAULT,
//		"											\
//			number: /-?[0-9]+/;						\
//			symbol: '+' | '-' | '*' | '/';			\
//			sexpr: '(' <expr>* ')';					\
//			expr: <number> | <symbol> | <sexpr>;	\
//			lispy: /^/ <expr>* /$/;					\
//		",
//		Number, Symbol, Sexpr, Expr, Lispy
//	);
//	
//	puts("Lispy Version 0.5\nPress Ctrl+c to Exit\n");
//	while(1){
//		char* input = readLine("lispy>");
//		add_history(input);
//		
//		mpc_result_t res;
//		if (mpc_parse("<stdin>", input, Lispy, &res)) {
//      		lval* x = lval_eval(lval_read(res.output));
//      		mpc_ast_print(res.output);
//     		lval_println(x);
//      		lval_del(x);
//      		mpc_ast_delete(res.output);
//    	} else {    
//      		mpc_err_print(res.error);
//      		mpc_err_delete(res.error);
//   		}
//		
//		free(input);
//	}
//	
//	//�ͷ����Ŀռ� 
//	mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Lispy);
//	return 0; 
//}
//

