#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*
For the language grammar, please refer to Grammar section on the github page:
  https://github.com/lightbulb12294/CSI2P-II-Mini1#grammar
*/

#define MAX_LENGTH 200
typedef enum {
	ASSIGN, ADD, SUB, MUL, DIV, REM, PREINC, PREDEC, POSTINC, POSTDEC, IDENTIFIER, CONSTANT, LPAR, RPAR, PLUS, MINUS, END
} Kind;
typedef enum {
	STMT, EXPR, ASSIGN_EXPR, ADD_EXPR, MUL_EXPR, UNARY_EXPR, POSTFIX_EXPR, PRI_EXPR
} GrammarState;
typedef struct TokenUnit {
	Kind kind;
	int val; // record the integer value or variable name
	struct TokenUnit *next;
} Token;
typedef struct ASTUnit {
	Kind kind;
	int val; // record the integer value or variable name
	struct ASTUnit *lhs, *mid, *rhs;
} AST;

/// utility interfaces

// err marco should be used when a expression error occurs.
// 輸入的expression不符合grammar / 無法通過semantic check 時呼叫
#define err(x) {\
	puts("Compile Error!");\
	if(DEBUG) {\
		fprintf(stderr, "Error at line: %d\n", __LINE__);\
		fprintf(stderr, "Error message: %s\n", x);\
	}\
	exit(0);\
}
// You may set DEBUG=1 to debug. Remember setting back to 0 before submit.
#define DEBUG 1
// Split the input char array into token linked list.
Token *lexer(const char *in);
// Create a new token.
Token *new_token(Kind kind, int val);
// Translate a token linked list into array, return its length.
size_t token_list_to_arr(Token **head);
// Parse the token array. Return the constructed AST.
AST *parser(Token *arr, size_t len);
// Parse the token array. Return the constructed AST.
AST *parse(Token *arr, int l, int r, GrammarState S);
// Create a new AST node.
AST *new_AST(Kind kind, int val);
// Find the location of next token that fits the condition(cond). Return -1 if not found. Search direction from start to end.
int findNextSection(Token *arr, int start, int end, int (*cond)(Kind));
// Return 1 if kind is ASSIGN.
int condASSIGN(Kind kind);
// Return 1 if kind is ADD or SUB.
int condADD(Kind kind);
// Return 1 if kind is MUL, DIV, or REM.
int condMUL(Kind kind);
// Return 1 if kind is RPAR.
int condRPAR(Kind kind);
// Check if the AST is semantically right. This function will call err() automatically if check failed.
void semantic_check(AST *now);
// Generate ASM code.
void codegen(AST *root);
// Free the whole AST.
void freeAST(AST *now);

/// debug interfaces

// Print token array.
void token_print(Token *in, size_t len);
// Print AST tree.
void AST_print(AST *head);

AST *simplify_AST(AST *ast_root);

char input[MAX_LENGTH];

int main() {
	while (fgets(input, MAX_LENGTH, stdin) != NULL) { // 逐行吃輸入(進input) &處理
		Token *content = lexer(input); // 將input轉為Token linked list
		size_t len = token_list_to_arr(&content); // 方便起見，linked list轉為array
		// token_print(content, len);
		if (len == 0) continue; // 空行不處理
		AST *ast_root = parser(content, len); // 用Token array建構AST
		// AST_print(ast_root);
		semantic_check(ast_root); // 執行semantic check

		simplify_AST(ast_root); // 優化AST

		codegen(ast_root); // 產生ASM code
		// Optimization 在這裡做(也可以在parser裡面做 or codegen裡面做)
		free(content); // 釋放記憶體: Token array
		freeAST(ast_root); // 釋放記憶體: AST
	}
	return 0;
}

