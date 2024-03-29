
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t aggregations_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
  struct ParserContext *next_ctx;
  // int ctx_id; /* 此次执行第几个 select */
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->aggregations_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.values_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        SELECT
        COUNT
        MAX
        MIN
        AVG
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
        ORDER
        GROUP
        BY
        UNIQUE
        ASC
        INNER
        JOIN
        IN
        NOT

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;
  struct Selects *select1;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;
%type <select1> after_select;


%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  do_select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index
  | create_unique_index
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:			
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, $7, 0);
		}
    ;
create_unique_index:
    CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, $8, 1);
		}
    ;
drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE 
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
    |ID_get type
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4);
			if (attribute.type == TEXTS) attribute.length = sizeof(int) * 2;
			if (attribute.type == CHARS) attribute.length = 256;
			if (attribute.type == DATES) attribute.length = 10;
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
    ;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
       | DATE_T { $$=DATES; }
       | TEXT_T { $$=TEXTS; }
       ;
ID_get:
	ID 
	{
		char *temp=$1; 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;

	
insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES values values_list SEMICOLON {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3);
    }

values_list:
    /* empty */
    | COMMA values values_list  {
    }

values:
    LBRACE value value_list RBRACE  {
      insert_value_tuple(&CONTEXT->ssql->sstr.insertion, CONTEXT->values, CONTEXT->value_length);
      CONTEXT->value_length=0;
    }

value_list:
    | COMMA value value_list  {}
value:
    NUMBER{
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    ;
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;
do_select:
    select SEMICOLON {}
    ;
select:				/*  select 语句的语法解析树*/
    SELECT select_attr_list FROM FromCluse where group_by order_by
		{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
	;
FromCluse:
  TableRefs {}
  | ID JoinTables {
    selects_insert_relation(&CONTEXT->ssql->sstr.selection, $1);
  }

TableRefs:
  TableRefs COMMA TableRef	{}
  | TableRef {}
  ;
TableRef:
	ID {
    selects_append_relation(&CONTEXT->ssql->sstr.selection, $1);
  }
  ;

JoinTables:
  JoinTables JoinTable {
  } | JoinTable {}
  ;
JoinTable:
  INNER JOIN ID ON condition condition_list {
    selects_append_relation(&CONTEXT->ssql->sstr.selection, $3);
  }

order_by:
  /*empty*/
  | ORDER BY order_attr_list {
  }
order_attr_list:
  order_attr {
  }
  | order_attr_list COMMA order_attr {
  }
order_attr:
  ID {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
  | ID ASC {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
  | ID DESC {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 1);
  }
  | ID DOT ID {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
  | ID DOT ID ASC {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 0);
  }
  | ID DOT ID DESC {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_orderby(&CONTEXT->ssql->sstr.selection, &attr, 1);
  }
  ;
group_by:
  /*empty*/
  | GROUP BY group_attr_list {
  }
group_attr_list:
  group_attr {
  }
  | group_attr_list COMMA group_attr {
  }
group_attr:
  ID {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_groupby(&CONTEXT->ssql->sstr.selection, &attr);
  }
  | ID DOT ID {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_groupby(&CONTEXT->ssql->sstr.selection, &attr);
  }
  ;
select_attr_list:
    select_attr {
    }
    | select_attr_list COMMA select_attr {}
    ;
select_attr:
    simple_select_attr {}
    | agg_attr {}
    ;
simple_select_attr:
    STAR {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      CONTEXT->ssql->sstr.selection.attr_num++;
		}
    | ID {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      CONTEXT->ssql->sstr.selection.attr_num++;
		}
    | ID DOT STAR {
      RelAttr attr;
      relation_attr_init(&attr, $1, "*");
      selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
  	| ID DOT ID {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_set_attribute(&CONTEXT->ssql->sstr.selection, &attr);
      CONTEXT->ssql->sstr.selection.attr_num++;
		}
    ;
agg_attr:
    COUNT LBRACE agg_value RBRACE {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_COUNT;
      selection->aggregate_num++;
      selection->attr_num++;
    }
    | MAX LBRACE agg_value RBRACE {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_MAX;
      selection->aggregate_num++;
      selection->attr_num++;
    }
    | MIN LBRACE agg_value RBRACE {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_MIN;
      selection->aggregate_num++;
      selection->attr_num++;
    }
    | AVG LBRACE agg_value RBRACE {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo *agg_info = &selection->attributes[selection->attr_num].attr.aggregation;
      agg_info->agg_type = AGG_AVG;
      selection->aggregate_num++;
      selection->attr_num++;
    }
    ;
agg_value:
    //特殊的 "*"
    STAR {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, NULL, "*");
      ainfo.need_all = 1;
      selects_set_aggregation(selection, &ainfo);
    }
    // 属性名
    | ID {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, NULL, strdup($1));
      selects_set_aggregation(selection, &ainfo);
    }
    | ID DOT ID {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, $1, $3);
      ainfo.need_table_name = 1;
      selects_set_aggregation(selection, &ainfo);
    }
    | ID DOT STAR {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
			AggInfo ainfo;
      memset(&ainfo, 0, sizeof(AggInfo));
			relation_attr_init(&ainfo.agg_attr, $1, "*");
      ainfo.need_table_name = 1;
      ainfo.need_all = 1;
      selects_set_aggregation(selection, &ainfo);
    }
    // 下面都是常量
    | NUMBER {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(ainfo));
      ainfo.is_constant = 1;
  		value_init_integer(&ainfo.value, $1);
      selects_set_aggregation(selection, &ainfo);
		}
    | FLOAT {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      AggInfo ainfo;
      memset(&ainfo, 0, sizeof(ainfo));
      ainfo.is_constant = 1;
  		value_init_float(&ainfo.value, $1);
      selects_set_aggregation(selection, &ainfo);
		}
    ;