Token *lexer(const char *in) {
	Token *head = NULL;
	Token **now = &head;
	for (int i = 0; in[i]; i++) {
		if (isspace(in[i])) // ignore space characters
			continue;
		else if (isdigit(in[i])) {
			(*now) = new_token(CONSTANT, atoi(in + i));
			while (in[i+1] && isdigit(in[i+1])) i++;
		}
		else if ('x' <= in[i] && in[i] <= 'z') // variable
			(*now) = new_token(IDENTIFIER, in[i]);
		else switch (in[i]) {
			case '=':
				(*now) = new_token(ASSIGN, 0);
				break;
			case '+':
				if (in[i+1] && in[i+1] == '+') {
					i++;
					// In lexer scope, all "++" will be labeled as PREINC.
					(*now) = new_token(PREINC, 0);
				}
				// In lexer scope, all single "+" will be labeled as PLUS.
				else (*now) = new_token(PLUS, 0);
				break;
			case '-':
				if (in[i+1] && in[i+1] == '-') {
					i++;
					// In lexer scope, all "--" will be labeled as PREDEC.
					(*now) = new_token(PREDEC, 0);
				}
				// In lexer scope, all single "-" will be labeled as MINUS.
				else (*now) = new_token(MINUS, 0);
				break;
			case '*':
				(*now) = new_token(MUL, 0);
				break;
			case '/':
				(*now) = new_token(DIV, 0);
				break;
			case '%':
				(*now) = new_token(REM, 0);
				break;
			case '(':
				(*now) = new_token(LPAR, 0);
				break;
			case ')':
				(*now) = new_token(RPAR, 0);
				break;
			case ';':
				(*now) = new_token(END, 0);
				break;
			default:
				err("Unexpected character.");
		}
		now = &((*now)->next);
	}
	return head;
}

Token *new_token(Kind kind, int val) {
	Token *res = (Token*)malloc(sizeof(Token));
	res->kind = kind;
	res->val = val;
	res->next = NULL;
	return res;
}

size_t token_list_to_arr(Token **head) {
	size_t res;
	Token *now = (*head), *del;
	for (res = 0; now != NULL; res++) now = now->next;
	now = (*head);
	if (res != 0) (*head) = (Token*)malloc(sizeof(Token) * res);
	for (int i = 0; i < res; i++) {
		(*head)[i] = (*now);
		del = now;
		now = now->next;
		free(del);
	}
	return res;
}

AST *parser(Token *arr, size_t len) { // 傳入先前建好的Token array跟array的長度
	for (int i = 1; i < len; i++) {
		// correctly identify "ADD" and "SUB"
		// lexer無法辨別的PLUS/ADD跟MINUS/SUB，在parser中要做辨識
		if (arr[i].kind == PLUS || arr[i].kind == MINUS) {
			switch (arr[i - 1].kind) {
				case PREINC:
				case PREDEC:
				case IDENTIFIER:
				case CONSTANT:
				case RPAR:
					arr[i].kind = arr[i].kind - PLUS + ADD; // 把PLUS轉成ADD，把MINUS轉成SUB
				default: break;
			}
		}
	}
	return parse(arr, 0, len - 1, STMT);
}

AST *parse(Token *arr, int l, int r, GrammarState S) {
	AST *now = NULL;
	if (l > r)
		err("Unexpected parsing range.");
	int nxt;
	switch (S) {
		case STMT:
			if (l == r && arr[l].kind == END)
				return NULL;
			else if (arr[r].kind == END)
				return parse(arr, l, r - 1, EXPR);
			else err("Expected \';\' at the end of line.");
		case EXPR:
			return parse(arr, l, r, ASSIGN_EXPR);
		case ASSIGN_EXPR:
			// 1. 先嘗試走 ASSIGN_EXPR -> UNARY_EXPR ASSIGN ASSIGN_EXPR
			// nxt 就是 "=" 的位置
			if ((nxt = findNextSection(arr, l, r, condASSIGN)) != -1) {
				// UNARY_EXPR ASSIGN ASSIGN_EXPR
				now = new_AST(arr[nxt].kind, 0);
				now->lhs = parse(arr, l, nxt - 1, UNARY_EXPR);
				now->rhs = parse(arr, nxt + 1, r, ASSIGN_EXPR);
				return now;
			}
			return parse(arr, l, r, ADD_EXPR); // 2. 當作ADD_EXPR往下走
		case ADD_EXPR:
			if((nxt = findNextSection(arr, r, l, condADD)) != -1) {
				now = new_AST(arr[nxt].kind, 0);
				now->lhs = parse(arr, l, nxt - 1, ADD_EXPR);
				now->rhs = parse(arr, nxt + 1, r, MUL_EXPR);
				return now;
			}
			return parse(arr, l, r, MUL_EXPR);
		case MUL_EXPR:
			// TODO: Implement MUL_EXPR.
			// hint: Take ADD_EXPR as reference.
			if((nxt = findNextSection(arr, r, l, condMUL)) != -1) {
				now = new_AST(arr[nxt].kind, 0);
				now->lhs = parse(arr, l, nxt - 1, MUL_EXPR);
				now->rhs = parse(arr, nxt + 1, r, UNARY_EXPR);
				return now;
			}
			return parse(arr, l, r, UNARY_EXPR);
		case UNARY_EXPR:
			// TODO: Implement UNARY_EXPR.
			// hint: Take POSTFIX_EXPR as reference.

			// 判斷是否為 "PREINC/PREDEC/PLUS/MINUS + UNARY_EXPR"，
			// 若是，則建立一個新的AST，並將其mid指向parse(arr, l + 1, r, UNARY_EXPR)
			if (arr[l].kind == PREINC || arr[l].kind == PREDEC || arr[l].kind == PLUS || arr[l].kind == MINUS) {
				now = new_AST(arr[l].kind, 0);
				now->mid = parse(arr, l + 1, r, UNARY_EXPR);
				return now;
			}
			return parse(arr, l, r, PRI_EXPR);
		case POSTFIX_EXPR:
			if (arr[r].kind == PREINC || arr[r].kind == PREDEC) {
				// translate "PREINC", "PREDEC" into "POSTINC", "POSTDEC"
				// 下面也涵蓋了 PREDEC 的情況
				now = new_AST(arr[r].kind - PREINC + POSTINC, 0);
				now->mid = parse(arr, l, r - 1, POSTFIX_EXPR);
				return now;
			}
			return parse(arr, l, r, PRI_EXPR);
		case PRI_EXPR:
			if (findNextSection(arr, l, r, condRPAR) == r) { // 如果最後一個token是右括號
				now = new_AST(LPAR, 0);
				now->mid = parse(arr, l + 1, r - 1, EXPR);
				return now;
			}
			if (l == r) {
				if (arr[l].kind == IDENTIFIER || arr[l].kind == CONSTANT)
					return new_AST(arr[l].kind, arr[l].val);
				err("Unexpected token during parsing.");
			}
			err("No token left for parsing.");
		default:
			err("Unexpected grammar state.");
	}
}

AST *new_AST(Kind kind, int val) {
	AST *res = (AST*)malloc(sizeof(AST));
	res->kind = kind;
	res->val = val;
	res->lhs = res->mid = res->rhs = NULL;
	return res;
}

// 找下一個token的位置，且符合cond()的條件。若找不到，回傳-1。搜尋方向由start到end。
int findNextSection(Token *arr, int start, int end, int (*cond)(Kind)) {
	int par = 0;
	int d = (start < end) ? 1 : -1;
	for (int i = start; (start < end) ? (i <= end) : (i >= end); i += d) {
		if (arr[i].kind == LPAR) par++;
		if (arr[i].kind == RPAR) par--;
		if (par == 0 && cond(arr[i].kind) == 1) return i;
	}
	return -1;
}

int condASSIGN(Kind kind) {
	return kind == ASSIGN;
}

int condADD(Kind kind) {
	return kind == ADD || kind == SUB;
}

int condMUL(Kind kind) {
	return kind == MUL || kind == DIV || kind == REM;
}

// 如果是右括號，回傳1
int condRPAR(Kind kind) {
	return kind == RPAR;
}

void semantic_check(AST *now) {
	if (now == NULL) return;
	// Left operand of '=' must be an identifier or identifier with one or more parentheses.
	if (now->kind == ASSIGN) {
		AST *tmp = now->lhs;
		while (tmp->kind == LPAR) tmp = tmp->mid;
		if (tmp->kind != IDENTIFIER)
			err("Lvalue is required as left operand of assignment.");
	}
	// Operand of INC/DEC must be an identifier or identifier with one or more parentheses.
	// TODO: Implement the remaining semantic_check code.
	// hint: Follow the instruction above and ASSIGN-part code to implement.
	// hint: Semantic of each node needs to be checked recursively (from the current node to lhs/mid/rhs node).
	if (now->kind == PREINC || now->kind == PREDEC || now->kind == POSTINC || now->kind == POSTDEC) {
		AST *tmp = now->mid; // now->mid is the operand of INC/DEC
		while (tmp->kind == LPAR) tmp = tmp->mid; // skip parentheses
		if (tmp->kind != IDENTIFIER) // check if the operand is an identifier
			err("Operand of INC/DEC must be an identifier or identifier with one or more parentheses.");
		semantic_check(now->lhs);
		semantic_check(now->mid);
		semantic_check(now->rhs);
	}
}