where:
    /* empty */ 
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition_list:
    /* empty */
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition:
    ID comOp value 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 0, NULL, right_value, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|value comOp value 
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, 0, NULL, right_value, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|ID comOp ID 
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 1, &right_attr, NULL, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
    |value comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, 1, &right_attr, NULL, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
    |ID DOT ID comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 0, NULL, right_value, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
    |value comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, 1, &right_attr, NULL, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
    |ID DOT ID comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 1, &right_attr, NULL, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
    |ID comOp before_select select after_select {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
      Selects *selection = $5;
			Condition condition;
      memset(&condition, 0, sizeof(Condition));
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 0, NULL, NULL, 1, selection);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    | before_select select after_select comOp ID {
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $5);
      Selects *selection = $3;
			Condition condition;
      memset(&condition, 0, sizeof(Condition));
			condition_init(&condition, CONTEXT->comp, 0, NULL, NULL, 1, selection, 1, &right_attr, NULL, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    |ID DOT ID comOp before_select select after_select {
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
      Selects *selection = $7;
			Condition condition;
      memset(&condition, 0, sizeof(Condition));
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, 0, NULL, NULL, 1, selection);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    | before_select select after_select comOp ID DOT ID {
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);
      Selects *selection = $3;
			Condition condition;
      memset(&condition, 0, sizeof(Condition));
			condition_init(&condition, CONTEXT->comp, 0, NULL, NULL, 1, selection, 1, &right_attr, NULL, 0, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    | before_select select after_select comOp before_select select after_select {
			RelAttr right_attr;
      Selects *right_selection = $3;
      Selects *left_selection = $7;
			Condition condition;
      memset(&condition, 0, sizeof(Condition));
			condition_init(&condition, CONTEXT->comp, 0, NULL, NULL, 1, right_selection, 0, NULL, NULL, 1, left_selection);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    ;
before_select:
    LBRACE {
      ParserContext *next_ctx_value = (ParserContext *)malloc(sizeof(ParserContext));
      next_ctx_value->ssql = CONTEXT->ssql;
      next_ctx_value->select_length = CONTEXT->select_length;
      next_ctx_value->condition_length = CONTEXT->condition_length;
      next_ctx_value->from_length = CONTEXT->from_length;
      next_ctx_value->value_length = CONTEXT->value_length;
      next_ctx_value->aggregations_length = CONTEXT->aggregations_length;
      next_ctx_value->comp = CONTEXT->comp;
      next_ctx_value->next_ctx = CONTEXT->next_ctx;
      memcpy(next_ctx_value->values, CONTEXT->values, MAX_NUM * sizeof(Value));
      memcpy(next_ctx_value->conditions, CONTEXT->conditions, MAX_NUM * sizeof(Condition));
      memcpy(next_ctx_value->id, CONTEXT->id, MAX_NUM * sizeof(char));
      /* 旧节点空 */
      memset(CONTEXT, 0, sizeof(ParserContext));
      ParserContext **next_ctx = &CONTEXT->next_ctx;
      *next_ctx = next_ctx_value;
      CONTEXT->ssql = calloc(1, sizeof(Query));
      // memcpy(CONTEXT->ssql->sstr.selection.relations, next_ctx_value->ssql->sstr.selection.relations, MAX_NUM * sizeof(char *));
      // CONTEXT->ssql->sstr.selection.relation_num = next_ctx_value->ssql->sstr.selection.relation_num;
    }
    ;
after_select:
    RBRACE {
      Selects *selection = &CONTEXT->ssql->sstr.selection;
      ParserContext **next_ctx = &CONTEXT->next_ctx;
      ParserContext *next_ctx_value = *next_ctx;
      CONTEXT->ssql = next_ctx_value->ssql;
      CONTEXT->select_length = next_ctx_value->select_length;
      CONTEXT->condition_length = next_ctx_value->condition_length;
      CONTEXT->from_length = next_ctx_value->from_length;
      CONTEXT->value_length = next_ctx_value->value_length;
      CONTEXT->aggregations_length = next_ctx_value->aggregations_length;
      CONTEXT->comp = next_ctx_value->comp;
      CONTEXT->next_ctx = next_ctx_value->next_ctx;

      memcpy(CONTEXT->values, next_ctx_value->values, MAX_NUM * sizeof(Value));
      memcpy(CONTEXT->conditions, next_ctx_value->conditions, MAX_NUM * sizeof(Condition));
      memcpy(CONTEXT->id, next_ctx_value->id, MAX_NUM * sizeof(char));
      $$ = selection;
    }
    ;
comOp:
  	  EQ { CONTEXT->comp = EQUAL_TO; }
    | LT { CONTEXT->comp = LESS_THAN; }
    | GT { CONTEXT->comp = GREAT_THAN; }
    | LE { CONTEXT->comp = LESS_EQUAL; }
    | GE { CONTEXT->comp = GREAT_EQUAL; }
    | NE { CONTEXT->comp = NOT_EQUAL; }
    | NOT IN { CONTEXT->comp = NOT_ING; }
    | IN { CONTEXT->comp = ING; }
    ;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