AST *simplify_AST(AST *ast_root) {
	if (ast_root == NULL)	return NULL;

	ast_root->lhs = simplify_AST(ast_root->lhs);
	ast_root->mid = simplify_AST(ast_root->mid);
	ast_root->rhs = simplify_AST(ast_root->rhs);

	if (ast_root->kind == PLUS || ast_root->kind == LPAR) {
		if (ast_root->mid == NULL) {
			err("Expected expression before \'+\' or \'(\'")
		}
		AST *tmp = ast_root;
		ast_root = ast_root->mid;
		free(tmp);
		return ast_root;
	}
	return ast_root;
}

int reg[256];

void reset_reg(){
	for (int i = 0; i < 256; i++) {
		reg[i] = i;
	}
}

int cur_mem = -1;
int cur = -1;

void codegen(AST *root) {
	// TODO: Implement your codegen in your own way.
	// You may modify the function parameter or the return type, even the whole structure as you wish.
	
	reset_reg();

    if(root == NULL)    return;

    switch(root->kind){
		// 1. LEAF NODE
		case IDENTIFIER:
            int mem_addr = (root->val - 'x') * 4; // 變數x的記憶體位置為0，變數y的記憶體位置為4，變數z的記憶體位置為8
			printf("load r%d [%d]\n", reg[++cur], mem_addr);
			cur_mem = mem; // 記錄變數的記憶體位置
            break;
        case CONSTANT:
            printf("add r%d 0 %d\n", reg[++cur], root->val);
            break;

		// 2. Intermediate Node
        case ASSIGN:
            codegen(root->rhs);
            codegen(root->lhs);
            printf("store [%d] r%d\n", cur_mem, reg[--cur]); // 將暫存器的值(rhs)存回記憶體
            break;

        case ADD: // 5+7
            codegen(root->lhs); // 5
            codegen(root->rhs); // 7
			// lhs: cur-1 ; rhs: cur
            printf("add r%d r%d r%d\n", reg[cur-1], reg[cur-1], reg[cur]); // 將兩個暫存器的值相加
			--cur; // 將相加後的暫存器值存回cur-1
            break;
        case SUB: // 9-5
            codegen(root->lhs); // 9
            codegen(root->rhs); // 5
			// lhs: cur-1 ; rhs: cur
            printf("sub r%d r%d r%d\n", reg[cur-1], reg[cur-1], reg[cur]);
			--cur; // 將相減後的暫存器值存回cur-1
            break;
        case MUL: // 8*7
            codegen(root->lhs); // 8
            codegen(root->rhs); // 7
			// lhs: cur-1 ; rhs: cur
            printf("mul r%d r%d r%d\n", reg[cur-1], reg[cur-1], reg[cur]);
            --cur;
			break;
        case DIV:
            codegen(root->lhs);
            codegen(root->rhs);
			// lhs: cur-1 ; rhs: cur
            printf("div r%d r%d r%d\n", reg[cur-1], reg[cur-1], reg[cur]);
			--cur;
            break;
        case REM:
            codegen(root->lhs);
            codegen(root->rhs);
            printf("rem r%d r%d r%d\n", reg[cur-1], reg[cur-1], reg[cur]);
			--cur;
            break;

        case PREINC:
            codegen(root->mid); // root->mid is the operand of INC/DEC (操作對象通常是一個變數)
            printf("add r%d r%d 1\n", reg[cur], reg[cur]);
            printf("store [%d] r%d\n", cur_mem, reg[cur]);
            break;
        case PREDEC:
            codegen(root->mid);
            printf("sub r%d r%d 1\n", reg[cur], reg[cur]); // 先將變數值減1
            printf("store [%d] r%d\n", cur_mem, reg[cur]); // 再將減1後的值存回記憶體
            break;
        case POSTINC:
            codegen(root->mid);
            printf("add r%d r%d 1\n", reg[cur], reg[cur]); // 先將變數值加1
            printf("store [%d] r%d\n", cur_mem, reg[cur]); // 再將加1後的值存回記憶體
            printf("sub r%d r%d 1\n", reg[cur], reg[cur]); // 最後將變數值減1
            break;
        case POSTDEC:
            codegen(root->mid);
            printf("sub r%d r%d 1\n", reg[cur], reg[cur]); // 先將變數值減1
            printf("store [%d] r%d\n", cur_mem, reg[cur]); // 再將減1後的值存回記憶體
            printf("add r%d r%d 1\n", reg[cur], reg[cur]); // 最後將變數值加1
            break;

        case LPAR:
            codegen(root->mid);
            break;
        case RPAR:
            break;
			
        case PLUS:
            codegen(root->mid); // 將變數值載入暫存器
            break;
        case MINUS:
            codegen(root->mid); // 將變數值載入暫存器
            printf("sub r%d 0 r%d\n", reg[cur], reg[cur]); // 0 - 暫存器的值
            break;
    }

    return;
}

void freeAST(AST *now) {
	if (now == NULL) return;
	freeAST(now->lhs);
	freeAST(now->mid);
	freeAST(now->rhs);
	free(now);
}

void token_print(Token *in, size_t len) {
	const static char KindName[][20] = {
		"Assign", "Add", "Sub", "Mul", "Div", "Rem", "Inc", "Dec", "Inc", "Dec", "Identifier", "Constant", "LPar", "RPar", "Plus", "Minus", "End"
	};
	const static char KindSymbol[][20] = {
		"'='", "'+'", "'-'", "'*'", "'/'", "'%'", "\"++\"", "\"--\"", "\"++\"", "\"--\"", "", "", "'('", "')'", "'+'", "'-'"
	};
	const static char format_str[] = "<Index = %3d>: %-10s, %-6s = %s\n";
	const static char format_int[] = "<Index = %3d>: %-10s, %-6s = %d\n";
	for(int i = 0; i < len; i++) {
		switch(in[i].kind) {
			case LPAR:
			case RPAR:
			case PREINC:
			case PREDEC:
			case ADD:
			case SUB:
			case MUL:
			case DIV:
			case REM:
			case ASSIGN:
			case PLUS:
			case MINUS:
				printf(format_str, i, KindName[in[i].kind], "symbol", KindSymbol[in[i].kind]);
				break;
			case CONSTANT:
				printf(format_int, i, KindName[in[i].kind], "value", in[i].val);
				break;
			case IDENTIFIER:
				printf(format_str, i, KindName[in[i].kind], "name", (char*)(&(in[i].val)));
				break;
			case END:
				printf("<Index = %3d>: %-10s\n", i, KindName[in[i].kind]);
				break;
			default:
				puts("=== unknown token ===");
		}
	}
}

void AST_print(AST *head) {
	static char indent_str[MAX_LENGTH] = "  ";
	static int indent = 2;
	const static char KindName[][20] = {
		"Assign", "Add", "Sub", "Mul", "Div", "Rem", "PreInc", "PreDec", "PostInc", "PostDec", "Identifier", "Constant", "Parentheses", "Parentheses", "Plus", "Minus"
	};
	const static char format[] = "%s\n";
	const static char format_str[] = "%s, <%s = %s>\n";
	const static char format_val[] = "%s, <%s = %d>\n";
	if (head == NULL) return;
	char *indent_now = indent_str + indent;
	indent_str[indent - 1] = '-';
	printf("%s", indent_str);
	indent_str[indent - 1] = ' ';
	if (indent_str[indent - 2] == '`')
		indent_str[indent - 2] = ' ';
	switch (head->kind) {
		case ASSIGN:
		case ADD:
		case SUB:
		case MUL:
		case DIV:
		case REM:
		case PREINC:
		case PREDEC:
		case POSTINC:
		case POSTDEC:
		case LPAR:
		case RPAR:
		case PLUS:
		case MINUS:
			printf(format, KindName[head->kind]);
			break;
		case IDENTIFIER:
			printf(format_str, KindName[head->kind], "name", (char*)&(head->val));
			break;
		case CONSTANT:
			printf(format_val, KindName[head->kind], "value", head->val);
			break;
		default:
			puts("=== unknown AST type ===");
	}
	indent += 2;
	strcpy(indent_now, "| ");
	AST_print(head->lhs);
	strcpy(indent_now, "` ");
	AST_print(head->mid);
	AST_print(head->rhs);
	indent -= 2;
	(*indent_now) = '\0';
}
